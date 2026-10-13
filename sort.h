//
// Created by Ben Babicka on 10/09/2026.
//

#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

#include <iostream>
#include <ostream>

class sort {
    public:
    static void bubble_sort(int *arr, const int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                   const int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    static void quick_sort(int *arr, const int size) {
        qsort(arr, 0, size - 1);
    }

private:
    static void qsort(int *arr, int low, int high) {
        if (low >= high) {
            return;
        }
        const int pivotIndex = partition(arr, low, high);
        qsort(arr, low, pivotIndex - 1);
        qsort(arr, pivotIndex + 1, high);
    }

    static int partition(int *arr, int low, int high) {
        const int pivot = arr[high];

        int index = low - 1;
        for (int i = low; i < high; i++) {
            if (arr[i] <= pivot) {
                index++;
                const int temp = arr[i];
                arr[i] = arr[index];
                arr[index] = temp;
            }
        }
        index++;
        arr[high] = arr[index];
        arr[index] = pivot;
        return index;
    }
};


#endif //ALGORITHMS_SORT_H
