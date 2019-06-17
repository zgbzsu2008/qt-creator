#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")

#include <QItemSelectionModel>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void getCurrentItemData();
    void toggleSelection();

    void updateSelection(const QItemSelection& selected, const QItemSelection& deselected);
    void changeCurrent(const QModelIndex& current, const QModelIndex& previous);

private:
    Ui::MainWindow* ui;
    QTableView* tableView;
};

#endif  // MAINWINDOW_H
