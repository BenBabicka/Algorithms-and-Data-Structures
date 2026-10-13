//
// Created by Ben Babicka on 9/09/2026.
//

#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H

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
};


#endif //ALGORITHMS_SEARCH_H
