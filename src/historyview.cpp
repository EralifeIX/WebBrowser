#include "historyview.h"

HistoryView::HistoryView(QWidget* parent, const QList<DataItem>& dataItems, const QString& title)
    : QDialog(parent), m_phistoryList(dataItems)
{
    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.5f);
    setWindowTitle(title);
    setWindowIcon(QIcon(":/assets/history.ico"));

    //Table layout initialization
    m_ptable = new QTableWidget(m_phistoryList.size(), 3 ,this);
    m_pdeleteButton = new QPushButton(QIcon(":/assets/history.ico"), "", this);
    m_ptable->setFixedSize(width(),height());

    const auto columWidth = m_ptable->width() / 3;
    m_ptable->setColumnWidth(0,columWidth);
    m_ptable->setColumnWidth(1,columWidth);
    m_ptable->setColumnWidth(2,columWidth);

    m_ptable->setHorizontalHeaderItem(0, new QTableWidgetItem("Date and Time"));
    m_ptable->setHorizontalHeaderItem(1, new QTableWidgetItem("Title"));
    m_ptable->setHorizontalHeaderItem(2, new QTableWidgetItem("Url"));

    int i = 0;
    for(const auto& temp : qAsConst(m_phistoryList))
    {
        m_ptable->setItem(i, 0, new QTableWidgetItem(temp.date, 0));
        m_ptable->setItem(i, 1, new QTableWidgetItem(temp.title, 0));
        m_ptable->setItem(i, 2, new QTableWidgetItem(temp.page, 0));
        i++;
    }
    m_ptable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto lay = new QVBoxLayout();

    lay->addWidget(m_ptable, 9);
    lay->addWidget(m_pdeleteButton, 1);
    connect(m_ptable, &QTableWidget::cellDoubleClicked, this, &HistoryView::slotOnItemClicked);
    connect(m_pdeleteButton, &QPushButton::clicked, this, &HistoryView::slotOnDelete);
}

// deleting one the rows
void HistoryView::slotOnDelete()
{
    const int pos = m_ptable->currentRow();
    m_ptable->removeRow(pos);
    m_ptable->setColumnWidth(0,0);

    if((pos < m_phistoryList.size()) && (!m_phistoryList.empty()) && (pos >= 0) )
    {
        m_phistoryList.takeAt(pos);
        emit historyItemDeleted(pos);
    }

}
void HistoryView::slotOnItemClicked(int x, int y)
{
    Q_UNUSED(y)
    emit goToUrl(QUrl(m_ptable->item(x, 2)->text()));
}