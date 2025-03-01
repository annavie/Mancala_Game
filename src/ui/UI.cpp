#include "../../include/ui/UI.h"
#include "../../include/engine/GameEngine.h"
#include "../../include/states/MainMenuState.h"
#include "../../include/states/SettingsState.h"
#include "../../include/states/GameplayState.h"
#include "../../include/states/GameOverState.h"
#include "../../include/ui/Constants.h"
#include "../../include/states/CommandCodes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <iostream>

UI::UI(GameEngine* gameEngine, QWidget* parent)
    : QMainWindow(parent), mediator(gameEngine), titleLabel(nullptr)
{
    qDebug() << "UI initialized";
    setupMainMenu();
}

UI::~UI() {}

QPushButton* UI::createPitButton(const QString& text, const QString& styleSheet) {
    QPushButton* button = new QPushButton(text, this);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setStyleSheet(styleSheet);
    return button;
}

void UI::clearLayout() {
    if (centralWidget()) {
        centralWidget()->deleteLater();
    }
}

void UI::setupMainMenu() {
    clearLayout();

    if (!titleLabel) {
        titleLabel = new QLabel("Mancala Game", this);
    }
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(QString("font-size: %1px;").arg(Constants::kTitleFontSize));

    startButton = new QPushButton("Start Game", this);
    settingsButton = new QPushButton("Settings", this);
    exitButton = new QPushButton("Exit", this);

    connect(startButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(static_cast<int>(CommandCode::StartGame));
    });
    connect(settingsButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(static_cast<int>(CommandCode::Settings));
    });
    connect(exitButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(static_cast<int>(CommandCode::ExitGame));
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(titleLabel);
    layout->addSpacing(Constants::kMenuSpacing);
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
    settingsLabel->setStyleSheet(QString("font-size: %1px;").arg(Constants::kTitleFontSize));

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
        emit pitClicked(static_cast<int>(CommandCode::ReturnToMainMenu));
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(settingsLabel);
    layout->addSpacing(Constants::kMenuSpacing);
    layout->addWidget(player1Label);
    layout->addWidget(player1Input);
    layout->addWidget(player2Label);
    layout->addWidget(player2Input);
    layout->addSpacing(Constants::kMenuSpacing);
    layout->addWidget(saveButton);
    layout->addWidget(backButton);

    QWidget* container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}

