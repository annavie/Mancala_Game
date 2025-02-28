#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <memory>
#include "State.h"

class GameEngine;

class GameStateManager {
public:
    explicit GameStateManager(GameEngine* engine);
    ~GameStateManager();

    void changeState(std::unique_ptr<State> newState);
    void handleInput(const std::string& input);

private:
    GameEngine* gameEngine;
    std::unique_ptr<State> currentState;
};

#endif // GAMESTATEMANAGER_H
