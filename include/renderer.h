#include <vector>

#include "object.h"
#include "camera.h"
#include "light.h"
#include <stdio.h>

#define MAX_RAY_LENGTH 1000
#define MAX_RAY_DEPTH  5

class Renderer{



    private:
        Renderer(){}
        ~Renderer(){}

        static void normalizeExposure(std::vector<color>& imageBuffer);
        static color getSample(int x, int y, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);
        static color processRay(Ray r, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, int rayDepth);

        static inline color computeDiffuse(color lightColor, color materialColor, float costeta, float diffuseCoef){
            return lightColor*materialColor*costeta*diffuseCoef;
        }

        static inline color computeSpecular(Ray eyeRay, Ray lightRay, Object* obj, point intersection, color lightColor){
            float reflectionDotCamera = dot(eyeRay.getDir(),(lightRay.reflection(
                                                                                 intersection,
                                                                                 obj->getNormal(intersection)
                                                                                )
                                                            ).getDir());
            if(reflectionDotCamera > 0.0f){
                return lightColor * obj->getSpecular() * pow(reflectionDotCamera, obj->getShininess());
            }
            else
                return {0.0f, 0.0f, 0.0f};
        }
    public:

        static void renderToImage(unsigned char* imageData, int imageChannels,
                                  const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);

};