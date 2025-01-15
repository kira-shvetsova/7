#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioSalesman,1);
    buttonGroup->addButton(ui->radioApartment,2);
    buttonGroup->addButton(ui->radioBuyer,3);
    buttonGroup->addButton(ui->radioSale,4);

    connect(buttonGroup, &QButtonGroup::buttonClicked, [this, buttonGroup](QAbstractButton *button)
    {
        handleRadioButtonSelection(buttonGroup->id(button));
    });
    ui->radioSalesman->setChecked(true);

    ui->label1->setText("id_salesman");
    ui->label2->setText("name");
    ui->label3->setText("surname");
    ui->label4->setText("year");
    ui->pushButtonSubmit->hide();

    // connecting action buttons to handlers
    connect(ui->buttonAdd,      &QPushButton::clicked, this, &MainWindow::addButtonClicked);
    connect(ui->buttonEdit,     &QPushButton::clicked, this, &MainWindow::editButtonClicked);
    connect(ui->buttonDelete,   &QPushButton::clicked, this, &MainWindow::deleteButtonClicked);
    connect(ui->buttonClearRowSelection,  &QPushButton::clicked, this, &MainWindow::buttonClearRowSelectionClicked);

    ui->buttonAdd->setDisabled(false);
    ui->buttonEdit->setDisabled(true);
    ui->buttonDelete->setDisabled(true);

    // Set up selection model
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &::MainWindow::onSelectionChanged);

    createTableView();
}

MainWindow::~MainWindow()
{
    if(currentTableModel)
    {
        delete currentTableModel;
    }
    delete ui;
}

void MainWindow::handleRadioButtonSelection(int id)
{
    ui->lineEdit1->clear();
    ui->lineEdit2->clear();
    ui->lineEdit3->clear();
    ui->lineEdit4->clear();
    ui->pushButtonSubmit->hide();
    ui->buttonAdd->setDisabled(false);
    ui->buttonEdit->setDisabled(true);
    ui->buttonDelete->setDisabled(true);
    switch (id)
    {
        case 1:
            qDebug() << "Option 1 selected";
            currentTableModel = new Salesman();
            ui->label1->setText("id_salesman");
            ui->label2->setText("name");
            ui->label3->setText("surname");
            ui->label4->setText("year");
            ui->lineEdit4->show();
            ui->label4->show();
            break;
        case 2:
            qDebug() << "Option 2 selected";
            currentTableModel = new Apartment();
            ui->label1->setText("id_apartment");
            ui->label2->setText("number");
            ui->label3->setText("price");
            ui->lineEdit4->hide();
            ui->label4->hide();
            break;
        case 3:
            qDebug() << "Option 3 selected";
            currentTableModel = new Buyer();
            ui->label1->setText("id_buyer");
            ui->label2->setText("name");
            ui->label3->setText("surname");
            ui->label4->setText("year");
            ui->lineEdit4->show();
            ui->label4->show();
            break;
        case 4:
            qDebug() << "Option 4 selected";
            currentTableModel = new Sale();
            ui->label1->setText("id_sale");
            ui->label2->setText("id_apartment");
            ui->label3->setText("id_salesman");
            ui->label4->setText("id_buyer");
            ui->lineEdit4->show();
            ui->label4->show();
            break;
    }
    this->id = id;
    loadTableView();
}

void MainWindow::onCellSelected(const QItemSelection& selected, const QItemSelection& deselected, QTableView* tableView)
{
    // Get the selection model
    qDebug() << "rows";
    QItemSelectionModel* selectionModel = tableView->selectionModel();
    if (!selectionModel->hasSelection())
    {
        qDebug() << "No selection.";
        return;
    }

    // Get the current index
    QModelIndex currentIndex = selectionModel->currentIndex();
    if (!currentIndex.isValid())
    {
        qDebug() << "Invalid selection.";
        return;
    }

    // Get row, column, and data of the selected cell
    int row = currentIndex.row();
    int column = currentIndex.column();
    QVariant cellData = currentIndex.data();

    qDebug() << "Selected Cell:" << "Row =" << row << ", Column =" << column << ", Data =" << cellData.toString();
}

