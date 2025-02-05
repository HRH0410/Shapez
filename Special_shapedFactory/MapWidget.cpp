#include "MapWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>


MapWidget::MapWidget(QWidget *parent, int cellSize)
    : QWidget(parent), cellSize(cellSize), deliveryCenter(nullptr), draggingMiner(false), draggingBelt(false), draggingCutter(false),draggingTrash(false),draggingSpade(false),currentDirection("up"),
    isGame1(true),isGame2(false),isGame3(false),v_belt(400),v_miner(2000),v_cutter(2000),isSmallhub(true),isBighub(false),isMoneyup(false)
{
    setFixedSize(1280, 700);

    //初始化各种图片
    minerIcons[0].load(":/image/miner_W.png");
    minerIcons[1].load(":/image/miner_S.png");
    minerIcons[2].load(":/image/miner_A.png");
    minerIcons[3].load(":/image/miner_D.png");
    minerIcons[4].load(":/image/miner_button.png");

    cutterIcons[0].load(":/image/cutter_W.png");
    cutterIcons[1].load(":/image/cutter_S.png");
    cutterIcons[2].load(":/image/cutter_A.png");
    cutterIcons[3].load(":/image/cutter_D.png");
    cutterIcons[4].load(":/image/cutter_button.png");

    trashIcons[0].load(":/image/trash_W.png");
    trashIcons[1].load(":/image/trash_S.png");
    trashIcons[2].load(":/image/trash_A.png");
    trashIcons[3].load(":/image/trash_D.png");
    trashIcons[4].load(":/image/trash_button.png");

    beltIcons[0].load(":/image/belt_W.png");
    beltIcons[1].load(":/image/belt_S.png");
    beltIcons[2].load(":/image/belt_A.png");
    beltIcons[3].load(":/image/belt_D.png");
    beltIcons[4].load(":/image/belt_W_D.png");
    beltIcons[5].load(":/image/belt_W_A.png");
    beltIcons[6].load(":/image/belt_S_D.png");
    beltIcons[7].load(":/image/belt_S_A.png");
    beltIcons[8].load(":/image/belt_A_W.png");
    beltIcons[9].load(":/image/belt_A_S.png");
    beltIcons[10].load(":/image/belt_D_W.png");
    beltIcons[11].load(":/image/belt_D_S.png");
    beltIcons[12].load(":/image/belt_button.png");

    oreIcons[0].load(":/image/cycle.png");
    oreIcons[1].load(":/image/rect.png");
    oreIcons[2].load(":/image/left_cycle.png");
    oreIcons[3].load(":/image/right_cycle.png");

    spadeIcon.load(":/image/spade.png");

    shopIcon.load(":/image/shop.png");

    // 使窗口能够接收键盘事件
    setFocusPolicy(Qt::StrongFocus);

    // 初始化并启动动画定时器
    connect(&animationTimer, &QTimer::timeout, this, &MapWidget::updateAnimation);
    animationTimer.start(v_belt);

    // 设置开采器更新定时器
    QTimer *minerTimer = new QTimer(this);
    connect(minerTimer, &QTimer::timeout, this, &MapWidget::updateMiners);
    minerTimer->start(v_miner);

    // 设置切割机更新定时器
    QTimer *cutterTimer = new QTimer(this);
    connect(cutterTimer, &QTimer::timeout, this, &MapWidget::updateCutters);
    cutterTimer->start(v_cutter);

    overlayWindow = new OverlayWindow(this);
    overlayWindow->hide();

    connect(overlayWindow, &OverlayWindow::buttonClicked, this, &MapWidget::handleOverlayButtonClicked);

    overlayWindow->setCustomImage(QPixmap(":/image/Task1.png"));
    overlayWindow->show();

    shop=new Shop(this);
    shop->hide();

    connect(shop, &Shop::buttonClicked,this,&MapWidget::handleShopButtonClicked);
}

