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

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>

/**
  MainWindow constructor

  @param[in] parent The parent widget (nothing)
*/
    MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
    {
      klingConfigSkeleton = new  KlingConfigSkeleton();
      klingConfigSkeleton->readConfig();
      /*if (KStandardDirs::locateLocal("appdata","kling.db") == "") {
        KStandardDirs test;
        QFile::copy(KStandardDirs::locate( "appdata", "kling.db" ),test.saveLocation("appdata")+"kling.db");
      }*/

      //Creating the database connection
      db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
      db->setDatabaseName( "/home/lepagee/dev/tp3-prog_sess2/kling.db" );
      if ( db->open())
      {
	std::cout << "database corectly opened" << std::endl;
      }
      else
      {
	std::cout << "ERROR while opening the database, get ready for a crash" << std::endl;
      }


      isDebugging = false;
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
    tabGestion->setStyleSheet(QString::fromUtf8("background-color:white;"));


    QSpacerItem* horizontalSpacer25 = new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    horizontalLayout_4->addItem(horizontalSpacer25);


    QSpacerItem* horizontalSpacer26 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    horizontalLayout_4->addItem(horizontalSpacer26);

    
//TABSHELL WAS HERE




    KIcon icon("window-close");
    tabEditor = new QWidget();
    tabEditor->setObjectName(QString::fromUtf8("tabEditor"));
    tabEditor->setGeometry(QRect(0, 0, 520, 609));
    verticalLayout_7 = new QVBoxLayout(tabEditor);
    verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
    hlControl2 = new QHBoxLayout();
    hlControl2->setObjectName(QString::fromUtf8("hlControl2"));
    btnPrevious = new KPushButton(tabEditor);
    btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
    btnPrevious->setMinimumSize(QSize(31, 31));
    btnPrevious->setMaximumSize(QSize(31, 31));
    KIcon icnEditUndo("edit-undo");
    btnPrevious->setIcon(icnEditUndo);

    hlControl2->addWidget(btnPrevious);

    bntNext = new KPushButton(tabEditor);
    bntNext->setObjectName(QString::fromUtf8("bntNext"));
    bntNext->setMinimumSize(QSize(31, 31));
    bntNext->setMaximumSize(QSize(31, 31));
    KIcon icnEditRedo("edit-redo");
    bntNext->setIcon(icnEditRedo);

    hlControl2->addWidget(bntNext);

    line = new QFrame(tabEditor);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    hlControl2->addWidget(line);

    btnSave = new KPushButton(tabEditor);
    btnSave->setObjectName(QString::fromUtf8("btnSave"));
    btnSave->setMinimumSize(QSize(31, 31));
    btnSave->setMaximumSize(QSize(31, 31));
    KIcon icnDocSave("document-save");
    btnSave->setIcon(icnDocSave);

    hlControl2->addWidget(btnSave);

    btnPrint = new KPushButton(tabEditor);
    btnPrint->setObjectName(QString::fromUtf8("btnPrint"));
    btnPrint->setMinimumSize(QSize(31, 31));
    btnPrint->setMaximumSize(QSize(31, 31));
    KIcon icnDocPrint("document-print");
    btnPrint->setIcon(icnDocPrint);

    hlControl2->addWidget(btnPrint);

    line_2 = new QFrame(tabEditor);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);

    hlControl2->addWidget(line_2);

    btnComment = new KPushButton(tabEditor);
    btnComment->setObjectName(QString::fromUtf8("btnComment"));
    btnComment->setMinimumSize(QSize(31, 31));
    btnComment->setMaximumSize(QSize(31, 31));
    KIcon icon5(KStandardDirs::locate( "appdata", "pixmap/22x22/comment.png"));
    btnComment->setIcon(icon5);
    btnComment->setIconSize(QSize(12, 12));

    hlControl2->addWidget(btnComment);

    btnUncomment = new KPushButton(tabEditor);
    btnUncomment->setObjectName(QString::fromUtf8("btnUncomment"));
    btnUncomment->setMinimumSize(QSize(31, 31));
    btnUncomment->setMaximumSize(QSize(31, 31));
    KIcon icon6(KStandardDirs::locate( "appdata", "pixmap/22x22/uncomment.png"));
    btnUncomment->setIcon(icon6);
    btnUncomment->setIconSize(QSize(14, 14));

    hlControl2->addWidget(btnUncomment);

    btnCopy = new KPushButton(tabEditor);
    btnCopy->setObjectName(QString::fromUtf8("btnCopy"));
    btnCopy->setMinimumSize(QSize(31, 31));
    btnCopy->setMaximumSize(QSize(31, 31));
    KIcon icnEditCopy("edit-copy");
    btnCopy->setIcon(icnEditCopy);

    hlControl2->addWidget(btnCopy);

    btnCut = new KPushButton(tabEditor);
    btnCut->setObjectName(QString::fromUtf8("btnCut"));
    btnCut->setMinimumSize(QSize(31, 31));
    btnCut->setMaximumSize(QSize(31, 31));
    KIcon icnEditCut("edit-cut");
    btnCut->setIcon(icnEditCut);

    hlControl2->addWidget(btnCut);

    btnPaste = new KPushButton(tabEditor);
    btnPaste->setObjectName(QString::fromUtf8("btnPaste"));
    btnPaste->setMinimumSize(QSize(31, 31));
    btnPaste->setMaximumSize(QSize(31, 31));
    KIcon icnEditPaste("edit-paste");
    btnPaste->setIcon(icnEditPaste);

    hlControl2->addWidget(btnPaste);

    line_3 = new QFrame(tabEditor);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::VLine);
    line_3->setFrameShadow(QFrame::Sunken);

    hlControl2->addWidget(line_3);

    btnDebug = new KPushButton(tabEditor);
    btnDebug->setObjectName(QString::fromUtf8("btnDebug"));
    btnDebug->setMinimumSize(QSize(31, 31));
    btnDebug->setMaximumSize(QSize(31, 31));
    KIcon icnArrowRight("arrow-right");
    btnDebug->setIcon(icnArrowRight);

    hlControl2->addWidget(btnDebug);

    btnStopDebug = new KPushButton(tabEditor);
    btnStopDebug->setObjectName(QString::fromUtf8("btnStopDebug"));
    btnStopDebug->setMinimumSize(QSize(31, 31));
    btnStopDebug->setMaximumSize(QSize(31, 31));
    btnStopDebug->setIcon(icon);

    hlControl2->addWidget(btnStopDebug);

    btnDbgNextLine = new KPushButton(tabEditor);
    btnDbgNextLine->setObjectName(QString::fromUtf8("btnDbgNextLine"));
    btnDbgNextLine->setMinimumSize(QSize(31, 31));
    btnDbgNextLine->setMaximumSize(QSize(31, 31));
    KIcon icon11(KStandardDirs::locate( "appdata", "pixmap/22x22/nextline.png"));
    btnDbgNextLine->setIcon(icon11);
    btnDbgNextLine->setIconSize(QSize(16, 16));

    hlControl2->addWidget(btnDbgNextLine);

    btnDbgSkipLine = new KPushButton(tabEditor);
    btnDbgSkipLine->setObjectName(QString::fromUtf8("btnDbgSkipLine"));
    btnDbgSkipLine->setMinimumSize(QSize(31, 31));
    btnDbgSkipLine->setMaximumSize(QSize(31, 31));
    KIcon icon12(KStandardDirs::locate( "appdata", "pixmap/22x22/skipline.png"));
    btnDbgSkipLine->setIcon(icon12);
    btnDbgSkipLine->setIconSize(QSize(16, 16));

    hlControl2->addWidget(btnDbgSkipLine);

    btnDgbNextBP = new KPushButton(tabEditor);
    btnDgbNextBP->setObjectName(QString::fromUtf8("btnDgbNextBP"));
    btnDgbNextBP->setMinimumSize(QSize(31, 31));
    btnDgbNextBP->setMaximumSize(QSize(31, 31));
    KIcon icon13(KStandardDirs::locate( "appdata", "pixmap/22x22/run.png"));
    btnDgbNextBP->setIcon(icon13);
    btnDgbNextBP->setIconSize(QSize(16, 16));

    hlControl2->addWidget(btnDgbNextBP);

    horizontalSpacer = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hlControl2->addItem(horizontalSpacer);


    verticalLayout_7->addLayout(hlControl2);

    scrollArea = new QScrollArea(tabEditor);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setStyleSheet(QString::fromUtf8("margin-left: 0px;\n"
"margin-right: 0px;\n"
"margin-top: 0px;\n"
"margin-bottom: 0px;\n"
"border-left: 0px;\n"
"border-right: 0px;\n"
"border-top: 0px;\n"
"border-bottom: 0px;\n"
"padding-left: 0px;\n"
"padding-right: 0px;\n"
"padding-top: 0px;\n"
"padding-bottom: 0px;"));
    scrollArea->setFrameShape(QFrame::StyledPanel);
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents_2 = new QWidget();
    scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
    scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 493, 1010));
    verticalLayout_13 = new QVBoxLayout(scrollAreaWidgetContents_2);
    verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
    textEditLayout = new QHBoxLayout();
    textEditLayout->setSpacing(0);
    textEditLayout->setObjectName(QString::fromUtf8("textEditLayout"));
    frame_3 = new QFrame(scrollAreaWidgetContents_2);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
    frame_3->setSizePolicy(sizePolicy);
    frame_3->setMinimumSize(QSize(35, 0));
    frame_3->setStyleSheet(QString::fromUtf8("margin:0;padding:0;border:0;spacing:0;padding-top:5"));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setLineWidth(0);

    textEditLayout->addWidget(frame_3);

    txtScriptEditor = new KTextEdit(scrollAreaWidgetContents_2);
    txtScriptEditor->setDisabled(true);
    txtScriptEditor->setFontPointSize ( 14 );
    txtScriptEditor->setObjectName(QString::fromUtf8("txtScriptEditor"));
    txtScriptEditor->setMinimumSize(QSize(0, 1000));
    txtScriptEditor->setStyleSheet(QString::fromUtf8("margin-left: 0px;\n"
"margin-right: 0px;\n"
"margin-top: 0px;\n"
"margin-bottom: 0px;\n"
"padding-left: 0px;\n"
"margin-left: 0px;"));
    txtScriptEditor->setFrameShape(QFrame::StyledPanel);
    txtScriptEditor->setLineWidth(1);
    txtScriptEditor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    txtScriptEditor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    txtScriptEditor->setLineWrapMode(QTextEdit::NoWrap);
    txtScriptEditor->setLineWrapColumnOrWidth(100);
    txtScriptEditor->setAcceptRichText(true);

    textEditLayout->addWidget(txtScriptEditor);


    verticalLayout_13->addLayout(textEditLayout);

    scrollArea->setWidget(scrollAreaWidgetContents_2);

    verticalLayout_7->addWidget(scrollArea);

    frame_2 = new QFrame(tabEditor);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setMinimumSize(QSize(0, 26));
    frame_2->setMaximumSize(QSize(16777215, 26));
    frame_2->setStyleSheet(QString::fromUtf8(""));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    frame_2->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0;border:0;border-color:#808000;padding-top:1;spacing:0;");
    frame_2->hide();
    horizontalLayout_5 = new QHBoxLayout(frame_2);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    kpushbutton_6 = new KPushButton(frame_2);
    kpushbutton_6->setObjectName(QString::fromUtf8("kpushbutton_6"));
    kpushbutton_6->setMinimumSize(QSize(22, 22));
    kpushbutton_6->setMaximumSize(QSize(22, 22));
    kpushbutton_6->setStyleSheet(QString::fromUtf8("background-color:  rgb(230, 255, 105);\n"
"border-style: outset;"));
    kpushbutton_6->setIcon(icon);

    horizontalLayout_5->addWidget(kpushbutton_6);

    label_2 = new QLabel(frame_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_5->addWidget(label_2);

    klineedit_4 = new KLineEdit(frame_2);
    klineedit_4->setObjectName(QString::fromUtf8("klineedit_4"));
    klineedit_4->setProperty("showClearButton", QVariant(true));
    klineedit_4->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0;border:1;border-style:solid;border-color:#808000;");

    horizontalLayout_5->addWidget(klineedit_4);

    kpushbutton_7 = new KPushButton(frame_2);
    kpushbutton_7->setObjectName(QString::fromUtf8("kpushbutton_7"));
    kpushbutton_7->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0;border:1;border-style:solid;border-color:#808000;padding-right:5;padding-left:5;");

    horizontalLayout_5->addWidget(kpushbutton_7);


    verticalLayout_7->addWidget(frame_2);

    
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

  
    //ScriptBrowser* dockScriptBrowser;
    //SheduledTask* dockSheduledTask;
    //CommandList* dockCommandList;
    //Man* dockManual;
    //Debug* dockDebug;

    commandStringList = new QStringList();
    dockScriptBrowser = new ScriptBrowser(this); 
    addDockWidget(Qt::LeftDockWidgetArea, dockScriptBrowser);

     dockSheduledTask = new SheduledTask(this); 
    addDockWidget(Qt::LeftDockWidgetArea, dockSheduledTask);



     dockCommandList = new CommandList(this, commandStringList); 
    addDockWidget(Qt::LeftDockWidgetArea, dockCommandList);

     dockManual = new Man(this); 
    addDockWidget(Qt::RightDockWidgetArea, dockManual);

     //dockDebug = new Debug(this); //TODO uncomment when the variable debugger will work, otherwise, this dock is just useless
    //addDockWidget(Qt::LeftDockWidgetArea, dockDebug->dockDebug);



    /*cmdLineCompleter = new QCompleter(*commandStringList, this);
    cmdLineCompleter->setCaseSensitivity(Qt::CaseSensitive);
    tabShell->txtCommand->setCompleter(cmdLineCompleter);*/

    historyStringList = new QStringList();
    dockHistory = new History(0, historyStringList); 
    addDockWidget(Qt::LeftDockWidgetArea, dockHistory);
    tabShell = new Term (dockHistory ,this, commandStringList, historyStringList);


    tabCategories->addTab(tabShell, QString());
    tabCategories->addTab(tabGestion, QString());
    tabCategories->addTab(tabEditor, QString());
    tabCategories->addTab(tabWebBrowser, QString());

    /*QFrame* aCompleter = new QFrame(this);
    //showPopup(aCompleter);
    aCompleter->setGeometry(100, 100, 564, 150);
    aCompleter->show();*/


    lineNBSideBar = new QTableWidget(frame_3);

    firstSBItem = new SideBar(1, NULL,lineNBSideBar );
    lastSBItem = firstSBItem;
    if (lineNBSideBar->columnCount() < 1)
        lineNBSideBar->setColumnCount(1);
    lineNBSideBar->resize ( 35, txtScriptEditor->height() );
    lineNBSideBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNBSideBar->setRowCount(50);
    lineNBSideBar->setRowHeight (0, 20 );
    lineNBSideBar->setColumnWidth(0, 35);
    lineNBSideBar->setCellWidget ( 0, 0, firstSBItem );
    lineNBSideBar->verticalHeader()->hide();
    lineNBSideBar->horizontalHeader()->hide();

    for (int j =1; j < ((txtScriptEditor->height()) /20); j++)
    {
      lineNBSideBar->setRowHeight (j, 20 );
      lastSBItem = new SideBar(2, lastSBItem, lineNBSideBar);
      lineNBSideBar->setCellWidget ( j, 0,lastSBItem);
    }
    

	  btnDbgNextLine->setDisabled(true);
	  btnDbgSkipLine->setDisabled(true);
	  btnDgbNextBP->setDisabled(true);
	  btnStopDebug->setDisabled(true);
          
          
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
    
    //statusBar()->addItem(new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum));
    
    /*QFrame* line_3 = new QFrame(this);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::VLine);
    line_3->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(line_3);*/
    
    statusTask = new QLabel();
    statusBar()->setItemAlignment(2, Qt::AlignRight);
    statusBar()->addWidget(statusTask);
    
    statusProgressBar = new QProgressBar();
    statusProgressBar->setMaximumSize(100,9999);
    statusProgressBar->setMinimumSize(100,0);
    statusBar()->setItemAlignment(3, Qt::AlignRight);
    statusBar()->addWidget(statusProgressBar);

    //QObject::connect(kpushbutton_4, SIGNAL(clicked()), frame, SLOT(hide()));
    QObject::connect(tabCategories, SIGNAL(currentChanged(int)), this, SLOT(modeChanged(int)));
    QObject::connect(kpushbutton_6, SIGNAL(clicked()), frame_2, SLOT(hide()));
    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(btnBack, SIGNAL(clicked()), webDefaultPage, SLOT(back()));
    QObject::connect(btnNext, SIGNAL(clicked()), webDefaultPage, SLOT(forward()));
    QObject::connect(btnReload, SIGNAL(clicked()), webDefaultPage, SLOT(reload()));
    QObject::connect(btnStop, SIGNAL(clicked()), webDefaultPage, SLOT(stop()));
    QObject::connect(cbbUrl, SIGNAL(returnPressed()), this, SLOT(loadWebPage()));
    QObject::connect(btnCopy, SIGNAL(clicked()), txtScriptEditor, SLOT(copy()));
    QObject::connect(btnPaste, SIGNAL(clicked()), txtScriptEditor, SLOT(paste()));
    QObject::connect(btnCut, SIGNAL(clicked()), txtScriptEditor, SLOT(cut()));
    QObject::connect(bntNext, SIGNAL(clicked()), txtScriptEditor, SLOT(redo()));
    QObject::connect(btnPrevious, SIGNAL(clicked()), txtScriptEditor, SLOT(undo()));

    //QObject::connect(kpushbutton_3, SIGNAL(clicked()), this, SLOT(sendCommand()));
    QObject::connect(btnPaste, SIGNAL(clicked()), this, SLOT(seNewLine()));
    //QObject::connect(txtCommand, SIGNAL(returnPressed()), this, SLOT(sendCommand()));
    //QObject::connect(tabShell->klineedit_3, SIGNAL(returnPressed()), this, SLOT(tabShell->searchCmdOutput()));/////////
    QObject::connect(klineedit_4, SIGNAL(returnPressed()), this, SLOT(searchEdit()));
    //QObject::connect(kpushbutton_5, SIGNAL(clicked()), this, SLOT(searchCmdOutput()));
    QObject::connect(kpushbutton_7, SIGNAL(clicked()), this, SLOT(searchEdit()));
    QObject::connect(btnDebug, SIGNAL(clicked()), this, SLOT(startDebugging()));
    QObject::connect(btnStopDebug, SIGNAL(clicked()), this, SLOT(stopDebugging()));
    QObject::connect(btnDbgNextLine, SIGNAL(clicked()), this, SLOT(dbgNextLine()));
    QObject::connect(btnDbgSkipLine, SIGNAL(clicked()), this, SLOT(dbgSkipLine()));
    QObject::connect(btnDgbNextBP, SIGNAL(clicked()), this, SLOT(dbgGoToNextBP()));
    QObject::connect(btnComment, SIGNAL(clicked()), this, SLOT(commentLine()));
    QObject::connect(btnUncomment, SIGNAL(clicked()), this, SLOT(uncommentLine()));
    //QObject::connect(btnUncomment, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
    QObject::connect(dockScriptBrowser, SIGNAL(enableEditor(bool)), txtScriptEditor, SLOT(setEnabled(bool)));
    QObject::connect(dockScriptBrowser, SIGNAL(setFileName(QString)), this, SLOT(setFileName(QString)));
    QObject::connect(dockScriptBrowser, SIGNAL(setEdirorText(QString)), txtScriptEditor, SLOT(setPlainText(QString)));
    QObject::connect(dockScriptBrowser, SIGNAL(launchScript(QString, QString)), this, SLOT(launchScript(QString, QString)));




      retranslateUi();
      setupActions();
      }

