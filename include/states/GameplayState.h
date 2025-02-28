// GameplayState.h
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"

class GameplayState : public State {
public:
    GameplayState() {}
    ~GameplayState() override {}

    void enterState(GameEngine* gameEngine) override;
    void exitState(GameEngine* gameEngine) override;
    void handleInput(GameEngine* gameEngine, const std::string& input) override;

private:
    void showInGameMenu(GameEngine* gameEngine);
};

#endif // GAMEPLAYSTATE_H
