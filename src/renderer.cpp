#include "renderer.h"


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
    
    switch(imageChannels){
        case 1:
            //create image buffer
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    imageBuffer.push_back(getSample(j, i, objects, lights, camera));
                }
            }

            //normalize exposure
            normalizeExposure(imageBuffer);

            //output to image
            for(int i = 0; i < width*height; i++)
                imageData[i] = imageBuffer[i].r*255;
        break;

        case 3:
            //create image buffer
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    imageBuffer.push_back(getSample(j, i, objects, lights, camera));
                }
            }

            //normalize exposure
            normalizeExposure(imageBuffer);

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
    
    for(unsigned int i = 0; i < objects.size(); i++){

        point intersection = objects[i]->intersectRay(camera.getRay(x, y));

        if(intersection != vec3f(0.0f, 0.0f, 0.0f)){
            color pixelColor(0.0f, 0.0f, 0.0f);
            color materialColor = objects[i]->getColor();

            for(unsigned int j = 0; j < lights.size(); j++){
                Ray shadowRay(intersection, lights[j]->getPosition() - intersection);

                float costeta = dot(shadowRay.getDir(), objects[i]->getNormal(intersection));

                if(costeta > 0)
                    pixelColor += lights[j]->getColor()*materialColor*costeta;
            }
            return pixelColor;
        }
    }
    return {0.05f, 0.05f, 0.05f};
}