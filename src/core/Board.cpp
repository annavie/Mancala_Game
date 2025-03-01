#include "../../include/core/Board.h"
#include "../../include/core/Player.h"
#include "../../include/core/BoardConstants.h"
#include <iostream>

bool Board::makeMove(int pitIndex, Player* player) {
    int playerNumber = player->getPlayerNumber();
    int stones = pits[pitIndex].removeStones();
    if (stones == 0) {
        return false;
    }
    int currentIndex = pitIndex;
    while (stones > 0) {
        currentIndex = (currentIndex + 1) % BoardConstants::kTotalPositions;
        if (currentIndex == BoardConstants::kPlayer1StoreIndex && playerNumber == 2) continue;
        if (currentIndex == BoardConstants::kPlayer2StoreIndex && playerNumber == 1) continue;
        if (currentIndex < BoardConstants::kPlayablePits) {
            pits[currentIndex].addStones(1);
        }
        else if (currentIndex == BoardConstants::kPlayer1StoreIndex) {
            player1Store += 1;
        }
        else if (currentIndex == BoardConstants::kPlayer2StoreIndex) {
            player2Store += 1;
        }
        stones--;
    }
    if ((playerNumber == 1 && currentIndex == BoardConstants::kPlayer1StoreIndex) ||
        (playerNumber == 2 && currentIndex == BoardConstants::kPlayer2StoreIndex)) {
        return true;
    }
    if (currentIndex < BoardConstants::kPlayablePits && pits[currentIndex].getStones() == 1) {
        if ((playerNumber == 1 && currentIndex < BoardConstants::kPitsPerPlayer) ||
            (playerNumber == 2 && currentIndex >= BoardConstants::kPitsPerPlayer)) {
            int oppositeIndex = BoardConstants::kMaxPitIndex - currentIndex;
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
    for (int i = 0; i < BoardConstants::kPitsPerPlayer; ++i) {
        if (pits[i].getStones() > 0) {
            player1Empty = false;
            break;
        }
    }
    bool player2Empty = true;
    for (int i = BoardConstants::kPitsPerPlayer; i < BoardConstants::kPlayablePits; ++i) {
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
            for (int i = BoardConstants::kPitsPerPlayer; i < BoardConstants::kPlayablePits; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player2Store += remainingStones;
        }
        else {
            for (int i = 0; i < BoardConstants::kPitsPerPlayer; ++i) {
                remainingStones += pits[i].removeStones();
            }
            player1Store += remainingStones;
        }
    }
}

bool Board::isValidMove(int pitIndex, Player* player) const {
    int playerNumber = player->getPlayerNumber();
    if (pitIndex < 0 || pitIndex >= BoardConstants::kPlayablePits) {
        return false;
    }
    if ((playerNumber == 1 && pitIndex >= BoardConstants::kPitsPerPlayer) ||
        (playerNumber == 2 && pitIndex < BoardConstants::kPitsPerPlayer)) {
        return false;
    }
    if (pits[pitIndex].getStones() == 0) {
        return false;
    }
    return true;
}