/**
  MainWindow destructor
*/
    MainWindow::~MainWindow()
    {
      db->close();



      delete centralwidget;
      /*FR QT s'occupe des delete d'une QMainWindow
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
void MainWindow::retranslateUi()
    {
   
    tabCategories->setTabText(tabCategories->indexOf(tabGestion), QApplication::translate("MainWindow", "Gestion  ", 0, QApplication::UnicodeUTF8));
    //label->setText(QApplication::translate("MainWindow", "Filter:", 0, QApplication::UnicodeUTF8));
    //kpushbutton_5->setText(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabShell), QApplication::translate("MainWindow", "Terminal  ", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "Filter:", 0, QApplication::UnicodeUTF8));
    kpushbutton_7->setText(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabEditor), QApplication::translate("MainWindow", "Creation  ", 0, QApplication::UnicodeUTF8));
    tabBBrowserPage->setTabText(tabBBrowserPage->indexOf(tabDefaultTab), QApplication::translate("MainWindow", "Page", 0, QApplication::UnicodeUTF8));
    tabCategories->setTabText(tabCategories->indexOf(tabWebBrowser), QApplication::translate("MainWindow", "Web Browser   ", 0, QApplication::UnicodeUTF8));



    } // retranslateUi


/**
  Setup action for key shortcut, toolbar items and menu items
*/
    void MainWindow::setupActions()
    {
    
      KAction* newScriptAction = new KAction(this);
      newScriptAction->setText(i18n("New Script"));
      newScriptAction->setIcon(KIcon("document-new"));
      newScriptAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("newScript", newScriptAction);
      connect(newScriptAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));
      
      KAction* importScriptAction = new KAction(this);
      importScriptAction->setText(i18n("Import"));
      importScriptAction->setIcon(KIcon("document-open"));
      importScriptAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("importScript", importScriptAction);
      connect(importScriptAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));
      
      KAction* saveTextAction = new KAction(this);
      saveTextAction->setText(i18n("Save"));
      saveTextAction->setIcon(KIcon("document-save"));
      saveTextAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("saveText", saveTextAction);
      connect(saveTextAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));
      
      KAction* clearAction = new KAction(this);
      clearAction->setText(i18n("Clear"));
      clearAction->setIcon(KIcon("document-new"));
      clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("clear", clearAction);
      connect(clearAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));

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
      txtScriptEditor, SLOT(clear()));

      KAction* pauseAction = new KAction(this);
      pauseAction->setText(i18n("Plause"));
      pauseAction->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/pause.png")));
      pauseAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("pause", pauseAction);
      connect(pauseAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));

      KAction* stopAction = new KAction(this);
      stopAction->setText(i18n("Stop"));
      stopAction->setIcon(KIcon("dialog-close"));
      stopAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("stop", stopAction);
      connect(stopAction, SIGNAL(triggered(bool)),
      txtScriptEditor, SLOT(clear()));

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
      
      /*KAction* newScriptAction = new KAction(this);
      newScriptAction->setText(i18n("New Script"));
      newScriptAction->setIcon(KIcon("list-add"));
      newScriptAction->setShortcut(Qt::CTRL + Qt::Key_W);
      actionCollection()->addAction("newScript", newScriptAction);
      connect(newScriptAction, SIGNAL(triggered(bool)),
      this, SLOT(showLog()));*/
      
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


 /*void MainWindow::newFile()//PASDEMOI
      {
	fileName.clear();
	txtScriptEditor->clear();
      }*/

      void MainWindow::saveFileAs(const QString &outputFileName)//PASDEMOI
      {
	KSaveFile file(outputFileName);
	file.open();
  
	QByteArray outputByteArray;
	outputByteArray.append(txtScriptEditor->toPlainText());
	file.write(outputByteArray);
	file.finalize();
	file.close();
  
	fileName = outputFileName;
      }

