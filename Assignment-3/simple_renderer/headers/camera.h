#pragma once

#include "common.h"

struct Camera {
    Vector3f from, to, up;
    float fieldOfView;
    Vector2i imageResolution;

    float focusDistance = 1.f;
    float aspect;

    Vector3f u, v, w;
    Vector3f pixelDeltaU, pixelDeltaV;
    Vector3f upperLeft;

    Camera() {};
    Camera(Vector3f from, Vector3f to, Vector3f up, float fieldOfView, Vector2i imageResolution);

    /** 
     * epsilons should be in [0, 1)
     * pass each epsilon value as 0 to have the ray shoot from pixel centre
     */
    Ray generateRay(int x, int y, float epsilon_x, float epsilon_y);
};