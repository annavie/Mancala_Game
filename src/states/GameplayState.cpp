#include "../../include/states/GameplayState.h"
#include "../../include/states/GameOverState.h"
#include "../../include/states/MainMenuState.h"
#include "../../include/engine/GameEngine.h"
#include "../../include/states/PauseState.h"
#include "../../include/states/CommandCodes.h"
#include <QDebug>
#include <string>

void GameplayState::enterState(GameEngine* gameEngine) {
    qDebug() << "GameplayState: Entering Gameplay";
    gameEngine->ui->displayGameplay();
    gameEngine->ui->renderBoard(gameEngine->getBoard());
}

void GameplayState::exitState(GameEngine* gameEngine) {
    qDebug() << "GameplayState: Exiting Gameplay";
}

void GameplayState::handleInput(GameEngine* gameEngine, const std::string& input) {
    int command = std::stoi(input);
    if (command == static_cast<int>(CommandCode::Pause)) {
        qDebug() << "GameplayState: Pausing game";
        gameEngine->changeState(std::make_unique<PauseState>());
    }
    else {
        qDebug() << "GameplayState: Unknown input -" << QString::fromStdString(input);
    }
}