/**
  Default KDE file saving funtion
*/
      void MainWindow::saveFileAs()//PASDEMOI
      {
	saveFileAs(KFileDialog::getSaveFileName());
      }

/**
  Default KDE file saving funtion
*/
      void MainWindow::saveFile()//PASDEMOI
      {
	if(!fileName.isEmpty())
	{
	  saveFileAs(fileName);
	}
	else
	{
	  saveFileAs();
	}
      }

/**
  Default KDE file opening funtion
*/
      void MainWindow::openFile() //PASDEMOI
      {
	openFile(KFileDialog::getOpenFileName());
      }

/**
  Default KDE file opening funtion
*/
      void MainWindow::openFile(const QString &inputFileName)//PASDEMOI
      {
	QString tmpFile;
	if(KIO::NetAccess::download(inputFileName, tmpFile,
	this))
	{
	  QFile file(tmpFile);
	  file.open(QIODevice::ReadOnly);
	  txtScriptEditor->setPlainText(QTextStream(&file).readAll());
	  fileName = inputFileName;
    
	  KIO::NetAccess::removeTempFile(tmpFile);
	}
	else
	{
	  KMessageBox::error(this,
	  KIO::NetAccess::lastErrorString());
	}
      }

/**
  send the txtCommand text to the terminal emulator
*/
//     void MainWindow::sendCommand()
//     {
//       if (txtCommand->text() != "")
//       {
// 	pxmCmdInactive->load("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearA.png");
// 	cmdStatus->setPixmap(*pxmCmdInactive);
// 	txtCommand->setDisabled(true);
// 	//Shell aShell(this);
// 	ShellThread* aThread = new ShellThread(txtCommand->text());
// 	QObject::connect(aThread->aShell, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
// 	QObject::connect(aThread->aShell, SIGNAL(newLine(QString)), this, SLOT(updateCmdOutput(QString)));
// 	QObject::connect(aThread->aShell, SIGNAL(clearCmdOutput()), this, SLOT(clearCmdOutput()));
// 	dockHistory->addItem(txtCommand->text());
// 	QSqlQuery query;
// 	query.exec("insert into THISTORY (COMMAND, TIME) values ('"+ txtCommand->text() +"', 2)"); //TODO add corect time
// 	//aShell.analyseCommand((txtCommand->text().toStdString()));
// 	//ThreadExec aThread(this);
// 	//QObject::disconnect(aThread->aShell, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
// 	aThread->start();
//       }
//     }
// 
// /**
//   add a new line to the script editor
//   @todo make it work again
// */
//     void MainWindow::seNewLine()
//     {
//       /*sbLineNB++;
//       lineNBSideBar->setRowCount(sbLineNB);
//       lastSBItem = new SideBar(2, lastSBItem, lineNBSideBar);
//       lineNBSideBar->setCellWidget( sbLineNB ,0,lastSBItem;
//       //verticalLayout_29->addItem(verticalSpacer_12);*/
//     }
// 
// /**
//   the command line tab search box function
// */
//    void MainWindow::searchCmdOutput()
//     {
//       if (klineedit_3->text() != "")
//       {
// 	    rtfCmdOutput->find(klineedit_3->text());
//       }
//     }

