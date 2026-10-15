//
// Created by Ben Babicka on 9/09/2026.
//

#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H
#include <cmath>
#include <vector>
#include <iostream>

class search {
public:
    //o(n)
    static bool linear_search(const std::vector<int> &arr, const int size, const int key) noexcept {
        int steps = 0;
        for (int i = 0; i < size; i++) {
            steps++;
            if (arr[i] == key) {
                std::cout << "Linear search - Steps: " << steps << ", Found: True" << std::endl;
                return true;
            }
        }
        std::cout << "Linear search - Steps: " << steps << ", Found: False" << std::endl;
        return false;
    }

    //o(log(n))
    static bool binary_search(const std::vector<int> &arr, const int size, const int key) noexcept {
        int lo = 0, hi = size;
        int steps = 0;

        while (lo < hi) {
            steps++;

            const int mid = lo + (hi - lo) / 2;

            const int value = arr[mid];

            if (value == key) {
                std::cout << "Binary search - Steps: " << steps << ", Found: True" << std::endl;
                return true;
            }
            if (value < key) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        std::cout << "Binary search - Steps: " << steps << ", Found: False" << std::endl;
        return false;
    }

    //o(sqrt(n))
    static bool jump_search(const std::vector<int> &arr, const int size, const int key) noexcept {
        if (size <= 0) {
            std::cout << "Jump search - Steps: 0, Found: False" << std::endl;
            return false;
        }
        const long long jmpAmount = static_cast<long long>(std::sqrt(static_cast<double>(size)));
        long long i = jmpAmount;
        int steps = 0;
        for (; i < size; i += jmpAmount) {
            steps++;
            if (arr[i] == key) {
                std::cout << "Jump search - Steps: " << steps << ", Found: True" << std::endl;
                return true;
            }
            if (arr[i] >= key) {
                break;
            }
        }

        i -= jmpAmount;
        for (long long j = 0; j < jmpAmount && i < size; j++, i++) {
            steps++;
            if (arr[i] == key) {
                std::cout << "Jump search - Steps: " << steps << ", Found: True" << std::endl;
                return true;
            }
        }

        std::cout << "Jump search - Steps: " << steps << ", Found: False" << std::endl;
        return false;
    }
};


#endif //ALGORITHMS_SEARCH_H
