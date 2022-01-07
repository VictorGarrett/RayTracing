#pragma once

#include <math.h>

class color{

    public:
        float r;
        float g;
        float b;

        color();
        color(const color& other);
        color(float r, float g, float b);
        ~color();

        void normalize();
        void operator=(const color& attrib);
        void operator*=(const color& col);
        void operator+=(const color& attrib);
        void operator-=(const color& attrib);
        const color operator*(float scalar) const;
        const color operator/(float scalar) const;
        
        void operator*=(float scalar);
};

inline bool operator==(const color& first, const color& second) {
    return first.r == second.r && first.g == second.g && first.b == second.b;
}

inline bool operator!=(const color& first, const color& second) {
    return first.r != second.r || first.g != second.g || first.b != second.b; 
}

const color operator+(const color& first, const color& second);

const color operator-(const color& first, const color& second);

const color operator*(float scalar, const color& col);

const color operator*(const color& first, const color& second);

const color operator/(float scalar, const color& col);