/**
  the editor tab search box function
*/
   void MainWindow::searchEdit()
    {	    std::cout << klineedit_4->text().toStdString();
      if (klineedit_4->text() != "")
      {

	    txtScriptEditor->find(klineedit_4->text());
      }
    }

/**
  called when you do a CTRL+F, show the right search box
*/
    void MainWindow::find()
    {
      if (tabCategories->currentIndex () == 0)
      {
	    tabShell->frame->show(); //TODO uncomment
	    tabShell->klineedit_3->setFocus();
	    tabShell->klineedit_3->selectAll();
      }
      else
      {
	    frame_2->show();
	    klineedit_4->setFocus();
	    klineedit_4->selectAll();
      }
    }

/**
  Launch a debugging session
*/
    void MainWindow::startDebugging()
    {
      isDebugging = true;
      txtScriptEditor->setReadOnly(true);
	  btnDbgNextLine->setDisabled(false);
	  btnDbgSkipLine->setDisabled(false);
	  btnDgbNextBP->setDisabled(false);
	  btnStopDebug->setDisabled(false);
	  btnDebug->setDisabled(true);
	  btnPaste->setDisabled(true);
	  btnCopy->setDisabled(true);
	  btnCut->setDisabled(true);
	  btnComment->setDisabled(true);
	  btnUncomment->setDisabled(true);

      int i =0;

      string script = txtScriptEditor->toPlainText().toStdString();
      script = script + "\n";

      for (int j = 0; j <= script.size(); j++) //Count the script line
      {
	    if ((script[j] == 0x0A) && (script[j+1] != 0x0A)) i++;
      } 

      cout << i << endl;
      commandArray = new string[i];

      int j =0;
      int k =0;
      
      while (script != "")
      {
	    if ((script[j] == 0x0A) || (j == (script.size()-1)))
	    {
	      char* command = new char[j];
	      commandArray[k] = script.substr(0,j);
	      script = script.substr((j+1), (script.size() - j -1));
	      j = 0;
	      k++;
	      while (script[0] == 0x0A)
	      {
		    script = script.substr(1, (script.size() -1));
	      }
	}
	else
	{
	  j++;
	}
      }
      
      sbCurrentLine = firstSBItem;
      currentLine = 0;
      lineNumber = i;
      cout << "Debbug state: " << sbCurrentLine->debugState << endl;
      while ((currentLine < lineNumber) && (sbCurrentLine->debugState == false))
      {
	    cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
	    if (sbCurrentLine->previousSBItem != NULL) sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
	    sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
	    system(commandArray[currentLine].c_str());
	    sbCurrentLine = sbCurrentLine->nextSBItem;
	    currentLine++;
      }
      if (currentLine == i)
      {
	    isDebugging = false;
	    txtScriptEditor->setReadOnly(false);
	    btnDbgNextLine->setDisabled(true);
	    btnDbgSkipLine->setDisabled(true);
	    btnDgbNextBP->setDisabled(true);
	    btnStopDebug->setDisabled(true);
	    btnDebug->setDisabled(false);
	    btnPaste->setDisabled(false);
	    btnCopy->setDisabled(false);
	    btnCut->setDisabled(false);
	    btnComment->setDisabled(false);
	    btnUncomment->setDisabled(false);
      }
    }

