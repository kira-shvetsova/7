#ifndef SALE_H
#define SALE_H

#include <string>
#include "TableModel.h"
#include "../Helper.h"

class Sale : public TableModel
{
public:
    // init names of db fields
    Sale()
    {
        TableModel::TableName = "sale";
        TableModel::Keys = "id_sale";
        TableModel::NonKeys = "id_apartment,id_salesman,id_buyer";
    }

    // handling tht values
    virtual std::string GetAllValues() override
    {
        return GetKeyValues();
    }

    virtual std::string GetKeyValues() override
    {
        return Helper::escapeValue(std::to_string(IdSale));
    }

    virtual std::string GetNonKeyValues() override
    {
        return Helper::escapeValue(std::to_string(IdAppartment)) +
               TableModel::DELIMETER +
               Helper::escapeValue(std::to_string(IdSalesman)) +
               TableModel::DELIMETER +
               Helper::escapeValue(std::to_string(IdBuyer));
    }

    virtual std::string GetPropertyNamesForTableCreation()
    {
        //id_sale BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,id_apartment BIGINT NOT NULL,id_salesman BIGINT NOT NULL,id_buyer BIGINT NOT NULL,FOREIGN KEY (id_apartment) REFERENCES apartment(id_apartment),FOREIGN KEY (id_salesman) REFERENCES salesman(id_salesman),FOREIGN KEY (id_buyer) REFERENCES buyer(id_buyer)
        //"id_sale INTEGER PRIMARY KEY,id_apartment INTEGER NOT NULL,id_salesman INTEGER NOT NULL,id_buyer INTEGER NOT NULL,FOREIGN KEY (id_apartment) REFERENCES apartment(id_apartment),FOREIGN KEY (id_salesman) REFERENCES salesman(id_salesman),FOREIGN KEY (id_buyer) REFERENCES buyer(id_buyer)";
        return "id_sale BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,id_apartment BIGINT NOT NULL,id_salesman BIGINT NOT NULL,id_buyer BIGINT NOT NULL,FOREIGN KEY (id_apartment) REFERENCES apartment(id_apartment),FOREIGN KEY (id_salesman) REFERENCES salesman(id_salesman),FOREIGN KEY (id_buyer) REFERENCES buyer(id_buyer)";
    }

    virtual std::string GetPropertyNamesForUpdate()
    {
        return "id_apartment = " + Helper::escapeValue(std::to_string(IdAppartment)) +
               + "," +
               "id_salesman = " + Helper::escapeValue(std::to_string(IdSalesman)) +
               + "," +
               "id_buyer = " + Helper::escapeValue(std::to_string(IdBuyer));
    }


    virtual void SetAllValuesToNull()
    {
        IdAppartment = 0;
        IdSalesman = 0;
        IdBuyer = 0;
    }

    virtual void SetId(int newId)
    {
        if(newId <= 0)
        {
            IdSale = 0;
        }
        else
        {
            IdSale = newId;
        }
    }
public:
    void SetIdAppartment(int newIdAppartment)
    {
        if(newIdAppartment <= 0)
        {
            IdAppartment = 0;
        }
        else
        {
            IdAppartment = newIdAppartment;
        }
    }

    void SetIdSalesman(int newIdSalesman)
    {
        if(newIdSalesman <= 0)
        {
            IdSalesman = 0;
        }
        else
        {
            IdSalesman = newIdSalesman;
        }
    }

    void SetIdBuyer(int newIdBuyer)
    {
        if(newIdBuyer <= 0)
        {
            IdBuyer = 0;
        }
        else
        {
            IdBuyer = newIdBuyer;
        }
    }
private:
    int IdSale;
    int IdAppartment;
    int IdSalesman;
    int IdBuyer;
};


#endif // SALE_H
