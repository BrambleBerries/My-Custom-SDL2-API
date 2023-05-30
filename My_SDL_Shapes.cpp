#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>
#include "My_SDL_Shapes.hpp"
#include "Geometrics.hpp"
#include <chrono>

#include <SDL2/SDL.h>

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
            float extMag = extensionDir.magnitude();
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


void triangleFill(const Vector2D &v1, const Vector2D &v2, const Vector2D &v3)
{
    std::cout << "fillinf" << std::endl;
    // 28.4 fixed-point coordinates
    const int Y1 = round(16.0f * v1.y);
    const int Y2 = round(16.0f * v2.y);
    const int Y3 = round(16.0f * v3.y);

    const int X1 = round(16.0f * v1.x);
    const int X2 = round(16.0f * v2.x);
    const int X3 = round(16.0f * v3.x);

    // Deltas
    const int DX12 = X1 - X2;
    const int DX23 = X2 - X3;
    const int DX31 = X3 - X1;

    const int DY12 = Y1 - Y2;
    const int DY23 = Y2 - Y3;
    const int DY31 = Y3 - Y1;

    // Fixed-point deltas
    const int FDX12 = DX12 << 4;
    const int FDX23 = DX23 << 4;
    const int FDX31 = DX31 << 4;

    const int FDY12 = DY12 << 4;
    const int FDY23 = DY23 << 4;
    const int FDY31 = DY31 << 4;

    // Bounding rectangle
    int minx = (min(X1, X2, X3) + 0xF) >> 4;
    int maxx = (max(X1, X2, X3) + 0xF) >> 4;
    int miny = (min(Y1, Y2, Y3) + 0xF) >> 4;
    int maxy = (max(Y1, Y2, Y3) + 0xF) >> 4;

    // Block size, standard 8x8 (must be power of two)
    const int q = 8;

    // Start in corner of 8x8 block
    minx &= ~(q - 1);
    miny &= ~(q - 1);

    //(char*&)colorBuffer += miny * stride;

    // Half-edge constants
    int C1 = DY12 * X1 - DX12 * Y1;
    int C2 = DY23 * X2 - DX23 * Y2;
    int C3 = DY31 * X3 - DX31 * Y3;

    // Correct for fill convention
    if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
    if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
    if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;

    // Loop through blocks
    for(int y = miny; y < maxy; y += q)
    {
        for(int x = minx; x < maxx; x += q)
        {
            // Corners of block
            int x0 = x << 4;
            int x1 = (x + q - 1) << 4;
            int y0 = y << 4;
            int y1 = (y + q - 1) << 4;

            // Evaluate half-space functions
            bool a00 = C1 + DX12 * y0 - DY12 * x0 > 0;
            bool a10 = C1 + DX12 * y0 - DY12 * x1 > 0;
            bool a01 = C1 + DX12 * y1 - DY12 * x0 > 0;
            bool a11 = C1 + DX12 * y1 - DY12 * x1 > 0;
            int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);

            bool b00 = C2 + DX23 * y0 - DY23 * x0 > 0;
            bool b10 = C2 + DX23 * y0 - DY23 * x1 > 0;
            bool b01 = C2 + DX23 * y1 - DY23 * x0 > 0;
            bool b11 = C2 + DX23 * y1 - DY23 * x1 > 0;
            int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);

            bool c00 = C3 + DX31 * y0 - DY31 * x0 > 0;
            bool c10 = C3 + DX31 * y0 - DY31 * x1 > 0;
            bool c01 = C3 + DX31 * y1 - DY31 * x0 > 0;
            bool c11 = C3 + DX31 * y1 - DY31 * x1 > 0;
            int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);

            // Skip block when outside an edge
            if(a == 0x0 || b == 0x0 || c == 0x0) continue;

            //unsigned int *buffer = colorBuffer;

            // Accept whole block when totally covered
            if(a == 0xF && b == 0xF && c == 0xF)
            {
                for(int iy = 0; iy < q; iy++)
                {
                    for(int ix = x; ix < x + q; ix++)
                    {
                        //buffer[ix] = 0x00007F00; // Green
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_RenderDrawPoint(renderer, ix, iy + y);
                            std::cout << "green" << std::endl;

                    }

                    //(char*&)buffer += stride;
                }
            }
            else // Partially covered block
            {
                int CY1 = C1 + DX12 * y0 - DY12 * x0;
                int CY2 = C2 + DX23 * y0 - DY23 * x0;
                int CY3 = C3 + DX31 * y0 - DY31 * x0;

                for(int iy = y; iy < y + q; iy++)
                {
                    int CX1 = CY1;
                    int CX2 = CY2;
                    int CX3 = CY3;

                    for(int ix = x; ix < x + q; ix++)
                    {
                        if(CX1 > 0 && CX2 > 0 && CX3 > 0)
                        {
                            //buffer[ix] = 0x0000007F;<< // Blue
                            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                            SDL_RenderDrawPoint(renderer, ix, iy);

                        }

                        CX1 -= FDY12;
                        CX2 -= FDY23;
                        CX3 -= FDY31;
                    }

                    CY1 += FDX12;
                    CY2 += FDX23;
                    CY3 += FDX31;

                    //(char*&)buffer += stride;
                }
            }
        }

        //(char*&)colorBuffer += q * stride;
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