/**
  End the debugging session manually
*/
    void MainWindow::stopDebugging()
    {
      isDebugging = false;
      txtScriptEditor->setReadOnly(false);
	  btnDbgNextLine->setDisabled(true);
	  btnDbgSkipLine->setDisabled(true);
	  btnDgbNextBP->setDisabled(true);
	  btnStopDebug->setDisabled(true);
	  btnDebug->setDisabled(false);
	  btnPaste->setDisabled(false);
	  btnCopy->setDisabled(false);
	  btnCut->setDisabled(false);
	  btnComment->setDisabled(false);
	  btnUncomment->setDisabled(false);
    }


/**
  Function called when you press on the btnNextLine button. Execute the next line.
*/
    void MainWindow::dbgNextLine()
    {
      if (currentLine != (lineNumber +1 ))
      {
	  	cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
	    if (sbCurrentLine->previousSBItem != NULL)
	    {
	      if (sbCurrentLine->previousSBItem->debugState == true) 
		  {
		    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
		  }
		  else
		  {
		    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
		  }
	    }

	    
	    if (sbCurrentLine->debugState == true) 
		{
		  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
		}
		else
		{
		  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
		}


	    system(commandArray[currentLine].c_str());
	    sbCurrentLine = sbCurrentLine->nextSBItem;
	    currentLine++;
      }
      else
      {
	    isDebugging = false;
	    txtScriptEditor->setReadOnly(false);
	    btnDbgNextLine->setDisabled(true);
	    btnDbgSkipLine->setDisabled(true);
	    btnDgbNextBP->setDisabled(true);
	    btnStopDebug->setDisabled(true);
	    btnDebug->setDisabled(false);
	    btnPaste->setDisabled(false);
	    btnCopy->setDisabled(false);
	    btnCut->setDisabled(false);
	    btnComment->setDisabled(false);
	    btnUncomment->setDisabled(false);
      }
    }

