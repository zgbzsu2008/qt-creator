#include "widget.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QTime>
#include <QTimer>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // QTimerEvent
    int times[3] = {1000, 1500, 2200};
    for (int i = 0; i < 3; ++i) {
        timerIds[i] = startTimer(times[i]);
    }

    // QTimer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::timerUpdate);
    timer->start(1000);

    // 随机数
    qsrand(static_cast<uint>(QTime::currentTime().second()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    qDebug() << "timer id : " << event->timerId();
}

void Widget::timerUpdate()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if (time.second() % 2 == 0) {
        text[2] = ' ';
    }
    ui->lcdNumber->display(text);

    int x = qrand() % 200;
    int y = static_cast<int>(QRandomGenerator::global()->generate() % 200);  // QRandomGenerator
    ui->lcdNumber->move(x, y);
}
