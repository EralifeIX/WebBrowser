#ifndef DATAITEM_H
#define DATAITEM_H

#include <QString>
//structure to save data about visited pages
struct DataItem
{
    QString date;
    QString title;
    QString page;

    DataItem(const QString &date, const QString &title, const QString &page)
            :date(date), title(title), page(page)
    {
    }
    DataItem(const DataItem &other)
            : date(other.date), title(other.title), page(other.page)
    {
    }
};


#endif //DATAITEM_H