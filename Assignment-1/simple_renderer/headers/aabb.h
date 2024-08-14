#pragma once

#include "common.h"

typedef std::pair<Vector3f, Vector3f> aabb; // min-point, max-point

aabb constructAABB(std::vector<Vector3f> &vertices);
bool rayAABBIntersect(Ray ray, aabb box);

// utils
double min2(double a, double b);
double max2(double a, double b);
double min3(double a, double b, double c);
double max3(double a, double b, double c);