add_library(libkaleidoscope
    lexer.cpp
)

target_include_directories(libkaleidoscope
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_executable(kaleidoscope main.cpp)

target_link_libraries(kaleidoscope
    PRIVATE libkaleidoscope
)
