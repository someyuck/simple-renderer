#include "obj_bvh.h"

objBVH::objBVH(int numTriangles)
{
    this->numTriangles = numTriangles;
    this->bvhList.resize(2 * numTriangles - 1);
    this->triangleIndices.resize(numTriangles);
    for(int i = 0; i < numTriangles; i++) this->triangleIndices[i] = i;
}

void objBVH::updateNodeBB(int nodeIndex, std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices)
{
    aabb &nodeBox = this->bvhList[nodeIndex].boundingBox;
    int firstTri = this->bvhList[nodeIndex].firstTriangle;

    // min bound
    nodeBox.first = Vector3f(1e30f, 1e30f, 1e30f);
    // max bound
    nodeBox.second = Vector3f(-1e30f, -1e30f, -1e30f);

    for(int i = firstTri; i < firstTri + this->bvhList[nodeIndex].numTriangles; i++) {
        int triangleIndex = this->triangleIndices[i];
        Vector3f v1 = vertices[indices[triangleIndex].x];
        Vector3f v2 = vertices[indices[triangleIndex].y];
        Vector3f v3 = vertices[indices[triangleIndex].z];

        nodeBox.first.x = min2(nodeBox.first.x, min3(v1.x, v2.x, v3.x));
        nodeBox.first.y = min2(nodeBox.first.y, min3(v1.y, v2.y, v3.y));
        nodeBox.first.z = min2(nodeBox.first.z, min3(v1.z, v2.z, v3.z));

        nodeBox.second.x = max2(nodeBox.second.x, max3(v1.x, v2.x, v3.x));
        nodeBox.second.y = max2(nodeBox.second.y, max3(v1.y, v2.y, v3.y));
        nodeBox.second.z = max2(nodeBox.second.z, max3(v1.z, v2.z, v3.z));
    }
}

void objBVH::subdivideBVHNode(int nodeIndex, std::vector<Vector3f> &triangleCentroids, std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices)
{
    if(this->bvhList[nodeIndex].numTriangles <= 2) return; // leaf node

    // find split plane's axis and position
    Vector3f bbExtent = this->bvhList[nodeIndex].boundingBox.second - this->bvhList[nodeIndex].boundingBox.first;
    int splitAxis = 0; // x
    if(bbExtent.y > bbExtent.x) splitAxis = 1; // y
    if(bbExtent.z > bbExtent[splitAxis]) splitAxis = 2; // z
    double splitPos = this->bvhList[nodeIndex].boundingBox.first[splitAxis] + 0.5f * bbExtent[splitAxis];

    // split trianglrs along axis about split position [on left, not on left]
    int l = this->bvhList[nodeIndex].firstTriangle;
    int r = this->bvhList[nodeIndex].firstTriangle + this->bvhList[nodeIndex].numTriangles - 1;
    while(l <= r) {
        if(triangleCentroids[this->triangleIndices[l]][splitAxis] < splitPos) l++;
        else { // swap with element at end to push this to right half
            this->triangleIndices[r] = 
            this->triangleIndices[l] + this->triangleIndices[r] - (this->triangleIndices[l] = this->triangleIndices[r]);
            r--;
        }
    }

    // return if either half is empty, don't create nodes
    int leftCount = l - this->bvhList[nodeIndex].firstTriangle;
    int rightCount = this->bvhList[nodeIndex].numTriangles - leftCount;
    if(leftCount == 0 || rightCount == 0) return;

    // create left and right child nodes
    int leftChildIndex = this->bvhNodesUsed++;
    int rightChildIndex = this->bvhNodesUsed++;
    this->bvhList[leftChildIndex].firstTriangle = this->bvhList[nodeIndex].firstTriangle;
    this->bvhList[leftChildIndex].numTriangles = leftCount;
    this->bvhList[rightChildIndex].firstTriangle = l;
    this->bvhList[rightChildIndex].numTriangles = rightCount;

    this->bvhList[nodeIndex].leftChildIndex = leftChildIndex;
    this->bvhList[nodeIndex].rightChildIndex = rightChildIndex;
    this->bvhList[nodeIndex].numTriangles = 0; // no longer leaf node so set to zero

    // update bounds of both children
    updateNodeBB(leftChildIndex, vertices, indices);
    updateNodeBB(rightChildIndex, vertices, indices);

    // recursive call
    subdivideBVHNode(leftChildIndex, triangleCentroids, vertices, indices);
    subdivideBVHNode(rightChildIndex, triangleCentroids, vertices, indices);
}

void objBVH::constructBVHonTriangles(std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices)
{
    // compute centroids
    std::vector<Vector3f> triangleCentroids;
    triangleCentroids.resize(this->numTriangles);
    for(int i = 0; i < this->numTriangles; i++) {
        Vector3f v1 = vertices[indices[i].x];
        Vector3f v2 = vertices[indices[i].y];
        Vector3f v3 = vertices[indices[i].z];
        triangleCentroids[i] = (v1 + v2 + v3) / 3.f;
    }

    // assign all surfaces to root
    this->bvhNodesUsed++;
    objBVHNode &root = this->bvhList[0];
    root.leftChildIndex = 0;
    root.rightChildIndex = 0;
    root.firstTriangle = 0;
    root.numTriangles = this->numTriangles;
    updateNodeBB(0, vertices, indices);
    subdivideBVHNode(0, triangleCentroids, vertices, indices);
}

