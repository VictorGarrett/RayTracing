#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "primitives.h"
#include "camera.h"
#include "light.h"

#define WIDTH   800
#define HEIGHT  600


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;


    Sphere ball({0.0f, 0.0f, 10.0f}, 2);

    Camera mainCamera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50*3.141592/180);

    LightSource mainLight({10.0f, 10.0f, 10.0f}, {255.0f, 255.0f, 255.0f});

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            
            point intersection = ball.intersectRay(mainCamera.getRay(j, i));
            if(intersection != vec3f(0.0f, 0.0f, 0.0f)){
                Ray shadowRay(intersection, mainLight.getCenter() - intersection);

                float costeta = dot(shadowRay.getDir(), ball.getNormal(intersection));
                
                imagedata[3*(j+WIDTH*i)] = costeta > 0 ? (unsigned char)(255.0f*costeta) : 0;
                //printf("(%f, %f, %f)\n", (intersection).x, (intersection).y, (intersection).z);
                //printf("(%f, %f, %f) -> %f\n", shadowRay.getDir().x, shadowRay.getDir().y, shadowRay.getDir().z, costeta);
            }
        }
    }



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    return 0;
}