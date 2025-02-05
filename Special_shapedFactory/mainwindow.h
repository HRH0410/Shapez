#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);

signals:
    void startGame();
};

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

    // 设置地图数据
    void setMapData(const std::vector<std::vector<int>>& data);

    // 设置交付中心
    void setDeliveryCenter(int x, int y);

private:
    // 地图大小
    int mapWidth;
    int mapHeight;

    // 地图数据结构，每个元素代表一个格子
    std::vector<std::vector<int>> mapData;

    // 交付中心
    int deliveryCenterX;
    int deliveryCenterY;

protected:
    void paintEvent(QPaintEvent *event) override;
};

class EndWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EndWidget(QWidget *parent = nullptr);

signals:
    void restartGame();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGame();
    void showEnd();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    StartWidget *startWidget;
    GameWidget *gameWidget;
};

#endif // MAINWINDOW_H
