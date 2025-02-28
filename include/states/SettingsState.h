#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include <iostream>

class SettingsState : public State {
public:
    void enterState(GameEngine* gameEngine) override ;
    void exitState(GameEngine* gameEngine) override;

    void handleInput(GameEngine* gameEngine, const std::string& input) override;
};

#endif // SETTINGSSTATE_H
