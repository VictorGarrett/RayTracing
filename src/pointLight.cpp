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
    const Material& material,
    const PointLight& light,
    const Vec4& point,
    const Vec4& eyev,
    const Vec4& normalv,
    const bool in_shadow
)
{
    Color effective_color = material.color * light.intensity;
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

Color shade_hit(World& world, Computations& comps) {

    const bool shadowed = is_shadowed(world, comps.over_point);
    return lighting(
        comps.object->material,
        world.light,
        comps.point,
        comps.eyev,
        comps.normalv,
        shadowed
    );
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

Color color_at(World& world, Ray* r) {
    std::list <Intersection* > xs = world.intersect(r);

    // If the ray misses all objects
    if (xs.size() == 0)
        return Color(0, 0, 0);

    Intersection* hitted = hit(xs);
    if (hitted == NULL) return Color(0, 0, 0);
    Computations comps = Computations(hitted, r);
    return shade_hit(world, comps);
}