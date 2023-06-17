#include <iostream>

#include "My_SDL_Implementation.hpp"


void msi::setup()
{
    msi::size(800, 800);
    msi::setFrameRate(1);
    msi::printElapsedTime(true);
}

void msi::draw()
{
    //std::cout << "this is from my custom implementation" << std::endl;
    //msi::rect(20, 20, 40, 60);
    //msi::square(40, 40, 40);
    //msi::line(20, 20, 40, 40);
    //msi::point(80, 80);
    //msi::strokeWeight(40);
    //msi::quad(100, 100, 300, 200, 400, 500, 50, 350);
    msi::strokeWeight(1);
    msi::triangle(100, 600, 300, 200, 400, 500);
}


