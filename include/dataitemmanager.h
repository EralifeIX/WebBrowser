#ifndef DATAITEMMANAGER_H
#define DATAITEMMANAGER_H

#include <QList>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <dataitem.h>


class DataItemManager {
public:
    DataItemManager();

    ~DataItemManager();

    [[nodiscard]] QList<DataItem> getAllHistoryData() const;

    void insertHistoryData(const DataItem &data);

    void deleteHistoryData(const DataItem &data);

    [[nodiscard]] QList<DataItem> getFavourites() const;

    void addFavourite(const DataItem &data);

    void deleteFavourite(const DataItem &data);

private:
    const QString DATABASE_TYPE{"QSQLITE"};
    const QString DATABASE_NAME{"WebBrowser.db"};
    QSqlDatabase db;
};



#endif //DATAITEMMANAGER_H
