#include "Shop.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

Shop::Shop(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(1280, 700);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignCenter);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignRight);
    imageLabel->setFixedSize(900, 80);

    topLayout->addWidget(imageLabel);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    button1 = new QPushButton(this);
    button2 = new QPushButton(this);
    button3 = new QPushButton(this);

    // 设置按钮的贴图
    button1->setIcon(QIcon(":/image/hub_up.png"));
    button1->setIconSize(QSize(300, 300));
    button2->setIcon(QIcon(":/image/money_up.png"));
    button2->setIconSize(QSize(300,300));
    button3->setIcon(QIcon(":/image/clear_barrier.png"));
    button3->setIconSize(QSize(300, 300));

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(layout);

    connect(button1, &QPushButton::clicked, this, &Shop::handleButton1);
    connect(button2, &QPushButton::clicked, this, &Shop::handleButton2);
    connect(button3, &QPushButton::clicked, this, &Shop::handleButton3);
}

void Shop::handleButton1() {
    emit buttonClicked(1);
}

void Shop::handleButton2() {
    emit buttonClicked(2);
}

void Shop::handleButton3() {
    emit buttonClicked(3);
}

void Shop::setCustomImage(const QPixmap &pixmap) {
    QImage image = pixmap.toImage();
    QImage scaledImage = image.scaled(900, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap scaledPixmap = QPixmap::fromImage(scaledImage);
    imageLabel->setPixmap(scaledPixmap);

}