void MapWidget::updateAnimation() {
    for (auto it = ores.begin(); it != ores.end(); ) {
        Ore& ore = *it;
        int x = ore.getX();
        int y = ore.getY();
        std::string direction = ore.getDirection();
        std::string type=ore.getType();

        // 根据传送带方向更新矿石的位置
        if (direction == "down"&&mapData[y+1][x]==5) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            it = ores.erase(it);
            continue;
        }
        else if (direction == "left"&&mapData[y][x-1]==5) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            it = ores.erase(it);
            continue;
        }
        else if (direction == "up"&&mapData[y-1][x]==5) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            it = ores.erase(it);
            continue;
        }
        else if (direction == "right"&&mapData[y][x+1]==5) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            it = ores.erase(it);
            continue;
        }
        else if (direction == "down"&&mapData[y+1][x]==11&&type=="Cycle"||direction == "down"&&mapData[y+1][x]==100&&type=="Cycle") {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            mapData[y+1][x]=100;
            mapData[y+1][x-1]=100;
            it = ores.erase(it);
            continue;
        }
        else if (direction == "left"&&mapData[y][x-1]==13&&type=="Cycle"||direction == "left"&&mapData[y][x-1]==100&&type=="Cycle") {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            mapData[y][x-1]=100;
            mapData[y-1][x-1]=100;
            it = ores.erase(it);
            continue;
        }
        else if (direction == "up"&&mapData[y-1][x]==10&&type=="Cycle"||direction == "up"&&mapData[y-1][x]==100&&type=="Cycle") {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            mapData[y-1][x]=100;
            mapData[y-1][x+1]=100;
            it = ores.erase(it);
            continue;
        }
        else if (direction == "right"&&mapData[y][x+1]==12&&type=="Cycle"||direction == "right"&&mapData[y][x+1]==100&&type=="Cycle") {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            mapData[y][x+1]=100;
            mapData[y+1][x+1]=100;
            it = ores.erase(it);
            continue;
        }

        if (direction == "up"&&mapData[y-1][x]==28) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
            mapData[y][x]+=20;
        }
        else if(direction =="up"&&mapData[y-1][x]==20){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
            mapData[y][x]+=20;
        }
        else if (direction == "up"&&mapData[y-1][x]==29) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
            ore.setDirection("left");
            mapData[y][x]+=20;
        }
        else if (direction == "down"&&mapData[y+1][x]==21) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
            mapData[y][x]+=20;
        }
        else if (direction == "down"&&mapData[y+1][x]==30) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
            mapData[y][x]+=20;
        }
        else if (direction == "down"&&mapData[y+1][x]==31) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
            ore.setDirection("left");
            mapData[y][x]+=20;
        }
        else if (direction == "left"&&mapData[y][x-1]==23) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x-=1;
            mapData[y][x]+=20;
        }
        else if (direction == "left"&&mapData[y][x-1]==25) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x-=1;
            ore.setDirection("up");
            mapData[y][x]+=20;
        }
        else if (direction == "left"&&mapData[y][x-1]==27) {
            x-=1;
            ore.setDirection("down");
        }
        else if (direction == "right"&&mapData[y][x+1]==22) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
            mapData[y][x]+=20;
        }
        else if (direction == "right"&&mapData[y][x+1]==24) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
            ore.setDirection("up");
            mapData[y][x]+=20;
        }
        else if (direction == "right"&&mapData[y][x+1]==26) {
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
            ore.setDirection("down");
            mapData[y][x]+=20;
        }
        else if(direction=="down"&&mapData[y+1][x]==3){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
        }
        else if(direction=="up"&&mapData[y-1][x]==3){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
        }
        else if(direction=="left"&&mapData[y][x-1]==3){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x-=1;
        }
        else if(direction=="right"&&mapData[y][x+1]==3){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
        }
        else if(mapData[y][x]==50){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
             ore.setDirection("right");
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==48){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x+=1;
            ore.setDirection("right");
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==49){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x-=1;
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==51){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            x-=1;
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==45){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==47){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==44){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y-=1;
            mapData[y][x]+=20;
        }
        else if(mapData[y][x]==46){
            if(mapData[y][x]>=20&&mapData[y][x]<=60){
                mapData[y][x]-=20;
            }
            y+=1;
            mapData[y][x]+=20;
        }

        // 检查是否到达交付中心
        if(isSmallhub){
        if (deliveryCenter && x >= deliveryCenter->getX()&&x < deliveryCenter->getX()+2 && y >= deliveryCenter->getY()&&y < deliveryCenter->getY()+2) {
            if (deliveryCenter->acceptOre(ore)) {
                if(!isMoneyup){
                    deliveryCenter->increaseMoney();}
                else{
                    deliveryCenter->increaseMoneyup();
                }

                if(isGame1){
                if(ore.getType()=="Cycle"){
                    deliveryCenter->increaseTask();
                }
                Task1();
                }

                if(isGame2){
                    if(ore.getType()=="Rect"){
                        deliveryCenter->increaseTask();
                    }
                    Task2();
                }

                if(isGame3){
                    if(ore.getType()=="Left_Cycle"){
                        deliveryCenter->increaseTask();
                    }
                    Task3();
                }
            }
            // 从矿石列表中移除该矿石
            it = ores.erase(it);
        }
        else {
            // 更新矿石位置
            ore.setPosition(x, y);
            ++it;
        }
        }
        else if(isBighub){
            if (deliveryCenter && x >= 11&& x < 15 && y >= 6&&y < 10) {
                if (deliveryCenter->acceptOre(ore)) {
                    deliveryCenter->increaseMoney();

                    if(isGame1){
                        if(ore.getType()=="Cycle"){
                            deliveryCenter->increaseTask();
                        }
                        Task1();
                    }

                    if(isGame2){
                        if(ore.getType()=="Rect"){
                            deliveryCenter->increaseTask();
                        }
                        Task2();
                    }
                    if(isGame3){
                        if(ore.getType()=="Left_Cycle"){
                            deliveryCenter->increaseTask();
                        }
                        Task3();
                    }
                }

                it = ores.erase(it);
            }
            else {
                ore.setPosition(x, y);
                ++it;
            }
        }

    }

    update();
}


