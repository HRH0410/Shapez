#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextBrowser>


class Help : public QWidget
{
    Q_OBJECT
public:
    Help(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void Return();//返回开始界面的信号

private:
    QPixmap backgroundPixmap;
    QTextBrowser *help_text;//帮助文本
};

#endif // HELP_H
