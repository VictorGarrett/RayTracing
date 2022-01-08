#include "transformations.h"


float** translation(const float x, const float y, const float z) {
    float** transl = get_idt_4x4();

    transl[0][3] = x;
    transl[1][3] = y;
    transl[2][3] = z;

    return transl;
}

float** scaling(const float x, const float y, const float z) {
    float** transl = get_idt_4x4();

    transl[0][0] = x;
    transl[1][1] = y;
    transl[2][2] = z;

    return transl;
}

float** rotation_x(float r) {
    float** rot = get_idt_4x4();

    rot[1][1] = rot[2][2] = cos(r);
    rot[1][2] = -sin(r);
    rot[2][1] = sin(r);

    return rot;
}

float** rotation_y(float r) {
    float** rot = get_idt_4x4();

    rot[0][0] = rot[2][2] = cos(r);
    rot[0][2] = sin(r);
    rot[2][0] = -sin(r);

    return rot;
}

float** rotation_z(float r) {
    float** rot = get_idt_4x4();

    rot[0][0] = rot[1][1] = cos(r);
    rot[0][1] = -sin(r);
    rot[1][0] = sin(r);

    return rot;
}

float** shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
    float** shr = get_idt_4x4();

    shr[0][1] = xy; shr[0][2] = xz;
    shr[1][0] = yx; shr[1][2] = yz;
    shr[2][0] = zx; shr[2][1] = zy;

    return shr;

}

float** view_transform(const Vec4& from, const Vec4& to, const Vec4& up) {
    float** orientation = get_idt_4x4();

    Vec4 forward = (to - from).normalize();
    Vec4 upn = up.normalize();
    Vec4 left = cross(forward, upn);
    Vec4 true_up = cross(left, forward);

    orientation[0][0] = left.x;
    orientation[0][1] = left.y;
    orientation[0][2] = left.z;

    orientation[1][0] = true_up.x;
    orientation[1][1] = true_up.y;
    orientation[1][2] = true_up.z;

    orientation[2][0] = -forward.x;
    orientation[2][1] = -forward.y;
    orientation[2][2] = -forward.z;

    return multiply4x4(orientation, translation(-from.x, -from.y, -from.z));
}