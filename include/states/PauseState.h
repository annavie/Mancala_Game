#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"

class PauseState : public State {
public:
    void enterState(GameEngine* gameEngine) override;
    void exitState(GameEngine* gameEngine) override;
    void handleInput(GameEngine* gameEngine, const std::string& input) override;
};

#endif // PAUSESTATE_H
