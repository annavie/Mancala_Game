#include "PauseState.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "GameEngine.h"
#include <QDebug>

void PauseState::enterState(GameEngine* gameEngine) {
    qDebug() << "PauseState: Entering Pause State";
    gameEngine->ui->showInGameMenu();
}

void PauseState::exitState(GameEngine* gameEngine) {
    qDebug() << "PauseState: Exiting Pause State";
}

void PauseState::handleInput(GameEngine* gameEngine, const std::string& input) {
    if (input == "-5") {
        qDebug() << "PauseState: Restarting game";

        gameEngine->restartGame();

    } else if (input == "-4") {
        qDebug() << "PauseState: Returning to Main Menu";

        gameEngine->returnToMainMenu();

    } else if (input == "-3") {
        qDebug() << "PauseState: Exiting game";
        gameEngine->exitGame();

    } else {
        qDebug() << "PauseState: Unknown input -" << QString::fromStdString(input);
    }
}
