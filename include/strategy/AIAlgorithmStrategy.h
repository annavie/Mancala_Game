#include "../core/Board.h"
#include "../core/Player.h"
#include "AlgorithmConstants.h"
#include <limits>
#include <vector>
#include"PlayerStrategy.h"
class AIAlgorithmStrategy : public PlayerStrategy {
public:
    int selectPit(Board* board, Player* player) override {
        int bestPit = -1;
        int maxScore = std::numeric_limits<int>::min();
        int start = (player->getPlayerNumber() == 1) ? AIConstants::kPlayer1Start : AIConstants::kPlayer2Start;
        int end = (player->getPlayerNumber() == 1) ? AIConstants::kPlayer1End : AIConstants::kPlayer2End;
        for (int i = start; i < end; ++i) {
            if (!board->isValidMove(i, player)) {
                continue;
            }
            int score = evaluateMove(board, player, i);
            if (score > maxScore) {
                maxScore = score;
                bestPit = i;
            }
        }
        return bestPit;
    }

private:
    int evaluateMove(Board* board, Player* player, int pitIndex) {
        Board simulatedBoard = *board;
        simulatedBoard.makeMove(pitIndex, player);
        int score = 0;
        int playerStore = (player->getPlayerNumber() == 1) ? simulatedBoard.getPlayer1Store() : simulatedBoard.getPlayer2Store();
        score += playerStore * AIConstants::kStoreWeight;
        if (simulatedBoard.isValidMove(pitIndex, player) && simulatedBoard.isGameOver()) {
            score += (playerStore - board->getPlayer1Store()) * AIConstants::kBonusMultiplier;
        }
        if (leavesOpponentAdvantage(simulatedBoard, player)) {
            score -= AIConstants::kOpponentAdvantagePenalty;
        }
        return score;
    }

    bool leavesOpponentAdvantage(const Board& board, Player* player) {
        int opponentStart = (player->getPlayerNumber() == 1) ? AIConstants::kPlayer2Start : AIConstants::kPlayer1Start;
        int opponentEnd = (player->getPlayerNumber() == 1) ? AIConstants::kPlayer2End : AIConstants::kPlayer1End;
        for (int i = opponentStart; i < opponentEnd; ++i) {
            if (board.isValidMove(i, player)) {
                return true;
            }
        }
        return false;
    }
};
