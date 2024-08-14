#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>

#include "vec.h"

#include "json/include/nlohmann/json.hpp"

#define M_PI 3.14159263f

struct Ray {
    Vector3f o, d;
    float t = 1e30f;
    float tmax = 1e30f;


    Ray(Vector3f origin, Vector3f direction, float t = 1e30f, float tmax = 1e30f)
        : o(origin), d(direction), t(t), tmax(tmax) {};
};

struct Interaction {
    Vector3f p, n;
    float t = 1e30f;
    bool didIntersect = false;
    Vector2f uv;
    bool hasDiffuse;
    void *texturePtr = 0; // to fetch color of the hit point
};

struct AABB {
    Vector3f min = Vector3f(1e30f, 1e30f, 1e30f);
    Vector3f max = Vector3f(-1e30f, -1e30f, -1e30f);
    Vector3f centroid = Vector3f(0.f, 0.f, 0.f);

    bool intersects(Ray ray)
    {
        float tx1 = (min.x - ray.o.x) / ray.d.x, tx2 = (max.x - ray.o.x) / ray.d.x;
        float tmin = std::min(tx1, tx2), tmax = std::max(tx1, tx2);
        float ty1 = (min.y - ray.o.y) / ray.d.y, ty2 = (max.y - ray.o.y) / ray.d.y;
        tmin = std::max(tmin, std::min(ty1, ty2)), tmax = std::min(tmax, std::max(ty1, ty2));
        float tz1 = (min.z - ray.o.z) / ray.d.z, tz2 = (max.z - ray.o.z) / ray.d.z;
        tmin = std::max(tmin, std::min(tz1, tz2)), tmax = std::min(tmax, std::max(tz1, tz2));
        return tmax >= tmin && tmin < ray.t && tmax > 0;
    }
};

struct BVHNode {
    AABB bbox;
    uint32_t left = 0, right = 0;
    uint32_t firstPrim = 0, primCount = 0;
};

enum INTERPOLATION_VARIANT_TYPE {
    NEAREST_NEIGHBOUR = 0,
    BILINEAR
};

extern INTERPOLATION_VARIANT_TYPE interpolationVariant;