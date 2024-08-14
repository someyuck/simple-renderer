#pragma once

#include "common.h"
#include "aabb.h"

typedef struct objBVHNode {
    aabb boundingBox;
    int leftChildIndex;     // 0 for leaves, non zero for others
    int rightChildIndex;    // 0 for leaves, non zero for others
    int firstTriangle;
    int numTriangles;        // non zero for leaves, zero for others
    bool isLeaf() { return numTriangles > 0; }
}objBVHNode;

struct objBVH {
    int numTriangles;
    std::vector<objBVHNode> bvhList;
    int bvhRootNodeIndex = 0, bvhNodesUsed = 0;
    std::vector<int> triangleIndices;

    objBVH() {};
    objBVH(int numTriangles);

    void updateNodeBB(int nodeIndex, std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices);
    void subdivideBVHNode(int nodeIndex, std::vector<Vector3f> &triangleCentroids, std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices);
    void constructBVHonTriangles(std::vector<Vector3f> &vertices, std::vector<Vector3i> &indices);
};
