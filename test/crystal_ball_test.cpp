#include <gtest/gtest.h>
#include "../crystal_ball.h"

TEST(crystal_ball_test, found_value_at_6) {
    bool array[10] = {false, false, false, false, false, false, true, true, true, true};
    constexpr int size = 10;
    EXPECT_EQ(crystal_ball::FindBreakingHeight(array, size), 6);
}


TEST(crystal_ball_test, found_value_at_9) {
    bool array[10] = {false, false, false, false, false, false, false, false, false, true};
    constexpr int size = 10;
    EXPECT_EQ(crystal_ball::FindBreakingHeight(array, size), 9);
}

TEST(crystal_ball_test, no_value_found_at) {
    bool array[10] = {false, false, false, false, false, false, false, false, false, false};
    constexpr int size = 10;
    EXPECT_EQ(crystal_ball::FindBreakingHeight(array, size), -1);
}

TEST(crystal_ball_test, found_value_at_0) {
    bool array[10] = {true, true, true, true, true, true, true, true, true, true};
    constexpr int size = 10;
    EXPECT_EQ(crystal_ball::FindBreakingHeight(array, size), 0);
}