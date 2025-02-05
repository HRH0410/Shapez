#include "factory.h"
#include "ui_factory.h"
#include "deliverycentre.h"
#include <QVBoxLayout>
#include <QPainter>
#include "MapWidget.h"

Factory::Factory(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Factory)
{
    ui->setupUi(this);

    // 初始化地图大小和数据
    mapWidth = 28;
    mapHeight = 16;
    mapData.resize(mapHeight, std::vector<int>(mapWidth, 0));

    // 创建自定义的MapWidget并设置地图数据
    int cellSize = 40;
    MapWidget *mapWidget = new MapWidget(this, cellSize);
    mapWidget->setMapData(mapData);

    // 创建交付中心
    deliveryCenter = new DeliveryCenter(12, 7, 2, 2, 0,0, ":/image/hub_small.png");
    mapWidget->setDeliveryCenter(deliveryCenter);
    for(int i=12;i<14;i++){
        for(int j=7;j<9;j++){
            mapData[j][i]=3;
        }
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mapWidget, 0, Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    setFixedSize(1280, 700);


    // 在地图上设置矿产区域
    // Cycle区域
    mapData[3][5] = 1;
    mapData[4][5] = 1;
    mapData[5][4] = 1;
    mapData[5][5] = 1;
    mapData[5][6] = 1;
    mapData[6][5] = 1;
    mapData[6][6] = 1;
    mapData[7][7] = 1;
    mapData[7][5] = 1;
    mapData[7][6] = 1;
    mapData[8][5] = 1;
    mapData[8][6] = 1;
    mapData[8][4] = 1;
    mapData[9][7] = 1;
    mapData[9][6] = 1;

    // Rect区域
    mapData[12][15] = 2;
    mapData[12][16] = 2;
    mapData[12][17] = 2;
    mapData[12][18] = 2;
    mapData[12][19] = 2;
    mapData[12][20] = 2;
    mapData[12][21] = 2;
    mapData[11][21] = 2;
    mapData[11][20] = 2;
    mapData[11][19] = 2;
    mapData[11][18] = 2;
    mapData[10][19] = 2;
    mapData[10][20] = 2;
    mapData[9][19] = 2;
    mapData[9][20] = 2;
    mapData[8][20] = 2;

    // Barrier区域
    mapData[2][6]=-1;
    mapData[3][7]=-1;
    mapData[6][8]=-1;
    mapData[8][9]=-1;
    mapData[5][11]=-1;
    mapData[4][16]=-1;
    mapData[11][11]=-1;
    mapData[10][10]=-1;
    mapData[10][14]=-1;
    mapData[7][15]=-1;
    mapData[6][17]=-1;
    mapData[3][13]=-1;
    mapData[5][14]=-1;
    mapData[11][17]=-1;


    mapWidget->setMapData(mapData);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Factory::GameFinished);
    timer->start(1000);
}

Factory::~Factory()
{
    delete ui;
    delete deliveryCenter;
}

//判断游戏是否胜利
void Factory::GameFinished(){
    if (deliveryCenter->getTask()>=40) {
        emit task3Completed();
    }
}
