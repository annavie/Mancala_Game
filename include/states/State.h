#ifndef STATE_H
#define STATE_H

#include <string>

class GameEngine;

class State {
public:
    virtual ~State() {}
    virtual void enterState(GameEngine* gameEngine) = 0;
    virtual void exitState(GameEngine* gameEngine) = 0;
    virtual void handleInput(GameEngine* gameEngine, const std::string& input) = 0;
};

#endif // STATE_H
