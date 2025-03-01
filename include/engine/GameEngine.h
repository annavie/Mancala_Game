#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <vector>
#include <memory>
#include "../states/GameStateManager.h"
#include "../core/Board.h"
#include "../core/Player.h"
#include "../core/Settings.h"
#include "../core/ScoreTracker.h"
#include "../ui/UI.h"

class State;

class GameEngine : public QObject {
    Q_OBJECT

public:
    explicit GameEngine(QObject* parent = nullptr);
    ~GameEngine();

    Player* getCurrentPlayer() const;
    std::vector<std::unique_ptr<Player>>& getPlayers();
    std::pair<int, int> getScores() const;
    void restartGame();
    void changeState(std::unique_ptr<State> newState);
    void returnToMainMenu();
    std::unique_ptr<UI> ui;
    void exitGame();


    const Board& getBoard() const;


public slots:
    void onPitClicked(int pitIndex);
    void onBackToMainMenu();
    void onSaveSettings(const std::string& player1Name, const std::string& player2Name);

signals:
    void showMainMenu();
    void showSettings();
    void showGameplay();
    void showGameOver(int player1Score, int player2Score);
    void updateBoard(const Board& board);
    void showHelp();

private:
    std::unique_ptr<GameStateManager> gameStateManager;
    Board board;
    Settings settings;
    ScoreTracker scoreTracker;
    std::vector<std::unique_ptr<Player>> players;
    int currentPlayerIndex;
    bool isRunning;

    void processMove(int pitIndex);
};

#endif // GAMEENGINE_H
