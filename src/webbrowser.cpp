#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget* parent)
        : QMainWindow(parent)
{
    onLoadHistory();
    onLoadFavourites();
    buildComponents();
    initToolTips();
    buildMenu();
    applyLayout();
    applyStyle();
    makeConnections();
}

// Connecting slots and signals

void WebBrowser::makeConnections()
{
    connect(tabs, &QTabWidget::tabCloseRequested, this, &WebBrowser::onCloseTab);
    connect(tabs, &QTabWidget::currentChanged, this, &WebBrowser::onUpdateLineEdit);
    connect(tabs, &QTabWidget::currentChanged, this, &WebBrowser::updateTitle);
    connect(tabs, &QTabWidget::currentChanged, this, &WebBrowser::updateConnect);
    connect(tabs, &QTabWidget::currentChanged, this, &WebBrowser::onUrlChanged);
    connect(localFile, &QAction::triggered, this, &WebBrowser::loadLocalFile);
    connect(privateTab, &QAction::triggered, this, &WebBrowser::onNewPrivateTab);
    connect(historyMenu, &QAction::triggered, this, &WebBrowser::onHistory);
    connect(favouritesList, &QAction::triggered, this, &WebBrowser::onFavorites);
    connect(favouritesButton, &QPushButton::clicked, this, &WebBrowser::onAddFavorites);
    connect(searchButton, &QPushButton::clicked, this, &WebBrowser::onUrl);
    connect(newTabButton, &QPushButton::clicked, this, &WebBrowser::onNewTab);
    connect(reloadButton, &QPushButton::clicked, this, &WebBrowser::onReload);
    connect(homeButton, &QPushButton::clicked, this, &WebBrowser::goHome);
    connect(previousButton, &QPushButton::clicked, this, &WebBrowser::onPreviousPage);
    connect(nextButton, &QPushButton::clicked, this, &WebBrowser::onNextPage);
    connect(downloadButton, &QPushButton::clicked, this, &WebBrowser::downloadCurrentPage);
    connect(currentWebView(), &WebView::loadStarted, this, &WebBrowser::onUrlChanged);
    connect(currentWebView(), &WebView::loadStarted, this, &WebBrowser::onStartLoading);
    connect(currentWebView(), &WebView::loadProgress, this, &WebBrowser::onLoading);
    connect(currentWebView(), &WebView::loadFinished, this, &WebBrowser::onEndLoading);
    connect(currentWebView(), &WebView::iconChanged, this, &WebBrowser::updateIcon);
}

// setting-up main window gui
void WebBrowser::buildComponents()
{
    installEventFilter(this);
    // Buttons
    webView = new WebView(this);
    loadingBar = new QProgressBar(this);
    tabs = new QTabWidget(this);
    menuBar = new QMenuBar( this);
    menu = new QMenu("Menu", this);
    urlEdit = new QLineEdit( this);
    searchButton = new QPushButton(QIcon(QStringLiteral(":/assets/search.ico")), "", this);
    newTabButton = new QPushButton(QIcon(QStringLiteral(":/assets/new.ico")), "", this);
    homeButton = new QPushButton(QIcon(QStringLiteral(":/assets/home.ico")), "", this);
    previousButton = new QPushButton(QIcon(QStringLiteral(":/assets/previous.ico")), "", this);
    nextButton = new QPushButton(QIcon(QStringLiteral(":/assets/next.ico")), "", this);
    reloadButton = new QPushButton(QIcon(QStringLiteral(":/assets/reload.ico")), "", this);
    favouritesButton = new QPushButton(QIcon(QStringLiteral(":/assets/favourites.ico")), "", this);
    downloadButton = new QPushButton(QIcon(QStringLiteral(":/assets/download.ico")), "", this);
    //Actions
    privateTab = new QAction(QIcon(QStringLiteral(":/assets/private.ico")), "Private tab", this);
    historyMenu = new QAction(QIcon(QStringLiteral(":/assets/history.ico")), "History", this);
    localFile = new QAction(QIcon(QStringLiteral(":/assets/open.ico")), "Open a local file", this);
    favouritesList = new QAction(QIcon(QStringLiteral(":/assets/list.ico")), "Favourite list", this);
    //setting up
    webView->load(HOME_PAGE);
    webView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    loadingBar->setVisible(false);
    loadingBar->setTextVisible(false);
    loadingBar->setFixedHeight(5);
    tabs->setElideMode(Qt::ElideRight);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->tabBar()->setExpanding(false);
    tabs->tabBar()->setMaximumHeight(30);
    tabs->addTab(webView, "New Tab");

}

