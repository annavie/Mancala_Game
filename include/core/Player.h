#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

class PlayerStrategy;
class Board;

class Player {
private:
    std::string name;
    int playerNumber;
    std::unique_ptr<PlayerStrategy> strategy;
    bool isAI;

public:
    Player(const std::string& name,
           int playerNumber,
           std::unique_ptr<PlayerStrategy> strategy,
           bool isAI);

    const std::string& getName() const;
    int getPlayerNumber() const;
    bool isAIPlayer() const;

    void setName(const std::string& newName);

    int makeMove(Board* board);
};

#endif // PLAYER_H
