#include "widget.h"

#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QTableView>
#include <QTreeView>

#include "stringlistmodel.h"

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    QStringList list;
    list << "A"
         << "B"
         << "C";

    StringListModel* model = new StringListModel(list);

    listView = new QListView(this);
    listView->setModel(model);

    tableView = new QTableView(this);
    tableView->setModel(model);

    treeView = new QTreeView(this);
    treeView->setModel(model);

    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(treeView);
    lay->addWidget(listView);
    lay->addWidget(tableView);
}

Widget::~Widget() {}
