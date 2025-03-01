#include "../../include/states/SettingsState.h"
#include "../../include/engine/GameEngine.h"
#include "../../include/states/MainMenuState.h"
#include "../../include/states/CommandCodes.h"   
#include <QDebug>
#include <string>

void SettingsState::enterState(GameEngine* gameEngine) {
    qDebug() << "SettingsState: Entering Settings";
    gameEngine->ui->displaySettings();
}

void SettingsState::exitState(GameEngine* gameEngine) {
    qDebug() << "SettingsState: Exiting Settings";
}

void SettingsState::handleInput(GameEngine* gameEngine, const std::string& input) {
    int command = std::stoi(input);
    if (command == static_cast<int>(CommandCode::Settings)) {
        qDebug() << "SettingsState: Saving settings";
    }
    else if (command == static_cast<int>(CommandCode::ReturnToMainMenu)) {
        qDebug() << "SettingsState: Returning to Main Menu";
        gameEngine->changeState(std::make_unique<MainMenuState>());
    }
    else {
        qDebug() << "SettingsState: Unknown input -" << QString::fromStdString(input);
    }
}
