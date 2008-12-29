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


#include "mainwindow.h"
#include "src/interface/scriptBrowser.h"
#include "src/interface/sheduledTask.h"
#include "src/interface/history.h"
#include "src/interface/commandList.h"
#include "src/interface/man.h"
#include "src/interface/debug.h"
#include "src/interface/scriptMonitor.h"
#include "src/interface/term.h"
#include "src/interface/completer.h"
#include "src/interface/logView.h"
#include "src/interface/config.h"
#include "src/interface/debugTerm.h"
#include "src/interface/newCronJob.h"
#include "src/interface/logView.h"
#include "src/interface/addScript.h"
#include "src/interface/defaultScreen.h"
#include "src/interface/sessionLoader.h"
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
#include <KDialog>
#include <kicon.h>
#include <QHeaderView>
#include <QScrollBar>
#include <KLocale>
#include <KActionCollection>

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
      QFile::copy(KStandardDirs::locate( "appdata", "kling.db" ),KStandardDirs::locateLocal("appdata","")+"kling.db");
    }

    //Creating the database connection
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(KStandardDirs::locateLocal("appdata", "kling.db") );
    
    if ( !db->open())
      printf("ERROR while opening the database, get ready for a crash\n");

    tabCategories = new QTabWidget(this);
    tabCategories->setObjectName(QString::fromUtf8("tabCategories"));
    tabCategories->setTabPosition(QTabWidget::East);
    tabCategories->setTabShape(QTabWidget::Rounded);
    setCentralWidget(tabCategories);
    
    //These dock need to exist, they manage the completer and the logging
    historyStringList = new QStringList();
    dockHistory = new History(historyStringList, klingConfigSkeleton); 
    
    commandStringList = new QStringList();
    aliasList = new QStringList();
    defaultArgsList = new QStringList();
    functionList = new QStringList();
    dockCommandList = new CommandList(this, commandStringList, aliasList, defaultArgsList, functionList); 

    tabWebBrowser = new WebBrowser(0);

    tabEditor = new ScriptEditor(0, commandStringList, aliasList, defaultArgsList, functionList);
    
    tabAdvScripManager = new AdvancedScriptManager(0);
    
    tabGestion = new ExecutionMonitor(0);
    
    tabShell = new TermSession(this);
    tabShell->addTerm(dockHistory, commandStringList, aliasList, defaultArgsList, commandStringList, historyStringList);

    setupActions();
    for (int l =0; l < 5; l++) {
      if (klingConfigSkeleton->terminalTabOrder == l)
        tabCategories->addTab(tabShell, QString());
      else if (klingConfigSkeleton->monitorTabOrder == l)
        tabCategories->addTab(tabGestion, QString());
      else if (klingConfigSkeleton->editorTabOrder == l)
        tabCategories->addTab(tabEditor, QString());
      else if (klingConfigSkeleton->webbrowserTabOrder == l)
        tabCategories->addTab(tabWebBrowser, QString());
      else if (klingConfigSkeleton->scriptManagerTabOrder == l)
        tabCategories->addTab(tabAdvScripManager, QString());
    }
    
    if (tabCategories->count() == 0) {
      setCentralWidget(new DefaultScreen(0, klingConfigSkeleton));
      delete tabCategories;
      tabCategories = NULL;
      dockScriptBrowser = NULL;
      dockSheduledTask =  NULL;
      dockDebug =  NULL;
      dockCommandList =  NULL;
      dockManual =  NULL;
      dockHistory =  NULL;
      viewManPage->setEnabled(false);
      viewHistory->setEnabled(false);
      viewCommandList->setEnabled(false);
      viewScheduledTask->setEnabled(false);
      viewScriptBrowser->setEnabled(false);
      viewDebug->setDisabled(true);
    }
    else {
      dockScriptBrowser = new ScriptBrowser(this); 
      addDockWidget(Qt::LeftDockWidgetArea, dockScriptBrowser);

      dockSheduledTask = new SheduledTask(this); 
      addDockWidget(Qt::LeftDockWidgetArea, dockSheduledTask);

      dockDebug = new Debug(this); 
      addDockWidget(Qt::RightDockWidgetArea, dockDebug);
      
      addDockWidget(Qt::LeftDockWidgetArea, dockCommandList);

      dockManual = new Man(this); 
      addDockWidget(Qt::RightDockWidgetArea, dockManual);

      addDockWidget(Qt::LeftDockWidgetArea, dockHistory);
    }
    
    //Status bar stuff
    statusJobRunning = new QLabel();
    statusJobRunning->setText(i18n("0 running, 0 paused"));
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
    //statusBar()->setItemAlignment(2, Qt::AlignRight);
    statusBar()->addWidget(statusTask);
    
    statusProgressBar = new QProgressBar();
    statusProgressBar->setMaximumSize(100,9999);
    statusProgressBar->setMinimumSize(100,0);
    //statusBar()->setItemAlignment(3, Qt::AlignRight);
    statusBar()->addWidget(statusProgressBar);

    if (tabCategories != NULL)
      QObject::connect(tabCategories, SIGNAL(currentChanged(int)), this, SLOT(modeChanged(int)));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser, SIGNAL(enableEditor(bool)), tabEditor->txtScriptEditor, SLOT(setEnabled(bool)));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser, SIGNAL(setFileName(QString)), tabEditor, SLOT(setFileName(QString)));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser, SIGNAL(setEdirorText(QString)), tabEditor, SLOT(setText(QString)));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser, SIGNAL(launchScript(QString, QString)), tabGestion, SLOT(launchScript(QString, QString)));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser->btnEdit, SIGNAL(clicked()), this, SLOT(setEditorMode()));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser->btnEdit, SIGNAL(clicked()), tabEditor->txtScriptEditor, SLOT(setFocus()));
    if (dockScriptBrowser != NULL)
      QObject::connect(dockScriptBrowser->btnLaunch, SIGNAL(clicked()), this, SLOT(setMonitorMode()));

    if (tabCategories != NULL) {
      retranslateUi();
      modeChanged(tabCategories->currentIndex());
    }
  }