void MainWindow::addButtonClicked()
{
    bool areFieldsFilled = !ui->lineEdit1->text().isEmpty() &&
                           !ui->lineEdit2->text().isEmpty() &&
                           !ui->lineEdit3->text().isEmpty();
    if(areFieldsFilled && getTableModelFromUser() != nullptr)
    {
        currentTableModel = getTableModelFromUser();
        if(id != 4)
        {
            manager->insertData(currentTableModel);
        }
        else
        {
            manager->insertDataUsingRelationTable(currentTableModel);
        }
        loadTableView();
    }
    qDebug() << "addButtonClicked";
}

void MainWindow::editButtonClicked()
{
    QAbstractItemModel* model = ui->tableView->model();
    ui->lineEdit1->setText(model->index(selected_row, 0).data().toString());
    ui->lineEdit2->setText(model->index(selected_row, 1).data().toString());
    ui->lineEdit3->setText(model->index(selected_row, 2).data().toString());
    ui->lineEdit4->setText(model->index(selected_row, 3).data().toString());

    ui->pushButtonSubmit->show();
    connect(ui->pushButtonSubmit, &QPushButton::clicked, this, [&]()
    {
        if(getTableModelFromUser() != nullptr)
        {
            currentTableModel = getTableModelFromUser();
            if(id != 4)
            {
                manager->updateData(currentTableModel);
            }
            else
            {
                manager->updateDataUsingRelationTable(currentTableModel);
            }
            loadTableView();
            ui->lineEdit1->clear();
            ui->lineEdit2->clear();
            ui->lineEdit3->clear();
            ui->lineEdit4->clear();

            ui->pushButtonSubmit->hide();
        }
    });
    qDebug() << "editButtonClicked";
}

void MainWindow::deleteButtonClicked()
{
    currentTableModel = getTableModelAtCurrentRow();
    if(id != 4)
    {
        manager->deleteData(currentTableModel);
    }
    else
    {
        manager->deleteDataUsingRelationTable(currentTableModel);
    }
    loadTableView();
    qDebug() << "deleteButtonClicked";
}

void MainWindow::buttonClearRowSelectionClicked()
{
    currentTableModel = getTableModelAtCurrentRow();
    currentTableModel->SetAllValuesToNull();
    manager->updateData(currentTableModel);
    selected_row = -1;

    ui->buttonAdd->setDisabled(false);
    ui->buttonEdit->setDisabled(true);
    ui->buttonDelete->setDisabled(true);

    loadTableView();
    qDebug() << "refreshButtonClicked";
}

void MainWindow::createTableView()
{
    manager = new DbManager(currentTableModel);
    QSqlQueryModel* queryModel = manager->selectData(currentTableModel);

    ui->tableView->setModel(queryModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);
}

void MainWindow::loadTableView()
{
    manager = new DbManager(currentTableModel);
    if(id != 4)
    {
        QSqlQueryModel* queryModel = manager->selectData(currentTableModel);
        ui->tableView->setModel(queryModel);
    }
    else
    {
        QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

        model->setTable("sale");

        model->setRelation(1, QSqlRelation("apartment", "id_apartment", "number"));
        model->setRelation(2, QSqlRelation("salesman", "id_salesman", "name"));
        model->setRelation(3, QSqlRelation("buyer", "id_buyer", "surname"));

        model->setHeaderData(1, Qt::Horizontal, tr("apartment_number"));
        model->setHeaderData(3, Qt::Horizontal, tr("salesman_name"));
        model->setHeaderData(4, Qt::Horizontal, tr("buyer_surname"));

        model->select();
        ui->tableView->setModel(model);
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);
}

TableModel *MainWindow::getTableModelAtCurrentRow()
{
    TableModel* tableModel = nullptr;
    QAbstractItemModel *model = ui->tableView->model();
    switch (id)
    {
    case 1:
    {
        Salesman* salesman = new Salesman();
        salesman->SetId(model->index(selected_row, 0).data().toInt());
        salesman->SetName(model->index(selected_row, 1).data().toString().toStdString());
        salesman->SetSurname(model->index(selected_row, 2).data().toString().toStdString());
        salesman->SetYear(model->index(selected_row, 3).data().toInt());
        tableModel = salesman;
        break;
    }
    case 2:
    {
        Apartment* apartment = new Apartment();
        apartment->SetId(model->index(selected_row, 0).data().toInt());
        apartment->SetNumber(model->index(selected_row, 1).data().toInt());
        apartment->SetPrice(model->index(selected_row, 2).data().toInt());
        tableModel = apartment;
        break;
    }
    case 3:
    {       
        Buyer* buyer = new Buyer();
        buyer->SetId(model->index(selected_row, 0).data().toInt());
        buyer->SetName(model->index(selected_row, 1).data().toString().toStdString());
        buyer->SetSurname(model->index(selected_row, 2).data().toString().toStdString());
        buyer->SetYear(model->index(selected_row, 3).data().toInt());
        tableModel = buyer;
        break;
    }
    case 4:
    {        
        Sale* sale = new Sale();
        sale->SetId(ui->lineEdit1->text().toInt());
        sale->SetIdAppartment(ui->lineEdit2->text().toInt());
        sale->SetIdBuyer(ui->lineEdit3->text().toInt());
        sale->SetIdSalesman(ui->lineEdit4->text().toInt());
        tableModel = sale;
        break;
    }
    }
    return tableModel;
}

