#include "../../include/states/MainMenuState.h"
#include "../../include/engine/GameEngine.h"
#include "../../include/states/GameplayState.h"
#include "../../include/states/SettingsState.h"
#include "../../include/states/GameOverState.h"
#include "../../include/states/CommandCodes.h"
#include <QDebug>
#include <string>

void MainMenuState::enterState(GameEngine* gameEngine) {
    qDebug() << "MainMenuState: Entering Main Menu";
    gameEngine->ui->displayMainMenu();
}

void MainMenuState::exitState(GameEngine* gameEngine) {
    qDebug() << "MainMenuState: Exiting Main Menu";
}

void MainMenuState::handleInput(GameEngine* gameEngine, const std::string& input) {
    int command = std::stoi(input);
    if (command == static_cast<int>(CommandCode::StartGame)) {
        qDebug() << "MainMenuState: Start Game selected";
        gameEngine->changeState(std::make_unique<GameplayState>());
    }
    else if (command == static_cast<int>(CommandCode::Settings)) {
        qDebug() << "MainMenuState: Settings selected";
        gameEngine->changeState(std::make_unique<SettingsState>());
    }
    else if (command == static_cast<int>(CommandCode::ExitGame)) {
        qDebug() << "MainMenuState: Exit Game selected";
        gameEngine->exitGame();
    }
    else {
        qDebug() << "MainMenuState: Unknown input -" << QString::fromStdString(input);
    }
}
