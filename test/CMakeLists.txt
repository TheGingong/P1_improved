add_executable(test_file test.c)
target_link_libraries(test_file main_lib)
add_test(NAME test_file COMMAND test_file)