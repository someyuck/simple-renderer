#include "light.h"
#include "scene.h"

// returns a vector of Light objects, first directional lights then point lights
Lights loadLights(nlohmann::json sceneConfig)
{
    Lights lights;
    uint32_t lightIdx = 0;

    auto directionalLights = sceneConfig["directionalLights"];
    auto pointLights = sceneConfig["pointLights"];

    lights.resize(directionalLights.size() + pointLights.size());
    
    for(auto d : directionalLights) {
        auto dir = d["direction"];
        auto rad = d["radiance"];
        Light l = Light(DIRECTIONAL_LIGHT, Vector3f(dir[0], dir[1], dir[2]), Vector3f(rad[0], rad[1], rad[2]));
        lights[lightIdx++] = l;
    }

    for(auto p : pointLights) {
        auto pos = p["location"];
        auto rad = p["radiance"];
        Light l = Light(POINT_LIGHT, Vector3f(pos[0], pos[1], pos[2]), Vector3f(rad[0], rad[1], rad[2]));
        lights[lightIdx++] = l;
    }

    return lights;
}

Vector3f getColorOfPoint(Light &light, Scene &scene, Ray &cameraRay, Interaction &si, Vector3f pointColor)
{
    Vector3f color;
    float brdf = 1 / M_PI; // diffuse brdf
    int visibility;
    float alignment;
    float normalAdjust = 1e-3;

    if(light.type == DIRECTIONAL_LIGHT) {
        alignment = Dot(light.positionOrDirection, si.n); // w.n
        Ray shadow = Ray(si.p + normalAdjust * si.n, Normalize(light.positionOrDirection));
        visibility = (scene.rayIntersect(shadow).didIntersect == false);
    }
    if(light.type == POINT_LIGHT) {
        Vector3f r = light.positionOrDirection - (si.p + normalAdjust * si.n);
        Vector3f direction = Normalize(r);

        Ray shadow = Ray(si.p + normalAdjust * si.n, direction);
        Interaction shadowHit = scene.rayIntersect(shadow);
        visibility = (shadowHit.didIntersect == false || shadowHit.t > r.Length());
        alignment = Dot(direction, si.n); // w.n
        brdf /= r.LengthSquared();
    }

    if(alignment < 0) alignment = 0.f; // if shadow ray points to inside surface, ignore the light source
    color = pointColor * light.radiance * brdf * visibility * alignment;
    return color;
}