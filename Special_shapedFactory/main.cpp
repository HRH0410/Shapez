#include "factory.h"
#include "startscreen.h"
#include "Help.h"
#include "endscreen.h"
#include <QApplication>
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStackedWidget stackedWidget;

    // 创建四个界面
    StartScreen startScreen;
    Factory Game;
    EndScreen endScreen;
    Help help;

    // 将四个界面添加到QStackedWidget中
    stackedWidget.addWidget(&startScreen);
    stackedWidget.addWidget(&Game);
    stackedWidget.addWidget(&endScreen);
    stackedWidget.addWidget(&help);


    // 设置初始界面为开始界面
    stackedWidget.setCurrentWidget(&startScreen);

    stackedWidget.setFixedSize(1280, 700);

    // 切换到游戏界面
    QObject::connect(&startScreen, &StartScreen::startGame, [&]() {
        stackedWidget.setCurrentWidget(&Game);
    });

    // 切换到结束界面
    QObject::connect(&Game, &Factory::task3Completed, [&]() {
        stackedWidget.setCurrentWidget(&endScreen);
    });

    //切换到帮助界面
    QObject::connect(&startScreen, &StartScreen::help, [&]() {
        stackedWidget.setCurrentWidget(&help);
    });

    //切换到开始界面
    QObject::connect(&help, &Help::Return, [&]() {
        stackedWidget.setCurrentWidget(&startScreen);
    });

    stackedWidget.show();
    return a.exec();
}
