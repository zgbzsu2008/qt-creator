#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QListView;
class QTreeView;
class QTableView;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QListView *listView;
    QTreeView *treeView;
    QTableView *tableView;
};

#endif  // WIDGET_H
