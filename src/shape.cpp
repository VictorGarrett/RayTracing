#include "shape.h"
#include "intersection.h"
#include "mat.h"

Shape::Shape(){
    this->transform = new float*[4];
    for(int i = 0; i < 4; i++){
        this->transform[i] = new float[4];
    }
    this->transform = get_idt_4x4();
}

Shape::~Shape(){
    free_mat4x4(this->transform);
}

void Shape::set_transform(float **m){
    this->transform = m;
}



