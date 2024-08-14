#pragma once

#include "common.h"
#include "aabb.h"
#include "surface.h"

typedef struct BVHNode {
    aabb boundingBox;
    int leftChildIndex;     // 0 for leaves, non zero for others
    int rightChildIndex;    // 0 for leaves, non zero for others
    int firstSurface;
    int numSurfaces;        // non zero for leaves, zero for others
    bool isLeaf() { return numSurfaces > 0; }
}BVHNode;

struct BVH {
    int numSurfaces;
    std::vector<BVHNode> bvhList;
    int bvhRootNodeIndex, bvhNodesUsed;
    std::vector<int> surfaceIndices;
    
    BVH() {};
    BVH(int numSurfaces);

    void constructBVHonAABB(std::vector<Surface> &surfaces);
    void subdivideBVHNode(int nodeIndex, std::vector<Vector3f> &surfaceCentroids, std::vector<Surface> &surfaces);
    void updateNodeBB(int nodeIndex, std::vector<Surface> &surfaces);
    Interaction rayBVHInteraction(Ray &ray, std::vector<Surface> &surfaces, int nodeIndex);
};
