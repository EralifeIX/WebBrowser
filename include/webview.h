#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebEngineView>
#include <QWebEngineSettings>

class WebView : public QWebEngineView {
Q_OBJECT

public:
    explicit WebView(QWidget *parent = nullptr);

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;;
};



#endif //WEBVIEW_H
