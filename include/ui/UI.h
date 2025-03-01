#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <string>
#include <vector>

class GameEngine;
class QLabel;
class QPushButton;
class QGridLayout;

class UI : public QMainWindow {
    Q_OBJECT

public:
    explicit UI(GameEngine* gameEngine, QWidget* parent = nullptr);
    ~UI();

    void displayMainMenu();
    void displaySettings();
    void displayGameplay();
    void displayGameOver(int player1Score, int player2Score);
    
    void renderBoard(const class Board& board);
    
    void showInGameMenu();

signals:
    void pitClicked(int pitIndex);
    
    void saveSettings(const std::string& player1Name, const std::string& player2Name);
    
    void backToMainMenu();

private:
    GameEngine* mediator;

    QLabel* titleLabel;
    QPushButton* startButton;
    QPushButton* settingsButton;
    QPushButton* exitButton;
    QPushButton* restartButton;
    QPushButton* mainMenuButton;
    QLabel* player1StoreLabel;
    QLabel* player2StoreLabel;
    QLabel* scoreLabel;
    QGridLayout* pitsLayout;
    std::vector<QPushButton*> pitButtons;

    void setupMainMenu();
    void setupSettings();
    void setupGameplay();
    void setupGameOver();
    
    QPushButton* createPitButton(const QString& text, const QString& styleSheet);
    
    void clearLayout();
};

#endif // UI_H
