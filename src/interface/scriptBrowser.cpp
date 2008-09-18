/**     @file scripBrowser.cpp

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

        scriptBrowser dock GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "scriptBrowser.h"
#include "../../mainwindow.h"

#include <iostream>

#include "addScript.h"
#include "scriptMonitor.h"
#include "../Shell.h"
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QString>
#include <QtGui/QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "kpushbutton.h"
#include <KApplication>
#include <KIO/NetAccess>
#include <KMessageBox>


/**
  ScriptBrowser constructor

  @param[in] parent The parent window
*/
ScriptBrowser::ScriptBrowser(MainWindow* parent)
{
  
//**************************************************************
//                    dockScriptBrowser
//**************************************************************

    mainwindow = parent;
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed); //
    sizePolicy1.setHorizontalStretch(31); //
    sizePolicy1.setVerticalStretch(31); //
    dockScriptBrowser = new QDockWidget();
    dockScriptBrowser->setGeometry(QRect(0, 24, 200, 151));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(dockScriptBrowser->sizePolicy().hasHeightForWidth());
    dockScriptBrowser->setSizePolicy(sizePolicy3);
    dockScriptBrowser->setMinimumSize(QSize(200, 75));
    dockScriptBrowser->setAcceptDrops(true);
    dockScriptBrowser->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dockScriptBrowserContents = new QWidget(dockScriptBrowser);
    dockScriptBrowserContents->setObjectName(QString::fromUtf8("dockScriptBrowserContents"));
    dockScriptBrowserContents->setGeometry(QRect(2, 22, 196, 127));
    verticalLayout_9 = new QVBoxLayout(dockScriptBrowserContents);
    verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
    verticalLayout_9->setContentsMargins(0, 0, 0, 0);
    tvScriptList = new QTreeWidget(dockScriptBrowserContents);
    fillTree();
    tvScriptList->setObjectName(QString::fromUtf8("tvScriptList"));
    tvScriptList->setDragEnabled(true);
    tvScriptList->setDragDropMode(QAbstractItemView::DragOnly);
    tvScriptList->setAnimated(true);
    tvScriptList->setWordWrap(true);
    tvScriptList->setHeaderHidden(true);

    verticalLayout_9->addWidget(tvScriptList);

    hlScriptControls = new QHBoxLayout();
    hlScriptControls->setObjectName(QString::fromUtf8("hlScriptControls"));
    btnNewScript = new KPushButton(dockScriptBrowserContents);
    btnNewScript->setObjectName(QString::fromUtf8("btnNewScript"));
    sizePolicy1.setHeightForWidth(btnNewScript->sizePolicy().hasHeightForWidth());
    btnNewScript->setSizePolicy(sizePolicy1);
    btnNewScript->setMinimumSize(QSize(31, 31));
    btnNewScript->setMaximumSize(QSize(31, 31));
    KIcon icnNewScript("list-add");
    btnNewScript->setIcon(icnNewScript);

    hlScriptControls->addWidget(btnNewScript);

    btnDeleteScipt = new KPushButton(dockScriptBrowserContents);
    btnDeleteScipt->setObjectName(QString::fromUtf8("btnDeleteScipt"));
    sizePolicy1.setHeightForWidth(btnDeleteScipt->sizePolicy().hasHeightForWidth());
    btnDeleteScipt->setSizePolicy(sizePolicy1);
    btnDeleteScipt->setMinimumSize(QSize(31, 31));
    btnDeleteScipt->setMaximumSize(QSize(31, 31));
    KIcon icnRemScript("list-remove");
    btnDeleteScipt->setIcon(icnRemScript);

    hlScriptControls->addWidget(btnDeleteScipt);

    btnEdit = new KPushButton(dockScriptBrowserContents);
    btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
    btnEdit->setMinimumSize(QSize(55, 31));
    btnEdit->setMaximumSize(QSize(55, 31));
    btnEdit->setText("Edit");

    hlScriptControls->addWidget(btnEdit);

    btnLaunch  = new KPushButton(dockScriptBrowserContents);
    btnLaunch->setObjectName(QString::fromUtf8("btLaunch"));
    btnLaunch->setMinimumSize(QSize(55, 31));
    btnLaunch->setMaximumSize(QSize(55, 31));
    btnLaunch->setText("Launch");

    hlScriptControls->addWidget(btnLaunch);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hlScriptControls->addItem(horizontalSpacer_2);


    verticalLayout_9->addLayout(hlScriptControls);

    dockScriptBrowser->setWidget(dockScriptBrowserContents);

    QObject::connect(btnNewScript, SIGNAL(clicked()), this, SLOT(addNewScript()));
    QObject::connect(btnEdit, SIGNAL(clicked()), this, SLOT(editSelectedScript()));
    QObject::connect(btnLaunch, SIGNAL(clicked()), this, SLOT(launchSelectedScript()));
    
    translateUi();
}


