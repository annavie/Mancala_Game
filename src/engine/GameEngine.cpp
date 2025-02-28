#include "GameEngine.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "GameplayState.h"
#include "GameOverState.h"
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include "AIAlgorithmStrategy.h"

GameEngine::GameEngine(QObject* parent)
    : QObject(parent),
    gameStateManager(std::make_unique<GameStateManager>(this)),
    ui(std::make_unique<UI>(this)),
    board(),
    settings(),
    scoreTracker(),
    currentPlayerIndex(0),
    isRunning(true)
{
    qDebug() << "GameEngine constructor called";

    ui->show();

    // Initialize players
    players.emplace_back(std::make_unique<Player>(settings.playerNames[0], 1, nullptr, false));
    players.emplace_back(std::make_unique<Player>(settings.playerNames[1], 2, std::make_unique<AIAlgorithmStrategy>(), true));

    qDebug() << "Players initialized";

    // Connect UI signals to GameEngine slots
    connect(ui.get(), &UI::pitClicked, this, &GameEngine::onPitClicked);
    connect(ui.get(), &UI::backToMainMenu, this, &GameEngine::onBackToMainMenu);
    connect(ui.get(), &UI::saveSettings, this, &GameEngine::onSaveSettings);

    // Connect signals for updating the UI
    connect(this, &GameEngine::updateBoard, ui.get(), &UI::renderBoard);
    connect(this, &GameEngine::showMainMenu, ui.get(), &UI::displayMainMenu);
    connect(this, &GameEngine::showSettings, ui.get(), &UI::displaySettings);
    connect(this, &GameEngine::showGameplay, ui.get(), &UI::displayGameplay);
    connect(this, &GameEngine::showGameOver, ui.get(), &UI::displayGameOver);

    qDebug() << "Signals and slots connected";

    // Start with the main menu
    changeState(std::make_unique<MainMenuState>());
}

GameEngine::~GameEngine() {
    qDebug() << "GameEngine destructor called";
}

void GameEngine::changeState(std::unique_ptr<State> newState) {
    qDebug() << "GameEngine: Changing state";
    gameStateManager->changeState(std::move(newState));
}

Player* GameEngine::getCurrentPlayer() const {
    return players[currentPlayerIndex].get();
}

std::vector<std::unique_ptr<Player>>& GameEngine::getPlayers() {
    return players;
}

std::pair<int, int> GameEngine::getScores() const {
    return { board.getPlayer1Store(), board.getPlayer2Store() };
}
void GameEngine::restartGame() {
    qDebug() << "GameEngine: Restarting game";

    board.resetBoard();
    scoreTracker = ScoreTracker(); // Reinitialize score tracker

    currentPlayerIndex = 0; // Start with Player 1
    isRunning = true;

    emit updateBoard(board);

    changeState(std::make_unique<GameplayState>());
}

void GameEngine::returnToMainMenu() {
    qDebug() << "GameEngine: Returning to Main Menu";
    board.resetBoard();
    currentPlayerIndex = 0;
    isRunning = false;

    // Reset scores by reinitializing ScoreTracker
    scoreTracker = ScoreTracker();

    changeState(std::make_unique<MainMenuState>());
}

void GameEngine::onPitClicked(int pitIndex) {
    qDebug() << "GameEngine: Pit clicked -" << pitIndex;

    if (pitIndex < 0) {
        gameStateManager->handleInput(std::to_string(pitIndex));
    } else {
        if (!players[currentPlayerIndex]->isAIPlayer() && board.getPit(pitIndex).getStones() > 0) {
            processMove(pitIndex);
        } else {
            QMessageBox::warning(ui.get(), "Invalid Move", "Selected pit is empty or invalid.");
        }
    }
}
void GameEngine::processMove(int pitIndex) {
    qDebug() << "GameEngine: Processing move for pit" << pitIndex;

    Player* currentPlayer = getCurrentPlayer();
    if (board.getPit(pitIndex).getStones() == 0) {
        QMessageBox::warning(ui.get(), "Invalid Move", "Selected pit is empty.");
        return;
    }
    bool extraTurn = board.makeMove(pitIndex, currentPlayer);
    qDebug() << "GameEngine: Extra turn?" << extraTurn;

    emit updateBoard(board);

    if (board.isGameOver()) {
        qDebug() << "GameEngine: Game is over!";
        changeState(std::make_unique<GameOverState>());
        return;
    }
    if (!extraTurn) {
        currentPlayerIndex = 1 - currentPlayerIndex;
    }
    emit updateBoard(board);

    if (players[currentPlayerIndex]->isAIPlayer()) {
        QTimer::singleShot(500, this, [this]() {
            int aiPit = players[currentPlayerIndex]->makeMove(&board);
            if (aiPit != -1) {
                processMove(aiPit);
            }
        });
    } else {
        emit updateBoard(board);
    }
}

void GameEngine::exitGame() {
    qDebug() << "GameEngine: Exiting game...";
    QMessageBox::information(ui.get(), "Exit Game", "Thank you for playing Mancala!");
    QApplication::quit();
}

void GameEngine::onBackToMainMenu() {
    qDebug() << "GameEngine: Back to Main Menu signal received.";
    returnToMainMenu();
}

void GameEngine::onSaveSettings(const std::string& player1Name, const std::string& player2Name) {
    qDebug() << "GameEngine: Saving settings.";
    players[0]->setName(player1Name);
    players[1]->setName(player2Name);
    QMessageBox::information(ui.get(), "Settings Saved", "Player names have been updated.");
}

const Board& GameEngine::getBoard() const {
    return board;
}
