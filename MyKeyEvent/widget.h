#ifndef WIDGET_H
#define WIDGET_H

#include <QMap>
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

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    Ui::Widget *ui;
    QMap<int, bool> keys;
};

#endif  // WIDGET_H
