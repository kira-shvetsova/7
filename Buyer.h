#ifndef BUYER_H
#define BUYER_H

#include <string>
#include "TableModel.h"
#include "../Helper.h"

class Buyer : public TableModel
{
public:
    // init names of db fields
    Buyer()
    {
        TableModel::TableName = "buyer";
        TableModel::Keys = "id_buyer";
        TableModel::NonKeys = "name,surname,year";
    }

    // handling tht values
    virtual std::string GetAllValues() override
    {
        return GetKeyValues() + TableModel::DELIMETER + GetNonKeyValues();
    }

    virtual std::string GetKeyValues() override
    {
        return Helper::escapeValue(std::to_string(IdBuyer));
    }

    virtual std::string GetNonKeyValues() override
    {
        return Helper::escapeValue(Name) +
               TableModel::DELIMETER +
               Helper::escapeValue(Surname) +
               TableModel::DELIMETER +
               Helper::escapeValue(std::to_string(Year));
    }

    virtual std::string GetPropertyNamesForTableCreation()
    {
        //id_buyer BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,name VARCHAR(100) NOT NULL,surname VARCHAR(100) NOT NULL,year INTEGER NOT NULL
        return "id_buyer BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,name VARCHAR(100) NOT NULL,surname VARCHAR(100) NOT NULL,year INTEGER NOT NULL";
    }

    virtual std::string GetPropertyNamesForUpdate()
    {
        return "name = " + Helper::escapeValue(Name) +
               + "," +
               "surname = " + Helper::escapeValue(Surname) +
               + "," +
               "year = " + Helper::escapeValue(std::to_string(Year));
    }

    virtual void SetAllValuesToNull()
    {
        Name = "";
        Surname = "";
        Year = 0;
    }

    virtual void SetId(int newId)
    {
        if(newId <= 0)
        {
            IdBuyer = 0;
        }
        else
        {
            IdBuyer = newId;
        }
    }
public:

    void SetName(std::string newName)
    {
        Name = newName;
    }

    void SetSurname(std::string newSurname)
    {
        Surname = newSurname;
    }

    void SetYear(int newYear)
    {
        if(newYear > 130)
        {
            Year = 130;
        }
        else
        {
            Year = newYear;
        }
    }

private:
    int IdBuyer;
    std::string Name;
    std::string Surname;
    int Year;
};


#endif // BUYER_H
