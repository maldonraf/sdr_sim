add_executable(tests tests.cpp)
add_executable(data_gen data_gen.cpp)
target_link_libraries(tests PRIVATE engine)
target_link_libraries(data_gen PRIVATE engine)