#include <iostream>
#include <iomanip>
#include <functional>
#include <thread>

//fix wonky main function for SDL
#define SDL_MAIN_HANDLED
//graphical render kit
#include <SDL2/SDL.h>

class MyGraphics{

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;
        std::chrono::_V2::steady_clock::time_point previousTime = std::chrono::steady_clock::now();

        const int WIDTH, HEIGHT;

    public:

        //this function will be responsible for updating and rawing your items
        virtual void draw() = 0;

        //this function is used for setup, such as screen size, framerate, static background
        virtual void setup() = 0;

        //this function will loop until the program is stopped
        int start(std::function<void(void)> setup, std::function<void(void)> logic);

    private:

        MyGraphics();
        ~MyGraphics();

        bool init();
        void timed_function(std::function<void(void)> func, unsigned int interval);

};