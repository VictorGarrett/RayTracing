#include "pointLight.h"
#include "material.h"
#include "world.h"
#include "computations.h"
#include "ray.h"

PointLight::PointLight() {}

PointLight::PointLight(const Vec4& pos, const Color& col) {
    this->position = pos;
    this->intensity = col;
}

PointLight::~PointLight() {}


Color lighting(
    Material& material,
    float **transform,
    const PointLight& light,
    const Vec4& point,
    const Vec4& eyev,
    const Vec4& normalv,
    const bool in_shadow
)
{
    Color effective_color = material.get_color(point, transform) * light.intensity;
    Vec4 lightv = (light.position - point).normalize();
    Color ambient = effective_color * material.ambient;

    if (in_shadow) return ambient;

    float light_dot_normal = dot(lightv, normalv);
    Color diffuse, specular;
    Color black = Color(0, 0, 0);
    // negative light_dot_normal means the lignt is on the 
    // other side of the surface   
    if (light_dot_normal < 0)
        diffuse = specular = black;
    else {
        diffuse = effective_color * material.diffuse * light_dot_normal;

        Vec4 reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);

        // negative means the light reflects away from the eye
        if (reflect_dot_eye <= 0)
            specular = black;
        else {
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }


    return ambient + diffuse + specular;
}

Color shade_hit(World& world, Computations& comps, int remaining) {
    const bool shadowed = is_shadowed(world, comps.over_point);

    Color surface = lighting(
        comps.object->material,
        comps.object->inverseTransform,
        world.light,
        comps.point,
        comps.eyev,
        comps.normalv,
        shadowed
    );

    Color refracted = refracted_color(world, comps, remaining);

    Color reflected = reflected_color(world, comps, remaining);

    if(comps.object->material.reflective > 0 && comps.object->material.transparency > 0){
        float reflectance = schlick(comps);
        return surface + reflected * reflectance + refracted * (1 - reflectance);
    }
    else 
        return surface + reflected + refracted;

    return surface + reflected + refracted;
}

const bool is_shadowed(World& world, const Vec4& point) {
    Vec4 v = world.light.position - point;
    float distance = v.magnitude();
    Vec4 direction = v.normalize();

    Ray* r = new Ray(point, direction);
    std::list<Intersection* > intersections = world.intersect(r);
    if (intersections.size() == 0) return false;
    Intersection* h = hit(intersections);

    if (h && h->t < distance) return true;
    return false;

}

Color color_at(World& world, Ray* r, int remaining) {
    std::list <Intersection* > xs = world.intersect(r);

    // If the ray misses all objects
    if (xs.size() == 0)
        return Color(0, 0, 0);

    Intersection* hitted = hit(xs);
    if (hitted == NULL) return Color(0, 0, 0);
    Computations comps = Computations(hitted, r, xs);
    return shade_hit(world, comps, remaining);
}

Color reflected_color(World& world, Computations comps, int remaining) {
    if(comps.object->material.reflective == 0 || remaining <= 0)
        return BLACK;
    
    Ray *reflect_ray = new Ray(comps.over_point, comps.reflectv);
    Color color = color_at(world, reflect_ray, remaining - 1);

    return color * comps.object->material.reflective;
}

Color refracted_color(World& world, Computations comps, int remaining){
    if(comps.object->material.transparency == 0 || remaining <= 0)
        return BLACK;

    float n_ratio = comps.n1 / comps.n2;
    float cos_i = dot(comps.eyev, comps.normalv);
    float sin2_t = (n_ratio * n_ratio)*(1 - cos_i*cos_i);
    if(sin2_t > 1) return BLACK;

    float cos_t = sqrt(1.0 - sin2_t);
    Vec4 direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;
    Ray *refract_ray = new Ray(comps.under_point, direction);
    Color color = color_at(world, refract_ray, remaining -1) * comps.object->material.transparency;
    return color;
}

float schlick(Computations& comps) {
    float cos = dot(comps.eyev, comps.normalv);

    if(comps.n1 > comps.n2){
        float n = comps.n1 / comps.n2;
        float sin2_t = (n*n)*(1 - cos*cos);
        // total internal reflection
        if(sin2_t > 1) return 1.0;

        float cos_t = sqrt(1.0 - sin2_t);
        cos = cos_t;
    }
    float r0 = pow((comps.n1 - comps.n2)/(comps.n1 + comps.n2), 2);
    
    float power =  pow(1-cos, 5);
    return r0 + (1 - r0) * power;
}