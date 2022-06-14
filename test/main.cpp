#include <SDL.h>

#include <application.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 画面サイズ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* argv[])
{
    Application application(SCREEN_WIDTH, SCREEN_HEIGHT);
    application.run();

    return 0;
}