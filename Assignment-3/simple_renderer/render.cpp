#include "render.h"

int spp, SAMPLING_VARIANT;

Integrator::Integrator(Scene &scene)
{
    this->scene = scene;
    this->outputImage.allocate(TextureType::UNSIGNED_INTEGER_ALPHA, this->scene.imageResolution);
}

long long Integrator::render()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < this->scene.imageResolution.x; x++) {
        for (int y = 0; y < this->scene.imageResolution.y; y++) {
            Vector3f result(0, 0, 0);
            for (int s = 0; s < spp; s++) {
                float epsilon_x = next_float();
                float epsilon_y = next_float();
                Ray cameraRay = this->scene.camera.generateRay(x, y, epsilon_x, epsilon_y);
                Ray cameraRayCopy = this->scene.camera.generateRay(x, y, epsilon_x, epsilon_y);
                Interaction si = this->scene.rayIntersect(cameraRay);
                Interaction siLight = this->scene.rayEmitterIntersect(cameraRayCopy); // as cameraRay gets modified

                if (si.didIntersect && (si.t < siLight.t)) {
                    Vector3f radiance;
                    LightSample ls;
                    for (Light &light : this->scene.lights) {
                        std::tie(radiance, ls) = light.sample(&si);
                        Ray shadowRay(si.p + 1e-3f * si.n, ls.wo);
                        Interaction siShadow = this->scene.rayIntersect(shadowRay);
                        int visibility;

                        if (light.type == LightType::POINT_LIGHT || light.type == LightType::DIRECTIONAL_LIGHT) {
                            visibility = (int)(!siShadow.didIntersect || siShadow.t > ls.d);
                        }
                        else { // Area light
                            Ray shadowRayCopy(si.p + 1e-3f * si.n, ls.wo);
                            Interaction siTemp = this->scene.rayEmitterIntersect(shadowRayCopy); // sets ray to intersect closest light; cheap hack but ok
                            Interaction doesHitLight = light.intersectLight(&shadowRayCopy); // only intersects if this light is closest light
                            visibility = (int)(doesHitLight.didIntersect && (!siShadow.didIntersect || siShadow.t > doesHitLight.t));
                        }

                        result += si.bsdf->eval(&si, si.toLocal(ls.wo))  * radiance * std::abs(Dot(si.n, ls.wo)) * visibility;
                    }
                }
                else if(siLight.didIntersect) {
                    result += siLight.emissiveColor;
                }
            }

            result /= spp;
            this->outputImage.writePixelColor(result, x, y);
        }
    }
    auto finishTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count();
}

int main(int argc, char **argv)
{
    if (argc != 5) {
        std::cerr << "Usage: ./render <scene_config> <out_path> <num_samples> <sampling_strategy>";
        return 1;
    }
    Scene scene(argv[1]);

    Integrator rayTracer(scene);
    spp = atoi(argv[3]);
    SAMPLING_VARIANT = atoi(argv[4]);
    auto renderTime = rayTracer.render();
    
    std::cout << "Render Time: " << std::to_string(renderTime / 1000.f) << " ms" << std::endl;
    rayTracer.outputImage.save(argv[2]);

    return 0;
}
