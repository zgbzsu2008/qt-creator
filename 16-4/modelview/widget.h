#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QListView;
class QTreeView;
class QTableView;
class QPushButton;
class QLineEdit;
class StringListModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void on_insert_clicked();
    void on_remove_clicked();

private:
    QListView *listView;
    QTreeView *treeView;
    QTableView *tableView;
    StringListModel *model;

    QPushButton *insert_btn;
    QPushButton *remove_btn;
};

#endif  // WIDGET_H
