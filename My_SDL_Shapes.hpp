#ifndef MY_SDL_SHAPES_H
#define MY_SDL_SHAPES_H

//fix wonky main function for SDL
#define SDL_MAIN_HANDLED
//graphical render kit
#include "src/include/SDL2/SDL.h"

namespace msi {


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
    void quad(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int x4, const int y4);
    
    /**
     * @brief  creates a rectangle at position with width and height
     * @note   
     * @param  x: x-Coordinate of the rectangle
     * @param  y: y-Coordinate of the rectangle
     * @param  width: width of the rectangle
     * @param  height: height of the rectangle
     * @retval None
     */
    void rect(const int x, const int y, const uint16_t width, const uint16_t height);

    /**
     * @brief  creates a square at x and y with size size
     * @note   
     * @param  x: x-Coordinate of the square
     * @param  y: y-Coordiante of the square
     * @param  size: width and height of the square
     * @retval None
     */
    void square(const int x, const int y, const uint16_t size);

    /**
     * @brief  draws a line between first and second point
     * @note   
     * @param  x1: x-Coordinate point 1
     * @param  y1: y-Coordinate point 1
     * @param  x2: x-Coordinate point 2
     * @param  y2: y-Cooridnate point 2
     * @retval None
     */
    void line(const int x1, const int y1, const int x2, const int y2);

    /**
     * @brief  Draws a point at the x- and y-coordinate
     * @note   
     * @param  x: x-Coordinate of point
     * @param  y: y-Coordinate of point
     * @retval None
     */
    void point(const int x, const int y);
}


#endif