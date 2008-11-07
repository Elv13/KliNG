#include "webBrowser.h"
#include <KLocale>
#include <KIcon>

  WebBrowser::WebBrowser(QWidget* parent) {
    setObjectName(QString::fromUtf8("tabWebBrowser"));
    setGeometry(QRect(0, 0, 520, 609));
    verticalLayout_8 = new QVBoxLayout(this);
    verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
    hlBrowserControl = new QHBoxLayout();
    hlBrowserControl->setObjectName(QString::fromUtf8("hlBrowserControl"));
    btnBack = new KPushButton(this);
    btnBack->setObjectName(QString::fromUtf8("btnBack"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed); //
    sizePolicy1.setHorizontalStretch(31); //
    sizePolicy1.setVerticalStretch(31); //
    sizePolicy1.setHeightForWidth(btnBack->sizePolicy().hasHeightForWidth()); //
    btnBack->setSizePolicy(sizePolicy1);
    btnBack->setMinimumSize(QSize(31, 31));
    btnBack->setMaximumSize(QSize(31, 31));
    btnBack->setToolTip(i18n("Go backward"));
    KIcon icnGoPrevious("go-previous");
    btnBack->setIcon(icnGoPrevious);
    hlBrowserControl->addWidget(btnBack);

    btnNext = new KPushButton(this);
    btnNext->setObjectName(QString::fromUtf8("btnNext"));
    sizePolicy1.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
    btnNext->setSizePolicy(sizePolicy1);
    btnNext->setMinimumSize(QSize(31, 31));
    btnNext->setMaximumSize(QSize(31, 31));
    btnNext->setToolTip(i18n("Go foward"));
    KIcon icnGoEdit("go-next");
    btnNext->setIcon(icnGoEdit);
    hlBrowserControl->addWidget(btnNext);

    btnReload = new KPushButton(this);
    btnReload->setObjectName(QString::fromUtf8("btnReload"));
    sizePolicy1.setHeightForWidth(btnReload->sizePolicy().hasHeightForWidth());
    btnReload->setSizePolicy(sizePolicy1);
    btnReload->setMinimumSize(QSize(31, 31));
    btnReload->setMaximumSize(QSize(31, 31));
    btnReload->setToolTip(i18n("Reload this page"));
    KIcon icnRefresh("view-refresh");
    btnReload->setIcon(icnRefresh);
    hlBrowserControl->addWidget(btnReload);

    btnStop = new KPushButton(this);
    btnStop->setObjectName(QString::fromUtf8("btnStop"));
    sizePolicy1.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
    btnStop->setSizePolicy(sizePolicy1);
    btnStop->setMinimumSize(QSize(31, 31));
    btnStop->setMaximumSize(QSize(31, 31));
    btnStop->setIcon(KIcon("window-close"));
    btnStop->setToolTip(i18n("Stop loading"));
    hlBrowserControl->addWidget(btnStop);

    cbbUrl = new KComboBox(this);
    cbbUrl->setObjectName(QString::fromUtf8("cbbUrl"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(cbbUrl->sizePolicy().hasHeightForWidth());
    cbbUrl->setSizePolicy(sizePolicy2);
    cbbUrl->setEditable(true);
    cbbUrl->setAutoCompletion(false);
    cbbUrl->setUrlDropsEnabled(false);
    cbbUrl->setTrapReturnKey(false);
    hlBrowserControl->addWidget(cbbUrl);

    btnBookmark = new KPushButton(this);
    btnBookmark->setObjectName(QString::fromUtf8("btnBookmark"));
    sizePolicy1.setHeightForWidth(btnBookmark->sizePolicy().hasHeightForWidth());
    btnBookmark->setSizePolicy(sizePolicy1);
    btnBookmark->setMinimumSize(QSize(31, 31));
    btnBookmark->setMaximumSize(QSize(31, 31));
    btnBookmark->setToolTip(i18n("Add a new bookmark"));
    KIcon icnBookmark("rating");
    btnBookmark->setIcon(icnBookmark);
    hlBrowserControl->addWidget(btnBookmark);

    line_4 = new QFrame(this);
    line_4->setObjectName(QString::fromUtf8("line_4"));
    line_4->setFrameShape(QFrame::VLine);
    line_4->setFrameShadow(QFrame::Sunken);
    hlBrowserControl->addWidget(line_4);

    btnNewTab = new KPushButton(this);
    btnNewTab->setObjectName(QString::fromUtf8("btnNewTab"));
    sizePolicy1.setHeightForWidth(btnNewTab->sizePolicy().hasHeightForWidth());
    btnNewTab->setSizePolicy(sizePolicy1);
    btnNewTab->setMinimumSize(QSize(31, 31));
    btnNewTab->setMaximumSize(QSize(31, 31));
    btnNewTab->setToolTip(i18n("Add a new tab"));
    KIcon icnNewWin("window-new");
    btnNewTab->setIcon(icnNewWin);
    hlBrowserControl->addWidget(btnNewTab);

    btnCloseTab = new KPushButton(this);
    btnCloseTab->setObjectName(QString::fromUtf8("btnCloseTab"));
    sizePolicy1.setHeightForWidth(btnCloseTab->sizePolicy().hasHeightForWidth());
    btnCloseTab->setSizePolicy(sizePolicy1);
    btnCloseTab->setMinimumSize(QSize(31, 31));
    btnCloseTab->setMaximumSize(QSize(31, 31));
    KIcon icnDelWin("window-suppressed");
    btnCloseTab->setIcon(icnDelWin);
    hlBrowserControl->addWidget(btnCloseTab);


    verticalLayout_8->addLayout(hlBrowserControl);

    tabBBrowserPage = new KTabWidget(this);
    tabBBrowserPage->setObjectName(QString::fromUtf8("tabBBrowserPage"));
    tabBBrowserPage->setTabPosition(QTabWidget::South);
    tabBBrowserPage->setTabReorderingEnabled(true);
    tabBBrowserPage->setHoverCloseButton(true);
    tabBBrowserPage->setHoverCloseButtonDelayed(false);
    tabBBrowserPage->setTabCloseActivatePrevious(true);
    tabBBrowserPage->setAutomaticResizeTabs(true);
    tabDefaultTab = new QWidget();
    tabDefaultTab->setObjectName(QString::fromUtf8("tabDefaultTab"));
    tabDefaultTab->setGeometry(QRect(0, 0, 500, 527));
    horizontalLayout_8 = new QHBoxLayout(tabDefaultTab);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    webDefaultPage = new QWebView(tabDefaultTab);
    webDefaultPage->setObjectName(QString::fromUtf8("webDefaultPage"));
    webDefaultPage->setUrl(QUrl("http://www.google.com/"));
    horizontalLayout_8->addWidget(webDefaultPage);

    tabBBrowserPage->addTab(tabDefaultTab, QString());
    
    verticalLayout_8->addWidget(tabBBrowserPage);
    
    tabBBrowserPage->setTabText(tabBBrowserPage->indexOf(tabDefaultTab), i18n("Page"));
    
    QObject::connect(btnBack, SIGNAL(clicked()), webDefaultPage, SLOT(back()));
    QObject::connect(btnNext, SIGNAL(clicked()), webDefaultPage, SLOT(forward()));
    QObject::connect(btnReload, SIGNAL(clicked()), webDefaultPage, SLOT(reload()));
    QObject::connect(btnStop, SIGNAL(clicked()), webDefaultPage, SLOT(stop()));
    QObject::connect(cbbUrl, SIGNAL(returnPressed()), this, SLOT(loadWebPage()));
  }
  
  void WebBrowser::loadWebPage() {
    webDefaultPage->setUrl(QUrl(cbbUrl->currentText()));
  }
  