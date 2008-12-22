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
#include "src/interface/debug.h"
#include "src/interface/termSession.h"
#include "src/interface/scriptEditor.h"
#include "src/interface/executionMonitor.h"
#include "src/interface/advancedScriptManager.h"
#include "src/interface/webBrowser.h"
#include "src/configSkeleton.h"


  class MainWindow : public KXmlGuiWindow {
    Q_OBJECT

    public:
      void retranslateUi();
      void setupActions();
      MainWindow(QWidget *parent=0, KlingConfigSkeleton* configuration = 0);
      ~MainWindow();
      QTabWidget *tabCategories;//
      ExecutionMonitor *tabGestion;
      TermSession *tabShell;
      ScriptEditor* tabEditor;
      WebBrowser* tabWebBrowser;
      AdvancedScriptManager* tabAdvScripManager;
      QStringList* commandStringList;
      QStringList* aliasList;
      QStringList* defaultArgsList;
      QStringList* functionList;
      QStringList* historyStringList;
      QProgressBar* statusProgressBar;
      QLabel* statusJobRunning;
      QLabel* statusCurrentDir;
      QLabel* statusTask;
      QCompleter *cmdLineCompleter;
      QSqlDatabase* db;
      KlingConfigSkeleton* klingConfigSkeleton;
      History* dockHistory;
      Debug* dockDebug;
      ScriptBrowser* dockScriptBrowser;
      SheduledTask* dockSheduledTask;
      CommandList* dockCommandList;
      Man* dockManual;
      
      KAction* viewManPage;
      KAction* viewHistory;
      KAction* viewCommandList;
      KAction* viewScheduledTask;
      KAction* viewScriptBrowser;
      KAction* viewDebug;
      KAction* actionUndo;
      KAction* actionRedo;
      KAction* actionCut;
      KAction* actionCopy;
      KAction* actionPaste;
      KAction* actionSelectAll;
      
    private:
      void saveDockState();
      char currentMode;


    private slots:
      void find();
      void save();
      void print();
      void exportLog();
      void backup();
      void cut();
      void copy();
      void paste();
      void undo();
      void redo();
      void selectAll();
      void searchEdit();
      void showLog();
      void showSettings();
      void showAdvancedScriptManager();
      void modeChanged(int index);
      void newCronJob();
      void parseAllManPage();
      void cleanStatusBarTask();
      
      void setViewScriptBrowser(bool value);
      void setViewScheduledTask(bool value);
      void setViewCommandList(bool value);
      void setViewHistory(bool value);
      void setViewManPage(bool value);
      void setViewDebug(bool value);
      void setEditorMode();
      void setMonitorMode();
      
      void newTerminal(); 
      void newGestion(); 
      void newEditor(); 
      void newWebBrowser();
      void newMonitor();
  };
#endif
