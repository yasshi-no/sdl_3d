cmake_minimum_required(VERSION 3.0.0)
project(sdl_3d CXX)

# SDL2の読み込み
# include(C:\\dev_lib\\SDL2-2.0.16-86-mingw\\lib\\cmake\\SDL2\\sdl2-config.cmake) # SDL2の修正したcmakeを読み込む. SDL2に関わる変数が読み込まれる.
find_package(SDL2 REQUIRED)
message(STATUS SDL2_INCLUDE_DIRS:${SDL2_INCLUDE_DIRS})
message(STATUS SDL2_LIBDIR:${SDL2_LIBDIR})
message(STATUS SDL2_LIBRARIES:${SDL2_LIBRARIES})

# SDL2_ttfの読み込み
set(SDL2_TTF_INCLUDDE_DIR C:/dev_lib/SDL_ttf/include)
set(SDL2_TTF_LIBDIR C:/dev_lib/SDL_ttf/lib)
set(SDL2_TTF_LIBRARIES SDL2_ttf)

# subdirectoryの追加
add_subdirectory(src)
add_subdirectory(test)