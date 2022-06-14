add_subdirectory(src)

# 実行ファイルの追加, インクルード, リンク
add_executable(main main.cpp)
target_link_libraries(main PUBLIC
    application
)

# コンパイルオプション
target_compile_options(main PUBLIC
    $<$<CONFIG:Debug>: -O0 -g -Wall>
    $<$<CONFIG:Release>: -O3 -Wall>
)
target_compile_features(main PRIVATE cxx_std_11)