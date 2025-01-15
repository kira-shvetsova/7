#include "dbmanagerhelper.h"

QString DbManagerHelper::GetCreateTableIfNullQuery(TableModel *model)
{
    return QString::fromStdString( "CREATE TABLE IF NOT EXISTS " + model->GetTableName() +
                                  " ( " + model->GetPropertyNamesForTableCreation() + " );");
}

QString DbManagerHelper::GetSelectQuery(TableModel *model)
{
    return QString::fromStdString( "SELECT " + model->GetAllNames() +
                                  " FROM " + model->GetTableName() + ";");
}

QString DbManagerHelper::GetInsertQuery(TableModel *model)
{
    return QString::fromStdString( "INSERT INTO " + model->GetTableName() + " ( " + model->GetNonKeyNames() + " ) " +
                                  " VALUES (" + model->GetNonKeyValues() + " )" ";" );
}

QString DbManagerHelper::GetUpdateQuery(TableModel *model)
{
    return QString::fromStdString( "UPDATE " + model->GetTableName() + " " +
                                  " SET " + model->GetPropertyNamesForUpdate() + " " +
                                  " WHERE " + model->GetKeyNames() + " = " + model->GetKeyValues() + ";" );
}

QString DbManagerHelper::GetDeleteQuery(TableModel *model)
{
    return QString::fromStdString( "DELETE FROM " + model->GetTableName() +
                                  " WHERE " + model->GetKeyNames() + " = " + model->GetKeyValues() + ";" );
}
