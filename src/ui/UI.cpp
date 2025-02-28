#include "UI.h"
#include "GameEngine.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "GameplayState.h"
#include "GameOverState.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>

UI::UI(GameEngine* gameEngine, QWidget* parent)
    : QMainWindow(parent), mediator(gameEngine) {
    qDebug() << "UI initialized";
    setupMainMenu();
}

UI::~UI() {}

void UI::setupMainMenu() {
    clearLayout();

    titleLabel = new QLabel("Mancala Game", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px;");

    startButton = new QPushButton("Start Game", this);
    settingsButton = new QPushButton("Settings", this);
    exitButton = new QPushButton("Exit", this);

    connect(startButton, &QPushButton::clicked, this, [this]() { emit pitClicked(-1); });
    connect(settingsButton, &QPushButton::clicked, this, [this]() { emit pitClicked(-2); });
    connect(exitButton, &QPushButton::clicked, this, [this]() { emit pitClicked(-3); });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(titleLabel);
    layout->addSpacing(20);
    layout->addWidget(startButton);
    layout->addWidget(settingsButton);
    layout->addWidget(exitButton);

    QWidget* container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}

void UI::setupSettings() {
    clearLayout();
    QLabel* settingsLabel = new QLabel("Settings", this);
    settingsLabel->setAlignment(Qt::AlignCenter);
    settingsLabel->setStyleSheet("font-size: 24px;");

    QLabel* player1Label = new QLabel("Player 1 Name:", this);
    QLineEdit* player1Input = new QLineEdit(this);
    player1Input->setPlaceholderText("Enter Player 1's name");
    player1Input->setText(QString::fromStdString(mediator->getPlayers()[0]->getName()));

    QLabel* player2Label = new QLabel("Player 2 Name:", this);
    QLineEdit* player2Input = new QLineEdit(this);
    player2Input->setPlaceholderText("Enter Player 2's name");
    player2Input->setText(QString::fromStdString(mediator->getPlayers()[1]->getName()));

    QPushButton* saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, [this, player1Input, player2Input]() {
        emit saveSettings(player1Input->text().toStdString(),
                          player2Input->text().toStdString());
        QMessageBox::information(this, "Settings Saved", "Player names have been updated.");
    });

    QPushButton* backButton = new QPushButton("Back to Main Menu", this);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(-4);
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(settingsLabel);
    layout->addSpacing(20);
    layout->addWidget(player1Label);
    layout->addWidget(player1Input);
    layout->addWidget(player2Label);
    layout->addWidget(player2Input);
    layout->addSpacing(20);
    layout->addWidget(saveButton);
    layout->addWidget(backButton);

    QWidget* container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}
void UI::setupGameplay() {
    clearLayout();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* gameplayLayout = new QHBoxLayout();
    QVBoxLayout* boardLayout = new QVBoxLayout();

    // Pits Layout
    pitsLayout = new QGridLayout();
    pitButtons.resize(12);

    for (int i = 11; i >= 6; --i) {
        QPushButton* pitButton = new QPushButton("4", this);
        pitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pitButton->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid black;"
            "   border-radius: 40px;"
            "   background-color: white;"
            "   font-size: 20px;"
            "   color: black;"
            "}"
            "QPushButton:enabled {"
            "   background-color: lightgreen;"
            "}"
            "QPushButton:disabled {"
            "   background-color: lightgray;"
            "   color: black;"
            "}"
            );

        pitButtons[i] = pitButton;
        connect(pitButton, &QPushButton::clicked, this, [this, i]() { emit pitClicked(i); });
        pitsLayout->addWidget(pitButton, 0, 11 - i + 1); // Columns 1–6
    }

    for (int i = 0; i < 6; ++i) {
        QPushButton* pitButton = new QPushButton("4", this);
        pitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pitButton->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid gray;"
            "   border-radius: 40px;"
            "   background-color: white;"
            "   font-size: 20px;"
            "   color: black;"
            "}"
            "QPushButton:disabled {"
            "   background-color: lightgray;"
            "   color: black;"
            "}"
            );

        pitButtons[i] = pitButton;
        connect(pitButton, &QPushButton::clicked, this, [this, i]() { emit pitClicked(i); });
        pitsLayout->addWidget(pitButton, 2, i + 1);
    }

    player2StoreLabel = new QLabel("Store: 0", this);
    player2StoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    player2StoreLabel->setAlignment(Qt::AlignCenter);
    player2StoreLabel->setStyleSheet("font-size: 18px; border: 1px solid black;");
    pitsLayout->addWidget(player2StoreLabel, 1, 0);

    player1StoreLabel = new QLabel("Store: 0", this);
    player1StoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    player1StoreLabel->setAlignment(Qt::AlignCenter);
    player1StoreLabel->setStyleSheet("font-size: 18px; border: 1px solid black;");
    pitsLayout->addWidget(player1StoreLabel, 1, 7);

    boardLayout->addLayout(pitsLayout);

    QPushButton* menuButton = new QPushButton("☰", this);
    menuButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    menuButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   border: black;"
        "   background-color: transparent;"
        "}"
        "QPushButton:hover {"
        "   color: darkgreen;"
        "}"
        );

    connect(menuButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(-4);
    });
    QHBoxLayout* menuLayout = new QHBoxLayout();
    menuLayout->addStretch();
    menuLayout->addWidget(menuButton);

    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(boardLayout);

    QWidget* container = new QWidget();
    container->setLayout(mainLayout);
    setCentralWidget(container);
}

