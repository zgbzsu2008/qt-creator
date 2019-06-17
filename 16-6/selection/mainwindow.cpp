#include "mainwindow.h"
#include <QDebug>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QStandardItemModel *model = new QStandardItemModel(7, 4, this);
    for (int row = 0; row < 7; ++row) {
        for (int column = 0; column < 4; ++column) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(row * 4 + column));
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
}

MainWindow::~MainWindow() {}
