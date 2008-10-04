/**     @file mainwindow.cpp

	This file is part of the Kling project
	Copyright (C) 2008 Emmanuel Lepage Vallee <elv1313@gmail.com>
	
	This software is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 or 3 of the License, or (at your option) any later version.

	This software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public License
	along with this library; see the file COPYING.LIB.  If not, write to
	the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA 02111-1307, USA.
	___________________

        The Main Window GUI and SLOTS functions

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/


#include <iostream>

#include "mainwindow.h"
#include "src/interface/scriptBrowser.h"
#include "src/interface/sheduledTask.h"
#include "src/interface/history.h"
#include "src/interface/commandList.h"
#include "src/interface/man.h"
#include "src/interface/debug.h"
#include "src/Shell.h"
#include "src/interface/scriptMonitor.h"
#include "src/interface/term.h"
#include "src/interface/completer.h"
#include "src/interface/logView.h"
#include "src/interface/config.h"
#include "src/interface/debugTerm.h"

#include "src/interface/newCronJob.h"
#include "src/interface/logView.h"
#include "src/interface/addScript.h"
#include "src/manParser.h"


#include <KFileDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <QTextStream>
#include <KStandardDirs>
#include <KConfigSkeleton>
#include <KConfigDialog>
#include <KMessageBox>
#include <KStatusBar>
#include <QFrame>

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QString>
#include <QtGui/QApplication> //
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
//#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow> //
#include <QtGui/QMenu> //
#include <QtGui/QMenuBar> //
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>//
#include <QtGui/QStatusBar> //
#include <QtGui/QTabWidget>
#include <QtGui/QTableView> //
#include <QtGui/QTableWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBox> //
#include <QtGui/QTreeWidget> //
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include "kcombobox.h" //
#include "klineedit.h"
#include "klistwidget.h" //
#include "kpushbutton.h"
#include "ktabwidget.h"
#include "ktextedit.h"
#include <kicon.h>
#include <KXmlGuiWindow>
#include <QTextDocumentFragment> //
#include <QCompleter>
#include <QHeaderView>
#include <QScrollBar>
#include <QColor>
#include <QBrush>
#include <QPalette>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>

/**
  MainWindow constructor

  @param[in] parent The parent widget (nothing)
*/
  MainWindow::MainWindow(QWidget *parent, KlingConfigSkeleton* configuration) : KXmlGuiWindow(parent) {
    klingConfigSkeleton = configuration;
    if (KStandardDirs::exists(KStandardDirs::locateLocal("appdata","")+"kling.db") == false) {
      KStandardDirs test;
      QFile::copy(KStandardDirs::locate( "appdata", "kling.db" ),KStandardDirs::locateLocal("appdata","")+"kling.db");
    }

    //Creating the database connection
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(KStandardDirs::locateLocal("appdata", "kling.db") );
    
    if ( db->open())
      std::cout << "database corectly opened" << std::endl;
    else
      std::cout << "ERROR while opening the database, get ready for a crash" << std::endl;


    
    centralwidget = new QWidget;
    setCentralWidget(centralwidget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(206, 24, 571, 629));
    verticalLayout_11 = new QVBoxLayout(centralwidget);
    verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
    tabCategories = new QTabWidget(centralwidget);
    tabCategories->setObjectName(QString::fromUtf8("tabCategories"));
    tabCategories->setGeometry(QRect(206, 24, 571, 629));
    tabCategories->setMaximumSize(QSize(16777215, 16777215));
    tabCategories->setTabPosition(QTabWidget::East);
    tabCategories->setTabShape(QTabWidget::Rounded);
    tabGestion = new QWidget();
    tabGestion->setObjectName(QString::fromUtf8("tabGestion"));
    tabGestion->setGeometry(QRect(0, 0, 520, 609));
    horizontalLayout_4 = new QVBoxLayout(tabGestion);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    QPalette aPalette;
    tabGestion->setStyleSheet(QString::fromUtf8("background-color:") + aPalette.base().color().name () +";");

    QSpacerItem* horizontalSpacer25 = new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    horizontalLayout_4->addItem(horizontalSpacer25);

    QSpacerItem* horizontalSpacer26 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    horizontalLayout_4->addItem(horizontalSpacer26);

    KIcon icon("window-close");
    tabEditor = new ScriptEditor(0);

    tabWebBrowser = new QWidget();
    tabWebBrowser->setObjectName(QString::fromUtf8("tabWebBrowser"));
    tabWebBrowser->setGeometry(QRect(0, 0, 520, 609));
    verticalLayout_8 = new QVBoxLayout(tabWebBrowser);
    verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
    hlBrowserControl = new QHBoxLayout();
    hlBrowserControl->setObjectName(QString::fromUtf8("hlBrowserControl"));
    btnBack = new KPushButton(tabWebBrowser);
    btnBack->setObjectName(QString::fromUtf8("btnBack"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed); //
    sizePolicy1.setHorizontalStretch(31); //
    sizePolicy1.setVerticalStretch(31); //
    sizePolicy1.setHeightForWidth(btnBack->sizePolicy().hasHeightForWidth()); //
    btnBack->setSizePolicy(sizePolicy1);
    btnBack->setMinimumSize(QSize(31, 31));
    btnBack->setMaximumSize(QSize(31, 31));
    KIcon icnGoPrevious("go-previous");
    btnBack->setIcon(icnGoPrevious);
    hlBrowserControl->addWidget(btnBack);

    btnNext = new KPushButton(tabWebBrowser);
    btnNext->setObjectName(QString::fromUtf8("btnNext"));
    sizePolicy1.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
    btnNext->setSizePolicy(sizePolicy1);
    btnNext->setMinimumSize(QSize(31, 31));
    btnNext->setMaximumSize(QSize(31, 31));
    KIcon icnGoEdit("go-next");
    btnNext->setIcon(icnGoEdit);
    hlBrowserControl->addWidget(btnNext);

    btnReload = new KPushButton(tabWebBrowser);
    btnReload->setObjectName(QString::fromUtf8("btnReload"));
    sizePolicy1.setHeightForWidth(btnReload->sizePolicy().hasHeightForWidth());
    btnReload->setSizePolicy(sizePolicy1);
    btnReload->setMinimumSize(QSize(31, 31));
    btnReload->setMaximumSize(QSize(31, 31));
    KIcon icnRefresh("view-refresh");
    btnReload->setIcon(icnRefresh);
    hlBrowserControl->addWidget(btnReload);

    btnStop = new KPushButton(tabWebBrowser);
    btnStop->setObjectName(QString::fromUtf8("btnStop"));
    sizePolicy1.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
    btnStop->setSizePolicy(sizePolicy1);
    btnStop->setMinimumSize(QSize(31, 31));
    btnStop->setMaximumSize(QSize(31, 31));
    btnStop->setIcon(icon);
    hlBrowserControl->addWidget(btnStop);

    cbbUrl = new KComboBox(tabWebBrowser);
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

    btnBookmark = new KPushButton(tabWebBrowser);
    btnBookmark->setObjectName(QString::fromUtf8("btnBookmark"));
    sizePolicy1.setHeightForWidth(btnBookmark->sizePolicy().hasHeightForWidth());
    btnBookmark->setSizePolicy(sizePolicy1);
    btnBookmark->setMinimumSize(QSize(31, 31));
    btnBookmark->setMaximumSize(QSize(31, 31));
    KIcon icnBookmark("rating");
    btnBookmark->setIcon(icnBookmark);
    hlBrowserControl->addWidget(btnBookmark);

    line_4 = new QFrame(tabWebBrowser);
    line_4->setObjectName(QString::fromUtf8("line_4"));
    line_4->setFrameShape(QFrame::VLine);
    line_4->setFrameShadow(QFrame::Sunken);
    hlBrowserControl->addWidget(line_4);

    btnNewTab = new KPushButton(tabWebBrowser);
    btnNewTab->setObjectName(QString::fromUtf8("btnNewTab"));
    sizePolicy1.setHeightForWidth(btnNewTab->sizePolicy().hasHeightForWidth());
    btnNewTab->setSizePolicy(sizePolicy1);
    btnNewTab->setMinimumSize(QSize(31, 31));
    btnNewTab->setMaximumSize(QSize(31, 31));
    KIcon icnNewWin("window-new");
    btnNewTab->setIcon(icnNewWin);
    hlBrowserControl->addWidget(btnNewTab);

    btnCloseTab = new KPushButton(tabWebBrowser);
    btnCloseTab->setObjectName(QString::fromUtf8("btnCloseTab"));
    sizePolicy1.setHeightForWidth(btnCloseTab->sizePolicy().hasHeightForWidth());
    btnCloseTab->setSizePolicy(sizePolicy1);
    btnCloseTab->setMinimumSize(QSize(31, 31));
    btnCloseTab->setMaximumSize(QSize(31, 31));
    KIcon icnDelWin("window-suppressed");
    btnCloseTab->setIcon(icnDelWin);
    hlBrowserControl->addWidget(btnCloseTab);


    verticalLayout_8->addLayout(hlBrowserControl);

    tabBBrowserPage = new KTabWidget(tabWebBrowser);
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
    webDefaultPage->setUrl(QUrl("http://www.google.ca/"));
    horizontalLayout_8->addWidget(webDefaultPage);

    tabBBrowserPage->addTab(tabDefaultTab, QString());
    verticalLayout_8->addWidget(tabBBrowserPage);

    verticalLayout_11->addWidget(tabCategories);

    commandStringList = new QStringList();
    dockScriptBrowser = new ScriptBrowser(this); 
    addDockWidget(Qt::LeftDockWidgetArea, dockScriptBrowser);

    dockSheduledTask = new SheduledTask(this); 
    addDockWidget(Qt::LeftDockWidgetArea, dockSheduledTask);

    dockDebug = new Debug(this); 
    addDockWidget(Qt::RightDockWidgetArea, dockDebug);

    dockCommandList = new CommandList(this, commandStringList); 
    addDockWidget(Qt::LeftDockWidgetArea, dockCommandList);

    dockManual = new Man(this); 
    addDockWidget(Qt::RightDockWidgetArea, dockManual);

    historyStringList = new QStringList();
    dockHistory = new History(0, historyStringList, klingConfigSkeleton); 
    addDockWidget(Qt::LeftDockWidgetArea, dockHistory);
    tabShell = new Term (dockHistory ,this, commandStringList, historyStringList);

    tabCategories->addTab(tabShell, QString());
    tabCategories->addTab(tabGestion, QString());
    tabCategories->addTab(tabEditor, QString());
    tabCategories->addTab(tabWebBrowser, QString());


          
          
    //Status bar stuff
    statusJobRunning = new QLabel();
    statusJobRunning->setText("0 running, 0 paused");
    statusJobRunning->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum);
    statusBar()->addWidget(statusJobRunning);
    
    QFrame* line_2 = new QFrame(this);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(line_2);
    
    statusCurrentDir = new QLabel();
    statusCurrentDir->setText("/home/lepagee");
    statusCurrentDir->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    statusBar()->addWidget(statusCurrentDir, 100);
    
    statusTask = new QLabel();
    statusBar()->setItemAlignment(2, Qt::AlignRight);
    statusBar()->addWidget(statusTask);
    
    statusProgressBar = new QProgressBar();
    statusProgressBar->setMaximumSize(100,9999);
    statusProgressBar->setMinimumSize(100,0);
    statusBar()->setItemAlignment(3, Qt::AlignRight);
    statusBar()->addWidget(statusProgressBar);

    QObject::connect(tabCategories, SIGNAL(currentChanged(int)), this, SLOT(modeChanged(int)));
    /*QObject::connect(kpushbutton_6, SIGNAL(clicked()), frame_2, SLOT(hide()));
    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(saveFile()));*/
    QObject::connect(btnBack, SIGNAL(clicked()), webDefaultPage, SLOT(back()));
    QObject::connect(btnNext, SIGNAL(clicked()), webDefaultPage, SLOT(forward()));
    QObject::connect(btnReload, SIGNAL(clicked()), webDefaultPage, SLOT(reload()));
    QObject::connect(btnStop, SIGNAL(clicked()), webDefaultPage, SLOT(stop()));
    QObject::connect(cbbUrl, SIGNAL(returnPressed()), this, SLOT(loadWebPage()));
    /*QObject::connect(btnCopy, SIGNAL(clicked()), txtScriptEditor, SLOT(copy()));
    QObject::connect(btnPaste, SIGNAL(clicked()), txtScriptEditor, SLOT(paste()));
    QObject::connect(btnCut, SIGNAL(clicked()), txtScriptEditor, SLOT(cut()));
    QObject::connect(bntNext, SIGNAL(clicked()), txtScriptEditor, SLOT(redo()));
    QObject::connect(btnPrevious, SIGNAL(clicked()), txtScriptEditor, SLOT(undo()));
    QObject::connect(btnPaste, SIGNAL(clicked()), this, SLOT(seNewLine()));
    QObject::connect(klineedit_4, SIGNAL(returnPressed()), this, SLOT(searchEdit()));
    QObject::connect(kpushbutton_7, SIGNAL(clicked()), this, SLOT(searchEdit()));
    QObject::connect(btnDebug, SIGNAL(clicked()), this, SLOT(startDebugging()));
    QObject::connect(btnStopDebug, SIGNAL(clicked()), this, SLOT(stopDebugging()));
    QObject::connect(btnDbgNextLine, SIGNAL(clicked()), this, SLOT(dbgNextLine()));
    QObject::connect(btnDbgSkipLine, SIGNAL(clicked()), this, SLOT(dbgSkipLine()));
    QObject::connect(btnDgbNextBP, SIGNAL(clicked()), this, SLOT(dbgGoToNextBP()));
    QObject::connect(btnComment, SIGNAL(clicked()), this, SLOT(commentLine()));
    QObject::connect(btnUncomment, SIGNAL(clicked()), this, SLOT(uncommentLine()));*/
    QObject::connect(dockScriptBrowser, SIGNAL(enableEditor(bool)), tabEditor->txtScriptEditor, SLOT(setEnabled(bool)));
    QObject::connect(dockScriptBrowser, SIGNAL(setFileName(QString)), tabEditor, SLOT(setFileName(QString)));
    QObject::connect(dockScriptBrowser, SIGNAL(setEdirorText(QString)), tabEditor, SLOT(setText(QString)));
    QObject::connect(dockScriptBrowser, SIGNAL(launchScript(QString, QString)), this, SLOT(launchScript(QString, QString)));

    retranslateUi();
    setupActions();
  }

