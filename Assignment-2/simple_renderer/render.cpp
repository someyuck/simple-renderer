#include "render.h"

INTERPOLATION_VARIANT_TYPE interpolationVariant;

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
            Ray cameraRay = this->scene.camera.generateRay(x, y);
            Interaction si = this->scene.rayIntersect(cameraRay);

            if (si.didIntersect) {
                Vector3f color(0, 0, 0);
                Vector3f pointColor;

                // flip normal back to be on same side as cameraRay in case it is on the opposite side
                if(Dot(cameraRay.d, si.n) > 0) si.n = -si.n;

                if(si.hasDiffuse == true) {
                    if(interpolationVariant == NEAREST_NEIGHBOUR) pointColor = ((Texture*)si.texturePtr)->nearestNeighbourFetch(si.uv);
                    else if(interpolationVariant == BILINEAR) pointColor = ((Texture*)si.texturePtr)->bilinearFetch(si.uv);
                }
                else pointColor = *(Vector3f*)si.texturePtr;

                for(auto light : this->scene.lights)
                    color += getColorOfPoint(light, this->scene, cameraRay, si, pointColor);
                this->outputImage.writePixelColor(color, x, y);
            }
            else
                this->outputImage.writePixelColor(Vector3f(0.f, 0.f, 0.f), x, y);
        }
    }
    auto finishTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count();
}

int main(int argc, char **argv)
{
    if (argc != 4 || strlen(argv[3]) != 1) {
        std::cerr << "Usage: ./render <scene_config> <out_path> <interpolation_variant>";
        return 1;
    }

    interpolationVariant = INTERPOLATION_VARIANT_TYPE(argv[3][0] - '0');

    Scene scene(argv[1]);

    Integrator rayTracer(scene);
    auto renderTime = rayTracer.render();
    
    std::cout << "Render Time: " << std::to_string(renderTime / 1000.f) << " ms" << std::endl;
    rayTracer.outputImage.save(argv[2]);

    return 0;
}
