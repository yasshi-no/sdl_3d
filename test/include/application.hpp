#pragma once
#include <SDL_ttf.h>
#include <sdl_3d.hpp>

class Application {
    /* SDL2のアプリケーションを管理するクラス. */
private:
    // スクリーンのサイズ
    int screen_width;
    int screen_height;
    int font_size;
    SDL_Window *window;
    SDL_Renderer *screen_renderer;
    TTF_Font *font;
    double PI = 3.14159265358979;

    bool init();
    bool load_media();
    void close();
    Perspective compute_new_perspective(Perspective perspective, Perspective perspective_change);
    void render_perspective_textures(Perspective perspective);

public:
    Application(int screen_width, int screen_height);
    void run();
};