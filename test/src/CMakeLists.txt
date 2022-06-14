# application
add_library(application STATIC application.cpp ../include/application.hpp)
target_include_directories(application PUBLIC 
    ../include/
)
target_link_directories(application PUBLIC
    ../../src/
)
target_link_libraries(application PUBLIC
    sdl_3d
)
target_compile_features(application PRIVATE cxx_std_11)
