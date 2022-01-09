#include "pattern.h"
#include "mat.h"

Pattern::Pattern(){

}

Pattern::Pattern(const Color& a,const Color& b){
    this->a = a;
    this->b = b;
    this->transform = get_idt_4x4();
    this->Fn = NULL;
}

Pattern::~Pattern(){

}

int abs_int(int x) { return x > 0 ? x : -x; }

Color stripe_pattern(Pattern *p, const Vec4& point){
    int x = floor(point.x);
    if(x % 2 == 0) return p->a;
    else return p->b;
}

Color gradient_pattern(Pattern *p, const Vec4& point) {
    Color distance = p->b - p->a;
    float fraction = point.x - floor(point.x);

    return p->a + distance * fraction;
}

Color ring_pattern(Pattern *p, const Vec4& point) {
    int radius = floor(sqrt(point.x*point.x + point.z+point.z));
    if(radius % 2 == 0)
        return p->a;
    return p->b;
}

Color checker_pattern(Pattern *p, const Vec4& point){
    int check = (int)floor(point.x) + (int)floor(point.z);
    if(check % 2 == 0)
        return p->a;
    return p->b;
}