// Tooltips for buttons
void WebBrowser::initToolTips(){
    searchButton->setToolTip(QStringLiteral("Search"));
    newTabButton->setToolTip(QStringLiteral("New Tab"));
    previousButton->setToolTip(QStringLiteral("Previous"));
    nextButton->setToolTip(QStringLiteral("Next"));
    reloadButton->setToolTip(QStringLiteral("Reload"));
    favouritesButton->setToolTip(QStringLiteral("Favourites"));
    downloadButton->setToolTip(QStringLiteral("Download"));
    homeButton->setToolTip(QStringLiteral("Home"));
}

// Building menu components
void WebBrowser::buildMenu()
{
    menuBar->addMenu(menu);
    menu->setIcon(QIcon(":/assets/menu.ico"));
    menu->addAction(historyMenu);
    menu->addAction(privateTab);
    menu->addAction(localFile);
    menu->addAction(favouritesList);
}


void WebBrowser::applyLayout(){
    QHBoxLayout* lineLayout = new QHBoxLayout();
    lineLayout->addWidget(urlEdit, 19);
    lineLayout->addWidget(searchButton, 1);
    lineLayout->setContentsMargins(0, 0, 0, 0);


    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(previousButton, 1);
    topLayout->addWidget(nextButton, 1);
    topLayout->addWidget(reloadButton, 1);
    topLayout->addWidget(homeButton, 1);
    topLayout->addLayout(lineLayout, 30);
    topLayout->addWidget(newTabButton, 1);
    topLayout->addWidget(favouritesButton, 1);
    topLayout->addWidget(downloadButton, 1);
    topLayout->addWidget(menuBar, 1);

    QVBoxLayout* appLayout = new QVBoxLayout();
    appLayout->setContentsMargins(0, 0, 0, 0);
    appLayout->addLayout(topLayout, 1);
    appLayout->addWidget(loadingBar, 1);
    appLayout->addWidget(tabs, 10);

    QWidget* central = new QWidget();
    central->setLayout(appLayout);
    setCentralWidget(central);

}


//set style
void WebBrowser::applyStyle(){
    resize(700, 500);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    QGuiApplication::primaryScreen()->availableGeometry()));
    setWindowIcon(QIcon(":/assets/icon.ico"));
    tabs->setTabIcon(0, webView->icon());
}

void WebBrowser::onLoadHistory(){
    history = dataManager.getAllHistoryData();
}

void WebBrowser::onLoadFavourites(){
    favourites = dataManager.getFavourites();
};

void WebBrowser::addToHistory(const QString& title, const QUrl& urlToAdd)
{
    if(!urlToAdd.toString().trimmed().isEmpty())
    {
        const DataItem tempItem{QDateTime::currentDateTime().toString(), title,
                                urlToAdd.toString()};
        dataManager.insertHistoryData(tempItem);
        history.push_back(tempItem);
    }
}

void WebBrowser::onAddFavorites()
{
    const DataItem tempFav{QDateTime::currentDateTime().toString(),
                           currentWebView()->title(), currentWebView()->url().toString()};
    favourites.push_back(tempFav);
    dataManager.addFavourite(tempFav);
}

void WebBrowser::onHistoryItemDeleted(int pos)
{
    if( (pos <  history.size()) && (!history.empty()) && (pos >= 0) ){
        dataManager.deleteHistoryData(history.at(pos));
        history.remove(pos);
    }
}


void WebBrowser::onFavoriteDeleted(int pos)
{
    if ((pos < favourites.size()) && (!favourites.empty()) && (pos >= 0))
    {
        dataManager.deleteFavourite(favourites.at(pos));
        favourites.removeAt(pos);
    }
}


void WebBrowser::onNewTab(){
    auto view = new WebView(this);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->load(HOME_PAGE);
    tabs->addTab(view, "New Tab");
}

void WebBrowser::onNewPrivateTab(){
    auto view = new WebView(this);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->load(HOME_PAGE);
    tabs->addTab(view, PRIVATE_TAB);
}

void WebBrowser::updateIcon(const QIcon& icon){
    tabs->setTabIcon(tabs->currentIndex(), icon);
}


bool WebBrowser::isPrivate() const{
    return (tabs->tabText(tabs->currentIndex()) == PRIVATE_TAB);
}

bool WebBrowser::searchOrNavigate(const QString& str) const
{
    QRegularExpression domainRegex("^(?!-)([A-Za-z0-9-]{1,63}(?<!-)\\.)+[A-Za-z]{2,6}(/.*)?$");
    QRegularExpressionMatch domainMatch = domainRegex.match(str);

    if(str.contains(" "))
        return false;
    if(domainMatch.hasMatch())
        return true;
    return false;
}

void WebBrowser::onUrlChanged()
{
    urlEdit->setText(currentWebView()->url().toString());
    if(!isPrivate())
        tabs->setTabText(tabs->currentIndex(), currentWebView()->title());
}