void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制地图
    if(isSmallhub){
    for (int i = 0; i < mapData.size(); i++) {
        for (int j = 0; j < mapData[i].size(); j++) {
            painter.setPen(Qt::lightGray);
            if(mapData[i][j]!=3){
                painter.drawRect(j * cellSize, i * cellSize, cellSize, cellSize);
            }
            if (deliveryCenter&&i==deliveryCenter->getY() && j == deliveryCenter->getX()) {
                QPixmap pixmap = deliveryCenter->getPixmap();
                painter.drawPixmap(j * cellSize, i * cellSize, deliveryCenter->getWidth() * cellSize, deliveryCenter->getHeight() * cellSize, pixmap);
                QString moneyText = QString("¥: %1").arg(deliveryCenter->getMoney());
                QFont font = painter.font();
                font.setPointSize(12);
                painter.setFont(font);

                int textX = j * cellSize +25;
                int textY = i * cellSize +35;

                painter.setPen(Qt::black);
                painter.drawText(textX, textY, moneyText);

                if(isGame1||isGame2){
                    QString taskText = QString("%1/20").arg(deliveryCenter->getTask());
                    painter.drawText(textX-6, textY+20, taskText);}
                else if(isGame3){
                    QString taskText = QString("%1/40").arg(deliveryCenter->getTask());
                    painter.drawText(textX-6, textY+20, taskText);}
            } else if (mapData[i][j] == 1) {
                QPixmap pixmap(":/image/cycle_mine.png");
                painter.drawPixmap(j * cellSize, i * cellSize, cellSize, cellSize, pixmap);
            } else if (mapData[i][j] == 2) {
                QPixmap pixmap(":/image/rect_mine.png");
                painter.drawPixmap(j * cellSize, i * cellSize, cellSize, cellSize, pixmap);
            } else if(mapData[i][j]==-1){
                QPixmap pixmap(":/image/barrier.png");
                painter.drawPixmap(j * cellSize, i * cellSize, cellSize, cellSize, pixmap);
            }
        }
    }
    }
    else if(isBighub){
        for(int i=11;i<15;i++){
            for(int j=6;j<10;j++){
                if(mapData[j][i]==5){
                    for (auto it = trashes.begin(); it != trashes.end(); ) {
                        Trash& trash = *it;
                        int x1 = trash.getX();
                        int y1 = trash.getY();
                        if(x1==i&&y1==j){
                            it=trashes.erase(it);
                            mapData[j][i]=0;
                            break;
                        }
                        else{
                            ++it;
                        }
                    }
                }
                else if(mapData[j][i]>=10&&mapData[j][i]<=13||mapData[j][i]==100){
                    for (auto it = cutters.begin(); it != cutters.end(); ) {
                        Cutter& cutter = *it;
                        int x1 = cutter.getX();
                        int y1 = cutter.getY();
                        if(x1==i&&y1==j){
                            it=cutters.erase(it);
                            mapData[j][i]=0;
                            break;
                        }
                        else{
                            ++it;
                        }
                    }
                }
                else if(mapData[j][i]>=20&&mapData[j][i]<=60){
                    for (auto it = belts.begin(); it != belts.end(); ) {
                        Belt& belt = *it;
                        int x1 = belt.getX();
                        int y1 = belt.getY();
                        if(x1==i&&y1==j){
                            it=belts.erase(it);
                            mapData[j][i]=0;
                            break;
                        }
                        else{
                            ++it;
                        }
                    }
                    for (auto it = ores.begin(); it != ores.end(); ) {
                        Ore& ore = *it;
                        int x1 = ore.getX();
                        int y1 = ore.getY();
                        if(x1==i&&y1==j){
                            it=ores.erase(it);
                            mapData[j][i]=0;
                            break;
                        }
                        else{
                            ++it;
                        }
                    }
                }
                update();
                mapData[j][i]=3;

            }
        }
        for (int i = 0; i < mapData.size(); i++) {
            for (int j = 0; j < mapData[i].size(); j++) {
                painter.setPen(Qt::lightGray);
                if(mapData[i][j]!=3){
                    painter.drawRect(j * cellSize, i * cellSize, cellSize, cellSize);
                }
                if (deliveryCenter&&i==6 && j == 11) {
                    QPixmap pixmap = QPixmap(":/image/hub_big.png");
                    painter.drawPixmap(440, 240, 160, 160, pixmap);
                    QString moneyText = QString("¥: %1").arg(deliveryCenter->getMoney());
                    QFont font = painter.font();
                    font.setPointSize(18);
                    painter.setFont(font);

                    int textX = j * cellSize +58;
                    int textY = i * cellSize +70;

                    painter.setPen(Qt::black);
                    painter.drawText(textX, textY, moneyText);

                    if(isGame1||isGame2){
                        QString taskText = QString("%1/20").arg(deliveryCenter->getTask());
                        painter.drawText(textX-6, textY+40, taskText);}
                    else if(isGame3){
                        QString taskText = QString("%1/40").arg(deliveryCenter->getTask());
                        painter.drawText(textX-6, textY+40, taskText);}
                } else if (mapData[i][j] == 1) {
                    QPixmap pixmap(":/image/cycle_mine.png");
                    painter.drawPixmap(j * cellSize, i * cellSize, cellSize, cellSize, pixmap);
                } else if (mapData[i][j] == 2) {
                    QPixmap pixmap(":/image/rect_mine.png");
                    painter.drawPixmap(j * cellSize, i * cellSize, cellSize, cellSize, pixmap);
                }
            }
        }
    }

    // 绘制Miner
    for (const Miner& miner : miners) {
        QPixmap* minerPixmap = nullptr;
        if (miner.getDirection() == "up") {
            minerPixmap = &minerIcons[0];
        } else if (miner.getDirection() == "down") {
            minerPixmap = &minerIcons[1];
        } else if (miner.getDirection() == "left") {
            minerPixmap = &minerIcons[2];
        } else if (miner.getDirection() == "right") {
            minerPixmap = &minerIcons[3];
        }
        if (minerPixmap) {
            painter.drawPixmap(miner.getX() * cellSize, miner.getY() * cellSize, cellSize, cellSize, *minerPixmap);
        }
    }

    // 绘制Cutter
    for (const Cutter& cutter : cutters) {
        QPixmap* cutterPixmap = nullptr;
        if (cutter.getDirection() == "up") {
            cutterPixmap = &cutterIcons[0];
        } else if (cutter.getDirection() == "down") {
            cutterPixmap = &cutterIcons[1];
        } else if (cutter.getDirection() == "left") {
            cutterPixmap = &cutterIcons[2];
        } else if (cutter.getDirection() == "right") {
            cutterPixmap = &cutterIcons[3];
        }
        if (cutterPixmap) {
            if(cutter.getDirection() == "up"||cutter.getDirection() == "down"){
                painter.drawPixmap(cutter.getX() * cellSize, cutter.getY() * cellSize, 2*cellSize, cellSize, *cutterPixmap);
            }
            else if(cutter.getDirection() == "left"||cutter.getDirection() == "right")
            {
                painter.drawPixmap(cutter.getX() * cellSize, cutter.getY() * cellSize, cellSize,2* cellSize, *cutterPixmap);
            }
        }
    }

    // 绘制Trash
    for (const Trash& trash : trashes) {
        QPixmap* trashPixmap = nullptr;
        if (trash.getDirection() == "up") {
            trashPixmap = &trashIcons[0];
        } else if (trash.getDirection() == "down") {
            trashPixmap = &trashIcons[1];
        } else if (trash.getDirection() == "left") {
            trashPixmap = &trashIcons[2];
        } else if (trash.getDirection() == "right") {
            trashPixmap = &trashIcons[3];
        }
        if (trashPixmap) {
            painter.drawPixmap(trash.getX() * cellSize, trash.getY() * cellSize, cellSize, cellSize, *trashPixmap);
        }
    }

    // 绘制Belt
    for (const Belt& belt : belts) {
        QPixmap* beltPixmap = nullptr;
        if (belt.getDirection() == "up") {
            beltPixmap = &beltIcons[0];
        } else if (belt.getDirection() == "down") {
            beltPixmap = &beltIcons[1];
        } else if (belt.getDirection() == "left") {
            beltPixmap = &beltIcons[2];
        } else if (belt.getDirection() == "right") {
            beltPixmap = &beltIcons[3];
        } else if (belt.getDirection() == "up_right") {
            beltPixmap = &beltIcons[4];
        } else if (belt.getDirection() == "up_left") {
            beltPixmap = &beltIcons[5];
        } else if (belt.getDirection() == "down_right") {
            beltPixmap = &beltIcons[6];
        } else if (belt.getDirection() == "down_left") {
            beltPixmap = &beltIcons[7];
        } else if (belt.getDirection() == "left_up") {
            beltPixmap = &beltIcons[8];
        } else if (belt.getDirection() == "left_down") {
            beltPixmap = &beltIcons[9];
        } else if (belt.getDirection() == "right_up") {
            beltPixmap = &beltIcons[10];
        } else if (belt.getDirection() == "right_down") {
            beltPixmap = &beltIcons[11];
        }
        if (beltPixmap) {
            painter.drawPixmap(belt.getX() * cellSize, belt.getY() * cellSize, cellSize, cellSize, *beltPixmap);
        }
    }

    // 绘制Ore
    for (const Ore& ore : ores) {
        QPixmap* orePixmap = nullptr;
        if(ore.getType()=="Cycle"){
        orePixmap=&oreIcons[0];
        }
        else if(ore.getType()=="Rect"){
           orePixmap=&oreIcons[1];
        }
        else if(ore.getType()=="Left_Cycle"){
            orePixmap=&oreIcons[2];
        }
        else if(ore.getType()=="Right_Cycle"){
            orePixmap=&oreIcons[3];
        }
        if(orePixmap){
            if(ore.getDirection()=="up"&&ore.getType()=="Rect"||ore.getDirection()=="up"&&ore.getType()=="Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+6, ore.getY() * cellSize+6, 28, 28, *orePixmap);
            }
            else if(ore.getDirection()=="up"&&ore.getType()=="Left_Cycle"||ore.getDirection()=="up"&&ore.getType()=="Right_Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+12, ore.getY() * cellSize+5, 16, 30, *orePixmap);
            }
            else if(ore.getDirection()=="down"&&ore.getType()=="Rect"||ore.getDirection()=="down"&&ore.getType()=="Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+6, ore.getY() * cellSize+6, 28, 28, *orePixmap);
            }
            else if(ore.getDirection()=="down"&&ore.getType()=="Left_Cycle"||ore.getDirection()=="down"&&ore.getType()=="Right_Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+12, ore.getY() * cellSize+5, 16, 30, *orePixmap);
            }
            else if(ore.getDirection()=="left"&&ore.getType()=="Rect"||ore.getDirection()=="left"&&ore.getType()=="Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+6, ore.getY() * cellSize+6, 28, 28, *orePixmap);
            }
            else if(ore.getDirection()=="left"&&ore.getType()=="Left_Cycle"||ore.getDirection()=="left"&&ore.getType()=="Right_Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+12, ore.getY() * cellSize+5, 16, 30, *orePixmap);
            }
            else if(ore.getDirection()=="right"&&ore.getType()=="Rect"||ore.getDirection()=="right"&&ore.getType()=="Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+6, ore.getY() * cellSize+6, 28, 28, *orePixmap);
            }
            else if(ore.getDirection()=="right"&&ore.getType()=="Left_Cycle"||ore.getDirection()=="right"&&ore.getType()=="Right_Cycle"){
                painter.drawPixmap(ore.getX() * cellSize+12, ore.getY() * cellSize+5, 16, 30, *orePixmap);
            }
    }
    }

    // 绘制Miner按钮图标
    painter.drawPixmap(1180, 50, 50, 50, minerIcons[4]);

    // 绘制Cutter按钮图标
    painter.drawPixmap(1180, 250, 50, 50, cutterIcons[4]);

    // 绘制Trash按钮图标
    painter.drawPixmap(1180, 350, 50, 50, trashIcons[4]);

    // 绘制Belt按钮图标
    painter.drawPixmap(1180, 150, 50, 50, beltIcons[12]);

    //绘制spade图标
    painter.drawPixmap(1180,450,50,50,spadeIcon);

    //绘制shop图标
    painter.drawPixmap(1180,550,50,50,shopIcon);

    if (draggingMiner) {
        QPixmap* minerPixmap = nullptr;
        if (currentDirection == "up") {
            minerPixmap = &minerIcons[0];
        } else if (currentDirection == "down") {
            minerPixmap = &minerIcons[1];
        } else if (currentDirection == "left") {
            minerPixmap = &minerIcons[2];
        } else if (currentDirection == "right") {
            minerPixmap = &minerIcons[3];
        }
        if (minerPixmap) {
            painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, cellSize, cellSize, *minerPixmap);
        }
    }

    if (draggingCutter) {
        QPixmap* cutterPixmap = nullptr;
        if (currentDirection == "up") {
            cutterPixmap = &cutterIcons[0];
        } else if (currentDirection == "down") {
            cutterPixmap = &cutterIcons[1];
        } else if (currentDirection == "left") {
            cutterPixmap = &cutterIcons[2];
        } else if (currentDirection == "right") {
            cutterPixmap = &cutterIcons[3];
        }
        if (cutterPixmap) {
           if(currentDirection == "up"||currentDirection == "down"){
                painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, 2*cellSize, cellSize, *cutterPixmap);
            }
           else if(currentDirection == "left"||currentDirection == "right")
            {
                painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, cellSize, 2*cellSize, *cutterPixmap);
            }
        }
    }

    if (draggingTrash) {
        QPixmap* trashPixmap = nullptr;
        if (currentDirection == "up") {
            trashPixmap = &trashIcons[0];
        } else if (currentDirection == "down") {
            trashPixmap = &trashIcons[1];
        } else if (currentDirection == "left") {
            trashPixmap = &trashIcons[2];
        } else if (currentDirection == "right") {
            trashPixmap = &trashIcons[3];
        }
        if (trashPixmap) {
            painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, cellSize, cellSize, *trashPixmap);
        }
    }

    if (draggingBelt) {
        QPixmap* beltPixmap = nullptr;
        if (currentDirection == "up") {
            beltPixmap = &beltIcons[0];
        } else if (currentDirection == "down") {
            beltPixmap = &beltIcons[1];
        } else if (currentDirection == "left") {
            beltPixmap = &beltIcons[2];
        } else if (currentDirection == "right") {
            beltPixmap = &beltIcons[3];
        } else if (currentDirection == "up_right") {
            beltPixmap = &beltIcons[4];
        } else if (currentDirection == "up_left") {
            beltPixmap = &beltIcons[5];
        } else if (currentDirection == "down_right") {
            beltPixmap = &beltIcons[6];
        } else if (currentDirection == "down_left") {
            beltPixmap = &beltIcons[7];
        } else if (currentDirection == "left_up") {
            beltPixmap = &beltIcons[8];
        } else if (currentDirection == "left_down") {
            beltPixmap = &beltIcons[9];
        } else if (currentDirection == "right_up") {
            beltPixmap = &beltIcons[10];
        } else if (currentDirection == "right_down") {
            beltPixmap = &beltIcons[11];
        }
        if (beltPixmap) {
            painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, cellSize, cellSize, *beltPixmap);
        }
    }

    if(draggingSpade){
        QPixmap* spadePixmap = nullptr;
        spadePixmap=&spadeIcon;
        if(spadePixmap){
            painter.drawPixmap(currentDragPos.x() - cellSize / 2, currentDragPos.y() - cellSize / 2, cellSize, cellSize, *spadePixmap);
        }
    }

    if (overlayWindow->isVisible()) {
        overlayWindow->raise();
    }

}

