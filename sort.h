//
// Created by Ben Babicka on 10/09/2026.
//

#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

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
};


#endif //ALGORITHMS_SORT_H
