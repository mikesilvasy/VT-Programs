#ifndef BOARD_H__
#define BOARD_H__

#include <vector>

class Board {
public:
    Board();
    ~Board();

    void buildBoard();
    void clearBoard();
    bool addPiece(int row, int col, char piece);
    char hasWon();
    bool isFull();
};

#endif
