#ifndef DELIVERYCENTER_H
#define DELIVERYCENTER_H

#include <QPixmap>
#include "ore.h"

class DeliveryCenter {
public:
    DeliveryCenter(int x, int y, int width, int height, int money, int task, const QString& imagePath);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getMoney() const;//获取金币数
    int getCycle() const;//判断矿石类型
    int getTask() const;//获取任务完成量
    void increaseMoney();//收取矿石后增加金币
    void increaseMoneyup();//商店升级矿石价值
    void consumeMoney();//在商店升级后花费
    void increaseTask();//接受任务所需矿石后任务完成数增加
    void resetTask();//将任务重置
    QPixmap getPixmap() const;
    bool acceptOre(const Ore& ore);//接收运送来的矿石

private:
    int x;
    int y;
    int width;
    int height;
    int money;//交付中心总金币数
    int task;//任务所需矿石数
    QPixmap pixmap;
};

#endif // DELIVERYCENTER_H