/**
  Function called when you press on the btnSkipLine button. Execute the line after the next one.
*/
    void MainWindow::dbgSkipLine()
    {
      sbCurrentLine = sbCurrentLine->nextSBItem;
	  currentLine++;
      if (currentLine != (lineNumber +1 ))
      {
	  	cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
	    if (sbCurrentLine->previousSBItem != NULL)
	    {
	      if (sbCurrentLine->previousSBItem->debugState == true) 
		  {
		    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
		  }
		  else
		  {
		    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
		  }
	    }

	    if (sbCurrentLine->previousSBItem->previousSBItem != NULL)
	    {
	      if (sbCurrentLine->previousSBItem->previousSBItem->debugState == true) 
		  {
		    sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
		  }
		  else
		  {
		    sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
		  }
	    }

	    
	    if (sbCurrentLine->debugState == true) 
		{
		  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
		}
		else
		{
		  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
		}


	    system(commandArray[currentLine].c_str());
	    sbCurrentLine = sbCurrentLine->nextSBItem;
	    currentLine++;
      }
      else
      {
	    isDebugging = false;
	    txtScriptEditor->setReadOnly(false);
	    btnDbgNextLine->setDisabled(true);
	    btnDbgSkipLine->setDisabled(true);
	    btnDgbNextBP->setDisabled(true);
	    btnStopDebug->setDisabled(true);
	    btnDebug->setDisabled(false);
	    btnPaste->setDisabled(false);
	    btnCopy->setDisabled(false);
	    btnCut->setDisabled(false);
	    btnComment->setDisabled(false);
	    btnUncomment->setDisabled(false);
      }
    }

