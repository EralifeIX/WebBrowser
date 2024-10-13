#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include "dataitem.h"
#include <QUrl>
#include <QIcon>
#include <QDebug>
#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScreen>


class HistoryView : public QDialog{
Q_OBJECT

public:
    explicit HistoryView(QWidget *parent = nullptr, const QList<DataItem>& dataItems = {},
        const QString& title = "History");

private:
    QTableWidget* m_ptable;
    QPushButton* m_pdeleteButton;
    QList<DataItem> m_phistoryList;

private slots:

    void slotOnDelete();

    void slotOnItemClicked(int x, int y);

    signals:

    void historyItemDeleted(int);

    void goToUrl(QUrl url);
};



#endif //HISTORYVIEW_H