/**
  User interface string
*/
void ScriptBrowser::translateUi()
{
    dockScriptBrowser->setWindowTitle(QApplication::translate("MainWindow", "Script browser", 0, QApplication::UnicodeUTF8));
    tvScriptList->headerItem()->setText(0, QApplication::translate("MainWindow", "Name", 0, QApplication::UnicodeUTF8));
    const bool __sortingEnabled = tvScriptList->isSortingEnabled();
    tvScriptList->setSortingEnabled(false);

    tvScriptList->setSortingEnabled(__sortingEnabled);
}

/**
  ScriptBrowser destructor
*/
ScriptBrowser::~ScriptBrowser()
{
  delete horizontalSpacer_2;
  delete btnLaunch;
  delete btnEdit;
  delete btnDeleteScipt;
  delete btnNewScript;
  delete hlScriptControls;
  delete tvScriptList;
  delete verticalLayout_9;
  delete dockScriptBrowserContents;
  delete dockScriptBrowser;
}

/**
  Launch the newScript dialog
*/
void ScriptBrowser::addNewScript()
{
  AddScript* aNewScript = new AddScript(this);
  aNewScript->exec();
  tvScriptList->clear();
  fillTree();
}


/**
  Read the DB and load all script into their categorie
*/
void ScriptBrowser::fillTree()
{
  QSqlQuery query;
  query.exec("SELECT NAME FROM TCATEGORIES");
  int j =0;
  int k=0;
    while (query.next()) 
    {
      QTreeWidgetItem* aTVItem = new QTreeWidgetItem(tvScriptList);
      tvScriptList->topLevelItem(j)->setText(0,query.value(0).toString());

      QSqlQuery query2;
      query2.exec("SELECT NAME FROM TSCRIPT WHERE CATEGORIE = '"+ query.value(0).toString() +"'");
      while (query2.next()) 
      {
	new QTreeWidgetItem(aTVItem);
	std::cout << query2.value(0).toString().toStdString() << std::endl << std::endl;
	
	tvScriptList->topLevelItem(j)->child(k)->setText(0,query2.value(0).toString());
	k++;
      }
      k = 0;
      j++;
    }
}


/**
  Load the script in the script editor
  @todo if a script is already loaded, check if it is edited and alert the user 
*/
void ScriptBrowser::editSelectedScript()
{
  std::string tmpPath =Shell::getResult("echo $HOME/.kling/script/");
  tmpPath = tmpPath.substr(0, tmpPath.size() -1);
  QString inputFileName = QString::fromStdString(tmpPath) + tvScriptList->currentItem()->text(0) + ".sh";
  QString tmpFile;
  if(KIO::NetAccess::download(inputFileName, tmpFile,
  this))
  {
    QFile file(tmpFile);
    file.open(QIODevice::ReadOnly);
    mainwindow->txtScriptEditor->setPlainText(QTextStream(&file).readAll());
    mainwindow->txtScriptEditor->setDisabled(false);
    mainwindow->fileName = inputFileName;

    KIO::NetAccess::removeTempFile(tmpFile);
  }
  else
  {
    KMessageBox::error(this,
    KIO::NetAccess::lastErrorString());
  }
}

/**
  Lauch the script
  @todo use a thread
*/
void ScriptBrowser::launchSelectedScript()
{
  if(tvScriptList->currentItem ())
  {
    std::string tmpPath =Shell::getResult("echo $HOME/.kling/script/");
    tmpPath = tmpPath.substr(0, tmpPath.size() -1);
    QString inputFileName = QString::fromStdString(tmpPath) + tvScriptList->currentItem()->text(0) + ".sh";
    QString tmpFile;
    if(KIO::NetAccess::download(inputFileName, tmpFile, this))
    {
      ScriptMonitor* aNewExecutionMonitor = new ScriptMonitor(mainwindow->tabGestion,"echo salut1\nsleep 2 \n echo salut2", tvScriptList->currentItem()->text(0).toStdString() );
      mainwindow->horizontalLayout_4->addWidget( aNewExecutionMonitor);
      QFile file(tmpFile);
      file.open(QIODevice::ReadOnly);
      QString script = (QTextStream(&file).readAll());
      aNewExecutionMonitor->launchScript(script.toStdString());
  
      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else
    {
      KMessageBox::error(this,
      KIO::NetAccess::lastErrorString());
    }

  }
}