//
// Created by Ben Babicka on 10/09/2026.
//

#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H
#include <vector>

class sort {
public:
    static void bubble_sort(std::vector<int> &arr, const int size) {
        for (int i = 0; i < size; i++) {
            bool swapped = false;
            for (int j = 0; j < size - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) // Array is sorted
                return;
        }
    }

    static void quick_sort(std::vector<int> &arr, const int size) {
        qsort(arr, 0, size - 1);
    }

private:
    static void qsort(std::vector<int> &arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            qsort(arr, low, pi - 1);
            qsort(arr, pi + 1, high);
        }
    }

    static int partition(std::vector<int> &arr, int low, int high) {
        int pivot = arr[high];

        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};


#endif //ALGORITHMS_SORT_H
