#include "mainwindow.h"

#include <QRegExp>
#include <QSortFilterProxyModel>
#include <QStringListModel>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;
    list << "yafei"
         << "yafeilinux"
         << "Qt"
         << "Qt Creator";

    QStringListModel *listModel = new QStringListModel(list, this);
    filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(listModel);
    ui->listView->setModel(filterModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QRegExp rx(ui->lineEdit->text());  // 正则表达式过滤
    filterModel->setFilterRegExp(rx);
}
