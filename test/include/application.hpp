#pragma once
#include <sdl_3d.hpp>

class Application {
    /* SDL2のアプリケーションを管理するクラス. */
private:
    // スクリーンのサイズ
    int screen_width;
    int screen_height;
    SDL_Window *window;
    SDL_Renderer *screen_renderer;

    bool init();
    bool load_media();
    void close();
    Perspective compute_new_perspective(Perspective perspective, Perspective perspective_change);

public:
    Application(int screen_width, int screen_height);
    void run();
};