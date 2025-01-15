#include "DbManager.h"

DbManager::DbManager(TableModel* model)
{
    db = QSqlDatabase::addDatabase("QPSQL"); 
    db.setHostName(HOST);                    // PostgreSQL server hostname
    db.setPort(PORT);                        // PostgreSQL port
    db.setDatabaseName(DB_NAME);             // Replace with your database name
    db.setUserName(USER);                    // Replace with your PostgreSQL username
    db.setPassword(PASSWORD);                // Replace with your PostgreSQL password

    if (db.open())
    {
        qDebug() << "Successfully connected to the database.";
        QSqlQuery query(DbManagerHelper::GetCreateTableIfNullQuery(model));
        if (query.lastError().type() == QSqlError::NoError)
        {
            qDebug() << "Table created successfully or already exists.";
        }
        else
        {
            qDebug() << "Error creating table : " << query.lastError().text();
        }
        query.finish();
    }
    else
    {
        qCritical() << "Failed to connect to the database:" << db.lastError().text();
        exit(EXIT_FAILURE);
    }
}

QSqlQueryModel* DbManager::selectData(TableModel *test_model)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetSelectQuery(test_model));
    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlQueryModel *DbManager::insertData(TableModel *test_model)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetInsertQuery(test_model));

    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlRelationalTableModel *DbManager::insertDataUsingRelationTable(TableModel *test_model)
{
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();
    // Set the query to the model
    model->setQuery(DbManagerHelper::GetInsertQuery(test_model));

    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlQueryModel *DbManager::updateData(TableModel *test_model)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetUpdateQuery(test_model));
    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlRelationalTableModel *DbManager::updateDataUsingRelationTable(TableModel *test_model)
{
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetUpdateQuery(test_model));
    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlQueryModel *DbManager::deleteData(TableModel *test_model)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetDeleteQuery(test_model));

    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}

QSqlRelationalTableModel *DbManager::deleteDataUsingRelationTable(TableModel *test_model)
{
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    // Set the query to the model
    model->setQuery(DbManagerHelper::GetDeleteQuery(test_model));

    // Check for errors
    if (model->lastError().isValid())
    {
        qDebug() << "Query execution failed:" << model->lastError().text();
    }
    else
    {
        qDebug() << "Query executed successfully!";
    }

    return model;
}