//鼠标点击事件
void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int x = event->x();
        int y = event->y();

        // 检查是否点击在Miner图标上
        if (x >= 1180 && x <= 1230 && y >= 50 && y <= 100) {
            currentDirection="up";
            draggingMiner = true;
            dragStartPos = event->pos();
            currentDragPos = event->pos();
        }

        // 检查是否点击在Cutter图标上
        if (x >= 1180 && x <= 1230 && y >= 250 && y <= 300) {
            currentDirection="up";
            draggingCutter = true;
            dragStartPos = event->pos();
            currentDragPos = event->pos();
        }

        // 检查是否点击在Trash图标上
        if (x >= 1180 && x <= 1230 && y >= 350 && y <= 400) {
            currentDirection="up";
            draggingTrash = true;
            dragStartPos = event->pos();
            currentDragPos = event->pos();
        }

        // 检查是否点击在Belt图标上
        if (x>= 1180 && x < 1230 && y>= 150 && y < 200) {
            draggingBelt = true;
            dragStartPos = event->pos();
            currentDragPos = event->pos();
            isAPressed = false;
            isWPressed = false;
            isSPressed = false;
            isDPressed = false;
            isRPressed = false;
        }

        // 检查是否点击在Spade图标上
        if (x >= 1180 && x <= 1230 && y >= 450 && y <= 500) {
            draggingSpade = true;
            dragStartPos = event->pos();
            currentDragPos = event->pos();
        }

        // 检查是否点击在Shop图标上
        if (x >= 1180 && x <= 1230 && y >= 550 && y <= 600) {
            shop->setCustomImage(QPixmap(":/image/list.png"));
            shop->show();
        }

    }
}

