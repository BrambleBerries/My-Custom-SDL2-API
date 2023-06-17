#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>
#include "My_SDL_Shapes.hpp"
#include <algorithm>
#include "Geometrics.hpp"
#include <chrono>

#include "src/include/SDL2/SDL.h"

//######## extern variables ############//
extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern float _strokeWeight;

int min(const int a, const int b, const int c){
    auto min = a;
    if (b < min) min = b;
    if (c < min) min = c;

    return min;
}

int max(const int a, const int b, const int c){
    auto max = a;
    if (b > max) max = b;
    if (c > max) max = c;

    return max;
}

void drawLines(const Vector2D points[], const int count){

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //draw lines without stroke thickness (center lines)
    if (_strokeWeight == 1){
        for (auto i = 0; i < count - 1; i++) SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[(i+1)].x, points[(i+1)].y);
        return;
    }
    

    //holds the two new vertices calculated due to the thicker border
    typedef struct WidenedVertices{
    Vector2D P1;
    Vector2D P2;
    } WidenedVertices;
    
    //list of vertices of thickened borders
    std::vector<WidenedVertices> expandedPoints;
    int newCount = count - 1;

    for (auto i = 0; i < newCount; i++)
    {
        //current vertex location
        Vector2D curr = points[i];

        //prev vertex location !relative to curr!
        Vector2D prev = points[(i + newCount - 1) % newCount];
            prev.x -= curr.x;
            prev.y -= curr.y;
            auto mPrev = prev.magnitude();
            prev.x /= mPrev;
            prev.y /= mPrev;

        //next vertex location !relative to curr!
        Vector2D next = points[(i+1) % newCount];
            next.x -= curr.x;
            next.y -= curr.y;
            auto mNext = next.magnitude();
            next.x /= mNext;
            next.y /= mNext;

        //angle between prev and next vertex
        float innerAngle = (atan2f(prev.y, prev.x) - atan2f(next.y, next.x));

        //need half angle size
        float innerAngle_2 = innerAngle / 2;

        //distance of the new vertex to the original vertex
        float extension = (_strokeWeight/2) / sinf(innerAngle_2);
        
        //if angle > 90°
        if (innerAngle * 180 / M_PI > -90) extension = -extension;

        //dir is the normalized vectors of vertices before and after
        Vector2D extensionDir = {next.x + prev.x, next.y + prev.y};
            float extMag = extensionDir.magnitude();
            extensionDir.x /= extMag;
            extensionDir.y /= extMag;

        
        Vector2D inner = { (curr.x + (extensionDir.x * extension)), (curr.y + (extensionDir.y * extension)) };
        Vector2D outer = { (curr.x - (extensionDir.x * extension)), (curr.y - (extensionDir.y * extension)) };
        WidenedVertices line = {inner, outer};

        expandedPoints.push_back(line);

    }

    for (long long unsigned int i = 0; i < expandedPoints.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, expandedPoints[i].P1.x, expandedPoints[i].P1.y, expandedPoints[(i+1)%newCount].P1.x, expandedPoints[(i+1)%newCount].P1.y);
        SDL_RenderDrawLine(renderer, expandedPoints[i].P2.x, expandedPoints[i].P2.y, expandedPoints[(i+1)%newCount].P2.x, expandedPoints[(i+1)%newCount].P2.y);
    }

}


void triangleFill(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3)
{
    Vector2D _v1 = p1, _v2 = p2, _v3 = p3; //highest y = v1, then v2, then v3
    std::vector<Vector2D> v = { _v1, _v2, _v3 };

    // sort the vectors
    std::sort(v.begin(), v.end(), [](Vector2D a, Vector2D b)
    {
        return (a.y < b.y);
    });

    std::cout << "Intervals sorted by start time : \n";
    for (auto x : v)
        std::cout << "[" << x.y << "] ";

    
}

void msi::triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    std::vector<Vector2D> points = {
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x1, y1}
        };
        
    Vector2D v1 = {x1, y1};
    Vector2D v2 = {x2, y2};
    Vector2D v3 = {x3, y3};
    triangleFill(v1, v2, v3);
    drawLines(&points[0], 4);
}


void msi::quad(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, const float x4, const float y4){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    std::vector<Vector2D> points = {
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x4, y4},
        {x1, y1}
        };
        

    drawLines(&points[0], 5);

}

void msi::rect(const float x, const float y, const float width, const float height){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //rectangle fill if fill is specified
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);

    //lines
    std::vector<Vector2D> points = {
        {x, y},
        {x + width, y},
        {x + width, y + height},
        {x, y + height},
        {x, y}
        };
    
    drawLines(&points[0], 5);

}

void msi::square(const float x, const float y, const float size){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    msi::rect(x, y, size, size);
}

void msi::line(const float x1, const float y1, const float x2, const float y2){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void msi::point(const float x, const float y){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}
