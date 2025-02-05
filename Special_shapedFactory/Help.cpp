#include "Help.h"
#include <QPushButton>
#include <QFont>
#include <QPainter>
#include <QVBoxLayout>

Help::Help(QWidget *parent) : QWidget(parent)
{
    QPushButton *ReturnButton = new QPushButton("Return", this);

    // 设置按钮的字体和字号
    QFont font("Comic Sans MS", 22, QFont::Bold);
    ReturnButton->setFont(font);
    ReturnButton->setFixedSize(200, 100);

    connect(ReturnButton, &QPushButton::clicked, this, &Help::Return);

    setFixedSize(1280, 700);

    backgroundPixmap=QPixmap(":/image/background.jpg");

    ReturnButton->move(540, 570);

    //设置帮助文本
    help_text=new QTextBrowser(this);
    help_text->setFixedSize(1000,540);
    help_text->move(140, 15);
    help_text->setFont(QFont("Comic Sans MS", 14));
    QString helpContent = R"(
        <h2>欢迎来到异形工厂！</h2>
        <p>你可以通过拖拽各种工具在地图上搭建自己的工厂，完成任务，升级工厂，以赢取最后的奖杯🏆</p>
        <ul>
            <li><b>开采器</b>：将开采器放在矿石上可以开采对应矿石</li>
            <li><b>传送带</b>：开采器开采的矿石将通过传送带运送至交付中心</li>
            <li><b>切割机</b>：切割机只能切割圆形矿石，切割后的矿石将分为两路进行运输</li>
            <li><b>垃圾桶</b>：通过在传送带传送方向后面紧接垃圾桶，可以将不需要的矿石回收</li>
            <li><b>铁铲</b>：当你摆错或需要重新搭建工厂时，可以通过铁铲将你已经摆放的工具清除</li>
        </ul>
            <p>注：</p>
            <ul>
            <li>你可以通过键盘上的"W" "A" "S" "D"在拖拽时改变对应工具的方向</li>
            <li>对于传送带，你可以通过同时按下其中两个或两个键加上"R"来刻画它的各种转向</li>
            <li>只有输出及运送物品的方向正确，工厂才能正常运行，否则会停滞</li>
            <li>每个新关卡开始时，你可以选择升级开采器、传送带、切割机中的一个，以提升它们的速率</li>
            <li>通过消耗金币，你可以在商店中升级交付中心，提升矿石价值或者清楚障碍</li>
            <li>根据每一关的任务，你需要开采一定数量的特定矿石，通过三关后即可获胜</li>
        </ul>
        <p>感谢游玩！</p>

    )";
    help_text->setHtml(helpContent);

}

void Help::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, 1280, 700, backgroundPixmap);
    QWidget::paintEvent(event);
}