/**
  MainWindow destructor
*/
  MainWindow::~MainWindow() {
    db->close();

    delete centralwidget;
    /*
    delete verticalLayout_11;
    delete tabCategories;
    delete tabGestion;/
    delete horizontalLayout_4;
    delete tabShell;//
    delete verticalLayout_6;
    delete frame;
    delete horizontalLayout_3;
    delete kpushbutton_4;
    delete label;
    delete klineedit_3; 
    delete kpushbutton_5;
    delete cmdStatus;
    delete pxmCmdInactive;
    delete rtfCmdOutput;
    delete hlCommand;
    delete txtCommand;
    delete cbbOutModifier;
    delete kpushbutton_3;
    delete tabEditor;//
    delete verticalLayout_7;
    delete hlControl2;
    delete btnPrevious;
    delete bntNext;
    delete line;
    delete btnSave;
    delete btnPrint;
    delete line_2;
    delete btnComment;
    delete btnUncomment;
    delete btnCopy;
    delete btnCut;
    delete btnPaste;
    delete line_3;
    delete btnDebug;
    delete btnStopDebug;
    delete btnDbgNextLine;
    delete btnDbgSkipLine;
    delete btnDgbNextBP;
    delete horizontalSpacer;
    delete scrollArea;
    delete scrollAreaWidgetContents_2;
    delete verticalLayout_13;
    delete textEditLayout;
    delete frame_3;
    delete verticalSpacer_12;
    delete verticalLayout_29;
    delete txtScriptEditor;
    delete frame_2;
    delete horizontalLayout_5;
    delete kpushbutton_6;
    delete label_2;
    delete klineedit_4;
    delete kpushbutton_7;
    delete tabWebBrowser;
    delete verticalLayout_8;
    delete hlBrowserControl;
    delete btnBack;
    delete btnNext;
    delete btnReload;
    delete btnStop;
    delete cbbUrl;
    delete btnBookmark;
    delete line_4;
    delete btnNewTab;
    delete btnCloseTab;
    delete tabBBrowserPage;
    delete tabDefaultTab;
    delete horizontalLayout_8;
    delete commandStringList;
    delete cmdLineCompleter;
    delete webDefaultPage; 
    delete db;
    delete lineNBSideBar;*/
  }

