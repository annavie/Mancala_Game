#include <QApplication>
#include "GameEngine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameEngine gameEngine;

    return a.exec();
}
