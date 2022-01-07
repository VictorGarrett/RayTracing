#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include "renderer.h"
#include "object_builder.h"

#define WIDTH   800
#define HEIGHT  600


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;

    ObjectBuilder objBuilder;

    objBuilder.setPrimitiveSphere({-6.0f, 0.0f, 10.0f}, 2);
    objBuilder.setMaterialColor({1.0f, 1.0f, 1.0f});
    Object* ball1 = objBuilder.getObject();

    objBuilder.setPrimitiveSphere({6.0f, 0.0f, 10.0f}, 4);
    objBuilder.setMaterialColor({1.0f, 1.0f, 1.0f});
    Object* ball2 = objBuilder.getObject();

    Camera mainCamera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50*3.141592/180);

    LightSource redLight({-20.0f, -10.0f, 0.0f}, {1.0f, 0.05f, 0.0f});
    LightSource blueLight({-20.0f, -10.0f, 0.0f}, {0.5f, 0.05f, 1.0f});

    std::vector<Object*> objects;
    std::vector<LightSource*> lights;

    objects.push_back(ball1);
    objects.push_back(ball2);
    lights.push_back(&redLight);
    lights.push_back(&blueLight);

    Renderer::renderToImage(imagedata, 3, objects, lights, mainCamera);



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    for(auto i = objects.begin(); i != objects.end(); i++)
        delete *i;

    return 0;
}