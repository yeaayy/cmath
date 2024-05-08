
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)
include_directories(../src)

function(generate_test name)
    add_executable(${name}-test ${name}-test.cpp)
    target_include_directories(${name}-test PUBLIC ${PROJECT_BINARY_DIR}/_deps/googletest-src/googlemock/include)
    target_link_libraries(${name}-test cmath_base gmock_main GTest::gtest_main)
    gtest_discover_tests(${name}-test)
endfunction()

generate_test(basic)
generate_test(parse-number)
generate_test(parse-whitespace)
generate_test(parse-variable)
generate_test(parse-expr)
generate_test(parse-bracket)
generate_test(parse-derrivative)
generate_test(expand-bracket)
generate_test(add)