void UI::showInGameMenu() {
    QWidget* overlay = new QWidget(this);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 150);");
    overlay->setGeometry(0, 0, this->width(), this->height());
    overlay->show();

    QWidget* menuWidget = new QWidget(this);
    menuWidget->setStyleSheet(
        "QWidget {"
        "   background-color: white;"
        "   border: 3px solid darkblue;"
        "   border-radius: 15px;"
        "   padding: 20px;"
        "   box-shadow: 5px 5px 15px rgba(0, 0, 0, 100);"
        "}");

    QVBoxLayout* menuLayout = new QVBoxLayout(menuWidget);

    QLabel* titleLabel = new QLabel("Game Menu", menuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");

    QPushButton* restartButton = new QPushButton("Restart Game", menuWidget);
    restartButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 18px; padding: 10px;"
        "   background-color: lightgreen; border-radius: 10px;"
        "   border: 2px solid green; color: darkgreen;"
        "}"
        "QPushButton:hover {"
        "   background-color: darkgreen; color: white;"
        "}");

    QPushButton* mainMenuButton = new QPushButton("Main Menu", menuWidget);
    mainMenuButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 18px; padding: 10px;"
        "   background-color: lightblue; border-radius: 10px;"
        "   border: 2px solid blue; color: darkblue;"
        "}"
        "QPushButton:hover {"
        "   background-color: darkblue; color: white;"
        "}");

    QPushButton* exitButton = new QPushButton("Exit Game", menuWidget);
    exitButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 18px; padding: 10px;"
        "   background-color: lightcoral; border-radius: 10px;"
        "   border: 2px solid red; color: darkred;"
        "}"
        "QPushButton:hover {"
        "   background-color: darkred; color: white;"
        "}");

    connect(restartButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(-5);
    });

    connect(mainMenuButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(-4);
    });

    connect(exitButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(-3);
    });

    menuLayout->addWidget(titleLabel);
    menuLayout->addSpacing(20);
    menuLayout->addWidget(restartButton);
    menuLayout->addWidget(mainMenuButton);
    menuLayout->addWidget(exitButton);

    menuWidget->setLayout(menuLayout);
    menuWidget->adjustSize();

    int x = (this->width() - menuWidget->width()) / 2;
    int y = (this->height() - menuWidget->height()) / 2;
    menuWidget->move(x, y);
    menuWidget->show();

    connect(overlay, &QWidget::destroyed, menuWidget, &QWidget::close);
}
void UI::setupGameOver() {
    clearLayout();

    scoreLabel = new QLabel("Game Over", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("font-size: 24px;");

    restartButton = new QPushButton("Restart Game", this);
    connect(restartButton, &QPushButton::clicked, this, [this]() { emit pitClicked(-5); });

    mainMenuButton = new QPushButton("Return to Main Menu", this);
    connect(mainMenuButton, &QPushButton::clicked, this, [this]() { emit pitClicked(-6); });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);

    QWidget* container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}
void UI::clearLayout() {
    QLayout* layout = centralWidget() ? centralWidget()->layout() : nullptr;
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    delete layout;
}

void UI::renderBoard(const Board& board) {
    Player* currentPlayer = mediator->getCurrentPlayer();
    int currentPlayerNumber = currentPlayer->getPlayerNumber();

    qDebug() << "Rendering board for Player" << currentPlayerNumber;

    for (int i = 0; i < 12; ++i) {
        int stones = board.getPit(i).getStones();
        pitButtons[i]->setText(QString::number(stones));

        bool isPlayer1Pit = (i < 6); // Pits 0–5 belong to Player 1
        bool isCurrentPlayerPit = (currentPlayerNumber == 1 && isPlayer1Pit) ||
                                  (currentPlayerNumber == 2 && !isPlayer1Pit);

        bool enable = isCurrentPlayerPit && (stones > 0);
        pitButtons[i]->setEnabled(enable);

        if (enable) {
            pitButtons[i]->setStyleSheet(
                "QPushButton {"
                "   border: 2px solid black;"
                "   border-radius: 40px;"
                "   background-color: lightgreen;"
                "   font-size: 20px;"
                "   color: black;"
                "}"
                );
        } else {
            pitButtons[i]->setStyleSheet(
                "QPushButton {"
                "   border: 2px solid black;"
                "   border-radius: 40px;"
                "   background-color: lightgray;"
                "   font-size: 20px;"
                "   color: black;"
                "}"
                "QPushButton:disabled {"
                "   color: black;"
                "   border: 2px dashed gray;"
                "}"
                );
        }

        qDebug() << "Pit" << i
                 << "-> stones =" << stones
                 << "-> enabled? " << enable
                 << "-> belongs to current player? " << isCurrentPlayerPit;
    }

    player1StoreLabel->setText(QString("Store: %1").arg(board.getPlayer1Store()));
    player2StoreLabel->setText(QString("Store: %1").arg(board.getPlayer2Store()));

}

void UI::displayMainMenu() {
    setupMainMenu();
}

void UI::displaySettings() {
    setupSettings();
}

void UI::displayGameplay() {
    setupGameplay();
}

void UI::displayGameOver(int player1Score, int player2Score) {
    setupGameOver();

    std::string player1Name = mediator->getPlayers()[0]->getName();
    std::string player2Name = mediator->getPlayers()[1]->getName();

    std::string winner;
    if (player1Score > player2Score) {
        winner = player1Name + " wins!";
    } else if (player2Score > player1Score) {
        winner = player2Name + " wins!";
    } else {
        winner = "It's a tie!";
    }

    scoreLabel->setText(QString::fromStdString(
        player1Name + ": " + std::to_string(player1Score) + "   " +
        player2Name + ": " + std::to_string(player2Score) + "\n" + winner
        ));
}

