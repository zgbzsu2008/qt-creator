#include "widget.h"

#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QTreeView>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    QFileSystemModel* model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());

    treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::currentPath()));

    listView = new QListView(this);
    listView->setModel(model);
    listView->setRootIndex(model->index(QDir::currentPath()));

    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(treeView);
    lay->addWidget(listView);
}

Widget::~Widget() {}
