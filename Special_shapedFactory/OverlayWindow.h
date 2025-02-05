#ifndef OVERLAYWINDOW_H
#define OVERLAYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class OverlayWindow : public QWidget {
    Q_OBJECT

public:
    OverlayWindow(QWidget *parent = nullptr);
    void setCustomImage(const QPixmap &pixmap);

signals:
    void buttonClicked(int buttonId);

private:
    QLabel *imageLabel;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

private slots:
    void handleButton1();
    void handleButton2();
    void handleButton3();
};

#endif
