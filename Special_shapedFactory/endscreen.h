#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class EndScreen : public QWidget
{
    Q_OBJECT
public:
    EndScreen(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap backgroundPixmap;
    QPixmap logoPixmap;
    QPixmap winPixmap;
};

#endif // ENDSCREEN_H
