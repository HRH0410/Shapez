#ifndef FACTORY_H
#define FACTORY_H

#include <QMainWindow>
#include <vector>
#include "deliverycentre.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Factory;
}
QT_END_NAMESPACE


class Factory : public QMainWindow
{
    Q_OBJECT

public:
    Factory(QWidget *parent = nullptr);
    ~Factory();

signals:
    void task3Completed();

private slots:
    void GameFinished();//游戏结束的信号

private:
    Ui::Factory *ui;

    // 地图大小
    int mapWidth;
    int mapHeight;

    // 地图数据结构，每个元素代表一个格子
    std::vector<std::vector<int>> mapData;

    DeliveryCenter* deliveryCenter; // 交付中心对象
};

#endif
