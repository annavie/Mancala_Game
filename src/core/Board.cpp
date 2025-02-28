#include "Board.h"
#include "Player.h"

bool Board::makeMove(int pitIndex, Player* player) {
    int playerNumber = player->getPlayerNumber();
    int stones = pits[pitIndex].removeStones();
    if (stones == 0) {
        return false;
    }

    int currentIndex = pitIndex;
    while (stones > 0) {
        currentIndex = (currentIndex + 1) % 14;

        if (currentIndex == 6 && playerNumber == 2) continue;
        if (currentIndex == 13 && playerNumber == 1) continue;
        if (currentIndex < 12) {
            pits[currentIndex].addStones(1);
        } else if (currentIndex == 12) {
            player1Store += 1;
        } else if (currentIndex == 13) {
            player2Store += 1;
        }

        stones--;
    }

    if ((playerNumber == 1 && currentIndex == 12) ||
        (playerNumber == 2 && currentIndex == 13)) {
        return true;
    }

    if (currentIndex < 12 && pits[currentIndex].getStones() == 1) {
        if ((playerNumber == 1 && currentIndex < 6) ||
            (playerNumber == 2 && currentIndex >= 6)) {
            int oppositeIndex = 11 - currentIndex;
            int capturedStones = pits[oppositeIndex].removeStones();
            if (playerNumber == 1) {
                player1Store += capturedStones + 1;
            } else {
                player2Store += capturedStones + 1;
            }
            pits[currentIndex].removeStones();
        }
    }

    return false;
}

bool Board::isGameOver() const {
    bool player1Empty = true;
    for(int i = 0; i < 6; ++i) {
        if(pits[i].getStones() > 0) {
            player1Empty = false;
            break;
        }
    }

    bool player2Empty = true;
    for(int i = 6; i < 12; ++i) {
        if(pits[i].getStones() > 0) {
            player2Empty = false;
            break;
        }
    }

    return player1Empty || player2Empty;
}

void Board::finalizeBoard() {
    if(isGameOver()) {
        int remainingStones = 0;
        if(player1Store == 0) {
            for(int i = 6; i < 12; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player2Store += remainingStones;
        }
        else {
            for(int i = 0; i < 6; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player1Store += remainingStones;
        }
    }
}
bool Board::isValidMove(int pitIndex, Player* player) const {
    int playerNumber = player->getPlayerNumber();

    if (pitIndex < 0 || pitIndex >= 12) {
        return false;
    }

    if ((playerNumber == 1 && pitIndex >= 6) ||
        (playerNumber == 2 && pitIndex < 6)) {
        return false;
    }
    if (pits[pitIndex].getStones() == 0) {
        return false;
    }

    return true;
}
