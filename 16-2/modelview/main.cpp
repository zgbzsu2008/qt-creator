#include <QApplication>
#include <QDebug>
#include <QStandardItemModel>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStandardItemModel model;
    QStandardItem *parentItem = model.invisibleRootItem();  // 不可见

    // item0
    QStandardItem *item0 = new QStandardItem;
    item0->setText("A");
    QPixmap pixmap(50, 50);
    pixmap.fill(Qt::red);
    item0->setIcon(QIcon(pixmap));
    item0->setToolTip("indexA");
    parentItem->appendRow(item0);

    // item1
    parentItem = item0;
    QStandardItem *item1 = new QStandardItem;
    item1->setText("B");
    QPixmap pixmap1(50, 50);
    pixmap1.fill(Qt::blue);
    item1->setIcon(QIcon(pixmap1));
    item1->setToolTip("indexB");
    parentItem->appendRow(item1);

    // item2
    QStandardItem *item2 = new QStandardItem;
    QPixmap pixmap2(50, 50);
    pixmap2.fill(Qt::green);
    item2->setIcon(QIcon(pixmap2));
    item2->setData("C", Qt::EditRole);                   // QString
    item2->setData("indexC", Qt::ToolTipRole);           // QString
    item2->setData(QIcon(pixmap2), Qt::DecorationRole);  // QIcon QPixmap QColor
    parentItem->appendRow(item2);

    // show
    QTreeView view;
    view.setModel(&model);
    view.show();

    // get
    QModelIndex indexA = model.index(0, 0, QModelIndex());
    qDebug() << "indexA row count: " << model.rowCount(indexA);

    QModelIndex indexB = model.index(0, 0, indexA);
    qDebug() << "indexB text: " << model.data(indexB, Qt::EditRole).toString();
    qDebug() << "indexB toolTip: " << model.data(indexB, Qt::ToolTipRole).toString();

    return app.exec();
}