//鼠标拖动事件
void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (draggingMiner||draggingCutter||draggingTrash||draggingBelt||draggingSpade) {
        currentDragPos = event->pos();
        update();
    }
}

//鼠标释放事件
void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (draggingMiner) {
        draggingMiner = false;
        int x = event->x() / cellSize;
        int y = event->y() / cellSize;

        if (isMineralTile(x, y)) {
            miners.emplace_back(x, y, currentDirection); // 创建并添加Miner对象
        }
        update();
    }

    if (draggingCutter) {
        draggingCutter = false;
        int x = event->x() / cellSize;
        int y = event->y() / cellSize;

        if (isEmptyTile(x, y)) {
            cutters.emplace_back(x, y, currentDirection); // 创建并添加Cutter对象

        if(currentDirection=="up"){
            mapData[y][x]=10;
            mapData[y][x+1]=10;
        }
        else if(currentDirection=="down"){
            mapData[y][x]=11;
            mapData[y][x+1]=11;
        }
        else if(currentDirection=="right"){
            mapData[y][x]=12;
            mapData[y+1][x]=12;
        }
        else if(currentDirection=="left"){
            mapData[y][x]=13;
            mapData[y+1][x]=13;
        }
        }
        update();
    }

    if (draggingTrash) {
        draggingTrash = false;
        int x = event->x() / cellSize;
        int y = event->y() / cellSize;

        if (isEmptyTile(x, y)) {
            trashes.emplace_back(x, y, currentDirection); // 创建并添加Trash对象
            mapData[y][x]=5;
        }
        update();
    }

    if (draggingBelt) {
        draggingBelt = false;
        int x = event->x() / cellSize;
        int y = event->y() / cellSize;

        if (isEmptyTile(x, y)) {
            belts.emplace_back(x, y, currentDirection); // 创建并添加Belt对象
        if(currentDirection=="up"){
            mapData[y][x]=20;
        }
        else if(currentDirection=="down"){
            mapData[y][x]=21;
        }
        else if(currentDirection=="right"){
            mapData[y][x]=22;
        }
        else if(currentDirection=="left"){
            mapData[y][x]=23;
        }
        else if(currentDirection=="right_up"){
            mapData[y][x]=24;
        }
        else if(currentDirection=="left_up"){
            mapData[y][x]=25;
        }
        else if(currentDirection=="right_down"){
            mapData[y][x]=26;
        }
        else if(currentDirection=="left_down"){
            mapData[y][x]=27;
        }
        else if(currentDirection=="up_right"){
            mapData[y][x]=28;
        }
        else if(currentDirection=="up_left"){
            mapData[y][x]=29;
        }
        else if(currentDirection=="down_right"){
            mapData[y][x]=30;
        }
        else if(currentDirection=="down_left"){
            mapData[y][x]=31;
        }
        }
        update();
    }

    if(draggingSpade){
        draggingSpade = false;
        int x = event->x() / cellSize;
        int y = event->y() / cellSize;
        if(mapData[y][x]==5){
            for (auto it = trashes.begin(); it != trashes.end(); ) {
                Trash& trash = *it;
                int x1 = trash.getX();
                int y1 = trash.getY();
                if(x1==x&&y1==y){
                    it=trashes.erase(it);
                    mapData[y][x]=0;
                    break;
                }
                else{
                    ++it;
                }
            }
        }
        else if(mapData[y][x]>=10&&mapData[y][x]<=13||mapData[y][x]==100){
            for (auto it = cutters.begin(); it != cutters.end(); ) {
                Cutter& cutter = *it;
                int x1 = cutter.getX();
                int y1 = cutter.getY();
                if(x1==x&&y1==y){
                    it=cutters.erase(it);
                    mapData[y][x]=0;
                    break;
                }
                else{
                    ++it;
                }
            }
        }
        else if(mapData[y][x]>=20&&mapData[y][x]<=60){
            for (auto it = belts.begin(); it != belts.end(); ) {
                Belt& belt = *it;
                int x1 = belt.getX();
                int y1 = belt.getY();
                if(x1==x&&y1==y){
                    it=belts.erase(it);
                    mapData[y][x]=0;
                    break;
                }
                else{
                    ++it;
                }
            }
            for (auto it = ores.begin(); it != ores.end(); ) {
                Ore& ore = *it;
                int x1 = ore.getX();
                int y1 = ore.getY();
                if(x1==x&&y1==y){
                    it=ores.erase(it);
                    mapData[y][x]=0;
                    break;
                }
                else{
                    ++it;
                }
            }


        }
        else if(mapData[y][x]>=1&&mapData[y][x]<=2){
            for (auto it = miners.begin(); it != miners.end(); ) {
                Miner& miner = *it;
                int x1 = miner.getX();
                int y1 = miner.getY();
                if(x1==x&&y1==y){
                    it=miners.erase(it);
                    break;
                }
                else{
                    ++it;
                }
            }
            for (auto it = ores.begin(); it != ores.end(); ) {
                Ore& ore = *it;
                int x1 = ore.getX();
                int y1 = ore.getY();
                if(x1==x&&y1==y){
                    it=ores.erase(it);
                    break;
                }
                else{
                    ++it;
                }
            }

        }
        update();
    }

}

