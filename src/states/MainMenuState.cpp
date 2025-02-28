// MainMenuState.cpp
#include "MainMenuState.h"
#include "GameEngine.h"
#include "GameplayState.h"
#include "SettingsState.h"
#include "GameOverState.h"
#include <QDebug>

void MainMenuState::enterState(GameEngine* gameEngine) {
    qDebug() << "MainMenuState: Entering Main Menu";
    gameEngine->ui->displayMainMenu();
}

void MainMenuState::exitState(GameEngine* gameEngine) {
    qDebug() << "MainMenuState: Exiting Main Menu";
}

void MainMenuState::handleInput(GameEngine* gameEngine, const std::string& input) {
    if (input == "-1") {
        qDebug() << "MainMenuState: Start Game selected";
        gameEngine->changeState(std::make_unique<GameplayState>());
    }
    else if (input == "-2") {
        qDebug() << "MainMenuState: Settings selected";
        gameEngine->changeState(std::make_unique<SettingsState>());
    }
    else if (input == "-3") {
        qDebug() << "MainMenuState: Exit Game selected";
        gameEngine->exitGame();
    }
    else {
        qDebug() << "MainMenuState: Unknown input -" << QString::fromStdString(input);
    }
}
