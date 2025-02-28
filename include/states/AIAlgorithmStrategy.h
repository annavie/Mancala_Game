#include "Board.h"
#include "Player.h"
#include <limits>
#include <vector>

class AIAlgorithmStrategy : public PlayerStrategy {
public:
    int selectPit(Board* board, Player* player) override {
        int bestPit = -1;
        int maxScore = std::numeric_limits<int>::min();

        int start = (player->getPlayerNumber() == 1) ? 0 : 6;
        int end = (player->getPlayerNumber() == 1) ? 6 : 12;

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
        int opponentStore = (player->getPlayerNumber() == 1) ? simulatedBoard.getPlayer2Store() : simulatedBoard.getPlayer1Store();

        score += playerStore * 10;

        if (simulatedBoard.isValidMove(pitIndex, player) && simulatedBoard.isGameOver()) {
            score += (playerStore - board->getPlayer1Store()) * 20;
        }

        if (leavesOpponentAdvantage(simulatedBoard, player)) {
            score -= 10;
        }

        return score;
    }

    bool leavesOpponentAdvantage(const Board& board, Player* player) {
        int opponentStart = (player->getPlayerNumber() == 1) ? 6 : 0;
        int opponentEnd = (player->getPlayerNumber() == 1) ? 12 : 6;

        for (int i = opponentStart; i < opponentEnd; ++i) {
            if (board.isValidMove(i, player)) {
                return true;
            }
        }

        return false;
    }
};
