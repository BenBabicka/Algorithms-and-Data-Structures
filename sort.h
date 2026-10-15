//
// Created by Ben Babicka on 10/09/2026.
//

#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H
#include <vector>
#include <utility>

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

    static void mergeSort(std::vector<int> &arr) {
        const int n = arr.size();
        msort(arr, 0, n - 1);
    }

private:
    static void msort(std::vector<int> &arr, const int left, const int right) {
        if (left >= right)
            return;
        const int mid = left + (right - left) / 2;
        msort(arr, left, mid);
        msort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    static void merge(std::vector<int> &arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        //Create two temp arrays
        std::vector<int> L(n1), R(n2);

        //Copy data to temp vectors L and R
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;

        //Merge the temp arrays back into arr [left...right]
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        //Copy the remaining elements of L
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        //Copy the remaining elements of R
        while (i < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

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
