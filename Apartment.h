#ifndef APARTMENT_H
#define APARTMENT_H

#include "TableModel.h"
#include "../Helper.h"

class Apartment : public TableModel
{
public:
    // init names of db fields
    Apartment()
    {
        TableModel::TableName = "apartment";
        TableModel::Keys = "id_apartment";
        TableModel::NonKeys = "number,price";
    }

    // handling tht values
    virtual std::string GetAllValues() override
    {
        return GetKeyValues() + TableModel::DELIMETER + GetNonKeyValues();
    }

    virtual std::string GetKeyValues() override
    {
        return Helper::escapeValue(std::to_string(IdAppartment));
    }

    virtual std::string GetNonKeyValues() override
    {
        return Helper::escapeValue(std::to_string(Number)) +
               TableModel::DELIMETER +
               Helper::escapeValue(std::to_string(Price));
    }

    virtual std::string GetPropertyNamesForTableCreation()
    {
        // id_apartment BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY, number INTEGER NOT NULL,price INTEGER NOT NULL
        return "id_apartment BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY, number INTEGER NOT NULL,price INTEGER NOT NULL";
    }

    virtual std::string GetPropertyNamesForUpdate()
    {
        return "number = " + Helper::escapeValue(std::to_string(Number)) +
               + "," +
               "price = " + Helper::escapeValue(std::to_string(Price));
    }

    virtual void SetAllValuesToNull()
    {
        Number = 0;
        Price = 0;
    }

    virtual void SetId(int newId)
    {
        if(newId <= 0)
        {
            IdAppartment = 0;
        }
        else
        {
            IdAppartment = newId;
        }
    }

public:
    void SetNumber(int newNumber)
    {
        Number = 0;
        if(newNumber > 0)
        {
            Number = newNumber;
        }
    }

    void SetPrice(int newPrice)
    {
        Price = 0;
        if(newPrice > 0)
        {
            Price = newPrice;
        }
    }
private:
    int IdAppartment;
    int Number;
    int Price;
};

#endif // APARTMENT_H
