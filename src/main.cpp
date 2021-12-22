#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "primitives.h"

#define WIDTH   800
#define HEIGHT  600


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;

    //for(int i = 0; i < WIDTH*HEIGHT; i++)
        //imagedata[3*i] = 255;


    float fov = 50;
    float aspectRatio = (float)WIDTH/HEIGHT;

    vec3f u(0.0f, -2*tanf(fov)/(aspectRatio*HEIGHT), 0.0f);
    vec3f r(2*tanf(fov)/(WIDTH), 0.0f, 0.0f);
    vec3f cameraForward(0.0f, 0.0f, 1.0f);

    Sphere ball({0.0f, 0.0f, 20.0f}, 2);

    for(int i = 0; i < HEIGHT; i++){
        printf("%d\n", i);
        for(int j = 0; j < WIDTH; j++){
            
            Ray ray({0.0f, 0.0f, 0.0f}, cameraForward + (j-WIDTH/2.0f)*r + (i-HEIGHT/2.0f)*u);
            if(ball.intersectRay(ray)){
                imagedata[3*(j+WIDTH*i)] = 255;
            }
        }
    }



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    return 0;
}