#include "light.h"

Light::Light(LightType type, nlohmann::json config) {
    switch (type) {
        case LightType::POINT_LIGHT:
            this->position = Vector3f(config["location"][0], config["location"][1], config["location"][2]);
            break;
        case LightType::DIRECTIONAL_LIGHT:
            this->direction = Vector3f(config["direction"][0], config["direction"][1], config["direction"][2]);
            break;
        case LightType::AREA_LIGHT:
            this->center = Vector3f(config["center"][0], config["center"][1], config["center"][2]);
            this->vx = Vector3f(config["vx"][0], config["vx"][1], config["vx"][2]);
            this->vy = Vector3f(config["vy"][0], config["vy"][1], config["vy"][2]);
            this->normal = Vector3f(config["normal"][0], config["normal"][1], config["normal"][2]);
            break;
        default:
            std::cout << "WARNING: Invalid light type detected";
            break;
    }

    this->radiance = Vector3f(config["radiance"][0], config["radiance"][1], config["radiance"][2]);
    this->type = type;
}

std::pair<Vector3f, LightSample> Light::sample(Interaction *si) {
    LightSample ls;
    memset(&ls, 0, sizeof(ls));

    Vector3f radiance;
    switch (type) {
        case LightType::POINT_LIGHT:
            ls.wo = (position - si->p);
            ls.d = ls.wo.Length();
            ls.wo = Normalize(ls.wo);
            radiance = (1.f / (ls.d * ls.d)) * this->radiance;
            break;
        case LightType::DIRECTIONAL_LIGHT:
            ls.wo = Normalize(direction);
            ls.d = 1e10;
            radiance = this->radiance;
            break;
        case LightType::AREA_LIGHT:
            float pdfInv;
            switch (SAMPLING_VARIANT) {
                case 0: {
                    // uniform sampling
                    float theta = acosf(next_float()); // ray should be in upper hemisphere
                    float phi = 2 * M_PI * next_float();
                    pdfInv = 2 * M_PI;                    

                    // not initialising full struct since only ls.wo is needed
                    ls.wo = Vector3f(sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), cosf(theta)); // shading space
                    ls.wo = Normalize(si->toWorld(ls.wo)); // world space
                    break;
                }
                case 1: {
                    // cosine weighted sampling
                    float theta = acosf((1 - 2 * next_float())) / 2.f;
                    float phi = 2 * M_PI * next_float();
                    pdfInv = M_PI / cosf(theta);

                    // not initialising full struct since only ls.wo is needed
                    ls.wo = Vector3f(sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), cosf(theta)); // shading space
                    ls.wo = Normalize(si->toWorld(ls.wo)); // world space
                    break;
                }
                case 2: {
                    // area light sampling
                    ls.wo = this->center + 2.f * (next_float() - 0.5f) * this->vx + 2.f * (next_float() - 0.5f) * this->vy;
                    ls.wo -= si->p;
                    float r_sq = ls.wo.LengthSquared();
                    ls.wo = Normalize(ls.wo); // in global space
                    
                    float area = 4.f * this->vx.Length() * this->vy.Length();
                    float pdf = r_sq / (Dot(this->normal, -ls.wo) * area);
                    pdfInv = 1.f / pdf;
                    break;
                }
            }
            radiance = pdfInv * this->radiance;
            break;
    }
    return { radiance, ls };
}

Interaction Light::intersectLight(Ray *ray) {
    Interaction si;
    memset(&si, 0, sizeof(si));

    if (type == LightType::AREA_LIGHT) {
        float dDotN = Dot(ray->d, this->normal); // if ray intersects plane of light
        if(dDotN != 0.f) {
            float t = -Dot((ray->o - this->center), this->normal) / dDotN;

            Vector3f intPoint = ray->o + ray->d * t;
            float intPointDistX = AbsDot((intPoint - this->center), Normalize(this->vx)); // distance of point of intersection from center of light
            float intPointDistY = AbsDot((intPoint - this->center), Normalize(this->vy));

            float alignment = Dot(-ray->d, this->normal); // if the light is facing the camera
            if (t >= 0.f && intPointDistX <= this->vx.Length() && intPointDistY <= this->vy.Length() && alignment > 0) {
                si.didIntersect = true;
                si.t = t;
                si.n = this->normal;
                si.p = intPoint;
                si.emissiveColor = this->radiance;
            }
        }
    }

    return si;
}