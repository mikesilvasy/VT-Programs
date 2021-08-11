#include "TicTacToe.h"
#include "Board.h"
#include <iostream>
#include <fstream>

bool player1Turn = true;
std::string player1, player2;
int player1Wins = 0;
int player2Wins = 0;

/*
 * Constructor
 */
TicTacToe::TicTacToe() {

}

/*
 * Destructor
 */
TicTacToe::~TicTacToe() {

}

/*
 * This method prints the rules of tic-tac-toe to the console.  The rules
 * were gathered from www.exploratorium.edu/brain_explorer/tictactoe.html.
 */
void TicTacToe::printRules() {
    // Opens the file using the file name as a string.
    std::ifstream rulesFile("tictactoe_rules.txt");
    // Reads the first line of the file.
    std::string nextLine;
    getline(rulesFile, nextLine);

    // Reads the file line by line until there are no more lines to read
    // in the file.
    while (rulesFile) {
        std::cout << nextLine << std::endl;
        getline(rulesFile, nextLine);
    }

    printSpaceDivider();
}

/*
 * This method prints the directions of this particular tic-tac-toe game to
 * the console.
 */
void TicTacToe::printDirections() {
    std::cout << "To place a piece, you will need to enter the row and column in which you wish to place it." << std::endl;
    std::cout << "The first row is row 1, the second row is row 2 and the third row is row 3; this applies for the columns as well." << std::endl;
    std::cout << "For example, to enter a piece in the top right corner, the row would be 1 and the column would be 3." << std::endl;
}

/*
 * This method prints a divider of 10 lines to the console.
 */
void TicTacToe::printSpaceDivider() {
    for (int i = 0; i < 10; i++) {
        std::cout << std::endl;
    }
}

/*
 * This method prints the score of the game to the console.  The score is
 * printed in the form:
 * --------------
 *   SCOREBOARD
 * --------------
 * player1 - # wins
 * player2 - # wins
 * --------------
 */
void TicTacToe::printScore() {
    std::cout << "--------------" << std::endl;
    std::cout << "  SCOREBOARD" << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << player1 << " - " << player1Wins << std::endl;
    std::cout << player2 << " - " << player2Wins << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << std::endl;
}

/*
 * This method executes the next turn in the game.  If it is player 1's
 * turn, an X piece will be placed on the board.  If it is player 2's
 * turn, an O piece will be placed on the board.
 */
void TicTacToe::nextTurn(Board board) {
    printSpaceDivider();

    // Lets the players know whose turn it is.
    if (player1Turn) {
        std::cout << player1 << ", it's your turn!" << std::endl;
    }
    else {
        std::cout << player2 << ", it's your turn!" << std::endl;
    }
    // Prompts the user to enter where they would like to place their next
    // piece.  This is done by entering what row and column the player wishes
    // to place their piece.  The row and column numbers are saved for future
    // use.
    int row, col;
    std::cout << "Enter the row:  ";
    std::cin >> row;
    std::cout << "Enter the column:  ";
    std::cin >> col;
    std::cout << std::endl;

    // Places the piece on the board if there is not already a piece there.
    // If a piece is already there, the same player is asked to place the
    // piece again.
    if (player1Turn) {
        bool validTurn = board.addPiece(row, col, 'X');
        if (!validTurn) {
            nextTurn(board);
        }
    }
    else {
        bool validTurn = board.addPiece(row, col, 'O');
        if (!validTurn) {
            nextTurn(board);
        }
    }
}

/*
 * This method executes one round of tic-tac-toe.  A single round
 * will end in a win for player 1, a win for player 2 or a draw.
 */
void TicTacToe::playRound(Board board) {
    // The round is played as long as no player has won and the game
    // has not ended in a draw.
    while (board.hasWon() == ' ' && !board.isFull()) {
        nextTurn(board);
        player1Turn = !player1Turn;
    }

    // Lets the players know the outcome of the round.
    if (board.hasWon() == 'X') {
        std::cout << player1 << " has won!" << std::endl;
        player1Wins += 1;
    }
    else if (board.hasWon() == 'O') {
        std::cout << player2 << " has won!" << std::endl;
        player2Wins += 1;
    }
    else {
        std::cout << "Draw!  " << player1 << " and " << player2 << " tied!" << std::endl;
    }
}

/* This method executes a complete game of tic-tac-toe.  The game is
 * played round-by-round until the players wish to no longer play.
 * After each round, the scoreboard will be printed to the console so
 * the players are aware of how many games they have both won.
 */
void TicTacToe::playTicTacToe() {
    printRules();

    // Prompts the players to enter their names.  They will be saved for
    // future use.
    std::cout << "Enter Player 1 Name:  ";
    std::cin >> player1;
    std::cout << "Enter Player 2 Name:  ";
    std::cin >> player2;
    std::cout << std::endl;

    // Lets the players know that player 1 will be X's and that player 2
    // will be O's.
    std::cout << player1 << " will be X's." << std::endl;
    std::cout << player2 << " will be O's." << std::endl;
    std::cout << std::endl;

    // Creates a new Board.
    Board ticTacToe;

    printDirections();

    // The game will be played round-by-round until the players no longer
    // want to play.
    char keepPlaying = 'y';
    bool game = true;
    while (keepPlaying == 'y') {
        player1Turn = game;
        playRound(ticTacToe);

        // Asks the players if they would like to keep playing.
        std::cout << std::endl;
        std::cout << "Would you like to play another game (y/n):  ";
        std::cin >> keepPlaying;
        std::cout << std::endl;

        printScore();

        // If the players wish to play again, the board is cleared so that
        // a new round may begin.
        if (keepPlaying == 'y') {
            ticTacToe.clearBoard();
        }

        game = !game;
    }
}

