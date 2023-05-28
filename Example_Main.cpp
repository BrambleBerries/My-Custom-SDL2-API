#include <iostream>

#include "My_SDL_Implementation.hpp"


void msi::setup()
{
    msi::size(800, 800);
    msi::setFrameRate(10);
    msi::printElapsedTime(true);
}

void msi::draw()
{
    std::cout << "this is from my custom implementation" << std::endl;
}


