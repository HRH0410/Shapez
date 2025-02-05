#include "endscreen.h"
#include <QFont>
#include <QPainter>
#include <QApplication>

EndScreen::EndScreen(QWidget *parent) : QWidget(parent)
{
    QPushButton *exitButton = new QPushButton("Exit Game", this); //创建退出按钮

    // 设置按钮的字体和字号
    QFont font("Comic Sans MS", 22, QFont::Bold);

    exitButton->setFont(font);

    exitButton->setFixedSize(200, 100);

    setFixedSize(1280, 700);

    exitButton->move(540, 500);

    // 加载背景图片
    logoPixmap = QPixmap(":/image/Victory.png");
    backgroundPixmap=QPixmap(":/image/background.jpg");
    winPixmap=QPixmap(":/image/win.png");

    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);  // 连接退出按钮的 clicked 信号到 QApplication::quit 槽
}

void EndScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, 1280, 700, backgroundPixmap);
    painter.drawPixmap(200, 100, 880, 220, logoPixmap);
    painter.drawPixmap(565, 320, 150, 150, winPixmap);
    QWidget::paintEvent(event);
}
