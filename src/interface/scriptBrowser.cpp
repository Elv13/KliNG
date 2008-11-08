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

#include "addScript.h"
#include "scriptMonitor.h"
#include "../virtTTY.h"
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QTreeWidgetItem>
#include <QString>
#include <QtGui/QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "kpushbutton.h"
#include <KApplication>
#include <KIO/NetAccess>
#include <KMessageBox>
#include <KStandardDirs>
#include <KLocalizedString>


/**
  ScriptBrowser constructor

  @param[in] parent The parent window
*/
  ScriptBrowser::ScriptBrowser(QWidget* parent) : QDockWidget ( 0 ) {
    setObjectName("ScriptBrowser");
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed); //
    sizePolicy1.setHorizontalStretch(31); //
    sizePolicy1.setVerticalStretch(31); //
    //setGeometry(QRect(0, 24, 200, 151));
    /*QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy3);*/
    setMinimumSize(QSize(200, 75));
    setAcceptDrops(true);
    setFeatures(QDockWidget::AllDockWidgetFeatures);
    dockScriptBrowserContents = new QWidget(this);
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
    //btnEdit->setMinimumSize(QSize(55, 31));
    //btnEdit->setMaximumSize(QSize(55, 31));
    //btnEdit->setText("Edit");
    btnEdit->setIcon(KIcon("draw-freehand"));
    btnEdit->setToolTip("Edit");
    hlScriptControls->addWidget(btnEdit);

    btnLaunch  = new KPushButton(dockScriptBrowserContents);
    btnLaunch->setIcon(KIcon("fork"));
    btnLaunch->setObjectName(QString::fromUtf8("btLaunch"));
    //btnLaunch->setMinimumSize(QSize(65, 31));
    //btnLaunch->setMaximumSize(QSize(65, 31));
    //btnLaunch->setText("Launch");
    btnLaunch->setToolTip("Launch");
    hlScriptControls->addWidget(btnLaunch);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hlScriptControls->addItem(horizontalSpacer_2);

    verticalLayout_9->addLayout(hlScriptControls);

    setWidget(dockScriptBrowserContents);

    QObject::connect(btnNewScript, SIGNAL(clicked()), this, SLOT(addNewScript()));
    QObject::connect(btnEdit, SIGNAL(clicked()), this, SLOT(editSelectedScript()));
    QObject::connect(btnLaunch, SIGNAL(clicked()), this, SLOT(launchSelectedScript()));
    
    translateUi();
  }


/**
  User interface string
*/
  void ScriptBrowser::translateUi() {
    setWindowTitle("Script browser");
    tvScriptList->headerItem()->setText(0, "Name");
    const bool __sortingEnabled = tvScriptList->isSortingEnabled();
    tvScriptList->setSortingEnabled(false);

    tvScriptList->setSortingEnabled(__sortingEnabled);
  }

/**
  ScriptBrowser destructor
*/
  ScriptBrowser::~ScriptBrowser() {
    /*delete horizontalSpacer_2;
    delete btnLaunch;
    delete btnEdit;
    delete btnDeleteScipt;
    delete btnNewScript;
    delete hlScriptControls;
    delete tvScriptList;
    delete verticalLayout_9;
    delete dockScriptBrowserContents;*/
  }

/**
  Launch the newScript dialog
*/
  void ScriptBrowser::addNewScript() {
    AddScript* aNewScript = new AddScript(this);
    aNewScript->exec();
    tvScriptList->clear();
    fillTree();
  }


/**
  Read the DB and load all script into their categorie
*/
  void ScriptBrowser::fillTree() {
    QSqlQuery query;
    query.exec("SELECT NAME FROM TCATEGORIES");
    int j =0;
    int k=0;
    while (query.next()) {
      QTreeWidgetItem* aTVItem = new QTreeWidgetItem(tvScriptList);
      tvScriptList->topLevelItem(j)->setText(0,query.value(0).toString());

      QSqlQuery query2;
      query2.exec("SELECT NAME FROM TSCRIPT WHERE CATEGORIE = '"+ query.value(0).toString() +"'");
      while (query2.next()) {
	new QTreeWidgetItem(aTVItem);
	
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
  void ScriptBrowser::editSelectedScript() {
    QString inputFileName = KStandardDirs::locateLocal("appdata", "/script/") + tvScriptList->currentItem()->text(0);
    QString tmpFile;
    if(KIO::NetAccess::download(inputFileName, tmpFile, this)) {
      QFile file(tmpFile);
      file.open(QIODevice::ReadOnly);
      emit setEdirorText(QTextStream(&file).readAll());
      emit enableEditor(true);
      emit setFileName(inputFileName);

      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else {
      KMessageBox::error(this,
      KIO::NetAccess::lastErrorString());
    }
  }

/**
  Launch the script
  @todo use a thread
*/
  void ScriptBrowser::launchSelectedScript() {
    if(tvScriptList->currentItem ()) {
      QString inputFileName = KStandardDirs::locateLocal("appdata", "/script/") + tvScriptList->currentItem()->text(0);
      QString tmpFile;
      if(KIO::NetAccess::download(inputFileName, tmpFile, this)) {
        QFile file(tmpFile);
        file.open(QIODevice::ReadOnly);
        QString script = (QTextStream(&file).readAll());
        
        emit launchScript(tvScriptList->currentItem()->text(0), script);
    
        KIO::NetAccess::removeTempFile(tmpFile);
      }
      else {
        KMessageBox::error(this,
        KIO::NetAccess::lastErrorString());
      }
    }
  }