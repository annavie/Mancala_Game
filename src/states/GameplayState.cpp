#include "GameplayState.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameEngine.h"
#include "PauseState.h"
#include <QDebug>

void GameplayState::enterState(GameEngine* gameEngine) {
    qDebug() << "GameplayState: Entering Gameplay";

    gameEngine->ui->displayGameplay();

    gameEngine->ui->renderBoard(gameEngine->getBoard());
}

void GameplayState::exitState(GameEngine* gameEngine) {
    qDebug() << "GameplayState: Exiting Gameplay";
}

void GameplayState::handleInput(GameEngine* gameEngine, const std::string& input) {
    if (input == "-4") {
        qDebug() << "GameplayState: Pausing game";
        gameEngine->changeState(std::make_unique<PauseState>());
    } else {
        qDebug() << "GameplayState: Unknown input -" << QString::fromStdString(input);
    }
}
