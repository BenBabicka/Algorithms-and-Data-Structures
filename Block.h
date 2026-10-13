//
// Created by Ben Babicka on 21/09/2026.
//

#ifndef ALGORITHMS_BLOCK_H
#define ALGORITHMS_BLOCK_H

#include <vector>

class Block {
public:
    Block(Block &block) noexcept : x(block.x), y(block.y), set(block.isSet()), posX(0), posY(0), shape(block.shape) {
    };

    Block(int aX, int aY, const std::vector<std::vector<bool> > &aShape)
        : x(aX), y(aY), shape(aShape), posX(0), posY(0), set(false) {
    }

    void move(int aX, int aY) {
        if (!set) {
                posX += aX;
            if (posX < 0) posX = 0;
            if (posX > 10 - x) posX = 10 - x;
            posY += aY;
        }
    }

    void rotate() noexcept {
        int oldRows = (int)shape.size();
        int oldCols = oldRows > 0 ? (int)shape[0].size() : 0;
        std::vector<std::vector<bool>> rotated(oldCols, std::vector<bool>(oldRows));
        for (int row = 0; row < oldRows; row++) {
            for (int col = 0; col < oldCols; col++) {
                rotated[col][oldRows - 1 - row] = shape[row][col];
            }
        }
        shape = std::move(rotated);
        std::swap(x,y);
    }

    void setPosX(int p) noexcept {posX = p;}
    void setPosY(int p) noexcept {posY = p;}

    void restoreShape(const std::vector<std::vector<bool> > &aShape, int oldX, int oldY) noexcept {
        shape = aShape;
        x = oldX;
        y = oldY;
    }

    const std::vector<std::vector<bool>>& getShapeGrid() const noexcept {return shape;}

    int getPosX() noexcept { return posX; }
    int getPosY() noexcept { return posY; }
    bool isSet() noexcept { return set; }
    std::vector<int> getShape() noexcept { return {x, y}; }
    void lock() noexcept {set=true;}
private:
    int x;
    int y;
    int posX;
    int posY;
    bool set;
    std::vector<std::vector<bool> > shape;
};
#endif //ALGORITHMS_BLOCK_H
