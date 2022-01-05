#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "renderer.h"

#define WIDTH   800
#define HEIGHT  600


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;


    Sphere ball1({-4.0f, 0.0f, 10.0f}, 2);
    Sphere ball2({4.0f, 0.0f, 10.0f}, 4);

    Camera mainCamera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50*3.141592/180);

    LightSource mainLight({50.0f, 80.0f, -50.0f}, {255.0f, 255.0f, 255.0f});

    std::vector<Primitive*> objects;
    std::vector<LightSource*> lights;

    objects.push_back(&ball1);
    objects.push_back(&ball2);
    lights.push_back(&mainLight);

    Renderer::renderToImage(imagedata, 3, objects, lights, mainCamera);



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    return 0;
}