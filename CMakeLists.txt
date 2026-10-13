cmake_minimum_required(VERSION 4.3)
project(algorithms)

set(CMAKE_CXX_STANDARD 20)

# --- main application ---
add_executable(algorithms main.cpp
        search.h
        crystal_ball.h
        sort.h
        DoublyLinkedList.h
        Queue.h
        Stack.h
        Node.h
        ArrayList.h
        BTree.h
        RingBuffer.h
        MinHeap.h
)

# --- gtest ---
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # required for MinGW to match runtime linkage
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- test executable (separate from main) ---
add_executable(algorithms_test
        search.h
        test/search_test.cpp
        test/crystal_ball_test.cpp
        test/sort_test.cpp
)
target_link_libraries(algorithms_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(algorithms_test)