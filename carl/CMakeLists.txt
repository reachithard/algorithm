enable_testing()

file(GLOB TestSource *.c *.cpp)
find_package(GTest REQUIRED)
add_executable(test_algorithm inlet.cpp)
target_link_libraries(
  test_algorithm
  ${GTEST_LIBRARIES}
  ${GTEST_MAIN_LIBRARIES} intf
)

target_include_directories(test_algorithm PRIVATE ${GTEST_INCLUDE_DIRS})
target_sources(test_algorithm PRIVATE ${TestSource})