add_library(sdl_3d INTERFACE)
target_include_directories(sdl_3d INTERFACE
    ${SDL2_INCLUDE_DIRS}
)
target_link_directories(sdl_3d INTERFACE
    ${SDL2_LIBDIR}
)
target_link_libraries(sdl_3d INTERFACE
    ${SDL2_LIBRARIES}
    matrix
)
target_compile_features(sdl_3d INTERFACE cxx_std_11)


# Matrix
add_library(matrix STATIC matrix.cpp ../include/matrix.hpp)
target_include_directories(matrix PUBLIC 
    ../include/
)
target_compile_features(matrix PRIVATE cxx_std_11)