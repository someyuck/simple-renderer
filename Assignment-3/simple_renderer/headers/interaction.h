#pragma once

#include "vec.h"

// Forward declaration of BSDF class
class BSDF;

struct Interaction {
    // Position of interaction
    Vector3f p;
    // Normal of the surface at interaction
    Vector3f n;
    // The uv co-ordinates at the intersection point
    Vector2f uv;
    // The viewing direction in local shading frame
    Vector3f wi; 
    // Distance of intersection point from origin of the ray
    float t = 1e30f; 
    // Used for light intersection, holds the radiance emitted by the emitter.
    Vector3f emissiveColor = Vector3f(0.f, 0.f, 0.f);
    // BSDF at the shading point
    BSDF* bsdf;
    // Vectors defining the orthonormal basis
    Vector3f a, b, c;

    bool didIntersect = false;

    Vector3f toWorld(Vector3f w) {
        // only call after ONB is defined
        Vector3f M_inv_col_0 = Vector3f(a[0], b[0], c[0]);
        Vector3f M_inv_col_1 = Vector3f(a[1], b[1], c[1]);
        Vector3f M_inv_col_2 = Vector3f(a[2], b[2], c[2]);
        return Vector3f(Dot(w, M_inv_col_0), Dot(w, M_inv_col_1), Dot(w, M_inv_col_2));
    }

    Vector3f toLocal(Vector3f w) {
        // only call after ONB is defined
        Vector3f M_col_0 = a;
        Vector3f M_col_1 = b;
        Vector3f M_col_2 = c;
        return Vector3f(Dot(w, M_col_0), Dot(w, M_col_1), Dot(w, M_col_2));
    }
};