/**
  User interface strings
*/
  void MainWindow::retranslateUi() {
    tabCategories->setTabText(tabCategories->indexOf(tabGestion), QApplication::translate("MainWindow", "Gestion  ", 0, QApplication::UnicodeUTF8));
    //label->setText(QApplication::translate("MainWindow", "Filter:", 0, QApplication::UnicodeUTF8));
    //kpushbutton_5->setText(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabShell), QApplication::translate("MainWindow", "Terminal  ", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabEditor), QApplication::translate("MainWindow", "Creation  ", 0, QApplication::UnicodeUTF8));
    tabBBrowserPage->setTabText(tabBBrowserPage->indexOf(tabDefaultTab), QApplication::translate("MainWindow", "Page", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabWebBrowser), QApplication::translate("MainWindow", "Web Browser   ", 0, QApplication::UnicodeUTF8));
  } // retranslateUi


/**
  Setup action for key shortcut, toolbar items and menu items
*/
  void MainWindow::setupActions() {
    KAction* newScriptAction = new KAction(this);
    newScriptAction->setText(i18n("New Script"));
    newScriptAction->setIcon(KIcon("document-new"));
    newScriptAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newScript", newScriptAction);
    connect(newScriptAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));
    
    KAction* importScriptAction = new KAction(this);
    importScriptAction->setText(i18n("Import"));
    importScriptAction->setIcon(KIcon("document-open"));
    importScriptAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("importScript", importScriptAction);
    connect(importScriptAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));
    
    KAction* saveTextAction = new KAction(this);
    saveTextAction->setText(i18n("Save"));
    saveTextAction->setIcon(KIcon("document-save"));
    saveTextAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("saveText", saveTextAction);
    connect(saveTextAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));
    
    KAction* clearAction = new KAction(this);
    clearAction->setText(i18n("Clear"));
    clearAction->setIcon(KIcon("document-new"));
    clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("clear", clearAction);
    connect(clearAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));

    KAction* findAction = new KAction(this);
    findAction->setText(i18n("Find"));
    findAction->setIcon(KIcon("edit-find"));
    findAction->setShortcut(Qt::CTRL + Qt::Key_F);
    actionCollection()->addAction("find", findAction);
    connect(findAction, SIGNAL(triggered(bool)),
    this, SLOT(find()));
    
    KAction* configureAction = new KAction(this);
    configureAction->setText(i18n("Configure Kling"));
    configureAction->setIcon(KIcon("configure"));
    //configureAction->setShortcut(Qt::CTRL + Qt::Key_F);
    actionCollection()->addAction("configure", configureAction);
    connect(configureAction, SIGNAL(triggered(bool)),
    this, SLOT(showSettings()));

    KAction* playAction = new KAction(this);
    playAction->setText(i18n("Play"));
    playAction->setIcon(KIcon("arrow-right"));
    playAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("play", playAction);
    connect(playAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));

    KAction* pauseAction = new KAction(this);
    pauseAction->setText(i18n("Plause"));
    pauseAction->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/pause.png")));
    pauseAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("pause", pauseAction);
    connect(pauseAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("Stop"));
    stopAction->setIcon(KIcon("dialog-close"));
    stopAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("stop", stopAction);
    connect(stopAction, SIGNAL(triggered(bool)),
    tabEditor->txtScriptEditor, SLOT(clear()));

    KAction* showLogAction = new KAction(this);
    showLogAction->setText(i18n("Show Log"));
    showLogAction->setIcon(KIcon("document-preview"));
    showLogAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("showLog", showLogAction);
    connect(showLogAction, SIGNAL(triggered(bool)),
    this, SLOT(showLog()));
    
    KAction* newCronAction = new KAction(this);
    newCronAction->setText(i18n("New Cron Job"));
    newCronAction->setIcon(KIcon("list-add"));
    newCronAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newCron", newCronAction);
    connect(newCronAction, SIGNAL(triggered(bool)),
    this, SLOT(newCronJob()));
    
    KAction* rescanManAction = new KAction(this);
    rescanManAction->setText(i18n("Rebuild Manual Database"));
    rescanManAction->setIcon(KIcon("list-add"));
    rescanManAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("rescanMan", rescanManAction);
    connect(rescanManAction, SIGNAL(triggered(bool)),
    this, SLOT(parseAllManPage()));
    
    viewScriptBrowser = new KAction(this);
    viewScriptBrowser->setCheckable(true);
    viewScriptBrowser->setText(i18n("Script Browser"));
    viewScriptBrowser->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewScriptBrowser", viewScriptBrowser);
    connect(viewScriptBrowser, SIGNAL(triggered(bool)),
    this, SLOT(setViewScriptBrowser(bool)));
    
    viewScheduledTask = new KAction(this);
    viewScheduledTask->setCheckable(true);
    viewScheduledTask->setText(i18n("Scheduled Tasks"));
    viewScheduledTask->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewScheduledTask", viewScheduledTask);
    connect(viewScheduledTask, SIGNAL(triggered(bool)),
    this, SLOT(setViewScheduledTask(bool)));

    viewCommandList = new KAction(this);
    viewCommandList->setCheckable(true);
    viewCommandList->setText(i18n("Command List"));
    viewCommandList->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewCommandList", viewCommandList);
    connect(viewCommandList, SIGNAL(triggered(bool)),
    this, SLOT(setViewCommandList(bool)));
    
    viewHistory = new KAction(this);
    viewHistory->setCheckable(true);
    viewHistory->setText(i18n("History"));
    viewHistory->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewHistory", viewHistory);
    connect(viewHistory, SIGNAL(triggered(bool)),
    this, SLOT(setViewHistory(bool)));
    
    viewManPage = new KAction(this);
    viewManPage->setCheckable(true);
    viewManPage->setChecked(true);
    viewManPage->setText(i18n("Man Page"));
    viewManPage->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewManPage", viewManPage);
    connect(viewManPage, SIGNAL(triggered(bool)),
    this, SLOT(setViewManPage(bool)));
    
    viewDebug = new KAction(this);
    viewDebug->setCheckable(true);
    viewDebug->setChecked(true);
    viewDebug->setText(i18n("Variables"));
    viewDebug->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("viewDebug", viewDebug);
    connect(viewDebug, SIGNAL(triggered(bool)),
    this, SLOT(setViewDebug(bool)));


    KStandardAction::quit(kapp, SLOT(quit()),
    actionCollection());

    KStandardAction::open(this, SLOT(openFile()),
    actionCollection());

    KStandardAction::save(this, SLOT(saveFile()),
    actionCollection());

    KStandardAction::saveAs(this, SLOT(saveFileAs()),
    actionCollection());
    
    setupGUI();
  }

