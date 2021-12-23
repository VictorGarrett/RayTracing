#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "primitives.h"
#include "camera.h"

#define WIDTH   800
#define HEIGHT  600


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;


    Sphere ball({0.0f, 0.0f, 20.0f}, 2);

    Camera mainCamera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50);

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            
            if(ball.intersectRay(mainCamera.getRay(j, i))){
                imagedata[3*(j+WIDTH*i)] = 255;
            }
        }
    }



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    return 0;
}