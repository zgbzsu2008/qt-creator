#include "widget.h"

#include <QDataWidgetMapper>
#include <QStandardItemModel>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(3, 2, this);
    model->setItem(0, 0, new QStandardItem("xiaoming"));
    model->setItem(0, 1, new QStandardItem("90"));
    model->setItem(1, 0, new QStandardItem("xiaogang"));
    model->setItem(1, 1, new QStandardItem("75"));
    model->setItem(2, 0, new QStandardItem("xiaohong"));
    model->setItem(2, 1, new QStandardItem("80"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->lineEdit, 0);
    mapper->addMapping(ui->lineEdit_2, 1);
    mapper->toFirst();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    mapper->toPrevious();
}

void Widget::on_pushButton_2_clicked()
{
    mapper->toNext();
}