bool MapWidget::isEmptyTile(int x, int y) const
{
    if (x < 0 || y < 0 || x >= mapData[0].size() || y >= mapData.size()) {
        return false;
    }
    return mapData[y][x] == 0&&mapData[y][x]!=-1;
}

bool MapWidget::isMineralTile(int x, int y) const
{
    if (x < 0 || y < 0 || x >= mapData[0].size() || y >= mapData.size()) {
        return false;
    }
    return mapData[y][x] == 1 || mapData[y][x] == 2;
}

//采矿动画
void MapWidget::updateMiners() {
    for (Miner& miner : miners) {
        int x = miner.getX();
        int y = miner.getY();
        std::string direction = miner.getDirection();
        std::string type;
        if(mapData[y][x]==1){
            type="Cycle";
        }
        else if(mapData[y][x]==2){
            type="Rect";
        }

        // 检查采矿器对应方向前方是否有传送带
        int nextX = x, nextY = y;
        if (direction == "up") {
            nextY--;
        } else if (direction == "down") {
            nextY++;
        } else if (direction == "left") {
            nextX--;
        } else if (direction == "right") {
            nextX++;
        }
        auto it = std::find_if(belts.begin(), belts.end(), [nextX, nextY, direction](const Belt& belt) {
            return belt.getX() == nextX && belt.getY() == nextY && belt.getDirection() == direction;
        });

        if (it != belts.end()) {
            if (direction == "up") {
                nextY++;
            } else if (direction == "down") {
                nextY--;
            } else if (direction == "left") {
                nextX++;
            } else if (direction == "right") {
                nextX--;
            }
            generateOre(nextX, nextY, direction,type);
        }
    }
}

