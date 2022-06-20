# sdl_3d
add_library(sdl_3d STATIC
    body.cpp
    coordinate_system.cpp
    coordinate.cpp
    local_coordinate_assets.cpp
    matrix.cpp
    screen.cpp
)
target_include_directories(sdl_3d PUBLIC
    ../include
    C:/dev_lib/SDL2-2.0.16-86-mingw/include/SDL2
    ${SDL2_INCLUDE_DIR}
)
target_link_directories(sdl_3d PUBLIC
    ${SDL2_LIBDIR}
)
target_link_libraries(sdl_3d PUBLIC
    ${SDL2_LIBRARIES}
)
target_compile_features(sdl_3d PUBLIC cxx_std_11)