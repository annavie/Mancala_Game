#include "Board.h"
#include "Player.h"
#include "BoardConstants.h"
#include <iostream>

bool Board::makeMove(int pitIndex, Player* player) {
    int playerNumber = player->getPlayerNumber();
    int stones = pits[pitIndex].removeStones();
    if (stones == 0) {
        return false;
    }
    int currentIndex = pitIndex;
    while (stones > 0) {
        currentIndex = (currentIndex + 1) % kTotalPositions;
        if (currentIndex == kPlayer1StoreIndex && playerNumber == 2) continue;
        if (currentIndex == kPlayer2StoreIndex && playerNumber == 1) continue;
        if (currentIndex < kPlayablePits) {
            pits[currentIndex].addStones(1);
        }
        else if (currentIndex == kPlayer1StoreIndex) {
            player1Store += 1;
        }
        else if (currentIndex == kPlayer2StoreIndex) {
            player2Store += 1;
        }
        stones--;
    }
    if ((playerNumber == 1 && currentIndex == kPlayer1StoreIndex) ||
        (playerNumber == 2 && currentIndex == kPlayer2StoreIndex)) {
        return true;
    }
    if (currentIndex < kPlayablePits && pits[currentIndex].getStones() == 1) {
        if ((playerNumber == 1 && currentIndex < kPitsPerPlayer) ||
            (playerNumber == 2 && currentIndex >= kPitsPerPlayer)) {
            int oppositeIndex = kMaxPitIndex - currentIndex;
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
    for (int i = 0; i < kPitsPerPlayer; ++i) {
        if (pits[i].getStones() > 0) {
            player1Empty = false;
            break;
        }
    }
    bool player2Empty = true;
    for (int i = kPitsPerPlayer; i < kPlayablePits; ++i) {
        if (pits[i].getStones() > 0) {
            player2Empty = false;
            break;
        }
    }
    return player1Empty || player2Empty;
}

void Board::finalizeBoard() {
    if (isGameOver()) {
        int remainingStones = 0;
        if (player1Store == 0) {
            for (int i = kPitsPerPlayer; i < kPlayablePits; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player2Store += remainingStones;
        }
        else {
            for (int i = 0; i < kPitsPerPlayer; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player1Store += remainingStones;
        }
    }
}

bool Board::isValidMove(int pitIndex, Player* player) const {
    int playerNumber = player->getPlayerNumber();
    if (pitIndex < 0 || pitIndex >= kPlayablePits) {
        return false;
    }
    if ((playerNumber == 1 && pitIndex >= kPitsPerPlayer) ||
        (playerNumber == 2 && pitIndex < kPitsPerPlayer)) {
        return false;
    }
    if (pits[pitIndex].getStones() == 0) {
        return false;
    }
    return true;
}
