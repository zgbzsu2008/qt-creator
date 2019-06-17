#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QListWidget;
class QTableWidget;
class QTreeWidget;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QListWidget *listWidget;
    QTableWidget *tableWidget;
    QTreeWidget *treeWidget;
};

#endif  // WIDGET_H
