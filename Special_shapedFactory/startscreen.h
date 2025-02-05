#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QAudioOutput>


class StartScreen : public QWidget
{
    Q_OBJECT
public:
    StartScreen(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void startGame();//开始游戏的信号
    void help();//进入帮助界面的信号

private:
    QPixmap backgroundPixmap;
    QPixmap logoPixmap;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};



#endif // STARTSCREEN_H
