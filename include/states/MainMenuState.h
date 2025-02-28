#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include<QObject>

class MainMenuState : public State {

public:
    explicit MainMenuState() : State() {}

    void enterState(GameEngine* gameEngine) override ;

    void exitState(GameEngine* gameEngine) override;

    void handleInput(GameEngine* gameEngine, const std::string& input) override;
};

#endif // MAINMENUSTATE_H
