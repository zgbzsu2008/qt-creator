#include "widget.h"

#include <QDebug>
#include <QKeyEvent>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFocus();
    startTimer(1000 / 60);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    // ctrl + m 窗口最大化
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_M) {
            setWindowState(Qt::WindowMaximized);
        }
    }

    keys[event->key()] = true;
    return QWidget::keyPressEvent(event);
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
    return QWidget::keyReleaseEvent(event);
}

void Widget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QPoint pos = ui->pushButton->pos();
    if (keys[Qt::Key_Up]) {
        pos.setY(pos.y() - 1);
    }

    if (keys[Qt::Key_Down]) {
        pos.setY(pos.y() + 1);
    }

    if (keys[Qt::Key_Left]) {
        pos.setX(pos.x() - 1);
    }

    if (keys[Qt::Key_Right]) {
        pos.setX(pos.x() + 1);
    }

    ui->pushButton->move(pos);
}
