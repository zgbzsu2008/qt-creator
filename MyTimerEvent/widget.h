#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void timerEvent(QTimerEvent *event);

private slots:
    void timerUpdate();

private:
    Ui::Widget *ui;
    int timerIds[3];
};

#endif  // WIDGET_H