/**
  Function called when you press on the btnToNextBP button. Execute all command until it find an other breakpoint
*/
    void MainWindow::dbgGoToNextBP()
    {
	  cout << "je suis vivant" << endl;
	  while ((currentLine < lineNumber) && (sbCurrentLine->debugState == false))
      {
	    cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
	    if (sbCurrentLine->previousSBItem != NULL) sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
	    sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
	    system(commandArray[currentLine].c_str());
	    sbCurrentLine = sbCurrentLine->nextSBItem;
	    currentLine++;
      }
      if (currentLine == lineNumber)
      {
	    isDebugging = false;
	    txtScriptEditor->setReadOnly(false);
	    btnDbgNextLine->setDisabled(true);
	    btnDbgSkipLine->setDisabled(true);
	    btnDgbNextBP->setDisabled(true);
	    btnStopDebug->setDisabled(true);
	    btnDebug->setDisabled(false);
	    btnPaste->setDisabled(false);
	    btnCopy->setDisabled(false);
	    btnCut->setDisabled(false);
	    btnComment->setDisabled(false);
	    btnUncomment->setDisabled(false);
      }
    }


/**
  Function called when you press on the btnComment button. Add a # at position 0 of the line
*/
    void MainWindow::commentLine()
    {
      if (txtScriptEditor->textCursor().hasSelection())
      {
	    string aScript = txtScriptEditor->toPlainText().toStdString().substr(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
	    string commentedScript;
	    while (aScript.find("\n") != -1)
	    {
	      commentedScript += "#" + aScript.substr(0, aScript.find("\n"))+ "\n";
	      aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n") -1));
	    cout << commentedScript << endl;
	    }
	    commentedScript += "#" + aScript;
	    
	    cout << commentedScript << endl;
	    txtScriptEditor->textCursor().removeSelectedText();
	    txtScriptEditor->textCursor().insertText(commentedScript.c_str());
      }
      else
      {
	    txtScriptEditor->insertPlainText("#");
      }
      txtScriptEditor->setFontPointSize ( 14 );
    }

/**
  Function called when you press on the btnUncomment button. Remove a # at position 0 of the line
*/
    void MainWindow::uncommentLine()
    {
      if (txtScriptEditor->textCursor().hasSelection())
      {
	    string aScript = txtScriptEditor->toPlainText().toStdString().substr(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
	    string commentedScript;
	    while (aScript.find("\n") != -1)
	    {
	      if (aScript[aScript.find("\n")+1] == '#')
	      {
		commentedScript += aScript.substr(1, aScript.find("\n"));
		aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n") -1));
		cout << commentedScript << endl;
	      }
	      else
	      {
		commentedScript += aScript.substr(0, aScript.find("\n")+1);
		aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n")-1));
		cout << commentedScript << endl;
	      }
	    }

	    if (aScript[0] == '#') commentedScript += aScript.substr(1, (aScript.size() -1));
	    else commentedScript += aScript.substr(0, (aScript.size()));
	    
	    txtScriptEditor->textCursor().removeSelectedText();
	    txtScriptEditor->textCursor().insertText(commentedScript.c_str());
      }
      /*else //TODO make it work again
      {
	    //txtScriptEditor->insertPlainText("#");
      }*/
      txtScriptEditor->setFontPointSize ( 14 );
    }

void MainWindow::loadWebPage()
{
  webDefaultPage->setUrl(QUrl(cbbUrl->currentText()));
}

void MainWindow::showLog() {
  LogView *dialog = new LogView( this );
  
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
    
    viewManPage->setChecked(klingConfigSkeleton->showManPageTerminal);
    viewHistory->setChecked(klingConfigSkeleton->showHistoryTerminal);
    viewCommandList->setChecked(klingConfigSkeleton->showCommandListTerminal);
    viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskTerminal);
    viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserTerminal);
  }
  else if (index == MONITOR_MODE) {
    dockHistory->setVisible(klingConfigSkeleton->showHistoryMonitor);
    dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserMonitor);
    dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskMonitor);
    dockCommandList->setVisible(klingConfigSkeleton->showCommandListMonitor);
    dockManual->setVisible(klingConfigSkeleton->showManPageMonitor);
        
    viewManPage->setChecked(klingConfigSkeleton->showManPageMonitor);
    viewHistory->setChecked(klingConfigSkeleton->showHistoryMonitor);
    viewCommandList->setChecked(klingConfigSkeleton->showCommandListMonitor);
    viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskMonitor);
    viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserMonitor);
  }
  else if (index == EDITOR_MODE) {
    dockHistory->setVisible(klingConfigSkeleton->showHistoryEditor);
    dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserEditor);
    dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskEditor);
    dockCommandList->setVisible(klingConfigSkeleton->showCommandListEditor);
    dockManual->setVisible(klingConfigSkeleton->showManPageEditor);
        
    viewManPage->setChecked(klingConfigSkeleton->showManPageEditor);
    viewHistory->setChecked(klingConfigSkeleton->showHistoryEditor);
    viewCommandList->setChecked(klingConfigSkeleton->showCommandListEditor);
    viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskEditor);
    viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserEditor);
  }
  else if (index == WEB_BROWSER_MODE) {
    dockHistory->setVisible(klingConfigSkeleton->showHistoryrWebBrowser); //TODO typo
    dockScriptBrowser->setVisible(klingConfigSkeleton->showScriptBrowserWebBrowser);
    dockSheduledTask->setVisible(klingConfigSkeleton->showScheduledTaskrWebBrowser);
    dockCommandList->setVisible(klingConfigSkeleton->showCommandListrWebBrowser);
    dockManual->setVisible(klingConfigSkeleton->showManPagerWebBrowser);
        
    viewManPage->setChecked(klingConfigSkeleton->showManPagerWebBrowser);
    viewHistory->setChecked(klingConfigSkeleton->showHistoryrWebBrowser);
    viewCommandList->setChecked(klingConfigSkeleton->showCommandListrWebBrowser);
    viewScheduledTask->setChecked(klingConfigSkeleton->showScheduledTaskrWebBrowser);
    viewScriptBrowser->setChecked(klingConfigSkeleton->showScriptBrowserWebBrowser);
  }
 
 }

