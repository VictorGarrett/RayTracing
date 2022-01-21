#include "shape.h"
#include "group.h"
#include "intersection.h"
#include "mat.h"

Shape::Shape() {
  this->transform = get_idt_4x4();
  this->inverseTransform = get_idt_4x4();
  this->inverseTransposed = get_idt_4x4();
  this->material = Material();
  this->parent = NULL;
}

Shape::~Shape() {
  free_mat4x4(this->transform);
  free_mat4x4(this->inverseTransform);
  free_mat4x4(this->inverseTransposed);
}

void Shape::set_transform(float **m) {
  this->transform = m;
  this->inverseTransform = inverse(m);
  this->inverseTransposed = transpose(this->inverseTransform);
}
