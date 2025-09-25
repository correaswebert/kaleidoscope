add_executable(libkaleidoscope_tests
    lexer_test.cpp
)

target_link_libraries(libkaleidoscope_tests
    PRIVATE libkaleidoscope GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(libkaleidoscope_tests)
