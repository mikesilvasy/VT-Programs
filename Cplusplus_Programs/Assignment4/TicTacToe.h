#ifndef TICTACTOE_H__
#define TICTACTOE_H__

#include "Board.h"

class TicTacToe {
public:
    TicTacToe();
    ~TicTacToe();

    void printRules();
    void printDirections();
    void printSpaceDivider();
    void printScore();
    void nextTurn(Board board);
    void playRound(Board board);
    void playTicTacToe();
};

#endif

