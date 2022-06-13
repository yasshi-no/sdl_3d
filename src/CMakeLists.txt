# Matrix
add_library(matrix STATIC matrix.cpp ../include/matrix.hpp)
target_include_directories(matrix PUBLIC 
    ../include/
)
target_compile_features(matrix PRIVATE cxx_std_11)

# sdl_3d(library)
add_library(sdl_3d sdl_3d.cpp ../include/sdl_3d.hpp)
target_include_directories(sdl_3d PUBLIC
    ../include/
)
target_compile_features(sdl_3d PRIVATE cxx_std_11)
target_link_libraries(sdl_3d PUBLIC
    matrix
)




# application
add_library(application STATIC application.cpp ../include/application.hpp)
target_include_directories(application PUBLIC 
    ../include/
    ${SDL2_INCLUDE_DIRS}
)
target_link_directories(application PUBLIC
${SDL2_LIBDIR}
)
target_link_libraries(application PUBLIC
    ${SDL2_LIBRARIES}
)
target_compile_features(application PRIVATE cxx_std_11)