//切割动画
void MapWidget::updateCutters() {
    for (Cutter& cutter : cutters) {
        int x = cutter.getX();
        int y = cutter.getY();
        std::string direction = cutter.getDirection();
        std::string type;

        // 检查Cutter前后是否有传送带
        int nextX = x, nextY = y;
        int nextX_side=0;
        int nextY_side=0;
        if (direction == "up") {
            nextX_side=x+1; nextY_side=y;
        } else if (direction == "down") {
            nextX_side=x-1;nextY_side=y;
        } else if (direction == "left") {
            nextX_side=x;nextY_side=y+1;
        } else if (direction == "right") {
            nextX_side=x;nextY_side=y-1;
        }

        if (direction == "up"&&mapData[y+1][x]==20&&mapData[y-1][x]==20&&mapData[y-1][x+1]==20&&mapData[y][x]==100||direction == "up"&&mapData[y+1][x]==40&&mapData[y-1][x]==20&&mapData[y-1][x+1]==20&&mapData[y][x]==100) {
            generateOre(nextX, nextY, direction,"Left_Cycle");
            generateOre(nextX_side, nextY_side, direction,"Right_Cycle");
        } else if (direction == "down"&&mapData[y+1][x]==21&&mapData[y-1][x+1]==21&&mapData[y+1][x+1]==21&&mapData[y][x]==100||direction == "down"&&mapData[y+1][x]==21&&mapData[y-1][x+1]==41&&mapData[y+1][x+1]==21&&mapData[y][x]==100) {
            nextX_side+=2;
            generateOre(nextX, nextY, direction,"Left_Cycle");
            generateOre(nextX_side, nextY_side, direction,"Right_Cycle");
        } else if (direction == "left"&&mapData[y][x-1]==23&&mapData[y+1][x+1]==23&&mapData[y+1][x-1]==23&&mapData[y][x]==100||direction == "left"&&mapData[y][x-1]==23&&mapData[y+1][x+1]==43&&mapData[y+1][x-1]==23&&mapData[y][x]==100) {
            nextY++;nextY_side--;
            generateOre(nextX, nextY, direction,"Left_Cycle");
            generateOre(nextX_side, nextY_side, direction,"Right_Cycle");
        } else if (direction == "right"&&mapData[y][x-1]==22&&mapData[y][x+1]==22&&mapData[y+1][x+1]==22&&mapData[y][x]==100||direction == "right"&&mapData[y][x-1]==42&&mapData[y][x+1]==22&&mapData[y+1][x+1]==22&&mapData[y][x]==100) {
            nextY_side+=2;
            generateOre(nextX, nextY, direction,"Left_Cycle");
            generateOre(nextX_side, nextY_side, direction,"Right_Cycle");
        }

    }
}

