#include <iostream>
#include <webbrowser.h>
#include <QStyleFactory>

int main(int argc, char* argv[])
{
    QStyleFactory factory;
    QApplication app(argc, argv);
    app.setStyle(factory.create("plastiq ue"));
    QCoreApplication::setApplicationName("Web Browser");
    QCoreApplication::setOrganizationName("Web Browser");
    QCoreApplication::setApplicationVersion("1.0");
    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);

    WebBrowser browser;

    if(argc > 1){
        for(auto i=1; i<argc; i++){
            browser.onNewTab();
            browser.onOpenUrl(QUrl(argv[i]));
        }
    }

    browser.show();
    return QApplication::exec();

}
