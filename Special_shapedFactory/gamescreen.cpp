#include "gamescreen.h"
#include <QPushButton>
#include <QVBoxLayout>

GameScreen::GameScreen(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    factory = new Factory(this);
    layout->addWidget(factory);


    // 创建一个结束按钮
   /* QPushButton *endButton = new QPushButton("End Game", this);
    layout->addWidget(endButton, 0, Qt::AlignCenter);

    connect(endButton, &QPushButton::clicked, this, &GameScreen::endGame);*/

    // 设置 GameScreen 的大小
    setFixedSize(factory->size());
}
