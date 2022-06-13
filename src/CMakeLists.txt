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



