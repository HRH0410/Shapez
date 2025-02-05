#include "startscreen.h"
#include <QPushButton>
#include <QFont>
#include <QPainter>
#include <QVBoxLayout>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    QPushButton *startButton = new QPushButton("Start Game", this);
    QPushButton *helpButton = new QPushButton("Help",this);

    QFont font("Comic Sans MS", 22, QFont::Bold);
    startButton->setFont(font);
    helpButton->setFont(font);
    startButton->setFixedSize(200, 100);
    helpButton->setFixedSize(200,100);

    connect(startButton, &QPushButton::clicked, this, &StartScreen::startGame);
    connect(helpButton, &QPushButton::clicked, this, &StartScreen::help);

    setFixedSize(1280, 700);

    logoPixmap = QPixmap(":/image/logo.png");
    backgroundPixmap=QPixmap(":/image/background.jpg");

    startButton->move(540, 520);
    helpButton->move(540,380);

    // 播放背景音乐
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/image/BGM.MP3"));
    audioOutput->setVolume(0.5);
    mediaPlayer->setLoops(QMediaPlayer::Infinite);
    mediaPlayer->play();
}

void StartScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, 1280, 700, backgroundPixmap);
     painter.drawPixmap(200, 100, 880, 220, logoPixmap);
    QWidget::paintEvent(event);
}
