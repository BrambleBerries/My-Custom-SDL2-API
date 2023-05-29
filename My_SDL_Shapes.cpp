#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>
#include "My_SDL_Shapes.hpp"

#include <chrono>

#include <SDL2/SDL.h>

//######## extern variables ############//
extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern float _strokeWeight;

//this structs holds two vertices that stam from the same corner but deplaced for the strokeWeight

typedef struct Vector2D{
    float x;
    float y;
} Vector2D;




float magnitude(const Vector2D v){
    return sqrt((v.x*v.x) + (v.y*v.y));
}

void drawLines(const Vector2D points[], const int count){


    // for (auto i = 0; i < count - 1; i++)
    // {
    //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //     SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[(i+1)].x, points[(i+1)].y);
    // }

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
            auto mPrev = magnitude(prev);
            prev.x /= mPrev;
            prev.y /= mPrev;

        //next vertex location !relative to curr!
        Vector2D next = points[(i+1) % newCount];
            next.x -= curr.x;
            next.y -= curr.y;
            auto mNext = magnitude(next);
            next.x /= mNext;
            next.y /= mNext;

        //angle between prev and next vertex
        float nextAngle = atan2f(next.y, next.x);
        float prevAngle = atan2f(prev.y, prev.x);
        float innerAngle = (prevAngle - nextAngle);

        //need half angle size
        float innerAngle_2 = innerAngle / 2;

        //distance of the new vertex to the original vertex
        float extension = (_strokeWeight/2) / sinf(innerAngle_2);
        
        //after debugging appears if innerAngle is too large it switches sides so this fixes that
        if (innerAngle * 180 / M_PI > -90) extension = -extension;

        //dir is the normalized vectors of vertices before and after
        Vector2D extensionDir = {next.x + prev.x, next.y + prev.y};
            float extMag = magnitude(extensionDir);
            extensionDir.x /= extMag;
            extensionDir.y /= extMag;

        
        Vector2D inner = { (curr.x + (extensionDir.x * extension)), (curr.y + (extensionDir.y * extension))};
        Vector2D outer = { (curr.x - (extensionDir.x * extension)), (curr.y - (extensionDir.y * extension))};
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

void msi::triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    std::vector<Vector2D> points = {
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x1, y1}
        };
        

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