//生成新的矿石
void MapWidget::generateOre(int x, int y, const std::string& direction,const std::string& type) {

    if(type=="Cycle"){
        QPixmap orePixmap(":/image/cycle.png");
        ores.emplace_back(x, y, direction,type,  orePixmap);
    }
    else if(type=="Rect"){
    QPixmap orePixmap(":/image/rect.png");
        ores.emplace_back(x, y, direction, type, orePixmap);
    }
    else if(type=="Left_Cycle"){
        QPixmap orePixmap(":/image/left_cycle.png");
        ores.emplace_back(x, y, direction, type, orePixmap);
    }
    else if(type=="Right_Cycle"){
        QPixmap orePixmap(":/image/right_cycle.png");
        ores.emplace_back(x, y, direction, type, orePixmap);
    }

}

void MapWidget::setMapData(const std::vector<std::vector<int>>& data)
{
    mapData = data;
    update();
}

void MapWidget::setDeliveryCenter(DeliveryCenter* center)
{
    deliveryCenter = center;
    update();
}

//键盘按下事件
void MapWidget::keyPressEvent(QKeyEvent *event)
{
    if (draggingMiner||draggingCutter||draggingTrash) {

        if (event->key() == Qt::Key_W) {
            currentDirection = "up";
        } else if (event->key() == Qt::Key_S) {
            currentDirection = "down";
        } else if (event->key() == Qt::Key_A) {
            currentDirection = "left";
        } else if (event->key() == Qt::Key_D) {
            currentDirection = "right";
        }
        update();
    }
    if (draggingBelt) {
        if (event->key() == Qt::Key_A) {
            isAPressed = true;
        }
        if (event->key() == Qt::Key_W) {
            isWPressed = true;
        }
        if (event->key() == Qt::Key_S) {
            isSPressed = true;
        }
        if (event->key() == Qt::Key_D) {
            isDPressed = true;
        }
        if (event->key() == Qt::Key_R) {
            isRPressed = true;
        }
        if (isWPressed&&isDPressed&&isRPressed) {
            currentDirection = "right_up";
        } else if (isWPressed&&isAPressed&&isRPressed) {
            currentDirection = "left_up";
        } else if (isSPressed&&isDPressed&&isRPressed) {
            currentDirection = "right_down";
        } else if (isSPressed&&isAPressed&&isRPressed) {
            currentDirection = "left_down";
        }
        else if (isWPressed&&isDPressed) {
            currentDirection = "up_right";
        } else if (isWPressed&&isAPressed) {
            currentDirection = "up_left";
        } else if (isSPressed&&isDPressed) {
            currentDirection = "down_right";
        } else if (isSPressed&&isAPressed) {
            currentDirection = "down_left";
        }
        else if (isWPressed) {
            currentDirection = "up";
        } else if (isSPressed) {
            currentDirection = "down";
        } else if (isAPressed) {
            currentDirection = "left";
        } else if (isDPressed) {
            currentDirection = "right";
        }
        update();
    }
}

//键盘释放事件
void MapWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (draggingBelt){
        if (event->key() == Qt::Key_A) {
            isAPressed = false;
        }
        if (event->key() == Qt::Key_W) {
            isWPressed = false;
        }
        if (event->key() == Qt::Key_S) {
            isSPressed = false;
        }
        if (event->key() == Qt::Key_D) {
            isDPressed = false;
        }
        if (event->key() == Qt::Key_R) {
            isRPressed = false;
        }
    }
}

void MapWidget::Task1() {
    if (deliveryCenter->getTask() == 20 && !overlayWindow->isVisible()) {
        overlayWindow->setCustomImage(QPixmap(":/image/Task2.png"));
        overlayWindow->show();
    }
}
void MapWidget::Task2() {
    if (deliveryCenter->getTask() == 20 && !overlayWindow->isVisible()) {
        overlayWindow->setCustomImage(QPixmap(":/image/Task3.png"));
        overlayWindow->show();
    }
}

void MapWidget::Task3(){

}

//三种工具升级
void MapWidget::handleOverlayButtonClicked(int buttonId) {
    switch (buttonId) {
    case 1:
        v_belt-=200;
        break;
    case 2:
        v_cutter-=600;
        break;
    case 3:
        v_miner-=600;
        break;
    default:
        break;
    }

    overlayWindow->hide();
    if(isGame1&&deliveryCenter->getTask()!=0){
        isGame1=false;
        isGame2=true;
        deliveryCenter->resetTask();
    }
    else if(isGame2){
        isGame2=false;
        isGame3=true;
        deliveryCenter->resetTask();
    }
}

//商店的升级项目
void MapWidget::handleShopButtonClicked(int buttonId) {
    switch (buttonId) {
    case 1:
        if(deliveryCenter->getMoney()>=200){
            deliveryCenter->consumeMoney();
            isSmallhub=false;
            isBighub=true;
        }
        break;
    case 2:
        if(deliveryCenter->getMoney()>=200){
            deliveryCenter->consumeMoney();
            isMoneyup=true;
        }
        break;
    case 3:
        if(deliveryCenter->getMoney()>=200){
            deliveryCenter->consumeMoney();
            clearBarrier();
        }
        break;
    default:
        break;
    }

    shop->hide();

}

//清除障碍
void MapWidget::clearBarrier(){
    for (int i = 0; i < mapData.size(); i++) {
        for (int j = 0; j < mapData[i].size(); j++) {
            if(mapData[i][j]==-1){
                mapData[i][j]=0;
            }
        }
    }
}