TableModel *MainWindow::getTableModelFromUser()
{
    TableModel* tableModel = nullptr;
    switch (id)
    {
        case 1:
        {
            bool validValues = Helper::isValidNumber(ui->lineEdit1->text()) &&
                               Helper::isValidNameOrSurname(ui->lineEdit2->text()) &&
                               Helper::isValidNameOrSurname(ui->lineEdit3->text()) &&
                               Helper::isValidNumber(ui->lineEdit4->text());
            if(validValues)
            {
                Salesman* salesman = new Salesman();
                salesman->SetId(ui->lineEdit1->text().toInt());
                salesman->SetName(ui->lineEdit2->text().toStdString());
                salesman->SetSurname(ui->lineEdit3->text().toStdString());
                salesman->SetYear(ui->lineEdit4->text().toInt());
                tableModel = salesman;
                break;
            }
        }
        case 2:
        {
            bool validValues = Helper::isValidNumber(ui->lineEdit1->text()) &&
                               Helper::isValidNumber(ui->lineEdit2->text()) &&
                               Helper::isValidNumber(ui->lineEdit3->text());
            if(validValues)
            {
                Apartment* apartment = new Apartment();
                apartment->SetId(ui->lineEdit1->text().toInt());
                apartment->SetNumber(ui->lineEdit2->text().toInt());
                apartment->SetPrice(ui->lineEdit3->text().toInt());
                tableModel = apartment;
            }
            break;
        }
        case 3:
        {
            bool validValues = Helper::isValidNumber(ui->lineEdit1->text()) &&
                               Helper::isValidNameOrSurname(ui->lineEdit2->text()) &&
                               Helper::isValidNameOrSurname(ui->lineEdit3->text()) &&
                               Helper::isValidNumber(ui->lineEdit4->text());
            if(validValues)
            {
                Buyer* buyer = new Buyer();
                buyer->SetId(ui->lineEdit1->text().toInt());
                buyer->SetName(ui->lineEdit2->text().toStdString());
                buyer->SetSurname(ui->lineEdit3->text().toStdString());
                buyer->SetYear(ui->lineEdit4->text().toInt());
                tableModel = buyer;
            }
            break;
        }
        case 4:
        {
            bool validValues = Helper::isValidNumber(ui->lineEdit1->text()) &&
                               Helper::isValidNumber(ui->lineEdit2->text()) &&
                               Helper::isValidNumber(ui->lineEdit3->text()) &&
                               Helper::isValidNumber(ui->lineEdit4->text());
            if(validValues)
            {
                Sale* sale = new Sale();
                sale->SetId(ui->lineEdit1->text().toInt());
                sale->SetIdAppartment(ui->lineEdit2->text().toInt());
                sale->SetIdSalesman(ui->lineEdit3->text().toInt());
                sale->SetIdBuyer(ui->lineEdit4->text().toInt());
                tableModel = sale;
            }
            break;
        }
    }
    return tableModel;
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (!selected.indexes().isEmpty())
    {
        // Get the index of the selected row (first index in selection)
        QModelIndex index = selected.indexes().first();
        int row = index.row();
        selected_row = row; // select row on table
        qDebug() << "Selected row:" << row;

        ui->buttonAdd->setDisabled(true);
        ui->buttonEdit->setDisabled(false);
        ui->buttonDelete->setDisabled(false);

        // Optionally, you can access data from the selected row
        // Example: Get data from the first column of the selected row
        QVariant data = index.model()->data(index.siblingAtColumn(0));
        qDebug() << "Data from first column of selected row:" << data.toString();
    }
}
