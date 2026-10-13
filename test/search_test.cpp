#include <gtest/gtest.h>
#include "../search.h"

TEST(linear_search, found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::linear_search(array, size, 5), true);
}

TEST(linear_search, not_found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::linear_search(array, size, 11), false);
}

TEST(binary_search, found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::binary_search(array, size, 5), true);
}

TEST(binary_search, not_found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::binary_search(array, size, 11), false);
}

TEST(sqaure_search, found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::square_search(array, size, 5), true);
}

TEST(sqaure_search, not_found_value) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = 10;
    EXPECT_EQ(search::square_search(array, size, 11), false);
}