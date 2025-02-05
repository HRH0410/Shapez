#include "OverlayWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

OverlayWindow::OverlayWindow(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(1280, 700);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignCenter);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignRight);
    imageLabel->setFixedSize(900, 120);

    topLayout->addWidget(imageLabel);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    button1 = new QPushButton(this);
    button2 = new QPushButton(this);
    button3 = new QPushButton(this);

    // 设置按钮的贴图
    button1->setIcon(QIcon(":/image/belt_button.png"));
    button1->setIconSize(QSize(300, 300));
    button2->setIcon(QIcon(":/image/cutter_button.png"));
    button2->setIconSize(QSize(300,300));
    button3->setIcon(QIcon(":/image/miner_button.png"));
    button3->setIconSize(QSize(300, 300));

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(layout);

    connect(button1, &QPushButton::clicked, this, &OverlayWindow::handleButton1);
    connect(button2, &QPushButton::clicked, this, &OverlayWindow::handleButton2);
    connect(button3, &QPushButton::clicked, this, &OverlayWindow::handleButton3);
}

void OverlayWindow::handleButton1() {
    emit buttonClicked(1);
}

void OverlayWindow::handleButton2() {
    emit buttonClicked(2);
}

void OverlayWindow::handleButton3() {
    emit buttonClicked(3);
}

void OverlayWindow::setCustomImage(const QPixmap &pixmap) {
    QImage image = pixmap.toImage();
    QImage scaledImage = image.scaled(900, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap scaledPixmap = QPixmap::fromImage(scaledImage);
    imageLabel->setPixmap(scaledPixmap);

}
