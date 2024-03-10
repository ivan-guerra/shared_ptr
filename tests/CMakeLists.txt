cmake_minimum_required(VERSION 3.27)

set(TESTNAME shared_ptr_test)

add_executable(${TESTNAME} ${TESTNAME}.cpp)

target_link_libraries(${TESTNAME} PRIVATE gtest_main shared_ptr)

gtest_discover_tests(${TESTNAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
