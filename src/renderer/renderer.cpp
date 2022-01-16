#include "renderer/renderer.h"
#include "objects/scene.h"
#include <stdlib.h>

#define PI  3.141592654
#define PI2 9.869604401
#define SAMPLES 500


Random* Renderer::rng = nullptr;
Scene* Renderer::scene = nullptr;

void Renderer::setRNG(Random* generator){
    rng = generator;
}
void Renderer::setScene(Scene* renderScene){
    scene = renderScene;
}

void Renderer::normalizeExposure(std::vector<color>& imageBuffer){
    float max = 0.0f;
    for(auto i = imageBuffer.begin(); i != imageBuffer.end(); i++){
        if(i->r > max)
            max = i->r;
        if(i->g > max)
            max = i->g;
        if(i->b > max)
            max = i->b;
    }
    max = 1.0f/max;
    for(auto i = imageBuffer.begin(); i != imageBuffer.end(); i++){
        *i *= max;
    }
    
}

void Renderer::renderToImage(unsigned char* imageData, int imageChannels, Scene* scene, const Camera& camera){

    setScene(scene);

    Random ram((uint64_t)imageData);
    setRNG(&ram);

    int width = camera.getTargetWidth();
    int height = camera.getTargetHeight();

    std::vector<color> imageBuffer;
    //create image buffer
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            imageBuffer.push_back(getPixel(j, i, camera));
        }
        printf("%.2f%\n", 100.0*i/height); 
    }
    //normalize exposure
    normalizeExposure(imageBuffer);

    switch(imageChannels){
        case 1:
            //output to image
            for(int i = 0; i < width*height; i++)
                imageData[i] = imageBuffer[i].r*255;
        break;

        case 3:
            //output to image
            for(int i = 0; i < width*height; i++){
                imageData[3*i  ] = imageBuffer[i].r*255;
                imageData[3*i+1] = imageBuffer[i].g*255;
                imageData[3*i+2] = imageBuffer[i].b*255;
            }
        break;

        default:
        break;
    }

}

color Renderer::getPixel(int x, int y, const Camera& camera){

    Ray cameraRay = camera.getRay(x, y);
    color pixelColor(0, 0, 0);

    for(int i = 0; i < SAMPLES; i++){
        pixelColor += processRay(cameraRay, 0);
    }

    return pixelColor/SAMPLES;

    
}

color Renderer::processRay(Ray& r, int rayDepth){

    if(rayDepth == MAX_RAY_DEPTH)
        return {0.0f, 0.0f, 0.0f};

    point closestIntersection = r.getPoint(MAX_RAY_LENGTH);
    Object* objectHit = nullptr;

    for(unsigned int i = 0; i < scene->size(); i++){//find closest hit object          
        point intersection = (*scene)[i]->intersectRay(r);

        if(intersection == vec3f(0.0f, 0.0f, 0.0f))
            continue;
        else if((intersection-r.getPoint(0)).length2() < (closestIntersection-r.getPoint(0)).length2()){
            closestIntersection = intersection;
            objectHit = (*scene)[i];
        }
    }

    if(!objectHit)//no hit detected
        return {0.0f, 0.0f, 0.0f};

    const vec3f yl = objectHit->getNormal(closestIntersection);
    const vec3f zl = cross(r.getDir(), yl).normalize();
    const vec3f xl = cross(zl, yl).normalize();
    float polar, azim; //spherical angles to integrate along

    polar = rng->dUnif()*PI/2;
    azim = rng->dUnif()*2*PI;
    float sinp = sin(polar);
    vec3f dir = cos(polar)*yl + sinp*cos(azim)*xl + sinp*sin(azim)*zl;

    Ray sampleRay(closestIntersection, dir);

    return processRay(sampleRay, rayDepth+1)*(objectHit->getColor()/(2*PI2))*dot(sampleRay.getDir(), yl) + objectHit->getEmissiveColor();
}