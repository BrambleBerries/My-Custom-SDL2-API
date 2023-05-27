#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>
#include <thread>

#include "nsTest.hpp"

//###### defining externs ######//
int myg::WIDTH, myg::HEIGHT;
long long myg::deltaTimeMs;


//###### file-scope variables ######//
bool printTime = false;
int targetIntervalMs = 16;

//###### anonymous namespace ######//
namespace {

    SDL_Window* window;
    SDL_Renderer* renderer;

    //keep track of timechanges
    std::chrono::time_point< std::chrono::steady_clock > previousTime = std::chrono::steady_clock::now();

   

    bool init()
    {
        SDL_Init( SDL_INIT_EVERYTHING );
        SDL_CreateWindowAndRenderer(myg::WIDTH, myg::HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
        
        if (window != NULL)
            return true;

        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return false;
    }

    void printTimeToConsole(std::chrono::duration<long long, std::micro> elapsedMicroSeconds)
    {
        std::cout << "elapsed time: \n";
        std::cout << std::setw(2) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() / 1'000'000)
            << "s." << std::setw(3) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() / 1'000)
            << "." << std::setw(3) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() % 1000) << std::endl;
    }

    void updateTime()
    {
        auto microseconds{ std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::steady_clock::now() - previousTime )};
        previousTime = std::chrono::steady_clock::now();
        myg::deltaTimeMs = microseconds.count() / 1'000;

        if (printTime) printTimeToConsole(microseconds);
    }

    void timed_function(std::function<void(void)> func, unsigned int interval, std::function<void(void)> timeFunc)
    {
        std::thread( 
        [func, interval, timeFunc]() 
        {
            while (true) 
            {
                auto timeToNextFrame = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                timeFunc();
                func();
                std::this_thread::sleep_until(timeToNextFrame);
            }
        }
        ).detach();
    }

}

//###### implementations ######//


int main()
{
    myg::run(myg::setup, myg::draw);
}


void myg::size(const int x, const int y)
{
    WIDTH = x;
    HEIGHT = y;
}

void myg::printElapsedTime(const bool print)
{
    std::cout << print << std::endl;
    std::cout << printTime << std::endl;
    printTime = print;
    std::cout << printTime << std::endl;

}

void myg::run(const std::function<void(void)> setup,const std::function<void(void)> loop)
{
    //add the start of the program, run the user-defined setup
    setup();

    //construct the graphical window according to the users preference
    if ( !init() )
        return;
    //start the draw loop
    timed_function(loop, targetIntervalMs, updateTime);

    SDL_Event windowEvent;

    while(true)
    {   
        if ( SDL_WaitEvent( &windowEvent ) )
        {
            if ( windowEvent.type == SDL_QUIT ){
                std::cout << "exiting program" << std::endl;
                break;
            }
        }            
    }

}

void myg::setFrameRate(const unsigned int frameRate)
{
    targetIntervalMs = 1000/frameRate;
}
