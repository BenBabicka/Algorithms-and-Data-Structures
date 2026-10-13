#include "gtest/gtest.h"
#include "../sort.h"

static bool compareArray(const int arr1[], const int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

TEST(bubble_sort, sorted) {
    constexpr int size = 10;
    int array[size] = {5, 1, 7, 8, 2, 3, 10, 4, 6, 9};
    sort::bubble_sort(array, size);
    const int sortedArray[size] = {1,2,3,4,5,6,7,8,9,10};
    EXPECT_EQ(compareArray(array, sortedArray, size), true);
}

TEST(quick_sort, sorted) {
    constexpr int size = 10;
    int array[size] = {5, 1, 7, 8, 2, 3, 10, 4, 6, 9};
    sort::quick_sort(array, size);
    const int sortedArray[size] = {1,2,3,4,5,6,7,8,9,10};
    EXPECT_EQ(compareArray(array, sortedArray, size), true);
}
