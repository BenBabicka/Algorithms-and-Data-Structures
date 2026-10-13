//
// Created by Ben Babicka on 10/09/2026.
//

#ifndef ALGORITHMS_CRYSTAL_BALL_H
#define ALGORITHMS_CRYSTAL_BALL_H
#include <cmath>

// You are given two crystal balls
// You need to find the lowest height of which the crystal balls will break
// Find the quickest algorithm

class crystal_ball {
public:
    static int FindBreakingHeight(const bool arr[], const int size) {
        int jmpAmount = std::floor(std::sqrt(size));
        int i = jmpAmount;

       for (; i < size; i += jmpAmount) {
           if (arr[i]) {
               break;
           }
       }

        i -= jmpAmount;

        for (int j = 0; j <= jmpAmount && i < size; j++, i++) {
            if (arr[i]) {
                return i;
            }
        }
        return -1;
    }
};


#endif //ALGORITHMS_CRYSTAL_BALL_H
