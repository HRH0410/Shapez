#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "factory.h"

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget *parent = nullptr);

signals:
    void endGame();

private:
    Factory *factory;
};

#endif // GAMESCREEN_H
