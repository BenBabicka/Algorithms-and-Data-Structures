//
// Created by Ben Babicka on 21/09/2026.
//

#ifndef ALGORITHMS_TETRIS_H
#define ALGORITHMS_TETRIS_H
#include <iostream>
#include <ostream>
#include <bits/this_thread_sleep.h>
#include <conio.h>
#include <thread>
#include <atomic>
#include "Block.h"

class Tetris {
    std::mutex stateMutex;
    Block *currBlock = nullptr;
    std::atomic<Block *> activeBlock{nullptr};

public:
    Tetris() noexcept : speed(1000),
                        score(0),
                        blocks{
                            Block(2, 2, {{true, true}, {true, true}}), // square
                            Block(2, 3, {{true, false}, {true, false}, {true, true}}), // lLeft
                            Block(2, 4, {{false, true}, {false, true}, {true, true}}), // lRight
                            Block(3, 2, {{false, true, false}, {true, true, true}}), // t
                            Block(1, 4, {{true, true, true, true}}), // line
                            Block(3, 2, {{false, true, true}, {true, true, false}}), // sRight
                            Block(3, 2, {{true, true, false}, {false, true, true}}) // sLeft
                        },
                        isPlaying(false) {
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 10; ++col) {
                grid[row][col] = false;
            }
        }
    };

    void reset() {
        isPlaying = false;
        speed = 1000;
        score = 0;
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 10; ++col) {
                grid[row][col] = false;
            }
        }
    }

    void stepDown() {
        tryMove(currBlock, 0, 1);
        if (currBlock->isSet()) {
            checkLoseCondition();
            completeRows();
            speed--;
            speed = std::max(speed, 20);
            currBlock = new Block(blocks[std::rand() % 7]);
            playedBlocks.push_back(currBlock);
            activeBlock.store(currBlock);
        }
    }

    static void controlBlocks(std::atomic<bool> &running, Tetris *self) {
        while (running.load()) {
            if (!_kbhit()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }
            char ch = _getch();
            std::lock_guard<std::mutex> lock(self->stateMutex);

            if (ch == 'a')
                self->tryMove(self->currBlock, -1, 0);
            else if (ch == 'd')
                self->tryMove(self->currBlock, 1, 0);
            else if (ch == 's')
                self->stepDown();
            else if (ch == 'w')
                self->tryRotate(self->currBlock);
            else
                continue;

            self->print(self->currBlock);
        }
    }

    void start() {
        reset();
        isPlaying = true;

        srand(time(0));

        currBlock = new Block(blocks[std::rand() % 7]);

        playedBlocks.push_back(currBlock);
        activeBlock.store(currBlock);

        std::atomic<bool> running{true};
        std::thread inputThread(controlBlocks, std::ref(running), this);

        while (isPlaying) {
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            std::lock_guard<std::mutex> lock(stateMutex);
            stepDown();
            print(currBlock);
        }

        running = false;
        inputThread.join();

        std::cout << "You have lost\nScore: " << getScore() << std::endl;
    }

    void tryMove(Block *block, int dx, int dy) {
        if (!detectCollision(block, dx, dy)) {
            block->move(dx, dy);
        } else if (dy > 0) {
            block->lock();
            settleBlock(block);
        }
    }

    void tryRotate(Block *block) {
        auto savedShape = block->getShapeGrid();
        auto dims = block->getShape();
        int savedX = dims[0], savedY = dims[1];
        int savedPosX = block->getPosX();

        block->rotate();

        auto newDims = block->getShape();
        int newX = newDims[0];
        if (block->getPosX() + newX > 10) block->setPosX(10 - newX);
        if (block->getPosX() < 0) block->setPosX(0);

        if (detectCollision(block, 0, 0)) {
            block->restoreShape(savedShape, savedX, savedY);
            block->setPosX(savedPosX);
        }
    }

    void completeRows() {
        for (int row = 0; row < 20;) {
            bool completeRow = true;
            for (int col = 0; col < 10; col++) {
                if (!grid[row][col]) completeRow = false;
            }
            if (completeRow) {
                for (int r = row; r > 0; r--) {
                    for (int col = 0; col < 10; col++) {
                        grid[r][col] = grid[r - 1][col];
                    }
                }
                for (int col = 0; col < 10; col++) {
                    grid[0][col] = false;
                }

                score += 10 * 10;
            } else {
                row++;
            }
        }
    }

    void gridReset() {
        for (int row = 0; row < 20; row++) {
            for (int col = 0; col < 10; col++) {
                grid[row][col] = false;
            }
        }
    }

    void settleBlock(Block *block) {
        const auto &s = block->getShapeGrid();
        for (int row = 0; row < (int) s.size(); row++) {
            for (int col = 0; col < (int) s[row].size(); col++) {
                if (s[row][col]) {
                    grid[block->getPosY() + row][block->getPosX() + col] = true;
                }
            }
        }
    }

    bool detectCollision(Block *block, int dx, int dy) {
        const auto &s = block->getShapeGrid();
        int baseX = block->getPosX() + dx;
        int baseY = block->getPosY() + dy;
        for (int row = 0; row < (int) s.size(); row++) {
            for (int col = 0; col < (int) s[row].size(); col++) {
                if (!s[row][col]) continue;

                int gx = baseX + col;
                int gy = baseY + row;

                if (gy < 0 || gy >= 20 || gx < 0 || gx >= 10)
                    return true;
                if (grid[gy][gx])
                    return true;
            }
        }
        return false;
    }

    void print(Block *active) noexcept {
        static bool first_call = true;
        if (!first_call) {
            std::cout << "\033[20A";
        }
        first_call = false;

        bool displayGrid[20][10];
        for (int row = 0; row < 20; row++) {
            for (int col = 0; col < 10; col++) {
                displayGrid[row][col] = grid[row][col];
            }
        }

        const auto &s = active->getShapeGrid();
        for (int r = 0; r < (int) s.size(); r++) {
            for (int c = 0; c < (int) s[r].size(); c++) {
                if (s[r][c]) {
                    displayGrid[active->getPosY() + r][active->getPosX() + c] = true;
                }
            }
        }

        for (int row = 0; row < 20; row++) {
            std::cout << "\033[2K\r<|";
            for (int col = 0; col < 10; col++) {
                char ch = *(displayGrid[row][col] ? "#" : ".");

                if (row == 0)
                    ch = *"*";
                std::cout << " " << ch << " ";
            }
            std::cout << "|>\n";
        }
        std::cout << std::flush;
    }

    int getScore() {
        return score;
    }

private:
    bool isPlaying;
    int speed;
    Block blocks[7];
    std::vector<Block *> playedBlocks;
    int score;
    bool grid[20][10];

    void checkLoseCondition() {
        bool lost = false;
        for (int col = 0; col < 10; col++) {
            if (grid[0][col]) {
                lost = true;
                break;
            }
        }
        if (lost) {
            isPlaying = false;
        }
    }
};
#endif //ALGORITHMS_TETRIS_H
