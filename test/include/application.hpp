#pragma once

#include <SDL.h>

class Application
{
    /* SDL2のアプリケーションを管理するクラス. */
private:
    double screen_width;
    double screen_height;
    SDL_Window* window;
    SDL_Renderer* screen_renderer;

    bool init();
    bool load_media();
    void close();

public:
    Application(int screen_width, int screen_height);
    void run();
};