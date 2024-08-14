#include "aabb.h"

aabb constructAABB(std::vector<Vector3f> &vertices)
{
    aabb boundingBox;
    boundingBox.first.x = vertices[0].x;
    boundingBox.first.y = vertices[0].y;
    boundingBox.first.z = vertices[0].z;

    boundingBox.second.x = vertices[0].x;
    boundingBox.second.y = vertices[0].y;
    boundingBox.second.z = vertices[0].z;

    for(int i = 0; i < vertices.size(); i++) {
        // find min coordinates for min point
        if(vertices[i].x < boundingBox.first.x) boundingBox.first.x = vertices[i].x;
        if(vertices[i].y < boundingBox.first.y) boundingBox.first.y = vertices[i].y;
        if(vertices[i].z < boundingBox.first.z) boundingBox.first.z = vertices[i].z;

        // find max coordinates for max point
        if(vertices[i].x > boundingBox.second.x) boundingBox.second.x = vertices[i].x;
        if(vertices[i].y > boundingBox.second.y) boundingBox.second.y = vertices[i].y;
        if(vertices[i].z > boundingBox.second.z) boundingBox.second.z = vertices[i].z;
    }
    
    return boundingBox;
}

double min2(double a, double b)
{
    if(a <= b) return a;
    return b;
}

double max2(double a, double b)
{
    if(a >= b) return a;
    return b;
}

double min3(double a, double b, double c)
{
    if(a <= b && a <= c) return a;
    if(b <= c && b <= a) return b;
    if(c <= a && c <= b) return c;
}

double max3(double a, double b, double c)
{
    if(a >= b && a >= c) return a;
    if(b >= c && b >= a) return b;
    if(c >= a && c >= b) return c;
}

// implements the slab test
bool rayAABBIntersect(Ray ray, aabb box)
{
    Vector3f t_min, t_max;
    Vector3f t_enter, t_exit;

    // intersection with min planes
    if(ray.d.x != 0) t_min.x = (box.first.x - ray.o.x) / ray.d.x;
    if(ray.d.y != 0) t_min.y = (box.first.y - ray.o.y) / ray.d.y;
    if(ray.d.z != 0) t_min.z = (box.first.z - ray.o.z) / ray.d.z;

    // intersection with max planes
    if(ray.d.x != 0) t_max.x = (box.second.x - ray.o.x) / ray.d.x;
    if(ray.d.y != 0) t_max.y = (box.second.y - ray.o.y) / ray.d.y;
    if(ray.d.z != 0) t_max.z = (box.second.z - ray.o.z) / ray.d.z;

    // plane via which ray enters slab
    t_enter.x = min2(t_min.x, t_max.x);
    t_enter.y = min2(t_min.y, t_max.y);
    t_enter.z = min2(t_min.z, t_max.z);
    
    // plane via which ray exits slab
    t_exit.x = max2(t_min.x, t_max.x);
    t_exit.y = max2(t_min.y, t_max.y);
    t_exit.z = max2(t_min.z, t_max.z);

    double t_in, t_out;
    t_in = max3(t_enter.x, t_enter.y, t_enter.z); // ray entering box
    t_out = min3(t_exit.x, t_exit.y, t_exit.z);   // ray exiting box

    return t_in <= t_out  && t_in < ray.t && t_out > 0;
}
