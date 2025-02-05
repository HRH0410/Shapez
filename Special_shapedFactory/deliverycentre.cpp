#include "deliverycentre.h"

DeliveryCenter::DeliveryCenter(int x, int y, int width, int height, int money, int task, const QString& imagePath)
    : x(x), y(y), width(width), height(height), money(money),task(task), pixmap(imagePath) {}

int DeliveryCenter::getX() const { return x; }
int DeliveryCenter::getY() const { return y; }
int DeliveryCenter::getWidth() const { return width; }
int DeliveryCenter::getHeight() const { return height; }
int DeliveryCenter::getMoney() const { return money; }
int DeliveryCenter::getTask() const{return task; }

void DeliveryCenter::increaseMoney() {
    money +=2;
}

void DeliveryCenter::increaseMoneyup() {
    money +=4;
}

void DeliveryCenter::consumeMoney(){
    money-=200;
}
void DeliveryCenter::increaseTask() {
    task ++;
}

void DeliveryCenter::resetTask() {
    task=0;
}

bool DeliveryCenter::acceptOre(const Ore& ore) {
    return true;
}

QPixmap DeliveryCenter::getPixmap() const { return pixmap; }
