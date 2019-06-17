#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTableView>

#include "spinboxdelegate.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->addAction(tr("当前项目"), this, &MainWindow::getCurrentItemData);
    ui->mainToolBar->addAction(tr("切换选择"), this, &MainWindow::toggleSelection);

    // model
    QStandardItemModel *model = new QStandardItemModel(7, 4, this);
    for (int row = 0; row < 7; ++row) {
        for (int column = 0; column < 4; ++column) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(4 * row + column));
            model->setItem(row, column, item);
        }
    }

    tableView = new QTableView;
    tableView->setModel(model);
    setCentralWidget(tableView);

    // selection model
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QModelIndex topLeft;
    QModelIndex bottomRight;
    topLeft = model->index(1, 1);
    bottomRight = model->index(5, 2);
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);

    // slots
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateSelection);
    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::changeCurrent);

    // spinboxdelegate
    SpinBoxDelegate *delegate = new SpinBoxDelegate(this);
    tableView->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentItemData()
{
    qDebug() << tr("当前项目的内容：") << tableView->selectionModel()->currentIndex().data().toString();
}

void MainWindow::toggleSelection()
{
    QAbstractItemModel *model = tableView->model();
    QModelIndex topLeft = model->index(0, 0);
    QModelIndex bottomRight = model->index(model->rowCount() - 1, model->columnCount() - 1);
    QItemSelection curSeclection(topLeft, bottomRight);
    tableView->selectionModel()->select(curSeclection, QItemSelectionModel::Toggle);
}

void MainWindow::updateSelection(const QItemSelection &selected, const QItemSelection &deselected)
{
    for (auto index : selected.indexes()) {
        QString text = QString("(%1, %2)").arg(index.row()).arg((index.column()));
        tableView->model()->setData(index, text);
    }

    for (auto index : deselected.indexes()) {
        tableView->model()->setData(index, "");
    }
}

void MainWindow::changeCurrent(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << tr("move(%1, %2) to (%3, %4)")
                    .arg(previous.row())
                    .arg(previous.column())
                    .arg(current.row())
                    .arg(current.column());
}
