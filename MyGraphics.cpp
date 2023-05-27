#include "MyGraphics.hpp"

int MyGraphics::start(std::function<void(void)> setup, std::function<void(void)> logic)
{
    setup();

     if (!init())
        return EXIT_FAILURE;

    timed_function(logic, 1000/60);

    SDL_Event windowEvent;

    auto previousTime = std::chrono::steady_clock::now();
    while(true)
    {   
        if ( SDL_WaitEvent( &windowEvent ) )
        {
            if ( windowEvent.type == SDL_QUIT )
                break;
        }            
    }
    return EXIT_SUCCESS;
}

bool MyGraphics::init()
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);

    if (window != NULL)
        return true;

    std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
    return false;
}

void MyGraphics::timed_function(std::function<void(void)> func, unsigned int interval)
{
    std::thread( 
    [func, interval]() 
    {
        while (true) 
        {
            auto timeToNextFrame = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            func();
            std::this_thread::sleep_until(timeToNextFrame);
        }
    }
    ).detach();
}

namespace myg
{
    void size(int x, int y){
        //dostuff
    }
}
