#include "Player.h"
#include "PlayerStrategy.h"
#include "Board.h"

Player::Player(const std::string& name,
               int playerNumber,
               std::unique_ptr<PlayerStrategy> strategy,
               bool isAI)
    : name(name),
    playerNumber(playerNumber),
    strategy(std::move(strategy)),
    isAI(isAI)
{
}

const std::string& Player::getName() const {
    return name;
}

int Player::getPlayerNumber() const {
    return playerNumber;
}

bool Player::isAIPlayer() const {
    return isAI;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

int Player::makeMove(Board* board) {
    if (strategy) {
        return strategy->selectPit(board, this);
    }
    return -1;
}
