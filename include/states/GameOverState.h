#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"

class GameOverState : public State {
public:
    GameOverState() {}
    ~GameOverState() override {}

    void enterState(GameEngine* gameEngine) override;
    void exitState(GameEngine* gameEngine) override;
    void handleInput(GameEngine* gameEngine, const std::string& input) override;
};

#endif // GAMEOVERSTATE_H
