#include <SDL.h>

#include <coordinate.hpp>
#include <matrix.hpp>
#include <screen.hpp>

/* Screenクラス */
Screen::Screen(SDL_Renderer* renderer) : renderer(renderer) {}
void Screen::set_draw_color(Color color)
{
    /* 描画する色を変更する. */
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
void Screen::draw_line(int x1, int y1, int x2, int y2)
{
    /* 直線を描く. */
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

/* Colorクラス */
Color::Color() {}
Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}