#include "renderer.h"


void Renderer::renderToImage(unsigned char* imageData, int imageChannels, const std::vector<Primitive*>& objects, const std::vector<LightSource*>& lights, const Camera& camera){

    int width = camera.getTargetWidth();
    int height = camera.getTargetHeight();

    switch(imageChannels){
        case 1:
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    color pixelColor = getSample(j, i, objects, lights, camera);
                    imageData[(j+width*i)] = pixelColor.x;
                }
            }
        break;

        case 3:
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    color pixelColor = getSample(j, i, objects, lights, camera);
                    imageData[3*(j+width*i)    ] = pixelColor.x;
                    imageData[3*(j+width*i) + 1] = pixelColor.y;
                    imageData[3*(j+width*i) + 2] = pixelColor.z;
                }
            }
        break;

        default:
        break;
    }

}

const color Renderer::getSample(int x, int y, const std::vector<Primitive*>& objects, const std::vector<LightSource*>& lights, const Camera& camera){
    
    for(unsigned int i = 0; i < objects.size(); i++){

        point intersection = objects[i]->intersectRay(camera.getRay(x, y));

        if(intersection != vec3f(0.0f, 0.0f, 0.0f)){
            color pixelColor(0.0f, 0.0f, 0.0f);

            for(unsigned int j = 0; j < lights.size(); j++){
                Ray shadowRay(intersection, lights[j]->getPosition() - intersection);

                float costeta = dot(shadowRay.getDir(), objects[i]->getNormal(intersection));
                
                pixelColor += color(costeta > 0 ? (unsigned char)(255.0f*costeta) : 0, 0, 0); //DEFINITELY NOT DEFINITIVE
            }
            return pixelColor;
        }
    }
    return {0.0f, 0.0f, 0.0f};
}