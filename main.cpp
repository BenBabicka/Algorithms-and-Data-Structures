#include <filesystem>
#include <iostream>
#include <string>
#include "Tetris.h"
#include <windows.h>

#include "MinHeap.h"

//Used to keep the text inlined in the console
void enable_vt_mode() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main() {

    // MinHeap heap;
    //
    // heap.insert(5);
    // heap.insert(2);
    // heap.insert(1);
    // heap.insert(20);
    // heap.insert(10);
    // std::cout << heap.remove() << std::endl;
    // std::cout << heap.remove() << std::endl;
    // std::cout << heap.remove() << std::endl;
    // std::cout << heap.remove() << std::endl;
    // std::cout << heap.remove() << std::endl;

    enable_vt_mode();

    Tetris tetris;
    tetris.start();
    return 0;
}
