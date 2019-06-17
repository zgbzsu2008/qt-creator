#include "widget.h"

#include <QLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QTreeWidget>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    {
        listWidget = new QListWidget(this);

        new QListWidgetItem("A", listWidget);  // 1
        new QListWidgetItem("C", listWidget);
        QListWidgetItem *item = new QListWidgetItem;
        item->setText("B");
        item->setIcon(QIcon("../modelview/yafeilinux.png"));
        item->setToolTip("this is B");
        listWidget->insertItem(1, item);  // 2

        listWidget->sortItems(Qt::DescendingOrder);

        listWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // 单选
        listWidget->setDragEnabled(true);                                  // 启用拖动
        listWidget->viewport()->setAcceptDrops(true);                      // 接收拖放
        listWidget->setDragDropMode(QAbstractItemView::InternalMove);      // 移动
    }
    {
        treeWidget = new QTreeWidget(this);
        treeWidget->setColumnCount(2);

        QStringList header;
        header << "name"
               << "year";
        treeWidget->setHeaderLabels(header);

        QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);  // 1
        item->setText(0, "A");
        QTreeWidgetItem *student = new QTreeWidgetItem(item);
        student->setText(0, "Tom");
        student->setText(1, "1986");

        QTreeWidgetItem *item2 = new QTreeWidgetItem(treeWidget, item);  // 2
        item2->setText(0, "B");

        QTreeWidgetItem *item3 = new QTreeWidgetItem;
        item3->setText(0, "C");
        treeWidget->addTopLevelItem(item3);  // 3
    }
    {
        tableWidget = new QTableWidget(3, 2, this);
        QTableWidgetItem *hv = new QTableWidgetItem("first");
        tableWidget->setVerticalHeaderItem(0, hv);
        QTableWidgetItem *hh = new QTableWidgetItem("id");
        tableWidget->setHorizontalHeaderItem(0, hh);

        QTableWidgetItem *item = new QTableWidgetItem("qt");
        tableWidget->setItem(1, 1, item);  // 1
    }

    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->addWidget(listWidget);
    lay->addWidget(treeWidget);
    lay->addWidget(tableWidget);
}

Widget::~Widget() {}
