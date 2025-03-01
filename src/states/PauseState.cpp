#include "../../include/states/PauseState.h"
#include "../../include/states/GameplayState.h"
#include "../../include/states/MainMenuState.h"
#include "../../include/engine/GameEngine.h"
#include "../../include/states/CommandCodes.h"
#include <QDebug>
#include <string>

void PauseState::enterState(GameEngine* gameEngine) {
    qDebug() << "PauseState: Entering Pause State";
    gameEngine->ui->showInGameMenu();
}

void PauseState::exitState(GameEngine* gameEngine) {
    qDebug() << "PauseState: Exiting Pause State";
}

void PauseState::handleInput(GameEngine* gameEngine, const std::string& input) {
    int command = std::stoi(input);
    if (command == static_cast<int>(CommandCode::RestartGame)) {
        qDebug() << "PauseState: Restarting game";
        gameEngine->restartGame();
    }
    else if (command == static_cast<int>(CommandCode::ReturnToMainMenu)) {
        qDebug() << "PauseState: Returning to Main Menu";
        gameEngine->returnToMainMenu();
    }
    else if (command == static_cast<int>(CommandCode::ExitGame)) {
        qDebug() << "PauseState: Exiting game";
        gameEngine->exitGame();
    }
    else {
        qDebug() << "PauseState: Unknown input -" << QString::fromStdString(input);
    }
}
