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

    static void mergeSort(std::vector<int> &arr, const int size) {
        // Using temp buffer to reduce number of allocations that occurring
        std::vector<int> buffer(arr.size());
        msort(arr, buffer, 0, size - 1);
    }

private:
    static void msort(std::vector<int> &arr, std::vector<int> &buffer, const int left, const int right) {
        if (left >= right)
            return;
        const int mid = left + (right - left) / 2;
        msort(arr, buffer, left, mid);
        msort(arr, buffer, mid + 1, right);
        merge(arr, buffer, left, mid, right);
    }

    static void merge(std::vector<int> &arr, std::vector<int> &buffer, int left, int mid, int right) {
        // Copy arr[left..right] into the buffer so the arr can be overwritten while merging
        for (int x = left; x <= right; x++)
            buffer[x] = arr[x];

        int i = left; // Next unread item of the left run (buffer[left...mid])
        int j = mid + 1; // Next unread item of the right run (buffer[mid+1...right])
        int k = left; // Next slot to write in array

        //Merge the two runs of buffer back into arr[left...right]
        while (i <= mid && j <= right) {
            if (buffer[i] <= buffer[j]) {
                arr[k] = buffer[i];
                i++;
            } else {
                arr[k] = buffer[j];
                j++;
            }
            k++;
        }

        //Copy whatever is left of either run
        while (i <= mid) {
            arr[k] = buffer[i];
            i++;
            k++;
        }
        while (j <= right) {
            arr[k] = buffer[j];
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
