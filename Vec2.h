#ifndef CONSOLEAPP_VEC2_H
#define CONSOLEAPP_VEC2_H
#pragma once

struct vec2
{
    float x, y;

    vec2(float value) : x(value), y(value) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    vec2 operator+(vec2 const& other) { return vec2(x + other.x, y + other.y); }
    vec2 operator-(vec2 const& other) { return vec2(x - other.x, y - other.y); }
    vec2 operator*(vec2 const& other) { return vec2(x * other.x, y * other.y); }
    vec2 operator/(vec2 const& other) { return vec2(x / other.x, y / other.y); }
};
#endif //CONSOLEAPP_VEC2_H
