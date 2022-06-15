# SDL2の読み込み
include(C:\\dev_lib\\SDL2-2.0.16-86-mingw\\lib\\cmake\\SDL2\\sdl2-config.cmake) # SDL2の修正したcmakeを読み込む. SDL2に関わる変数が読み込まれる.
message(STATUS SDL2_INCLUDE_DIRS:${SDL2_INCLUDE_DIRS})
message(STATUS SDL2_LIBRARIES:${SDL2_LIBRARIES})

# sdl_3d
add_library(sdl_3d INTERFACE)
target_link_libraries(sdl_3d INTERFACE
    matrix
    coordinate_system
    coordinate
    screen
    body
)
target_compile_features(sdl_3d INTERFACE cxx_std_11)

# Matrix
add_library(matrix STATIC matrix.cpp ../include/matrix.hpp)
target_include_directories(matrix PUBLIC
    ../include/
)
target_compile_features(matrix PRIVATE cxx_std_11)

# body
add_library(body STATIC body.cpp ../include/body.hpp)
target_include_directories(body PUBLIC
    ../include/
)
target_link_libraries(body PUBLIC
    matrix
    coordinate
    screen
)
target_compile_features(body INTERFACE cxx_std_11)

# coordinate
add_library(coordinate STATIC coordinate.cpp ../include/coordinate.hpp)
target_include_directories(coordinate PUBLIC
    ../include/
)

# coordinate_system
add_library(coordinate_system STATIC coordinate_system.cpp ../include/coordinate_system.hpp)
target_include_directories(coordinate_system PUBLIC
    ../include/
)
target_link_libraries(coordinate_system PUBLIC
    matrix
    coordinate
    screen
)
target_compile_features(coordinate_system INTERFACE cxx_std_11)

# screen
add_library(screen STATIC screen.cpp ../include/screen.hpp)
target_include_directories(screen PUBLIC
    ../include/
    ${SDL2_INCLUDE_DIRS}
)
target_link_directories(screen INTERFACE
    ${SDL2_LIBDIR}
)
target_link_libraries(screen PUBLIC
    ${SDL2_LIBRARIES}
    matrix
    coordinate
)
target_compile_features(screen INTERFACE cxx_std_11)
include_directories(${SDL2_INCLUDE_DIR})
