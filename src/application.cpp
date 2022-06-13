#include <SDL.h>

#include <application.hpp>
#include <cmath>
#include <iostream>
#include <sdl_3d.hpp>
#include <vector>

using namespace std;

Application::Application(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height)
{
    init();
}

bool Application::init()
{
    /* SDLを初期化する
    返り値:成功したか否か */
    // SDLを初期化する
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDLを初期化できませんでした." << std::endl;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // windowとrendererの作成
    SDL_CreateWindowAndRenderer(screen_width, screen_height, SDL_WINDOW_SHOWN,
                                &window, &screen_renderer);
    if(window == NULL || screen_renderer == NULL) {
        std::cout << "windowを作成できませんでした." << std::endl;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetWindowTitle(window, "pendulum simulation");

    return true;
}

void Application::close()
{
    /* SDLを終了する. */

    // rendererを開放する
    SDL_DestroyRenderer(screen_renderer);

    // windowを破棄する
    SDL_DestroyWindow(window);
    window = NULL;

    // SDL subsystemsを終了する
    SDL_Quit();
}

void Application::run()
{
    bool quit = false;  // メインループを終了するか否か
    SDL_Event event;

    vector<vector<double>> v1 = {{1, 2, 3}, {2, 1, 5}, {3, 1, 2}};
    vector<vector<double>> v2 = {{2, 2, 3}, {2, 1, 5}, {3, -1, 2}};
    Matrix mat1(v1);
    Matrix mat2(v2);
    Matrix mat3 = mat1 * mat2;
    for(int i = 0; i < 3; i++) {
        SDL_Log("%f %f %f\n", mat3[i][0], mat3[i][1], mat3[i][2]);
    }

    while(!quit) {
        // rendererを更新する
        SDL_RenderClear(screen_renderer);
        // 背景の更新
        SDL_SetRenderDrawColor(screen_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(screen_renderer, NULL);
        // 画面の更新
        SDL_RenderPresent(screen_renderer);

        // イベントの処理
        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                // case SDL_MOUSEWHEEL:
                //     // 拡大縮小
                //     if(event.wheel.y > 0) {
                //         canvas.modify_scale(1 / scale_change_rate);
                //     } else if(event.wheel.y < 0) {
                //         canvas.modify_scale(scale_change_rate);
                //     }
                // case SDL_MOUSEBUTTONDOWN:
                //     // 移動の開始位置を記録
                //     SDL_GetMouseState(&mouse_bfr_x, &mouse_bfr_y);
                //     break;
                // case SDL_MOUSEBUTTONUP:
                //     mouse_bfr_x = -1;
                //     mouse_bfr_y = -1;
                //     break;
                default:
                    break;
            }
        }

        SDL_Delay(100);
    }
    close();
}