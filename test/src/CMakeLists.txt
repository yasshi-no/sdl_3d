# SDL2の読み込み
include(C:/dev_lib/SDL2-2.0.16-86-mingw/lib/cmake/SDL2/sdl2-config.cmake) # SDL2の修正したcmakeを読み込む. SDL2に関わる変数が読み込まれる.

set(SDL2_TTF_INCLUDDE_DIR C:/dev_lib/SDL_ttf/include)
set(SDL2_TTF_LIBRARY_DIR C:/dev_lib/SDL_ttf/lib)
set(SDL2_TTF_LIBRARY SDL2_ttf)

# application
add_library(application STATIC application.cpp ../include/application.hpp)
target_include_directories(application PUBLIC
    ../include/
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDDE_DIR}
)
target_link_directories(application PUBLIC
    ../../src/
    ${SDL2_LIBRARY_DIR}
    ${SDL2_TTF_LIBRARY_DIR}
)
target_link_libraries(application PUBLIC
    sdl_3d
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARY}
)
target_compile_features(application PRIVATE cxx_std_11)
