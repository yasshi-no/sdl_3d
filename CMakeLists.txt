cmake_minimum_required(VERSION 3.0.0)
project(sdl_3d CXX)

# SDL2の読み込み
include(C:\\dev_lib\\SDL2-2.0.16-86-mingw\\lib\\cmake\\SDL2\\sdl2-config.cmake) # SDL2の修正したcmakeを読み込む. SDL2に関わる変数が読み込まれる.
message(STATUS SDL2_INCLUDE_DIRS:${SDL2_INCLUDE_DIRS})
message(STATUS SDL2_LIBRARIES:${SDL2_LIBRARIES})

# subdirectoryの追加
add_subdirectory(src)

# 実行ファイルの追加, インクルード, リンク
add_executable(main main.cpp)
target_include_directories(main PUBLIC
${SDL2_INCLUDE_DIRS}
)
target_link_directories(main PUBLIC
${SDL2_LIBDIR}
)
target_link_libraries(main PUBLIC
    ${SDL2_LIBRARIES}
    application
    sdl_3d
)

# コンパイルオプション
target_compile_options(main PUBLIC
    $<$<CONFIG:Debug>: -O0 -g -Wall>
    $<$<CONFIG:Release>: -O3 -Wall>
)
target_compile_features(main PRIVATE cxx_std_11)