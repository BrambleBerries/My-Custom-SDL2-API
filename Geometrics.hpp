#ifndef GEOMETRICS_HPP
#define GEOMETRICS_HPP
#include <cmath>
#include <math.h>
#include <iostream>

typedef struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;


class Vector2D
{
	public:
        float x, y;
        Color c;

		Vector2D(const float x, const float y, const Color c = {});

        inline float magnitude(){ return sqrt( (x*x) + (y*y) ); }        
};

class Edge
{
	public:
        Vector2D v1, v2;

		Edge(const int x1, const int y1, const int x2, const int y2, const Color c1 = {}, const Color c2 = {});
        Edge(const Vector2D v1, const Vector2D v2);

};

#endif