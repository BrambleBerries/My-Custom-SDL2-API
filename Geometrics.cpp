
#include <cmath>
#include <math.h>
#include "Geometrics.hpp"


Vector2D::Vector2D(const float x, const float y, const Color c)
{
    this->x = x;
    this->y = y;
    this->c = c;
}

Edge::Edge(const int x1, const int y1, const int x2, const int y2, const Color c1, const Color c2)
    : v1(x1, y1, c1), v2(x2, y2, c2)
{
    if (v2.y > v1.y){
        Vector2D v1_copy = v1;
        this->v1 = v2;
        this->v2 = v1_copy;
    }
}

Edge::Edge(const Vector2D v1, const Vector2D v2)
    : v1(v1), v2(v2)
{
    //switch positions if y2 > y1
    if (v2.y > v1.y){
        Vector2D v1_copy = this->v1;
        this->v1 = v2;
        this->v2 = v1_copy;
    }
    
}
