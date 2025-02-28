#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "GameEngine.h"
#include <QDebug>

void GameOverState::enterState(GameEngine* gameEngine) {
    qDebug() << "GameOverState: Entering Game Over State";
    auto scores = gameEngine->getScores();
    gameEngine->ui->displayGameOver(scores.first, scores.second);
}

void GameOverState::exitState(GameEngine* gameEngine) {
    qDebug() << "GameOverState: Exiting Game Over State";
}

void GameOverState::handleInput(GameEngine* gameEngine, const std::string& input) {
    if (input == "-5") {
        qDebug() << "GameOverState: Restarting Game";
        gameEngine->restartGame();
    }
    else if (input == "-6") {
        qDebug() << "GameOverState: Returning to Main Menu";
        gameEngine->changeState(std::make_unique<MainMenuState>());
    }
    else {
        qDebug() << "GameOverState: Unknown input -" << QString::fromStdString(input);
    }
}
