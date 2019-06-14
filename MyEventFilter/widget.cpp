#include "widget.h"

#include <QKeyEvent>
#include <QWheelEvent>

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);  // 安装事件过滤器
    ui->spinBox->installEventFilter(this);

    QKeyEvent myEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    qApp->sendEvent(ui->spinBox, &myEvent);  // sendEvent要求event栈上创建

    QKeyEvent* myEvent2 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    qApp->postEvent(ui->spinBox, myEvent2);  // postEvent要求event堆上创建会自动delete
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->textEdit) {
        if (event->type() == QEvent::Wheel) {
            QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
            if (wheelEvent->angleDelta().y() > 0) {
                ui->textEdit->zoomIn();
            } else {
                ui->textEdit->zoomOut();
            }
            return true;  // 事件已经被处理
        }
    } else if (obj == ui->spinBox) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                ui->spinBox->setValue(0);
                return true;
            } else {
                return false;  // 事件可以传递
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
