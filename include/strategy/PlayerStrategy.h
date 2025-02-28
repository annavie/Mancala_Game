#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

class Board;
class Player;

class PlayerStrategy {
public:
    virtual ~PlayerStrategy() {}
    virtual int selectPit(Board* board, Player* player) = 0;
};

#endif // PLAYERSTRATEGY_H
