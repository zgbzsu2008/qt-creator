#include "widget.h"

#include <QDebug>
#include <QFileSystemModel>
#include <QLayout>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QTableView>
#include <QTreeView>

#include "stringlistmodel.h"

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    QStringList list;
    list << "A"
         << "B"
         << "C";

    model = new StringListModel(list);

    listView = new QListView(this);
    listView->setModel(model);

    // 设置拖拽
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);

    tableView = new QTableView(this);
    tableView->setModel(model);

    treeView = new QTreeView(this);
    treeView->setModel(model);

    insert_btn = new QPushButton("insert", this);
    remove_btn = new QPushButton("remove", this);

    QGridLayout* lay = new QGridLayout(this);
    lay->addWidget(treeView, 0, 0);
    lay->addWidget(listView, 0, 1);
    lay->addWidget(tableView, 0, 2);
    lay->addWidget(insert_btn, 1, 0);
    lay->addWidget(remove_btn, 2, 0);

    connect(insert_btn, &QPushButton::clicked, this, &Widget::on_insert_clicked);
    connect(remove_btn, &QPushButton::clicked, this, &Widget::on_remove_clicked);
}

Widget::~Widget() {}

void Widget::on_insert_clicked()
{
    int row = listView->currentIndex().row() + 1;
    model->insertRows(row, 1);
}

void Widget::on_remove_clicked()
{
    int row = listView->currentIndex().row();
    if (row >= 0) {
        model->removeRows(row, 1);
    }
}
