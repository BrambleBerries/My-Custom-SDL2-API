#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>
#include <thread>

#include "My_SDL_Implementation.hpp"

//###### defining externs ######//
int msi::WIDTH, msi::HEIGHT;
long long msi::deltaTimeMs;
long long msi::frameCount = 0;

//###### variables ######//
bool _printTime = false;
int _targetIntervalMs = 16;
float _strokeWeight = 1;

//###### things probably needed elsewhere ######//
SDL_Window* window;
SDL_Renderer* renderer;

//###### anonymous namespace ######//
namespace {

    

    //keep track of timechanges
    std::chrono::time_point< std::chrono::steady_clock > previousTime = std::chrono::steady_clock::now();

   

    bool init()
    {
        SDL_Init( SDL_INIT_EVERYTHING );
        SDL_CreateWindowAndRenderer(msi::WIDTH, msi::HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
        
        if (window != NULL)
            return true;

        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return false;
    }

    void printTimeToConsole(std::chrono::duration<long long, std::micro> elapsedMicroSeconds)
    {
        /*std::cout << "elapsed time: \n";
        std::cout << std::setw(2) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() / 1'000'000)
            << "s." << std::setw(3) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() / 1'000)
            << "." << std::setw(3) << std::setfill('0') << std::to_string(elapsedMicroSeconds.count() % 1000) << std::endl;*/
    }

    void updateTime()
    {
        auto microseconds{ std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::steady_clock::now() - previousTime )};
        previousTime = std::chrono::steady_clock::now();
        msi::deltaTimeMs = microseconds.count() / 1000;
        msi::frameCount++;
        if (_printTime) printTimeToConsole(microseconds);
    }

    void timed_function(std::function<void(void)> userFunc, unsigned int interval)
    {
        std::thread( 
        [userFunc, interval]() 
        {
            while (true) 
            {
                auto timeToNextFrame = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);

                auto start1 = std::chrono::high_resolution_clock::now();

                updateTime();

                auto stop1 = std::chrono::high_resolution_clock::now();
                auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
                std::cout << "time for updateTime: " << duration1.count() << std::endl;


                auto start2 = std::chrono::high_resolution_clock::now();

                userFunc();

                auto stop2 = std::chrono::high_resolution_clock::now();
                auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
                std::cout << "time for userFunction: " << duration2.count() << std::endl;


                auto start3 = std::chrono::high_resolution_clock::now();

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderPresent(renderer);

                auto stop3 = std::chrono::high_resolution_clock::now();
                auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);
                std::cout << "time for renderer: " << duration3.count() << std::endl;
                std::this_thread::sleep_until(timeToNextFrame);
            }
        }
        ).detach();
    }

}

//###### implementations ######//


int main()
{
    msi::run(msi::setup, msi::draw);
}


void msi::size(const int x, const int y)
{
    WIDTH = x;
    HEIGHT = y;
}

void msi::printElapsedTime(const bool print)
{
    _printTime = print;
}

void msi::run(const std::function<void(void)> setup,const std::function<void(void)> loop)
{
    //add the start of the program, run the user-defined setup
    setup();

    //construct the graphical window according to the users preference
    if ( !init() )
        return;
    //start the draw loop
    timed_function(loop, _targetIntervalMs);

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

void msi::setFrameRate(const unsigned int frameRate)
{
    _targetIntervalMs = 1000/frameRate;
}

void msi::strokeWeight(float weight){
    _strokeWeight = weight;
}
