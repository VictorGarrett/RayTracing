#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include "renderer.h"
#include "object_builder.h"

#define WIDTH   1366
#define HEIGHT  768


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;

    ObjectBuilder objBuilder;

    objBuilder.setPrimitiveSphere({-15.0f, 4.0f, 8.0f}, 2);
    objBuilder.setMaterial({0.3f, 1.0f, 0.3f}, 1.0f, 0.0f, 200.0f);
    Object* ball1 = objBuilder.getObject();

    objBuilder.setPrimitiveSphere({6.0f, 2.0f, 12.0f}, 4);
    objBuilder.setMaterial({1.0f, 0.3f, 0.3f}, 0.0f, 0.9f, 200.0f);
    Object* ball2 = objBuilder.getObject();

    objBuilder.setPrimitiveSphere({0.0f, 2.0f, 11.0f}, 1);
    objBuilder.setMaterial({0.1f, 0.1f, 0.9f}, 0.0f, 0.9f, 100.0f);
    Object* ball3 = objBuilder.getObject();

    objBuilder.setPrimitivePlane({0.0f, -2.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    objBuilder.setMaterial({0.4f, 0.4f, 0.4f}, 0.2f, 0.9f, 200.0f);
    Object* ground = objBuilder.getObject();

    objBuilder.setPrimitivePlane({0.0f, 0.0f, 50.0f}, {0.0f, 0.0f, -1.0f});
    objBuilder.setMaterial({0.5f, 0.5f, 0.8f}, 0.0f, 0.9f, 200.0f);
    Object* wall1 = objBuilder.getObject();

    objBuilder.setPrimitivePlane({0.0f, 0.0f, -50.0f}, {0.0f, 0.0f, 1.0f});
    objBuilder.setMaterial({0.5f, 0.5f, 0.8f}, 0.0f, 0.9f, 200.0f);
    Object* wall2 = objBuilder.getObject();

    objBuilder.setPrimitivePlane({100.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f});
    objBuilder.setMaterial({0.5f, 0.8f, 0.5f}, 0.0f, 0.9f, 200.0f);
    Object* wall3 = objBuilder.getObject();

    objBuilder.setPrimitivePlane({-100.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f});
    objBuilder.setMaterial({0.5f, 0.8f, 0.5f}, 0.0f, 0.9f, 200.0f);
    Object* wall4 = objBuilder.getObject();

    objBuilder.setPrimitivePlane({0.0f, 200.0f, 0.0f}, {0.0f, -1.0f, 0.0f});
    objBuilder.setMaterial({0.9f, 0.5f, 0.5f}, 0.0f, 0.9f, 200.0f);
    Object* ceil = objBuilder.getObject();

    Camera mainCamera({0.0f, 5.0f, -10.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50*3.141592/180);

    LightSource redLight({0.0f, 100.0f, -25.0f}, {3.0f, 3.0f, 3.0f});
    LightSource blueLight({0.0f, 100.0f, 25.0f}, {3.0f, 3.0f, 3.0f});
    //LightSource greenLight({-20.0f, 1.0f, 5.0f}, {0.1f, 0.9f, 0.1f});

    std::vector<Object*> objects;
    std::vector<LightSource*> lights;

    objects.push_back(ball1);
    objects.push_back(ball2);
    objects.push_back(ball3);
    objects.push_back(ground);
    objects.push_back(wall1);
    objects.push_back(wall2);
    objects.push_back(wall3);
    objects.push_back(wall4);
    objects.push_back(ceil);
    lights.push_back(&redLight);
    //lights.push_back(&blueLight);
    //lights.push_back(&greenLight);

    Renderer::renderToImage(imagedata, 3, objects, lights, mainCamera);



    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    for(auto i = objects.begin(); i != objects.end(); i++)
        delete *i;

    return 0;
}