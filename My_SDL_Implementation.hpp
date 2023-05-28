#ifndef MY_SDL_IMPLEMENTATION_H
#define MY_SDL_IMPLEMENTATION_H

#include <functional>

//fix wonky main function for SDL
#define SDL_MAIN_HANDLED
//graphical render kit
#include "src/include/SDL2/SDL.h"

namespace msi
{
    extern int WIDTH, HEIGHT;
    extern long long deltaTimeMs;

    void setup();
    void draw();
    
    /**
     * @brief  sets the size of the graphics window
     * @note  only considers integers 
     * @param  x: width
     * @param  y: height
     * @retval None
     */
    void size(const int x, const int y);

    //TODO: complete the printing in the window, not cli
    /**
     * @brief  if true, prints the time in top-right corner
     * @note   not implemented
     * @param  print: 
     * @retval None
     */
    void printElapsedTime(const bool print);

    /**
     * @brief  Takes a setup and update function, the update function loop following the framerate if it is set
     * @note   
     * @param setup: setup function
     * @param loop: repeating function
     * @retval None
     */
    void run(const std::function<void(void)> setup,const std::function<void(void)> loop);

    /**
     * @brief  sets the frames per second for the program to target
     * @note   
     * @param  frameRate: frames per second
     * @retval None
     */
    void setFrameRate(const unsigned int frameRate);

}

#endif
