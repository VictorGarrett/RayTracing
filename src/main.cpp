#include "vec4.h"
#include "canvas.h"

// display and other stuff
void displayVec(const Vec4& v) {
    std::cout << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')' << '\n';
}

void displayColor(const Color& c) {
    std::cout << '(' << c.red << ", " << c.green << ", " << c.blue << ") ";
}

void displayCanvas(const Canvas& c) {
    for(unsigned int i = 0; i < c.height; i++) {
        for(unsigned int j = 0; j < c.width; j++)
            displayColor(c.grid[i][j]);
        std::cout << '\n';
    }
}

class Projectile {
public:
    Vec4 position;
    Vec4 velocity;

    Projectile(const Vec4& pos, const Vec4& vel){
        this->position = pos;
        this->velocity = vel;
    }
};

class Environment {
public:
    Vec4 gravity;
    Vec4 wind;

    Environment(const Vec4& grav, const Vec4& win){
        this->gravity = grav;
        this->wind = win;
    }
};

Projectile tick(Projectile& p, Environment& e){
    Vec4 position = p.position + p.velocity;
    Vec4 velocity = p.velocity + e.gravity + e.wind;
    return Projectile(position, velocity);
}


int main() {
    Vec4 start = point(0, 1, 0);
    Vec4 velocity = vector(1, 1.8, 0).normalize() * 11.25;
    Projectile p = Projectile(start, velocity);

    Vec4 gravity = vector(0, -0.1, 0);
    Vec4 wind = vector(-0.01, 0, 0);
    Environment e = Environment(gravity, wind);

    Canvas c = Canvas(900, 550);

    while (p.position.x < 900 &&  p.position.y >= 0) {
        c.write_pixel(p.position.x, p.position.y, Color(1, 0, 0));
        p = tick(p, e);
    }
    canvas_to_ppm(c);

    return 0;
}

