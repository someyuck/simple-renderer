#include "bvh_aabb.h"

BVH::BVH(int numSurfaces)
{
    this->numSurfaces = numSurfaces;
    this->bvhList.resize(2 * numSurfaces - 1);
    this->bvhRootNodeIndex = 0;
    this->bvhNodesUsed = 0;
    this->surfaceIndices.resize(numSurfaces);
    for(int i = 0; i < numSurfaces; i++) this->surfaceIndices[i] = i;
}

void BVH::updateNodeBB(int nodeIndex, std::vector<Surface> &surfaces)
{
    aabb &nodeBox = this->bvhList[nodeIndex].boundingBox;
    int firstSurf = this->bvhList[nodeIndex].firstSurface;
    int firstLeafIndex = this->surfaceIndices[firstSurf];

    // min bound
    nodeBox.first.x = surfaces[firstLeafIndex].boundingBox.first.x;
    nodeBox.first.y = surfaces[firstLeafIndex].boundingBox.first.y;
    nodeBox.first.z = surfaces[firstLeafIndex].boundingBox.first.z;
    // max bound
    nodeBox.second.x = surfaces[firstLeafIndex].boundingBox.second.x;
    nodeBox.second.y = surfaces[firstLeafIndex].boundingBox.second.y;
    nodeBox.second.z = surfaces[firstLeafIndex].boundingBox.second.z;

    for(int i = firstSurf; i < firstSurf + this->bvhList[nodeIndex].numSurfaces; i++) {
        int surfaceIndex = this->surfaceIndices[i];
        aabb &surfBox = surfaces[surfaceIndex].boundingBox;
        if(surfBox.first.x <= nodeBox.first.x) nodeBox.first.x = surfBox.first.x;
        if(surfBox.first.y <= nodeBox.first.y) nodeBox.first.y = surfBox.first.y;
        if(surfBox.first.z <= nodeBox.first.z) nodeBox.first.z = surfBox.first.z;

        if(surfBox.second.x >= nodeBox.second.x) nodeBox.second.x = surfBox.second.x;
        if(surfBox.second.y >= nodeBox.second.y) nodeBox.second.y = surfBox.second.y;
        if(surfBox.second.z >= nodeBox.second.z) nodeBox.second.z = surfBox.second.z;
    }
}

void BVH::subdivideBVHNode(int nodeIndex, std::vector<Vector3f> &surfaceCentroids, std::vector<Surface> &surfaces)
{
    if(this->bvhList[nodeIndex].numSurfaces <= 1) return; // leaf node

    // find split plane's axis and position
    Vector3f bbExtent = this->bvhList[nodeIndex].boundingBox.second - this->bvhList[nodeIndex].boundingBox.first;
    int splitAxis = 0; // x
    if(bbExtent.y > bbExtent.x) splitAxis = 1; // y
    if(bbExtent.z > bbExtent[splitAxis]) splitAxis = 2; // z
    double splitPos = this->bvhList[nodeIndex].boundingBox.first[splitAxis] + 0.5f * bbExtent[splitAxis];

    // split surfaces along axis about split position [on left, not on left]
    int l = this->bvhList[nodeIndex].firstSurface;
    int r = this->bvhList[nodeIndex].firstSurface + this->bvhList[nodeIndex].numSurfaces - 1;
    while(l <= r) {
        if(surfaceCentroids[this->surfaceIndices[l]][splitAxis] < splitPos) l++;
        else { // swap with element at end to push this to right half
            this->surfaceIndices[r] = 
            this->surfaceIndices[l] + this->surfaceIndices[r] - (this->surfaceIndices[l] = this->surfaceIndices[r]);
            r--;
        }
    }

    // return if either half is empty, don't create nodes
    int leftCount = l - this->bvhList[nodeIndex].firstSurface;
    int rightCount = this->bvhList[nodeIndex].numSurfaces - leftCount;
    if(leftCount == 0 || rightCount == 0) return;

    // create left and right child nodes
    int leftChildIndex = this->bvhNodesUsed++;
    int rightChildIndex = this->bvhNodesUsed++;
    this->bvhList[leftChildIndex].firstSurface = this->bvhList[nodeIndex].firstSurface;
    this->bvhList[leftChildIndex].numSurfaces = leftCount;
    this->bvhList[rightChildIndex].firstSurface = l;
    this->bvhList[rightChildIndex].numSurfaces = rightCount;

    this->bvhList[nodeIndex].leftChildIndex = leftChildIndex;
    this->bvhList[nodeIndex].rightChildIndex = rightChildIndex;
    this->bvhList[nodeIndex].numSurfaces = 0; // no longer leaf node so set to zero

    // update bounds of both children
    updateNodeBB(leftChildIndex, surfaces);
    updateNodeBB(rightChildIndex, surfaces);

    // recursive call
    subdivideBVHNode(leftChildIndex, surfaceCentroids, surfaces);
    subdivideBVHNode(rightChildIndex, surfaceCentroids, surfaces);
}

void BVH::constructBVHonAABB(std::vector<Surface> &surfaces)
{
    // compute centroids
    std::vector<Vector3f> surfaceCentroids;
    surfaceCentroids.resize(this->numSurfaces);
    for(int i = 0; i < this->numSurfaces; i++) 
        surfaceCentroids[i] = 0.5f * (surfaces[i].boundingBox.first + surfaces[i].boundingBox.second);

    // assign all surfaces to root
    this->bvhNodesUsed++;
    BVHNode &root = this->bvhList[0];
    root.leftChildIndex = 0;
    root.rightChildIndex = 0;
    root.firstSurface = 0;
    root.numSurfaces = this->numSurfaces;
    updateNodeBB(0, surfaces);
    subdivideBVHNode(0, surfaceCentroids, surfaces);
}

Interaction BVH::rayBVHInteraction(Ray &ray, std::vector<Surface> &surfaces, int nodeIndex)
{
    Interaction siFinal;
    if(rayAABBIntersect(ray, this->bvhList[nodeIndex].boundingBox) == false) return siFinal;

    if(this->bvhList[nodeIndex].isLeaf() == true) {
        // hit a leaf, so intersect with its surface now
        int firstSurfIndex = this->bvhList[nodeIndex].firstSurface;
        for(int i = 0; i < this->bvhList[nodeIndex].numSurfaces; i++)
        {
            if(rayAABBIntersect(ray, surfaces[this->surfaceIndices[firstSurfIndex + i]].boundingBox) == false) continue;
            Interaction si = surfaces[this->surfaceIndices[firstSurfIndex + i]].rayIntersect(ray);
            if (si.t <= ray.t) {
                siFinal = si;
                ray.t = si.t;
            }
        }
        return siFinal;
    }

    int left = this->bvhList[nodeIndex].leftChildIndex, right = this->bvhList[nodeIndex].rightChildIndex;
    Interaction siLeft = rayBVHInteraction(ray, surfaces, left);
    Interaction siRight = rayBVHInteraction(ray, surfaces, right);

    Interaction siMin = siLeft;
    if(siRight.t <= siLeft.t) siMin = siRight;

    if (siMin.t <= ray.t) {
        siFinal = siMin;
        ray.t = siMin.t;
    }

    return siFinal;
}
