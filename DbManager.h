#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSql>
#include <QDebug>

#include <QString>

#include "dbmanagerhelper.h"

class DbManager
{
public:
    DbManager(TableModel* model);
    QSqlQueryModel* selectData(TableModel *test_model);
    QSqlRelationalTableModel* insertDataUsingRelationTable(TableModel *test_model);
    QSqlQueryModel* insertData(TableModel *test_model);

    QSqlQueryModel* updateData(TableModel *test_model);
    QSqlRelationalTableModel* updateDataUsingRelationTable(TableModel *test_model);

    QSqlQueryModel* deleteData(TableModel *test_model);
    QSqlRelationalTableModel* deleteDataUsingRelationTable(TableModel *test_model);
private:
    const QString HOST = "localhost";
    const int PORT = 5432;
    const QString DB_NAME = "postgres";
    const QString USER = "postgres";
    const QString PASSWORD = "Kirakira8922310";

    QSqlDatabase db;
};


#endif // DBMANAGER_H
