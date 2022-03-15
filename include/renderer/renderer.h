#include <vector>

#include "objects/object.h"
#include "renderer/camera.h"
#include <stdio.h>
#include "math/random.h"

#define MAX_RAY_LENGTH 100000
#define MAX_RAY_DEPTH  3
#define SAMPLES 500

class Scene;

class Renderer{



    private:
        static Random* rng;
        static Scene* scene;

        Renderer(){}
        ~Renderer(){}

        static void setRNG(Random* generator);
        static void setScene(Scene* renderScene);

        static void normalizeExposure(std::vector<color>& imageBuffer);
        static color getPixel(int x, int y, const Camera& camera);
        static color processRay(Ray& r, int rayDepth);

        static color integrate(point& surfacePoint, vec3f&& surfaceNormal, vec3f&& incidentDirection, int rayDepth);
    public:

        static void renderToImage(unsigned char* imageData, int imageChannels,
                                  Scene* scene, const Camera& camera);

};