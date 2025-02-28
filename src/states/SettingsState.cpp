#include "SettingsState.h"
#include "GameEngine.h"
#include "MainMenuState.h"
#include <QDebug>

void SettingsState::enterState(GameEngine* gameEngine) {
    qDebug() << "SettingsState: Entering Settings";
    gameEngine->ui->displaySettings();
}

void SettingsState::exitState(GameEngine* gameEngine) {
    qDebug() << "SettingsState: Exiting Settings";
}

void SettingsState::handleInput(GameEngine* gameEngine, const std::string& input) {
    if (input == "-2") {
        qDebug() << "SettingsState: Saving settings";
    }
    else if (input == "-4") {
        qDebug() << "SettingsState: Returning to Main Menu";
        gameEngine->changeState(std::make_unique<MainMenuState>());
    }
    else {
        qDebug() << "SettingsState: Unknown input -" << QString::fromStdString(input);
    }
}
