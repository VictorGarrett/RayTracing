#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "renderer/stb_image_write.h"


#include "renderer/renderer.h"
#include "objects/scene_manager.h"

#define WIDTH   400
#define HEIGHT  300


int main(){

    unsigned char* imagedata = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));

    for(int i = 0; i < 3*WIDTH*HEIGHT; i++)
        imagedata[i] = 0;

    SceneManager sm;

    Camera mainCamera({0.0f, 5.0f, -10.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, WIDTH, HEIGHT, 50*3.141592/180);

    std::vector<Object*> objects;


    /* objects.push_back(ball1);
    objects.push_back(ball2);
    objects.push_back(ball3);
    objects.push_back(ground);
    objects.push_back(wall1);
    objects.push_back(wall2);
    objects.push_back(wall3);
    objects.push_back(wall4);
    objects.push_back(ceil); */


    Renderer::renderToImage(imagedata, 3, sm.getScene("./scenes/scene1.yaml"), mainCamera);

    printf("rendered\n");
    stbi_write_png("./ray.png", WIDTH, HEIGHT, 3, imagedata, 3*WIDTH*sizeof(unsigned char));
    free(imagedata);

    for(auto i = objects.begin(); i != objects.end(); i++)
        delete *i;

    return 0;
}