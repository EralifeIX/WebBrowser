#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include "webview.h"
#include "dataitem.h"
#include "historyview.h"
#include "dataitemmanager.h"
#include <QUrl>
#include <QFile>
#include <QScreen>
#include <QStyle>
#include <QTextStream>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QTabWidget>
#include <QList>
#include <QMessageBox>
#include <QMimeData>
#include <QDateTime>
#include <QKeyEvent>
#include <QProgressBar>
#include <QIcon>
#include <QRegularExpression>

class WebBrowser : public QMainWindow{
Q_OBJECT

public:
    explicit WebBrowser(QWidget *parent = nullptr);
    ~WebBrowser() = default;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    const QString PRIVATE_TAB = "Private Tab";
    const QString HTTP = "http://";
    const QString HTTPS = "https://";
    const QUrl HOME_PAGE = {"https://google.com"};

    [[nodiscard]] WebView* currentWebView() const;
    void onLoadHistory();
    void onLoadFavourites();
    void addToHistory(const QString& title, const QUrl& urlToAdd);
    [[nodiscard]] bool isPrivate() const;
    [[nodiscard]] bool searchOrNavigate(const QString& str) const;
    void buildComponents();
    void initToolTips();
    void buildMenu();
    void applyStyle();
    void applyLayout();
    void makeConnections();

    QTabWidget* tabs;
    WebView* webView;
    QLineEdit* urlEdit;
    QUrl currentUrl;
    QList<DataItem> history;
    QList<DataItem> favourites;
    QMenuBar* menuBar;
    QMenu* menu;
    QAction* historyMenu;
    QAction* privateTab;
    QAction* localFile;
    QAction* favouritesList;

    QPushButton* favouritesButton;
    QPushButton* searchButton;
    QPushButton* newTabButton;
    QPushButton* previousButton;
    QPushButton* nextButton;
    QPushButton* reloadButton;
    QPushButton* homeButton;
    QPushButton* downloadButton;

    QProgressBar* loadingBar;
    DataItemManager dataManager;

    private slots:

    void onUrl();
    void onReload();
    void onUpdateLineEdit();
    void onNewPrivateTab();
    void onCloseTab(const int &index);
    void onHistory();
    void onFavorites();
    void onQuit();
    void onHistoryItemDeleted(int pos);
    void onFavoriteDeleted(int pos);
    void onUrlChanged();
    void onPreviousPage();
    void onNextPage();
    void goHome();
    void onStartLoading();
    void onLoading(int percentage);
    void onEndLoading();
    void onAddFavorites();
    void updateIcon(const QIcon &icon);
    void updateTitle();
    void loadLocalFile();
    void downloadCurrentPage();
    void updateConnect();

public slots:
    void onNewTab();
    void onOpenUrl(const QUrl &urlToOpen);
};



#endif //WEBBROWSER_H
