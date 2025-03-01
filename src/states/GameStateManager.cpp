#include "../../include/states/GameStateManager.h"
#include "../../include/engine/GameEngine.h"

GameStateManager::GameStateManager(GameEngine* engine)
    : gameEngine(engine), currentState(nullptr) {}

GameStateManager::~GameStateManager() {
    if(currentState) {
        currentState->exitState(gameEngine);
    }
}

void GameStateManager::changeState(std::unique_ptr<State> newState) {
    if(currentState) {
        currentState->exitState(gameEngine);
    }
    currentState = std::move(newState);
    if(currentState) {
        currentState->enterState(gameEngine);
    }
}

void GameStateManager::handleInput(const std::string& input) {
    if(currentState) {
        currentState->handleInput(gameEngine, input);
    }
    else {
        qDebug() << "GameStateManager: No current state to handle input";
    }
}