/**
  MainWindow destructor
*/
  MainWindow::~MainWindow() {
    db->close();
  }

/**
  User interface strings
*/
  void MainWindow::retranslateUi() {
    tabCategories->setTabText(tabCategories->indexOf(tabGestion), i18n("Gestion") + "  ");
    tabCategories->setTabText(tabCategories->indexOf(tabShell), i18n("Terminal") + "  ");
    tabCategories->setTabText(tabCategories->indexOf(tabEditor), i18n("Creation") + "  ");
    tabCategories->setTabText(tabCategories->indexOf(tabWebBrowser), i18n("Web Browser") + "  ");
    tabCategories->setTabText(tabCategories->indexOf(tabAdvScripManager), i18n("Manager") + "  ");
  }


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

    KAction* loadSessionAction = new KAction(this);
    loadSessionAction->setText(i18n("Load session"));
    loadSessionAction->setIcon(KIcon("document-new"));
    loadSessionAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("loadSession", loadSessionAction);
    connect(loadSessionAction, SIGNAL(triggered(bool)),
    this, SLOT(loadSession()));
    
    KAction* importScriptAction = new KAction(this);
    importScriptAction->setText(i18n("Import"));
    importScriptAction->setIcon(KIcon("document-import"));
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
    
    KAction* showAdvScriptManager = new KAction(this);
    showAdvScriptManager->setText(i18n("Script Manager"));
    showAdvScriptManager->setIcon(KIcon("list-add"));
    showAdvScriptManager->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("showAdvScriptManager", showAdvScriptManager);
    connect(showAdvScriptManager, SIGNAL(triggered(bool)),
    this, SLOT(showAdvancedScriptManager()));
    
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
    
    //File menu
    /*newScript = new KAction(this);
    newScript->setCheckable(true);
    newScript->setText(i18n("Scheduled Tasks"));
    newScript->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newScript", newScript);
    connect(newScript, SIGNAL(triggered(bool)),
    this, SLOT(setViewScheduledTask(bool)));*/
    
    KAction* newTermWindow = new KAction(this);
    newTermWindow->setText(i18n("Terminal"));
    newTermWindow->setIcon(KIcon("utilities-terminal"));
    newTermWindow->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newTermWindow", newTermWindow);
    connect(newTermWindow, SIGNAL(triggered(bool)),
    this, SLOT(newTerminal()));
    
    KAction* newTermTab = new KAction(this);
    newTermTab->setText(i18n("Terminal Tab"));
    newTermTab->setIcon(KIcon("utilities-terminal"));
    newTermTab->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newTermTab", newTermTab);
    connect(newTermTab, SIGNAL(triggered(bool)),
    this->tabShell, SLOT(addTerm()));
    
    KAction* newEditor = new KAction(this);
    newEditor->setText(i18n("Editor"));
    newEditor->setIcon(KIcon("accessories-text-editor"));
    newEditor->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("newEditor", newEditor);
    connect(newEditor, SIGNAL(triggered(bool)),
    this, SLOT(newEditor()));
    
    KAction* saveScript = new KAction(this);
    saveScript->setText(i18n("Save"));
    saveScript->setIcon(KIcon("document-save"));
    saveScript->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("saveScript", saveScript);
    connect(saveScript, SIGNAL(triggered(bool)),
    this, SLOT(save()));
    
    KAction* printScript = new KAction(this);
    printScript->setText(i18n("Print"));
    printScript->setIcon(KIcon("document-print"));
    printScript->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("printScript", printScript);
    connect(printScript, SIGNAL(triggered(bool)),
    this, SLOT(print()));
        
    KAction* exportLog = new KAction(this);
    exportLog->setText(i18n("Export Logs"));
    exportLog->setIcon(KIcon("document-export"));
    exportLog->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("exportLog", exportLog);
    connect(exportLog, SIGNAL(triggered(bool)),
    this, SLOT(exportLog()));
    
    KAction* backupLog = new KAction(this);
    backupLog->setText(i18n("Backup"));
    backupLog->setIcon(KIcon("tools-media-optical-copy"));
    backupLog->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("backupLog", backupLog);
    connect(backupLog, SIGNAL(triggered(bool)),
    this, SLOT(backup()));
    
    /*KAction* quit = new KAction(this);
    quit->setCheckable(true);
    quit->setText(i18n("Scheduled Tasks"));
    quit->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("quit", quit);
    connect(quit, SIGNAL(triggered(bool)),
    this, SLOT(setViewScheduledTask(bool)));*/

    //Edit menu
    actionUndo = new KAction(this);
    actionUndo->setText(i18n("Undo"));
    actionUndo->setIcon(KIcon("edit-undo"));
    actionUndo->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("undo", actionUndo);
    connect(actionUndo, SIGNAL(triggered(bool)),
    this, SLOT(undo()));
    
    actionRedo = new KAction(this);
    actionRedo->setText(i18n("Redo"));
    actionRedo->setIcon(KIcon("edit-redo"));
    actionRedo->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("redo", actionRedo);
    connect(actionRedo, SIGNAL(triggered(bool)),
    this, SLOT(redo()));
    
    actionCut = new KAction(this);
    actionCut->setText(i18n("Cut"));
    actionCut->setIcon(KIcon("edit-cut"));
    actionCut->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("cut", actionCut);
    connect(actionCut, SIGNAL(triggered(bool)),
    this, SLOT(cut()));
    
    actionCopy = new KAction(this);
    actionCopy->setText(i18n("Copy"));
    actionCopy->setIcon(KIcon("edit-copy"));
    actionCopy->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("copy", actionCopy);
    connect(actionCopy, SIGNAL(triggered(bool)),
    this, SLOT(copy()));
    
    actionPaste = new KAction(this);
    actionPaste->setText(i18n("Paste"));
    actionPaste->setIcon(KIcon("edit-paste"));
    actionPaste->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("paste", actionPaste);
    connect(actionPaste, SIGNAL(triggered(bool)),
    this, SLOT(paste()));
    
    actionSelectAll = new KAction(this);
    actionSelectAll->setText(i18n("Select All"));
    actionSelectAll->setIcon(KIcon("edit-select-all"));
    actionSelectAll->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("selectAll", actionSelectAll);
    connect(actionSelectAll, SIGNAL(triggered(bool)),
    this, SLOT(selectAll()));
    
    
    

    //KStandardAction::quit(kapp, SLOT(quit()),actionCollection());
    
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
      tabShell->getCurrentTerm()->frame->show();
      tabShell->getCurrentTerm()->klineedit_3->setFocus();
      tabShell->getCurrentTerm()->klineedit_3->selectAll();
    }
    else {
      tabEditor->frame_2->show();
      tabEditor->klineedit_4->setFocus();
      tabEditor->klineedit_4->selectAll();
    }
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
    saveDockState();
    if (index == klingConfigSkeleton->terminalTabOrder) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryTerminal);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserTerminal);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskTerminal);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListTerminal);
      dockManual->setVisible(klingConfigSkeleton->showManPageTerminal);
      dockDebug->setVisible(klingConfigSkeleton->showDebugTerminal);
        
      if (klingConfigSkeleton->scriptBrowserHeightTerminal != -1) {
        dockScriptBrowser->resize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        /*dockScriptBrowser->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockScriptBrowser->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockScriptBrowser->setMaximumSize(99999, 99999);
        dockScriptBrowser->setMinimumSize(0, 0);*/
      }
      if (klingConfigSkeleton->scheduledTaskHeightTerminal != -1) {
        dockSheduledTask->resize(dockSheduledTask->width(), klingConfigSkeleton->scheduledTaskHeightTerminal);
        /*dockSheduledTask->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockSheduledTask->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockSheduledTask->setMaximumSize(99999, 99999);
        dockSheduledTask->setMinimumSize(0, 0);*/
      }
      if (klingConfigSkeleton->commandListTHeighterminal != -1) {
        dockCommandList->resize(dockCommandList->width(), klingConfigSkeleton->commandListTHeighterminal);
        /*dockCommandList->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockCommandList->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockCommandList->setMaximumSize(99999, 99999);
        dockCommandList->setMinimumSize(0, 0);*/
      }
      if (klingConfigSkeleton->historyHeightTerminal != -1) {
        dockHistory->resize(dockHistory->width(), klingConfigSkeleton->historyHeightTerminal);
        /*dockHistory->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockHistory->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockHistory->setMaximumSize(99999, 99999);
        dockHistory->setMinimumSize(0, 0);*/
      }
      if (klingConfigSkeleton->manPageHeightTerminal != -1) {
        dockManual->resize(dockManual->width(), klingConfigSkeleton->manPageHeightTerminal);
        /*dockManual->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockManual->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockManual->setMaximumSize(99999, 99999);
        dockManual->setMinimumSize(0, 0);*/
      }
      if (klingConfigSkeleton->debugHeightTerminal != -1) {
        dockDebug->resize(dockDebug->width(), klingConfigSkeleton->debugHeightTerminal);
        /*dockDebug->setMaximumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockDebug->setMinimumSize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightTerminal);
        dockDebug->setMaximumSize(99999, 99999);
        dockDebug->setMinimumSize(0, 0);*/
      }
      
      viewManPage->setChecked(klingConfigSkeleton->showManPageTerminal);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryTerminal);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListTerminal);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskTerminal);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserTerminal);
      viewDebug->setChecked(klingConfigSkeleton->showDebugTerminal);
    }
    else if (index == klingConfigSkeleton->monitorTabOrder) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryMonitor);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserMonitor);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskMonitor);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListMonitor);
      dockManual->setVisible(klingConfigSkeleton->showManPageMonitor);
      dockDebug->setVisible(klingConfigSkeleton->showDebugMonitor);
      
      if (klingConfigSkeleton->scriptBrowserHeightMonitor != -1)
        dockScriptBrowser->resize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightMonitor);
      if (klingConfigSkeleton->scheduledTaskHeightMonitor != -1)
        dockSheduledTask->resize(dockSheduledTask->width(), klingConfigSkeleton->scheduledTaskHeightMonitor);
      if (klingConfigSkeleton->commandListHeightMonitor != -1)
        dockCommandList->resize(dockCommandList->width(), klingConfigSkeleton->commandListHeightMonitor);
      if (klingConfigSkeleton->historyHeightMonitor != -1)
        dockHistory->resize(dockHistory->width(), klingConfigSkeleton->historyHeightMonitor);
      if (klingConfigSkeleton->manPageHeightMonitor != -1)
        dockManual->resize(dockManual->width(), klingConfigSkeleton->manPageHeightMonitor);
      if (klingConfigSkeleton->debugHeightMonitor != -1)
        dockDebug->resize(dockDebug->width(), klingConfigSkeleton->debugHeightMonitor);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPageMonitor);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryMonitor);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListMonitor);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskMonitor);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserMonitor);
      viewDebug->setChecked(klingConfigSkeleton->showDebugMonitor);
    }
    else if (index == klingConfigSkeleton->editorTabOrder) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryEditor);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserEditor);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskEditor);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListEditor);
      dockManual->setVisible(klingConfigSkeleton->showManPageEditor);
      dockDebug->setVisible(klingConfigSkeleton->showDebugEditor);
      
      if (klingConfigSkeleton->scriptBrowserHeightEditor != -1)
        dockScriptBrowser->resize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightEditor);
      if (klingConfigSkeleton->scheduledTaskHeightEditor != -1)
        dockSheduledTask->resize(dockSheduledTask->width(), klingConfigSkeleton->scheduledTaskHeightEditor);
      if (klingConfigSkeleton->commandListHeightEditor != -1)
        dockCommandList->resize(dockCommandList->width(), klingConfigSkeleton->commandListHeightEditor);
      if (klingConfigSkeleton->historyHeightEditor != -1)
        dockHistory->resize(dockHistory->width(), klingConfigSkeleton->historyHeightEditor);
      if (klingConfigSkeleton->manPageHeightEditor != -1)
        dockManual->resize(dockManual->width(), klingConfigSkeleton->manPageHeightEditor);
      if (klingConfigSkeleton->debugHeightEditor != -1)
        dockDebug->resize(dockDebug->width(), klingConfigSkeleton->debugHeightEditor);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPageEditor);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryEditor);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListEditor);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskEditor);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserEditor);
      viewDebug->setChecked(klingConfigSkeleton->showDebugEditor);
    }
    else if (index == klingConfigSkeleton->webbrowserTabOrder) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryrWebBrowser); //TODO typo
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserWebBrowser);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskrWebBrowser);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListrWebBrowser);
      dockManual->setVisible(klingConfigSkeleton->showManPagerWebBrowser);
      dockDebug->setVisible(klingConfigSkeleton->showDebugWebBrowser);
      
      if (klingConfigSkeleton->scriptBrowserHeightWebBrowser != -1)
        dockScriptBrowser->resize(dockScriptBrowser->width(), klingConfigSkeleton->scriptBrowserHeightWebBrowser);
      if (klingConfigSkeleton->scheduledTaskHeightWebBrowser != -1)
        dockSheduledTask->resize(dockSheduledTask->width(), klingConfigSkeleton->scheduledTaskHeightWebBrowser);
      if (klingConfigSkeleton->commandListHeightWebBrowser != -1)
        dockCommandList->resize(dockCommandList->width(), klingConfigSkeleton->commandListHeightWebBrowser);
      if (klingConfigSkeleton->historyHeightWebBrowser != -1)
        dockHistory->resize(dockHistory->width(), klingConfigSkeleton->historyHeightWebBrowser);
      if (klingConfigSkeleton->manPageHeightWebBrowser != -1)
        dockManual->resize(dockManual->width(), klingConfigSkeleton->manPageHeightWebBrowser);
      if (klingConfigSkeleton->debugHeightWebBrowser != -1)
        dockDebug->resize(dockDebug->width(), klingConfigSkeleton->debugHeightWebBrowser);
          
      viewManPage->setChecked(klingConfigSkeleton->showManPagerWebBrowser);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryrWebBrowser);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListrWebBrowser);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskrWebBrowser);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserWebBrowser);
      viewDebug->setChecked(klingConfigSkeleton->showDebugWebBrowser);
    }
    else if (index == klingConfigSkeleton->scriptManagerTabOrder) {
      dockHistory->setVisible(klingConfigSkeleton->showHistoryAdvScriptManager);
      dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserAdvScriptManager);
      dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskAdvScriptManager);
      dockCommandList->setVisible(klingConfigSkeleton->showCommandListAdvScriptManager);
      dockManual->setVisible(klingConfigSkeleton->showManPageAdvScriptManager);
      dockDebug->setVisible(klingConfigSkeleton->showDebugAdvScriptManager);
      
   
          
      viewManPage->setChecked(klingConfigSkeleton->showManPageAdvScriptManager);
      viewHistory->setChecked(klingConfigSkeleton->showHistoryAdvScriptManager);
      viewCommandList->setChecked(klingConfigSkeleton->showCommandListAdvScriptManager);
      viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskAdvScriptManager);
      viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserAdvScriptManager);
      viewDebug->setChecked(klingConfigSkeleton->showDebugAdvScriptManager);
    }
    currentMode= index;
  }



  void MainWindow::setViewScriptBrowser(bool value) {  
    dockScriptBrowser->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showScriptBrowserTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showScriptBrowserMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showScriptBrowserEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showScriptBrowserWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewScheduledTask(bool value) {
    dockSheduledTask->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showScheduledTaskTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showScheduledTaskMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showScheduledTaskEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showScheduledTaskrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewCommandList(bool value) {
    dockCommandList->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showCommandListTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showCommandListMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showCommandListEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showCommandListrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewHistory(bool value) {
    dockHistory->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showHistoryTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showHistoryMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showHistoryEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showHistoryrWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }

  void MainWindow::setViewManPage(bool value) {
    dockManual->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showManPageTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showManPageMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showManPageEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showManPagerWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }
  
  void MainWindow::setViewDebug(bool value) {
    dockDebug->setVisible(value);
    if (tabCategories->currentIndex() == klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->showDebugTerminal = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->showDebugMonitor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->showDebugEditor = value;
    }
    else if (tabCategories->currentIndex() == klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->showDebugWebBrowser = value;
    }
    klingConfigSkeleton->writeConfig();
  }
  
  void MainWindow::saveDockState() {
    if (currentMode ==  klingConfigSkeleton->terminalTabOrder) {
      klingConfigSkeleton->scriptBrowserHeightTerminal = dockScriptBrowser->height();
      klingConfigSkeleton->scheduledTaskHeightTerminal = dockSheduledTask->height();
      klingConfigSkeleton->commandListTHeighterminal = dockCommandList->height();
      klingConfigSkeleton->historyHeightTerminal = dockHistory->height();
      klingConfigSkeleton->manPageHeightTerminal = dockManual->height();
      klingConfigSkeleton->debugHeightTerminal = dockDebug->height();
    }
    else if (currentMode ==  klingConfigSkeleton->monitorTabOrder) {
      klingConfigSkeleton->scriptBrowserHeightMonitor = dockScriptBrowser->height();
      klingConfigSkeleton->scheduledTaskHeightMonitor = dockSheduledTask->height();
      klingConfigSkeleton->commandListHeightMonitor = dockCommandList->height();
      klingConfigSkeleton->historyHeightMonitor = dockHistory->height();
      klingConfigSkeleton->manPageHeightMonitor = dockManual->height();
      klingConfigSkeleton->debugHeightMonitor = dockDebug->height();
    }
    else if (currentMode ==  klingConfigSkeleton->editorTabOrder) {
      klingConfigSkeleton->scriptBrowserHeightEditor = dockScriptBrowser->height();
      klingConfigSkeleton->scheduledTaskHeightEditor = dockSheduledTask->height();
      klingConfigSkeleton->commandListHeightEditor = dockCommandList->height();
      klingConfigSkeleton->historyHeightEditor = dockHistory->height();
      klingConfigSkeleton->manPageHeightEditor = dockManual->height();
      klingConfigSkeleton->debugHeightEditor = dockDebug->height();
    }
    else if (currentMode ==  klingConfigSkeleton->webbrowserTabOrder) {
      klingConfigSkeleton->scriptBrowserHeightWebBrowser = dockScriptBrowser->height();
      klingConfigSkeleton->scheduledTaskHeightWebBrowser = dockSheduledTask->height();
      klingConfigSkeleton->commandListHeightWebBrowser = dockCommandList->height();
      klingConfigSkeleton->historyHeightWebBrowser = dockHistory->height();
      klingConfigSkeleton->manPageHeightWebBrowser = dockManual->height();
      klingConfigSkeleton->debugHeightWebBrowser = dockDebug->height();
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
      statusTask->setText(i18n("Clearing database"));
      QSqlQuery query;
      query.exec("REMOVE * FROM TMAN_PAGE");
      statusTask->setText(i18n("Scanning manual"));
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

  void MainWindow::setEditorMode() {
    tabCategories->setCurrentIndex(klingConfigSkeleton->editorTabOrder);
  }

  void MainWindow::setMonitorMode() {
    tabCategories->setCurrentIndex(klingConfigSkeleton->monitorTabOrder);
  }
  
  void MainWindow::showAdvancedScriptManager() {
    KDialog* aDialog = new KDialog(this);
    AdvancedScriptManager* dialogContent = new AdvancedScriptManager(aDialog);
    aDialog->setMainWidget(dialogContent);
    aDialog->resize(875,500);
    aDialog->show();
  }

  void MainWindow::newTerminal() {    
    if (dockCommandList == NULL)
      dockCommandList = new CommandList(0, commandStringList, aliasList, defaultArgsList, functionList);
    if (dockHistory == NULL)
      dockHistory = new History(historyStringList, klingConfigSkeleton);
    
    
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Terminal");
    aDialog->resize(780,530);
    Term* centralWidget = new Term(dockHistory, 0, commandStringList, aliasList, defaultArgsList, functionList, historyStringList);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void MainWindow::newGestion() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Current Task Monitor");
    aDialog->resize(780,530);
    ExecutionMonitor* centralWidget = new ExecutionMonitor(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void MainWindow::newEditor() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Script Editor");
    aDialog->resize(780,530);
    ScriptEditor* centralWidget = new ScriptEditor(0, commandStringList, aliasList, defaultArgsList, functionList);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void MainWindow::newWebBrowser() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Web Browser");
    aDialog->resize(780,530);
    WebBrowser* centralWidget = new WebBrowser(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void MainWindow::newMonitor() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Script Manager");
    aDialog->resize(780,530);
    AdvancedScriptManager* centralWidget = new AdvancedScriptManager(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }  
  
  void MainWindow::save() {
    
  }
  
  void MainWindow::print() {
    
  }
  
  void MainWindow::exportLog() {
    
  }
  
  void MainWindow::backup() {
    
  }
  
  void MainWindow::cut() {
    
  }
  
  void MainWindow::copy() {
    
  }
  
  void MainWindow::paste() {
    
  }
  
  void MainWindow::undo() {
    
  }
  
  void MainWindow::redo() {
    
  }
  
  void MainWindow::selectAll() {
    
  }
  
  void MainWindow::loadSession() {
    SessionLoader* aLoader = new SessionLoader(this, tabShell);
    aLoader->show();
  }