void WebBrowser::onUrl(){
    if(searchOrNavigate(urlEdit->text()))
        onOpenUrl(urlEdit->text());
    else
        onOpenUrl("https://www.google.com/search?q=" + urlEdit->text());
}

void WebBrowser::onOpenUrl(const QUrl& url)
{
     const QUrl newUrl{
     ((url.toString().left(7)) == HTTP || (url.toString().left(8) == HTTPS))
         ? url.toString() : HTTPS + url.toString()};
    if(newUrl.isValid())
    {
        urlEdit->setText(newUrl.toString());
        currentWebView()->setUrl(newUrl);
        if(!isPrivate())
        {
            tabs->setTabText(tabs->currentIndex(), currentWebView()->title());
            setWindowTitle(currentWebView()->title());

        }
    }
}


void WebBrowser::onReload(){
    currentWebView()->reload();
}


void WebBrowser::goHome(){
    onOpenUrl(HOME_PAGE);
}


void WebBrowser::onUpdateLineEdit(){
    urlEdit->setText(currentWebView()->url().toString());
}


void WebBrowser::onCloseTab(const int& index)
{
    if(tabs->count() > 1){
        auto window_id = tabs->widget((index));
        tabs->removeTab(index);
        delete window_id;
    }
    else
        onQuit();
}


void WebBrowser::onHistory(){
    HistoryView* historyView = new HistoryView(this, history);
    connect(historyView, &HistoryView::historyItemDeleted, this, &WebBrowser::onHistoryItemDeleted);
    connect(historyView, &HistoryView::goToUrl, this, &WebBrowser::onOpenUrl);
    historyView->show();
}


void WebBrowser::onFavorites(){
    auto historyView = new HistoryView(this, favourites, "Favorites");
    connect(historyView, &HistoryView::historyItemDeleted, this, &WebBrowser::onHistoryItemDeleted);
    connect(historyView, &HistoryView::goToUrl, this, &WebBrowser::onOpenUrl);
    historyView->show();
}


void WebBrowser::onPreviousPage(){
    currentWebView()->back();
}

void WebBrowser::onNextPage(){
    currentWebView()->forward();
}

void WebBrowser::updateTitle(){
    setWindowTitle(currentWebView()->title());
}

void WebBrowser::updateConnect(){
    connect(currentWebView(), &WebView::loadStarted, this, &WebBrowser::onStartLoading);
    connect(currentWebView(), &WebView::loadProgress, this, &WebBrowser::onLoading);
    connect(currentWebView(), &WebView::loadFinished, this, &WebBrowser::onEndLoading);
    connect(currentWebView(), &WebView::loadFinished, this, &WebBrowser::onUrlChanged);
    connect(currentWebView(), &WebView::iconChanged, this, &WebBrowser::updateIcon);
}

void WebBrowser::onStartLoading()
{
    loadingBar->setVisible(true);
    if(!isPrivate())
        addToHistory(currentWebView()->title(), currentWebView()->url());
}


void WebBrowser::onLoading(int percentage){
    loadingBar->setValue(percentage);
}

void WebBrowser::onEndLoading(){
    loadingBar->setVisible(false);
    loadingBar->setValue(0);
}


void WebBrowser::loadLocalFile()
{
    const QString fileName = QFileDialog::getOpenFileName(this, "Open a local page", "/home",
                                                        "*.htm *.shtml *.xhtml *.html");
    auto view = new WebView(this);
    view->load(QUrl::fromLocalFile(fileName));
    tabs->addTab(view, fileName);
}

void WebBrowser::downloadCurrentPage()
{
    const QString  pageName = QFileDialog::getSaveFileName(this, "Download page");
    if((pageName.trimmed().isEmpty()) || (pageName.isNull()))
        return;
    currentWebView()->page()->save(pageName);
}

bool WebBrowser::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress){
        auto *keyEvent = dynamic_cast<QKeyEvent*>(event);
        if((keyEvent->key() == Qt::Key_Return) && (urlEdit->cursorPosition() != 0))
            onUrl();
    }
    return QObject::eventFilter(obj, event);
}


void WebBrowser::dragEnterEvent(QDragEnterEvent* event){
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}


void WebBrowser::dropEvent(QDropEvent* event)
{
    const auto urlList = event->mimeData()->urls();
    const auto filename = urlList.at(0).toLocalFile();
    onOpenUrl(QUrl::fromLocalFile(filename));
}


void WebBrowser::onQuit(){
    qApp->quit();
}


WebView* WebBrowser::currentWebView() const{
    return qobject_cast<WebView*>(tabs->currentWidget());
}


































































































































