//
// Created by Ben Babicka on 9/09/2026.
//

#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H
#include <cmath>

class search {
public:
    //o(n)
    static bool linear_search(const int arr[], const int size, const int key) noexcept {
        for (int i = 0; i < size; i++) {
            if (arr[i] == key) {
                return true;
            }
        }
        return false;
    }

    //o(log(n))
    static bool binary_search(const int arr[], const int size, const int key) noexcept {
        int lo = 0, hi = size;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;

            const int value = arr[mid];

            if (value == key) {
                return true;
            }
            if (value < key) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return false;
    }
};


#endif //ALGORITHMS_SEARCH_H