/**
  the editor tab search box function
*/
   void MainWindow::searchEdit() {
      if (tabEditor->klineedit_4->text() != "")
        tabEditor->txtScriptEditor->find(tabEditor->klineedit_4->text());
    }

/**
  called when you do a CTRL+F, show the right search box
*/
  void MainWindow::find() {
    if (tabCategories->currentIndex () == 0) {
      tabShell->frame->show();
      tabShell->klineedit_3->setFocus();
      tabShell->klineedit_3->selectAll();
    }
    else {
      tabEditor->frame_2->show();
      tabEditor->klineedit_4->setFocus();
      tabEditor->klineedit_4->selectAll();
    }
  }



  void MainWindow::loadWebPage() {
    webDefaultPage->setUrl(QUrl(cbbUrl->currentText()));
  }

  void MainWindow::showLog() {
    LogView *dialog = new LogView( this, klingConfigSkeleton);
    dialog->show();
  }

  void MainWindow::showSettings(){
    if(KConfigDialog::showDialog("settings"))
      return;
      
    Config* aConfigDialog = new Config(this, klingConfigSkeleton);
    aConfigDialog->show();
  }
 
  void MainWindow::modeChanged(int index) {
    if (index == TERMINAL_MODE) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryTerminal);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserTerminal);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskTerminal);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListTerminal);
      dockManual->setVisible(klingConfigSkeleton->showManPageTerminal);
      dockDebug->setVisible(klingConfigSkeleton->showDebugTerminal);
      
      viewManPage->setChecked(klingConfigSkeleton->showManPageTerminal);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryTerminal);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListTerminal);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskTerminal);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserTerminal);
      viewDebug->setChecked(klingConfigSkeleton->showDebugTerminal);
    }
    else if (index == MONITOR_MODE) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryMonitor);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserMonitor);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskMonitor);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListMonitor);
      dockManual->setVisible(klingConfigSkeleton->showManPageMonitor);
      dockDebug->setVisible(klingConfigSkeleton->showDebugMonitor);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPageMonitor);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryMonitor);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListMonitor);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskMonitor);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserMonitor);
      viewDebug->setChecked(klingConfigSkeleton->showDebugMonitor);
    }
    else if (index == EDITOR_MODE) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryEditor);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserEditor);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskEditor);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListEditor);
      dockManual->setVisible(klingConfigSkeleton->showManPageEditor);
      dockDebug->setVisible(klingConfigSkeleton->showDebugEditor);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPageEditor);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryEditor);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListEditor);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskEditor);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserEditor);
      viewDebug->setChecked(klingConfigSkeleton->showDebugEditor);
    }
    else if (index == WEB_BROWSER_MODE) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryrWebBrowser); //TODO typo
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserWebBrowser);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskrWebBrowser);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListrWebBrowser);
      dockManual->setVisible(klingConfigSkeleton->showManPagerWebBrowser);
      dockDebug->setVisible(klingConfigSkeleton->showDebugWebBrowser);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPagerWebBrowser);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryrWebBrowser);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListrWebBrowser);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskrWebBrowser);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserWebBrowser);
      viewDebug->setChecked(klingConfigSkeleton->showDebugWebBrowser);
    }
  
  }

