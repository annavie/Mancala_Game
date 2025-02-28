#ifndef SCORETRACKER_H
#define SCORETRACKER_H

#include "Board.h"

class ScoreTracker {
public:
    ScoreTracker() : player1Score(0), player2Score(0) {}

    void updateScores(const Board& board) {
        player1Score = board.getPlayer1Store();
        player2Score = board.getPlayer2Store();
    }

    int getPlayer1Score() const { return player1Score; }
    int getPlayer2Score() const { return player2Score; }

    void reset() {
        player1Score = 0;
        player2Score = 0;
    }

private:
    int player1Score;
    int player2Score;
};

#endif // SCORETRACKER_H
