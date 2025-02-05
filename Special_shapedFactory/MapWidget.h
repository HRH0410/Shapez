#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <string>
#include <QKeyEvent>
#include <Qtimer>
#include "Miner.h"
#include "Belt.h"
#include "Cutter.h"
#include "Trash.h"
#include "DeliveryCentre.h"
#include "ore.h"
#include "OverlayWindow.h"
#include "Shop.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr, int cellSize = 50);
    void setMapData(const std::vector<std::vector<int>>& data);
    void setDeliveryCenter(DeliveryCenter* center);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateAnimation();
    void updateMiners();
    void updateCutters();
    void handleOverlayButtonClicked(int buttonId);
    void handleShopButtonClicked(int buttonId);

private:
    bool isEmptyTile(int x, int y) const;//判断是否是空地
    bool isMineralTile(int x, int y) const;//判断是否是矿地

    int cellSize;

    std::vector<std::vector<int>> mapData;

    DeliveryCenter* deliveryCenter;

    //创建容器用来存储各种工具与矿石
    std::vector<Miner> miners;
    std::vector<Belt> belts;
    std::vector<Cutter>cutters;
    std::vector<Trash> trashes;
    std::vector<Ore> ores;

    //用于存储图标的图像
    QPixmap minerIcons[5];
    QPixmap cutterIcons[5];
    QPixmap trashIcons[5];
    QPixmap beltIcons[13];
    QPixmap oreIcons[4];
    QPixmap spadeIcon;
    QPixmap shopIcon;

    //判断拖动事件
    bool draggingMiner;
    bool draggingBelt;
    bool draggingCutter;
    bool draggingTrash;
    bool draggingSpade;

    //获取坐标
    QPoint dragStartPos;
    QPoint currentDragPos;

    //获取当前方向
    std::string currentDirection;

    //判断键盘是否被按下
    bool isWPressed;
    bool isDPressed;
    bool isAPressed;
    bool isSPressed;
    bool isRPressed;

    //判断在第几个关卡
    bool isGame1;
    bool isGame2;
    bool isGame3;

    //判断交付中心大小
    bool isSmallhub;
    bool isBighub;

    //判断矿石价值是否提升
    bool isMoneyup;

    OverlayWindow *overlayWindow;

    Shop *shop;

    //三个关卡三个任务
    void Task1();
    void Task2();
    void Task3();

    //清除障碍
    void clearBarrier();

    //各组件运行速度
    int v_belt;
    int v_miner;
    int v_cutter;

    //用于生成新的矿石
    void generateOre(int x, int y, const std::string& direction,const std::string& type);

    //计时器
    QTimer animationTimer;
};

#endif