void MainWindow::launchScript(QString name, QString content) {
  ScriptMonitor* aNewExecutionMonitor = new ScriptMonitor(tabGestion, name );
  horizontalLayout_4->addWidget( aNewExecutionMonitor);
  aNewExecutionMonitor->launchScript(content.toStdString());
}


  void MainWindow::setViewScriptBrowser(bool value) {  
    dockScriptBrowser->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showScriptBrowserTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showScriptBrowserMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showScriptBrowserEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showScriptBrowserWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewScheduledTask(bool value) {
    dockSheduledTask->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showScheduledTaskTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showScheduledTaskMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showScheduledTaskEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showScheduledTaskrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewCommandList(bool value) {
    dockCommandList->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showCommandListTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showCommandListMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showCommandListEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showCommandListrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewHistory(bool value) {
    dockHistory->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showHistoryTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showHistoryMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showHistoryEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showHistoryrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewManPage(bool value) {
    dockManual->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showManPageTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showManPageMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showManPageEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showManPagerWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }
  
  void MainWindow::setViewDebug(bool value) {
    dockDebug->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
      klingConfigSkeleton->showDebugTerminal = value;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      klingConfigSkeleton->showDebugMonitor = value;
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      klingConfigSkeleton->showDebugEditor = value;
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      klingConfigSkeleton->showDebugWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::newCronJob() {
    NewCronJob* aCronJob = new NewCronJob(0);
    aCronJob->show();
    dockSheduledTask->fillTable(); 
  }

  void MainWindow::parseAllManPage() {
    int answer = KMessageBox::warningYesNo( 0, i18n( "Please confirm. \n Note that the scan may take up to 1 hours to complete. \n You can use your computer during the procedure." ), i18n( "Warning" ));

    if (answer == KMessageBox::Yes) {
      statusProgressBar->setMinimum(0);
      statusProgressBar->setMaximum(0);
      statusTask->setText("Clearing database");
      QSqlQuery query;
      query.exec("REMOVE * FROM TMAN_PAGE");
      statusTask->setText("Scanning manual");
      ManThread* aThread = new ManThread(this);
      QObject::connect(aThread, SIGNAL(over()), this, SLOT(cleanStatusBarTask()));
      aThread->start();
    }
  }

  void MainWindow::cleanStatusBarTask() {
    statusProgressBar->setRange(0,100);
    statusProgressBar->setValue(0);
    statusTask->setText("");
  }