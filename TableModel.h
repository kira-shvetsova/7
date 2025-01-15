#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <string>
#include "TableModel.h"

class TableModel
{
protected:
    std::string TableName = "";
    std::string Keys = "";
    std::string NonKeys = "";

public:
    static const char DELIMETER = ',';

public:

    std::string GetTableName()
    {
        return TableName;
    }

    // need to return this in order as keys are presented
    virtual std::string GetAllValues() = 0;
    virtual std::string GetKeyValues() = 0;
    virtual std::string GetNonKeyValues() = 0;
    virtual std::string GetPropertyNamesForTableCreation() = 0;
    virtual std::string GetPropertyNamesForUpdate() = 0;

    virtual void SetAllValuesToNull() = 0;
    virtual void SetId(int newId) = 0;
    std::string GetKeyNames()
    {
        return Keys;
    }

    std::string GetNonKeyNames()
    {
        return NonKeys;
    }

    std::string GetAllNames()
    {
        return Keys + DELIMETER + NonKeys;
    }

    virtual ~TableModel(){}
};
#endif // TABLEMODEL_H
