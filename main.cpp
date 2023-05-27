#include <iostream>

#include "nsTest.hpp"


void myg::setup()
{
    myg::size(800, 800);
    myg::setFrameRate(10);
    myg::printElapsedTime(true);
}

void myg::draw()
{
    std::cout << "this is from my custom implementation" << std::endl;
}


