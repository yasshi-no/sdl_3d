#include <SDL.h>

#include <application.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 画面サイズ
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 576;

int main(int argc, char *argv[]) {
#ifndef NDEBUG
    SDL_Log("debug\n");
#endif
    Application application(SCREEN_WIDTH, SCREEN_HEIGHT);
    application.run();

    return 0;
}