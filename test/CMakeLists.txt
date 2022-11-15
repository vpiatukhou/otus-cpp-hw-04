add_executable(print_ip_test print_ip_test.cpp)

set_target_properties(print_ip_test PROPERTIES 
    CMAKE_CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

if (WIN32)
    # Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

target_include_directories(print_ip_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(print_ip_test GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(print_ip_test)

enable_testing()