void UI::setupGameplay() {
    clearLayout();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QVBoxLayout* boardLayout = new QVBoxLayout();

    pitsLayout = new QGridLayout();
    pitButtons.resize(Constants::kTotalPits);

    for (int i = Constants::kTotalPits - 1; i >= Constants::kPitsPerPlayer; --i) {
        QString style =
            "QPushButton {"
            "   border: 2px solid black;"
            "   border-radius: " + QString::number(Constants::kPitBorderRadius) + "px;"
                                                             "   background-color: white;"
                                                             "   font-size: " + QString::number(Constants::kPitFontSize) + "px;"
                                                         "   color: black;"
                                                         "}"
                                                         "QPushButton:enabled {"
                                                         "   background-color: lightgreen;"
                                                         "}"
                                                         "QPushButton:disabled {"
                                                         "   background-color: lightgray;"
                                                         "   color: black;"
                                                         "}";
        pitButtons[i] = createPitButton("4", style);
        int column = (Constants::kTotalPits - i);
        connect(pitButtons[i], &QPushButton::clicked, this, [this, i]() {
            emit pitClicked(i);
        });
        pitsLayout->addWidget(pitButtons[i], Constants::kPlayer2PitsRow, column);
    }

    for (int i = 0; i < Constants::kPitsPerPlayer; ++i) {
        QString style =
            "QPushButton {"
            "   border: 2px solid gray;"
            "   border-radius: " + QString::number(Constants::kPitBorderRadius) + "px;"
                                                             "   background-color: white;"
                                                             "   font-size: " + QString::number(Constants::kPitFontSize) + "px;"
                                                         "   color: black;"
                                                         "}"
                                                         "QPushButton:disabled {"
                                                         "   background-color: lightgray;"
                                                         "   color: black;"
                                                         "}";
        pitButtons[i] = createPitButton("4", style);
        connect(pitButtons[i], &QPushButton::clicked, this, [this, i]() {
            emit pitClicked(i);
        });
        pitsLayout->addWidget(pitButtons[i], Constants::kPlayer1PitsRow, i + 1);
    }

    player2StoreLabel = new QLabel("Store: 0", this);
    player2StoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    player2StoreLabel->setAlignment(Qt::AlignCenter);
    player2StoreLabel->setStyleSheet(QString("font-size: %1px; border: 1px solid black;")
                                         .arg(Constants::kStoreFontSize));
    pitsLayout->addWidget(player2StoreLabel, 1, Constants::kPlayer2StoreColumn);

    player1StoreLabel = new QLabel("Store: 0", this);
    player1StoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    player1StoreLabel->setAlignment(Qt::AlignCenter);
    player1StoreLabel->setStyleSheet(QString("font-size: %1px; border: 1px solid black;")
                                         .arg(Constants::kStoreFontSize));
    pitsLayout->addWidget(player1StoreLabel, 1, Constants::kPlayer1StoreColumn);

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
        emit pitClicked(static_cast<int>(CommandCode::Pause));
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
        "}"
        );

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
        "}"
        );

    QPushButton* mainMenuButton = new QPushButton("Main Menu", menuWidget);
    mainMenuButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 18px; padding: 10px;"
        "   background-color: lightblue; border-radius: 10px;"
        "   border: 2px solid blue; color: darkblue;"
        "}"
        "QPushButton:hover {"
        "   background-color: darkblue; color: white;"
        "}"
        );

    QPushButton* exitButton = new QPushButton("Exit Game", menuWidget);
    exitButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 18px; padding: 10px;"
        "   background-color: lightcoral; border-radius: 10px;"
        "   border: 2px solid red; color: darkred;"
        "}"
        "QPushButton:hover {"
        "   background-color: darkred; color: white;"
        "}"
        );

    connect(restartButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(static_cast<int>(CommandCode::RestartGame));
    });
    connect(mainMenuButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(static_cast<int>(CommandCode::ReturnToMainMenu));
    });
    connect(exitButton, &QPushButton::clicked, this, [this, overlay, menuWidget]() {
        overlay->close();
        menuWidget->close();
        emit pitClicked(static_cast<int>(CommandCode::ExitGame));
    });

    menuLayout->addWidget(titleLabel);
    menuLayout->addSpacing(Constants::kMenuSpacing);
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
    scoreLabel->setStyleSheet(QString("font-size: %1px;").arg(Constants::kTitleFontSize));

    restartButton = new QPushButton("Restart Game", this);
    connect(restartButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(static_cast<int>(CommandCode::RestartGame));
    });

    mainMenuButton = new QPushButton("Return to Main Menu", this);
    connect(mainMenuButton, &QPushButton::clicked, this, [this]() {
        emit pitClicked(static_cast<int>(CommandCode::ReturnToMainMenu));
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);

    QWidget* container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}

void UI::renderBoard(const Board& board) {
    Player* currentPlayer = mediator->getCurrentPlayer();
    int currentPlayerNumber = currentPlayer->getPlayerNumber();

    qDebug() << "Rendering board for Player" << currentPlayerNumber;

    for (int i = 0; i < Constants::kTotalPits; ++i) {
        int stones = board.getPit(i).getStones();
        pitButtons[i]->setText(QString::number(stones));

        bool isPlayer1Pit = (i < Constants::kPitsPerPlayer);
        bool isCurrentPlayerPit = (currentPlayerNumber == 1 && isPlayer1Pit) ||
                                  (currentPlayerNumber == 2 && !isPlayer1Pit);

        bool enable = isCurrentPlayerPit && (stones > 0);
        pitButtons[i]->setEnabled(enable);

        if (enable) {
            pitButtons[i]->setStyleSheet(
                "QPushButton {"
                "   border: 2px solid black;"
                "   border-radius: " + QString::number(Constants::kPitBorderRadius) + "px;"
                                                                 "   background-color: lightgreen;"
                                                                 "   font-size: " + QString::number(Constants::kPitFontSize) + "px;"
                                                             "   color: black;"
                                                             "}"
                );
        } else {
            pitButtons[i]->setStyleSheet(
                "QPushButton {"
                "   border: 2px solid black;"
                "   border-radius: " + QString::number(Constants::kPitBorderRadius) + "px;"
                                                                 "   background-color: lightgray;"
                                                                 "   font-size: " + QString::number(Constants::kPitFontSize) + "px;"
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
