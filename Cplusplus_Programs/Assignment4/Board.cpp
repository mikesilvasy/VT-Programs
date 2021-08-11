#include "Board.h"
#include <iostream>

std::vector<std::string> row1;
std::vector<std::string> row2;
std::vector<std::string> row3;

/*
 * Constructor
 * Initializes the 3 rows with 3 "   " values and builds the board.
 */
Board::Board() {
    for (int i = 0; i < 3; i++) {
        row1.push_back("   ");
        row2.push_back("   ");
        row3.push_back("   ");
    }

    buildBoard();
}

/*
 * Destructor
 */
Board::~Board() {

}

/*
 * This method constructs the board using the 3 vectors.  Each
 * vector represents a row of the board.  The board will be in
 * the form:
 *  P | P | P
 * -----------
 *  P | P | P
 * -----------
 *  P | P | P
 * Where P is an "X", "O" or " ".
 */
void Board::buildBoard() {
    std::cout << row1.at(0) << "|" << row1.at(1) << "|" << row1.at(2) << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << row2.at(0) << "|" << row2.at(1) << "|" << row2.at(2) << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << row3.at(0) << "|" << row3.at(1) << "|" << row3.at(2) << std::endl;
    std::cout << std::endl;
}

/*
 * This method clears the board by setting the values in the 3 vectors
 * to "   ".  After clearing all pieces on the board, the board is
 * rebuilt.
 */
void Board::clearBoard() {
    for (int i = 0; i < 3; i++) {
        row1.at(i) = "   ";
        row2.at(i) = "   ";
        row3.at(i) = "   ";
    }

    buildBoard();
}

/*
 * This method places the next piece on the board and returns true.
 * However, if a piece exists in row row and in column col, a
 * warning message is printed and this method returns false.  The
 * board is also rebuilt at the end of the method.
 */
bool Board::addPiece(int row, int col, char piece) {
    bool valid = true;

    std::string p(1, piece);
    if (row == 1) {
        // If valid:
        if (row1.at(col - 1) == "   ") {
            row1.at(col - 1) = " " + p + " ";
        }
        // If invalid:
        else {
            std::cout << "Invalid move; there is already a piece at (" << row << ", " << col << ")." << std::endl;
            std::cout << std::endl;
            valid = false;
        }
    }
    else if (row == 2) {
        // If valid:
        if (row2.at(col - 1) == "   ") {
            row2.at(col - 1) = " " + p + " ";
        }
        // If invalid:
        else {
            std::cout << "Invalid move; there is already a piece at (" << row << ", " << col << ")." << std::endl;
            std::cout << std::endl;
            valid = false;
        }
    }
    else {
        // If valid:
        if (row3.at(col - 1) == "   ") {
            row3.at(col - 1) = " " + p + " ";
        }
        // If invalid:
        else {
            std::cout << "Invalid move; there is already a piece at (" << row << ", " << col << ")." << std::endl;
            std::cout << std::endl;
            valid = false;
        }
    }

    buildBoard();
    return valid;
}

/*
 * This method determines whether a player has won the round.  If
 * player 1 has won the round, the character 'X' is returned.  If
 * player 2 has won the round, the character 'O' is returned.  If
 * neither player has won the game, character ' ' is returned.  A
 * player is determined to have won the round if they have 3 pieces
 * in a row, either vertically, horizontally or diagonally.
 */
char Board::hasWon() {
    //  P |   |
    // -----------
    //  P |   |
    // -----------
    //  P |   |
    if (row1.at(0) == row2.at(0) && row1.at(0) == row3.at(0)) {
        return row1.at(0)[1];
    }
    //    | P |
    // -----------
    //    | P |
    // -----------
    //    | P |
    else if (row1.at(1) == row2.at(1) && row1.at(1) == row3.at(1)) {
        return row1.at(1)[1];
    }
    //    |   | P
    // -----------
    //    |   | P
    // -----------
    //    |   | P
    else if (row1.at(2) == row2.at(2) && row1.at(2) == row3.at(2)) {
        return row1.at(2)[1];
    }
    //  P | P | P
    // -----------
    //    |   |
    // -----------
    //    |   |
    else if (row1.at(0) == row1.at(1) && row1.at(0) == row1.at(2)) {
        return row1.at(0)[1];
    }
    //    |   |
    // -----------
    //  P | P | P
    // -----------
    //    |   |
    else if (row2.at(0) == row2.at(1) && row2.at(0) == row2.at(2)) {
        return row2.at(0)[1];
    }
    //    |   |
    // -----------
    //    |   |
    // -----------
    //  P | P | P
    else if (row3.at(0) == row3.at(1) && row3.at(0) == row3.at(2)) {
        return row3.at(0)[1];
    }
    //  P |   |
    // -----------
    //    | P |
    // -----------
    //    |   | P
    else if (row1.at(0) == row2.at(1) && row1.at(0) == row3.at(2)) {
        return row1.at(0)[1];
    }
    //    |   | P
    // -----------
    //    | P |
    // -----------
    //  P |   |
    else if (row1.at(2) == row2.at(1) && row1.at(2) == row3.at(0)) {
        return row1.at(2)[1];
    }
    // There are not three in a row.
    else {
        return ' ';
    }
}

/*
 * This method returns true if the board is full (there is a
 * piece in all 9 spots); false otherwise.  This method is used
 * to determine if the round has ended in a draw.
 */
bool Board::isFull() {
    // If there is any blank spot on the board, false is returned.
    for (int i = 0; i < 3; i++) {
        if (row1.at(i) == "   ") {
            return false;
        }
        if (row2.at(i) == "   ") {
            return false;
        }
        if (row3.at(i) == "   ") {
            return false;
        }
    }
    // If all spots on the board have a piece on it, true is returned.
    return true;
}
