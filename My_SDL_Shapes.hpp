#ifndef MY_SDL_SHAPES_H
#define MY_SDL_SHAPES_H

//fix wonky main function for SDL
#define SDL_MAIN_HANDLED
//graphical render kit
#include "src/include/SDL2/SDL.h"

namespace msi {


    /**
     * @brief  Draws a triangle between the given pcoordinates
     * @note   
     * @param  x1: x-Coordinate point 1
     * @param  y1: x-Coordinate point 1
     * @param  x2: x-Coordinate point 2
     * @param  y2: x-Coordinate point 2
     * @param  x3: x-Coordinate point 3
     * @param  y3: x-Coordinate point 3
     * @retval None
     */
    void triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3);

    /**
     * @brief  Draws a quad between the given pcoordinates
     * @note   
     * @param  x1: x-Coordinate point 1
     * @param  y1: x-Coordinate point 1
     * @param  x2: x-Coordinate point 2
     * @param  y2: x-Coordinate point 2
     * @param  x3: x-Coordinate point 3
     * @param  y3: x-Coordinate point 3
     * @param  x4: x-Coordinate point 4
     * @param  y4: y-Coordinate point 4
     * @retval None
     */
    void quad(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, const float x4, const float y4);
    
    /**
     * @brief  creates a rectangle at position with width and height
     * @note   
     * @param  _x: x-Coordinate of the rectangle
     * @param  _y: y-Coordinate of the rectangle
     * @param  _width: width of the rectangle
     * @param  _height: height of the rectangle
     * @retval None
     */
    void rect(const float x, const float y, const float width, const float height);

    /**
     * @brief  creates a square at x and y with size size
     * @note   
     * @param  x: x-Coordinate of the square
     * @param  y: y-Coordiante of the square
     * @param  size: width and height of the square
     * @retval None
     */
    void square(const float x, const float y, const float size);

    /**
     * @brief  draws a line between first and second point
     * @note   
     * @param  x1: x-Coordinate point 1
     * @param  y1: y-Coordinate point 1
     * @param  x2: x-Coordinate point 2
     * @param  y2: y-Cooridnate point 2
     * @retval None
     */
    void line(const float x1, const float y1, const float x2, const float y2);

    /**
     * @brief  Draws a point at the x- and y-coordinate
     * @note   
     * @param  x: x-Coordinate of point
     * @param  y: y-Coordinate of point
     * @retval None
     */
    void point(const float x, const float y);
}


#endif