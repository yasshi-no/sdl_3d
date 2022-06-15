#include <SDL.h>

#include <coordinate.hpp>
#include <matrix.hpp>

class Color
{
    /* 色彩 */
public:
    // RGB及び透過度
    int r;
    int g;
    int b;
    int a;
    Color();
    Color(int r, int g, int b, int a);
};

class Screen
{
    /* 画面への描画のインタフェース */
private:
    SDL_Renderer* renderer;

public:
    Screen(SDL_Renderer* renderer);
    void set_draw_color(Color color);
    void draw_line(int x1, int y1, int x2, int y2);
};
