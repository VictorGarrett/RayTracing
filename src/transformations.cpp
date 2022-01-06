#include "transformations.h"


float** translation(const float x, const float y, const float z) {
    float **transl = get_idt_4x4();

    transl[0][3] = x;
    transl[1][3] = y;
    transl[2][3] = z;
    
    return transl;
}

float** scaling(const float x, const float y, const float z) {
    float **transl = get_idt_4x4();

    transl[0][0] = x;
    transl[1][1] = y;
    transl[2][2] = z;
    
    return transl;
}

float** rotation_x(float r) {
    float **rot = get_idt_4x4();

    rot[1][1] = rot[2][2] = cos(r);
    rot[1][2] = -sin(r); 
    rot[2][1] = sin(r);

    return rot;
}

float** rotation_y(float r) {
    float **rot = get_idt_4x4();

    rot[0][0] = rot[2][2] = cos(r);
    rot[0][2] = sin(r); 
    rot[2][0] = -sin(r);

    return rot;
}

float** rotation_z(float r) {
    float **rot = get_idt_4x4();

    rot[0][0] = rot[1][1] = cos(r);
    rot[0][1] = -sin(r); 
    rot[1][0] = sin(r);

    return rot;
}

float** shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
    float **shr = get_idt_4x4();

    shr[0][1] = xy; shr[0][2] = xz;
    shr[1][0] = yx; shr[1][2] = yz;
    shr[2][0] = zx; shr[2][1] = zy;

    return shr;

}
