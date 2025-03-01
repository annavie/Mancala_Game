#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "GameEngine.h"
#include "CommandCodes.h"
#include <QDebug>
#include <string>

void GameOverState::enterState(GameEngine* gameEngine) {
    qDebug() << "GameOverState: Entering Game Over State";
    auto scores = gameEngine->getScores();
    gameEngine->ui->displayGameOver(scores.first, scores.second);
}

void GameOverState::exitState(GameEngine* gameEngine) {
    qDebug() << "GameOverState: Exiting Game Over State";
}

void GameOverState::handleInput(GameEngine* gameEngine, const std::string& input) {
    int command = std::stoi(input);
    if (command == static_cast<int>(CommandCode::RestartGame)) {
        qDebug() << "GameOverState: Restarting Game";
        gameEngine->restartGame();
    }
    else if (command == static_cast<int>(CommandCode::ReturnToMainMenu)) {
        qDebug() << "GameOverState: Returning to Main Menu";
        gameEngine->changeState(std::make_unique<MainMenuState>());
    }
    else {
        qDebug() << "GameOverState: Unknown input -" << QString::fromStdString(input);
    }
}
