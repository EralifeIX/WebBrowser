#include "dataitemmanager.h"

DataItemManager::DataItemManager()
{
    db = QSqlDatabase::addDatabase(DATABASE_TYPE);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open())
    {
        QSqlQuery queryInit{db};
        queryInit.exec(
                "CREATE TABLE IF NOT EXISTS History ( Id INTEGER PRIMARY KEY AUTOINCREMENT,Date VARCHAR(30),Title VARCHAR(100),Url TEXT);");
        queryInit.exec(
                "CREATE TABLE IF NOT EXISTS Favourite ( Id INTEGER PRIMARY KEY AUTOINCREMENT,Date VARCHAR(30),Title VARCHAR(100),Url TEXT);");
    }
}

QList<DataItem> DataItemManager::getAllHistoryData() const
{
     QList<DataItem> historyList{};
     QSqlQuery queryAll(db);
     queryAll.exec("SELECT  Date, Title, Url FROM History");
     while(queryAll.next())
     {
         historyList.push_back(
             DataItem{queryAll.value(0).toString(), queryAll.value(1).toString(), queryAll.value(2).toString()} );
     }
    return historyList;
}

QList<DataItem> DataItemManager::getFavourites() const
{
    QList<DataItem> historyList{};
    QSqlQuery queryAll{db};
    queryAll.exec("SELECT Date,Title,Url FROM Favourites");
    while(queryAll.next())
    {
        historyList.push_back(
            DataItem{queryAll.value(0).toString(), queryAll.value(1).toString(), queryAll.value(2).toString()} );
    }
    return historyList;
}


void DataItemManager::insertHistoryData(const DataItem& data)
{
    QSqlQuery insertQuery{db};
    insertQuery.prepare("INSERT INTO History(Date,Title,Url)"
                        "VALUES (:date, :title, :url)");

    insertQuery.bindValue(":date", data.date);
    insertQuery.bindValue(":title", data.title);
    insertQuery.bindValue(":page", data.page);
    insertQuery.exec();
}


void DataItemManager::deleteHistoryData(const DataItem &data)
{
    QSqlQuery deleteQuery{db};
    deleteQuery.prepare("DELETE FROM History WHERE (Date= :date AND Title= :title AND Url= :url)");

    deleteQuery.bindValue(":date", data.date);
    deleteQuery.bindValue(":title", data.title);
    deleteQuery.bindValue(":page", data.page);
    deleteQuery.exec();
}


void DataItemManager::addFavourite(const DataItem &data)
{
    QSqlQuery insertQuery{db};
    insertQuery.prepare("INSERT INTO Favourite(Date,Title,Url)"
                        "VALUES (:date, :title, :url)");

    insertQuery.bindValue(":date", data.date);
    insertQuery.bindValue(":title", data.title);
    insertQuery.bindValue(":page", data.page);
    insertQuery.exec();
}
void DataItemManager::deleteFavourite(const DataItem &data)
{
    QSqlQuery deleteQuery{db};
    deleteQuery.prepare("DELETE FROM Favourite WHERE (Date= :date AND Title= :title AND Url= :url)");

    deleteQuery.bindValue(":date", data.date);
    deleteQuery.bindValue(":title", data.title);
    deleteQuery.bindValue(":page", data.page);
    deleteQuery.exec();
}

DataItemManager::~DataItemManager(){
    db.close();
}


