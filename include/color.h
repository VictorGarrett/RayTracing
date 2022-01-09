#pragma once

class Color {
public:
    float red;
    float green;
    float blue;

    Color();
    Color(const float r, const float g, const float b);
    ~Color();
};

inline Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
}

inline Color operator-(const Color& c1, const Color& c2) {
    return Color(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue);
}

inline Color operator*(const Color& c1, const float s) {
    return Color(c1.red * s, c1.green * s, c1.blue * s);
}

inline Color operator*(const float s, const Color& c1) {
    return Color(c1.red * s, c1.green * s, c1.blue * s);
}

inline Color operator*(const Color& c1, const Color& c2) {
    return Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
}

// Colors
const Color BLACK { Color(0, 0, 0) };
const Color WHITE { Color(1, 1, 1) };
const Color RED { Color(1, 0, 0) };
const Color GREEN { Color(0, 1, 0) };
const Color BLUE { Color(0, 0, 1) };