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
    // 視点の位置と角度の変化について
    Perspective perspective(Coordinate(0.0, 0.0, 0.0), 0.0, 0.0);
    Coordinate coord(0.0, 0.0, 0.0);
    double xy_angle = 0.0;
    double yz_angle = 0.0;
    double change_length = 5.0;

    double pi = 3.14;

    // Perspectiveの変化量
    Perspective perspective_change(Coordinate(0.0, 0.0, 0.0), 0.0, 0.0);

    // for(int i = 0; i < 3; i++) {
    //     SDL_Log("%f %f %f\n", mat[i][0], mat[i][1], mat[i][2]);
    // }

    while(!quit) {
        // rendererを更新する
        SDL_RenderClear(screen_renderer);
        // 背景の更新
        SDL_SetRenderDrawColor(screen_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(screen_renderer, NULL);
        // ScreenCoordinateSystemの描画
        SDL_SetRenderDrawColor(screen_renderer, 255, 255, 255,
                               SDL_ALPHA_OPAQUE);
        // 現在の視点の位置と方向を計算
        perspective = perspective + perspective_change;
        // 直線のある世界を生成
        LocalCoordinateSystem local_coords;
        Line line(Coordinate(320, 0, 500), Coordinate(320, 320, 500));
        local_coords.add_body(&line);
        WorldCoordinateSystem world_coords;
        world_coords.add_bodys(local_coords,
                               Perspective(Coordinate(0, 0, 0), 0, 0));
        CameraCoordinateSystem camera_coords(
            world_coords, Perspective(coord, xy_angle, yz_angle));
        // yz_angle += 0.01;
        ProjectionCoordinateSystem proj_coords(
            camera_coords, screen_width, screen_height, 10, 1000, pi / 1.5);
        ScreenCoordinateSystem screen_coords(proj_coords, screen_width,
                                             screen_height);
        // SDL_Log("coord:%f %f %f", coord.get_x(), coord.get_y(),
        // coord.get_z()); 処理した変化量の初期化
        // coord = Coordinate(0.0, 0.0, 0.0);
        screen_coords.draw(screen_renderer);

        // 画面の更新
        SDL_RenderPresent(screen_renderer);

        // イベントの処理
        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                // 終了
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    // キーボードが押し下げられたとき
                    switch(event.key.keysym.sym) {
                        // 終了
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        // 視点の移動
                        case SDLK_w:
                            // 前へ
                            coord.set_z(coord.get_z() - change_length);
                            break;
                        case SDLK_a:
                            // 左へ
                            coord.set_x(coord.get_x() - change_length);
                            break;
                        case SDLK_s:
                            // 後ろへ
                            coord.set_z(coord.get_z() + change_length);
                            break;
                        case SDLK_d:
                            // 右へ
                            coord.set_x(coord.get_x() + change_length);
                            break;
                        case SDLK_UP:
                            // 上へ
                            coord.set_y(coord.get_y() - change_length);
                            break;
                        case SDLK_DOWN:
                            // 下へ
                            coord.set_y(coord.get_y() + change_length);
                            break;

                        default:
                            break;
                    }
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

        SDL_Delay(33);
    }
    close();
}
