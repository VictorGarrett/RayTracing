#include "renderer.h"
#include "stdio.h"

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
    for(auto i = imageBuffer.begin(); i != imageBuffer.end(); i++)
        *i *= max;
}

void Renderer::renderToImage(unsigned char* imageData, int imageChannels, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera){

    int width = camera.getTargetWidth();
    int height = camera.getTargetHeight();

    std::vector<color> imageBuffer;
    //create image buffer
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            imageBuffer.push_back(getSample(j, i, objects, lights, camera));
        } 
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

color Renderer::getSample(int x, int y, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera){

    Ray cameraRay = camera.getRay(x, y);
    return processRay(cameraRay, objects, lights, 0);
    
}

color Renderer::processRay(Ray r, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, int rayDepth){

    if(rayDepth > MAX_RAY_DEPTH)
        return color(0.05f, 0.05f, 0.05f);

    point closestIntersection = r.getPoint(MAX_RAY_LENGTH);
    Object* objectHit;
    color pixelColor(0.0f, 0.0f, 0.0f);
  
    for(unsigned int i = 0; i < objects.size(); i++){//find closest hit object          
        point intersection = objects[i]->intersectRay(r);

        if(intersection == vec3f(0.0f, 0.0f, 0.0f))
            continue;
        else if((intersection-r.getPoint(0)).length2() < (closestIntersection-r.getPoint(0)).length2()){
            closestIntersection = intersection;
            objectHit = objects[i];
        }
    }

    if(closestIntersection == r.getPoint(MAX_RAY_LENGTH))//no hit detected
        return color(0.05f, 0.05f, 0.05f);

    for(unsigned int j = 0; j < lights.size(); j++){//accumulate contribution of every light source
        
        bool inShadow = false;
        Ray shadowRay(closestIntersection, lights[j]->getPosition() - closestIntersection);
        
        float costeta = dot(shadowRay.getDir(), objectHit->getNormal(closestIntersection));

        if(costeta > 0){//a light ray cannot hit a surface from behind     
            for(unsigned int k = 0; k < objects.size(); k++){//check for obstruction in the light path
                if(objects[k]->intersectRay(shadowRay) != point(0.0f, 0.0f, 0.0f) && 
                  (objects[k]->intersectRay(shadowRay)-closestIntersection).length2() < (lights[j]->getPosition() - closestIntersection).length2())
                {
                    inShadow = true;
                    break;
                }         
            }
            
            if(!inShadow){
                pixelColor += computeDiffuse(lights[j]->getColor(), objectHit->getColor(), costeta, objectHit->getDiffuse()); 
                pixelColor += computeSpecular(r, shadowRay, objectHit, closestIntersection, lights[j]->getColor());
            }
        }   
    }
    //the reflection component is independent of light sources
    pixelColor += objectHit->getSpecular()*processRay(r.reflection(closestIntersection, objectHit->getNormal(closestIntersection)), objects, lights, rayDepth+1);
    
    return pixelColor ;
}