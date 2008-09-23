/**     @file mainwindow.h

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
	_____________________

        Header file of the main main window. Contain pointer to all widget use by the application.

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

      #ifndef MAINWINDOW_H
      #define MAINWINDOW_H

      #define TERMINAL_MODE  0
      #define MONITOR_MODE  1
      #define EDITOR_MODE 2
      #define WEB_BROWSER_MODE  3

      #include <iostream>
      #include <QtCore/QVariant>
      #include <QtGui/QAction>
      #include <QtGui/QApplication>
      #include <QtGui/QButtonGroup>
      #include <QtGui/QFrame>
      #include <QtGui/QGraphicsView>
      #include <QtGui/QHBoxLayout>
      #include <QtGui/QLabel>
      #include <QtGui/QScrollArea>
      #include <QtGui/QSpacerItem>
      #include <QtGui/QTabWidget>
      #include <QtGui/QTableView>
      #include <QtGui/QTableWidget>
      #include <QtGui/QTextBrowser>
      #include <QtGui/QTextEdit>
      #include <QtGui/QVBoxLayout>
      #include <QtGui/QWidget>
      #include <QtWebKit/QWebView> 
      #include <QProgressBar>
      #include "kcombobox.h"
      #include "klineedit.h"
      #include "kpushbutton.h"
      #include "ktabwidget.h"
      #include "ktextedit.h"
      #include <kicon.h>
      #include <KXmlGuiWindow>
      #include <QSqlDatabase>
      #include <QStringList>
      #include <QCompleter>
      #include <KAction>
      #include "src/interface/history.h"
      #include "src/interface/scriptBrowser.h"
      #include "src/interface/sheduledTask.h"
      #include "src/interface/commandList.h"
      #include "src/interface/man.h"
      #include "src/interface/sideBar.h"
      #include "src/interface/term.h"
      #include "src/configSkeleton.h"

      class MainWindow : public KXmlGuiWindow
      {
      Q_OBJECT

      public:
      void retranslateUi();
      void setupActions();
      MainWindow(QWidget *parent=0);
      ~MainWindow();
      QWidget *centralwidget;
      QVBoxLayout *verticalLayout_11;//
      QTabWidget *tabCategories;//
      QWidget *tabGestion;//
      QVBoxLayout *horizontalLayout_4;
      Term *tabShell;//
      //TABSHELL WIDGER WERE HERE
      QWidget *tabEditor;//
      QVBoxLayout *verticalLayout_7;
      QHBoxLayout *hlControl2;
      KPushButton *btnPrevious;
      KPushButton *bntNext;
      QFrame *line;
      KPushButton *btnSave;
      KPushButton *btnPrint;
      QFrame *line_2;
      KPushButton *btnComment;
      KPushButton *btnUncomment;
      KPushButton *btnCopy;
      KPushButton *btnCut;
      KPushButton *btnPaste;
      QFrame *line_3;
      KPushButton *btnDebug;
      KPushButton *btnStopDebug;
      KPushButton *btnDbgNextLine;
      KPushButton *btnDbgSkipLine;
      KPushButton *btnDgbNextBP;
      QSpacerItem *horizontalSpacer;
      QScrollArea *scrollArea;
      QWidget *scrollAreaWidgetContents_2;
      QVBoxLayout *verticalLayout_13;
      QHBoxLayout *textEditLayout;
      QFrame *frame_3;
      QSpacerItem *verticalSpacer_12;
      QVBoxLayout *verticalLayout_29;
      KTextEdit *txtScriptEditor;
      QFrame *frame_2;
      QHBoxLayout *horizontalLayout_5;
      KPushButton *kpushbutton_6;
      QLabel *label_2;
      KLineEdit *klineedit_4;
      KPushButton *kpushbutton_7;
      QWidget *tabWebBrowser;
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
      QStringList* commandStringList;
      QStringList* historyStringList;
      QProgressBar* statusProgressBar;
      QLabel* statusJobRunning;
      QLabel* statusCurrentDir;
      QLabel* statusTask;
      QCompleter *cmdLineCompleter;
      QWebView *webDefaultPage; 
      QSqlDatabase* db;
      QTableWidget* lineNBSideBar;
      KlingConfigSkeleton* klingConfigSkeleton;
      History* dockHistory;
      ScriptBrowser* dockScriptBrowser;
      SheduledTask* dockSheduledTask;
      CommandList* dockCommandList;
      Man* dockManual;
      
      KAction* viewManPage;
      KAction* viewHistory;
      KAction* viewCommandList;
      KAction* viewScheduledTask;
      KAction* viewScriptBrowser;


      
      QString fileName;
      void openFile(const QString &inputFileName);

      private:
	    std::string* commandArray;
	    bool isDebugging;
	    int currentLine;
	    int lineNumber;
	    int sbLineNB2;
	    SideBar* firstSBItem;
	    SideBar* lastSBItem;
	    SideBar* sbCurrentLine;

      private slots:
	    //void newFile();
	    void loadWebPage();
	    void openFile();
	    void saveFile();
	    void saveFileAs();
	    void find();
	    void saveFileAs(const QString &outputFileName);
	    //void sendCommand();
	    //void seNewLine();
	    //void searchCmdOutput();
	    void searchEdit();
	    void startDebugging();
	    void stopDebugging();
	    void dbgNextLine();
	    void dbgSkipLine();
	    void dbgGoToNextBP();
	    void commentLine();
	    void uncommentLine();
// 	    void updateCmdOutput(QString line);
// 	    void resetCmdInputLine();
// 	    void clearCmdOutput();
            void showLog();
            void showSettings();
            void modeChanged(int index);
            void setFileName(QString name);
            void launchScript(QString name, QString content);
            void newCronJob();
            void parseAllManPage();
            void cleanStatusBarTask();
            
            void setViewScriptBrowser(bool value);
            void setViewScheduledTask(bool value);
            void setViewCommandList(bool value);
            void setViewHistory(bool value);
            void setViewManPage(bool value);
            
      };

      #endif
