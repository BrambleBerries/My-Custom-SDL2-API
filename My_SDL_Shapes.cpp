#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>
#include "My_SDL_Shapes.hpp"

#include <SDL2/SDL.h>

//######## extern variables ############//
extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int strokeWeight;
typedef struct my_SDL_Point{
    int x;
    int y;
} my_SDL_Point;
//this structs holds two vertices that stam from the same corner but deplaced for the strokeWeight
typedef struct WidenedVertices{
    my_SDL_Point P1;
    my_SDL_Point P2;
} WidenedVertices;

typedef struct Vector2D{
    float x;
    float y;
} Vector2D;

float manhattanDist(Vector2D p1, Vector2D p2){
    return ((p2.x - p1.x) + (p2.y - p1.y));
}

void drawLines(const my_SDL_Point points[], const int count){
    //if we work with float strokeWeight, just subtract and add half along the normal
    //SDL_RenderDrawLines(renderer, points, count);

    int newCount = count - 1;

    //find the centerPoint
    float x = 0, y = 0;
    for(int i = 0; i < newCount; i++){
        x += points[i].x;
        y += points[i].y;
    }
    Vector2D centerPos = {x / newCount, y / newCount};
    if (centerPos.x);
    std::vector<WidenedVertices> expandedPoints;
    //std::vector<SDL_Point> newPoints2;

    
    for (int i = 0; i < newCount; i++)
    {
        my_SDL_Point prev = points[(i + newCount - 1) % newCount];
        my_SDL_Point curr = points[i];
        my_SDL_Point next = points[(i+1) % newCount];

        if (curr.x == next.x && curr.y == next.y) continue;

        float radians1, radians2;
        if (0) radians1 = 0;
        else radians1 = atan2f( prev.y - curr.y, prev.x - curr.x );
        if (0) radians2 = 0;
        else radians2 = atan2f( next.y - curr.y, next.x - curr.x );

        
        
        //if (radians1 < 0) radians1 += 360;
        //if (radians2 < 0) radians2 += 360;
        float thetaRadians = (radians1 + radians2)/2;

        Vector2D cornerAngle = {cosf(thetaRadians), sinf(thetaRadians)};
        
        my_SDL_Point one = { (int) (curr.x + (cornerAngle.x * strokeWeight)), (int) (curr.y + (cornerAngle.y * strokeWeight))};
        my_SDL_Point two = { (int) (curr.x - (cornerAngle.x * strokeWeight)), (int) (curr.y - (cornerAngle.y * strokeWeight))};

        WidenedVertices line;
        line = {one, two};
        expandedPoints.push_back(line);

    }

    for (long long unsigned int i = 0; i < expandedPoints.size(); i++)
    {
        
        SDL_RenderDrawLine(renderer, expandedPoints[i].P1.x, expandedPoints[i].P1.y, expandedPoints[(i+1)%newCount].P1.x, expandedPoints[(i+1)%newCount].P1.y);
        SDL_RenderDrawLine(renderer, expandedPoints[i].P2.x, expandedPoints[i].P2.y, expandedPoints[(i+1)%newCount].P2.x, expandedPoints[(i+1)%newCount].P2.y);

    
    }

}


void msi::quad(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int x4, const int y4){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    std::vector<my_SDL_Point> points = {
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x4, y4},
        {x1, y1}
        };

    drawLines(&points[0], 5);

}

void msi::rect(const int x, const int y, const uint16_t width, const uint16_t height){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //rectangle fill if fill is specified
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);

    //lines
    std::vector<my_SDL_Point> points = {
        {x, y},
        {x + width, y},
        {x + width, y + height},
        {x, y + height},
        {x, y}
        };
    
    drawLines(&points[0], 5);

}

void msi::square(const int x, const int y, const uint16_t size){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    msi::rect(x, y, size, size);
}

void msi::line(const int x1, const int y1, const int x2, const int y2){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void msi::point(const int x, const int y){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}
