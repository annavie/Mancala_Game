#ifndef BOARD_H
#define BOARD_H

#include "Pit.h"
#include <vector>
#include<iostream>

class Player;

class Board  {
private:
    std::vector<Pit> pits; 
    int player1Store;
    int player2Store;

public:
    Board() : pits(12, Pit()), player1Store(0), player2Store(0) {
    }

    const std::vector<Pit>& getPits() const { return pits; }
    Pit& getPit(int index) { return pits[index]; }
    const Pit& getPit(int index) const { return pits[index]; }

    int getPlayer1Store() const { return player1Store; }
    int getPlayer2Store() const { return player2Store; }

    void addToPlayer1Store(int stones) { player1Store += stones; }
    void addToPlayer2Store(int stones) { player2Store += stones; }
    bool isValidMove(int pitIndex,Player* player) const;


    void resetBoard() {
       // std::cout <<"reste board";
        for(auto& pit : pits) {
            pit.setStones(4);
        }
        player1Store = 0;
        player2Store = 0;

    }

    bool makeMove(int pitIndex, Player* player);
    bool isGameOver() const;
    void finalizeBoard();

};

#endif // BOARD_H
