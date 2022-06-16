#include <application.hpp>
#include <cmath>
#include <iostream>
#include <sdl_3d.hpp>
#include <vector>

using namespace std;

Application::Application(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height) { init(); }

bool Application::init() {
    /* SDLを初期化する
    返り値:成功したか否か */
    // SDLを初期化する
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDLを初期化できませんでした." << std::endl;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // windowとrendererの作成
    SDL_CreateWindowAndRenderer(screen_width, screen_height, SDL_WINDOW_SHOWN, &window, &screen_renderer);
    if(window == NULL || screen_renderer == NULL) {
        std::cout << "windowを作成できませんでした." << std::endl;
        std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // windowのタイトルの設定
    SDL_SetWindowTitle(window, "sdl 3d");
    // カーソルの移動・表示を無効にする
    SDL_SetRelativeMouseMode(SDL_TRUE);

    return true;
}

void Application::close() {
    /* SDLを終了する. */

    // rendererを開放する
    SDL_DestroyRenderer(screen_renderer);

    // windowを破棄する
    SDL_DestroyWindow(window);
    window = NULL;

    // SDL subsystemsを終了する
    SDL_Quit();
}

Perspective Application::compute_new_perspective(Perspective perspective, Perspective perspective_change) {
    /* 新しい視点の位置を計算する. */
    Matrix zx_rotation_matrix = CoordinateSystem::compute_zxrotation_matrix(perspective.zx_angle); // y軸回転の行列
    Coordinate rotaioned_x = zx_rotation_matrix * Coordinate(1.0, 0.0, 0.0);                       // y軸回転で移動したx軸
    Matrix rodrigues_matrix =
        CoordinateSystem::compute_rodrigues_rotatin_matrix(rotaioned_x, -perspective.zy_angle); // y軸回転で移動したx軸を軸とした回転行列
    // 回転した移動方向のベクトル, 角度の変化から新しい視点を計算する
    Perspective rotationed_perspective_change(
        Coordinate(rodrigues_matrix * zx_rotation_matrix * perspective_change.coord),
        perspective_change.zx_angle,
        perspective_change.zy_angle);
    // 変化の更新
    Perspective ret = perspective + rotationed_perspective_change;
    return ret;
}

void Application::run() {
    // スクリーンを管理するオブジェクト
    Screen screen(screen_renderer);
    bool quit = false; // メインループを終了するか否か
    SDL_Event event;
    // 視点の位置と角度の変化について
    Perspective perspective(Coordinate(0.0, 0.0, 0.0), 0.0, 0.0);
    double change_length = 20.0;
    double change_angle = 0.01;

    double pi = 3.14;

    // Perspectiveの変化量
    Perspective perspective_change(Coordinate(0.0, 0.0, 0.0), 0.0, 0.0);

    // 直線のある世界を生成
    LocalCoordinateSystem rectangular = create_rectangular(100, 200, 300, Color(255, 0, 0, 255));
    LocalCoordinateSystem cube = create_cube(150, Color(0, 128, 128, 255));

    while(!quit) {
        // 描画をリセットする
        screen.clear();
        // 背景の更新
        screen.set_draw_color(Color(240, 255, 255, SDL_ALPHA_OPAQUE));
        screen.fill_rect();

        // 現在の視点の位置と方向を計算
        // 視点の方向に進むよう回転
        Matrix affine = CoordinateSystem::compute_affine_transformation_matrix(
            Perspective(Coordinate(0.0, 0.0, 0.0), perspective.zx_angle, perspective.zy_angle));

        // 回転した変化量を格納より, 新しい視点の位置と方向を計算する.
        perspective = compute_new_perspective(perspective, perspective_change);
        // SDL_Log("change   %f %f %f, %f %f, %f %f",
        //         rotationed_perspective_change.coord.get_x(),
        //         rotationed_perspective_change.coord.get_y(),
        //         rotationed_perspective_change.coord.get_z(),
        //         rotationed_perspective_change.zx_angle,
        //         rotationed_perspective_change.yz_angle, perspective.zx_angle,
        //         perspective.yz_angle);

        // 視点の方向の変化を初期化
        perspective_change.zx_angle = 0.0;
        perspective_change.zy_angle = 0.0;
        // 画面描画までの各種変換
        // WorldCoordinateSystemにLocalCoodinateSystemを追加する
        WorldCoordinateSystem world_coords;
        world_coords.add_bodys(rectangular, Perspective(Coordinate(0, 0, 0), 0, 0));
        world_coords.add_bodys(cube, Perspective(Coordinate(100, 200, 300), 0.5, 0));

        // WorldCoordinateSystemをCameraCoodinateSystemに変換する
        CameraCoordinateSystem camera_coords(world_coords, -perspective);

        // CameraCoodinateSystemをProjectionCoordinateSystemに変換する
        ProjectionCoordinateSystem proj_coords(camera_coords, screen_width, screen_height, 1, 10000, pi / 3.0);

        // ScreenCoordinateSystemの描画
        screen.set_draw_color(Color(255, 255, 255, SDL_ALPHA_OPAQUE));
        ScreenCoordinateSystem screen_coords(proj_coords, screen_width, screen_height);
        screen_coords.draw(screen);

        // 画面の更新
        screen.update();

        // イベントの処理
        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
            // 終了
            case SDL_QUIT: quit = true; break;
            case SDL_KEYDOWN:
                // キーボードが押し下げられたとき
                switch(event.key.keysym.sym) {
                // 終了
                case SDLK_ESCAPE: quit = true; break;
                // 視点の移動
                case SDLK_w:
                    // 前へ
                    perspective_change.coord.set_z(change_length);
                    break;
                case SDLK_a:
                    // 左へ
                    perspective_change.coord.set_x(-change_length);
                    break;
                case SDLK_s:
                    // 後ろへ
                    perspective_change.coord.set_z(-change_length);
                    break;
                case SDLK_d:
                    // 右へ
                    perspective_change.coord.set_x(change_length);
                    break;
                case SDLK_UP:
                    // 上へ
                    perspective_change.coord.set_y(-change_length);
                    break;
                case SDLK_DOWN:
                    // 下へ
                    perspective_change.coord.set_y(change_length);
                    break;
                default: break;
                }
                break;
            case SDL_KEYUP:
                // キーボードが押し上げられたとき
                switch(event.key.keysym.sym) {
                // 視点の移動
                case SDLK_w:
                    // 前への移動を無効にする
                    perspective_change.coord.set_z(0.0);
                    break;
                case SDLK_a:
                    // 左への移動を無効にする
                    perspective_change.coord.set_x(0.0);
                    break;
                case SDLK_s:
                    // 後ろへの移動を無効にする
                    perspective_change.coord.set_z(0.0);
                    break;
                case SDLK_d:
                    // 右への移動を無効にする
                    perspective_change.coord.set_x(0.0);
                    break;
                case SDLK_UP:
                    // 上への移動を無効にする
                    perspective_change.coord.set_y(0.0);
                    break;
                case SDLK_DOWN:
                    // 下への移動を無効にする
                    perspective_change.coord.set_y(0.0);
                    break;
                default: break;
                }
                break;
            case SDL_MOUSEMOTION:
                // 回転の操作
                perspective_change.zx_angle = event.motion.xrel * change_angle;
                perspective_change.zy_angle = event.motion.yrel * change_angle;
            default: break;
            }
        }

        SDL_Delay(33);
    }
    close();
}
