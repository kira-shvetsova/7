#ifndef DBMANAGERHELPER_H
#define DBMANAGERHELPER_H
#include <QString>
#include "Models/TableModel.h"

class DbManagerHelper
{
public:
    static QString GetCreateTableIfNullQuery(TableModel *model);

    static QString GetSelectQuery(TableModel *model);

    static QString GetInsertQuery(TableModel *model);

    static QString GetUpdateQuery(TableModel *model);

    static QString GetDeleteQuery(TableModel *model);
};

#endif // DBMANAGERHELPER_H
