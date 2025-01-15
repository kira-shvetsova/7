#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QButtonGroup>
#include <QTableView>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>

#include "DbManager.h"
#include "Models/Apartment.h"
#include "Models/Buyer.h"
#include "Models/Sale.h"
#include "Models/Salesman.h"
#include "Helper.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onCellSelected(const QItemSelection& selected, const QItemSelection& deselected, QTableView* tableView);
    void addButtonClicked();
    void editButtonClicked();
    void deleteButtonClicked();
    void buttonClearRowSelectionClicked();
    void createTableView();
    void handleRadioButtonSelection(int id);
private:
    void loadTableView();
    TableModel *getTableModelAtCurrentRow();
    TableModel *getTableModelFromUser();
private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Ui::MainWindow *ui;
    DbManager *manager;
    TableModel* currentTableModel = new Salesman();
    int selected_row = -1;
    int id = 1;
};
#endif // MAINWINDOW_H
