#ifndef WEB_BROWSER
#define WEB_BROWSER

#include <QWidget>
#include <QtWebKit/QWebView> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <KPushButton>
#include <KComboBox>
#include <QFrame>
#include <KTabWidget>


  class WebBrowser : public QWidget {
    Q_OBJECT
    public:
      WebBrowser(QWidget* parent);
      QVBoxLayout *verticalLayout_8;
      QHBoxLayout *hlBrowserControl;
      KPushButton *btnBack;
      KPushButton *btnNext;
      KPushButton *btnReload;
      KPushButton *btnStop;
      KComboBox *cbbUrl;
      KPushButton *btnBookmark;
      QFrame *line_4;
      KPushButton *btnNewTab;
      KPushButton *btnCloseTab;
      KTabWidget *tabBBrowserPage;
      QWidget *tabDefaultTab;
      QHBoxLayout *horizontalLayout_8;
      QWebView *webDefaultPage; 
  
    private slots:
      void loadWebPage();

  };
  
#endif