cmake_minimum_required(VERSION 3.0.0)
project(sdl_3d CXX)

# SDL2の読み込み
include(C:\\dev_lib\\SDL2-2.0.16-86-mingw\\lib\\cmake\\SDL2\\sdl2-config.cmake) # SDL2の修正したcmakeを読み込む. SDL2に関わる変数が読み込まれる.
message(STATUS SDL2_INCLUDE_DIRS:${SDL2_INCLUDE_DIRS})
message(STATUS SDL2_LIBRARIES:${SDL2_LIBRARIES})

# subdirectoryの追加
add_subdirectory(src)
add_subdirectory(test)