void MainWindow::setFileName(QString name) {
  fileName = name;
}

void MainWindow::launchScript(QString name, QString content) {
  ScriptMonitor* aNewExecutionMonitor = new ScriptMonitor(tabGestion, name );
  horizontalLayout_4->addWidget( aNewExecutionMonitor);
  aNewExecutionMonitor->launchScript(content.toStdString());
}


void MainWindow::setViewScriptBrowser(bool value) {  
  dockScriptBrowser->setVisible(value);
    if (tabCategories->currentIndex() == TERMINAL_MODE) {
    klingConfigSkeleton->showManPageTerminal;
    klingConfigSkeleton->showHistoryTerminal;
    klingConfigSkeleton->showCommandListTerminal;
    klingConfigSkeleton->showScheduledTaskTerminal;
    klingConfigSkeleton->showScriptBrowserTerminal;
    }
    else if (tabCategories->currentIndex() == MONITOR_MODE) {
      
    }
    else if (tabCategories->currentIndex() == EDITOR_MODE) {
      
    }
    else if (tabCategories->currentIndex() == WEB_BROWSER_MODE) {
      
    }
}

void MainWindow::setViewScheduledTask(bool value) {
  dockSheduledTask->setVisible(value);
}

void MainWindow::setViewCommandList(bool value) {
  dockCommandList->setVisible(value);
}

void MainWindow::setViewHistory(bool value) {
  dockHistory->setVisible(value);
}

void MainWindow::setViewManPage(bool value) {
  dockManual->setVisible(value);
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