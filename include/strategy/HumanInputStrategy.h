#ifndef HUMANINPUTSTRATEGY_H
#define HUMANINPUTSTRATEGY_H

#include "PlayerStrategy.h"
#include <iostream>
#include"../core/Player.h"
#include"../core/Board.h"
class HumanInputStrategy : public PlayerStrategy {
public:
    int selectPit(Board* board, Player* player) override {
        int pit = -1;
        while(true) {
            std::cout << player->getName() << " (Player " << player->getPlayerNumber() << "), "
                      << "select a pit (1-6): ";
            std::cin >> pit;
            if(std::cin.fail() || pit < 1 || pit > 6) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
                continue;
            }
            pit -= 1;
            if(board->isValidMove(pit, player)) {
                return pit;
            } else {
                std::cout << "Invalid pit selection or pit is empty. Try again.\n";
            }
        }
    }
};

#endif // HUMANINPUTSTRATEGY_H
