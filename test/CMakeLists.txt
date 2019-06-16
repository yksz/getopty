set(tests
    getopty_test
)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/test
)
foreach(test IN LISTS tests)
    add_executable(${test} ${test}.c odr_check.c)
    add_test(NAME ${test}
             COMMAND ${test}
             WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
endforeach()
