/**     @file history.cpp

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

        Dock history GUI

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9 
*/

#include "history.h"
#include <iostream>
#include "../../mainwindow.h"

#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <QStringList>
#include <QScrollBar>
#include "klistwidget.h"
#include "klineedit.h"
#include <time.h>

/**
  History constructor

  @param[in] mainWindowCL The main window command line
*/
History::History(KLineEdit* mainWindowCL, QStringList* aStringList) : QDockWidget ( 0 )
{
    historyStringList = aStringList;
    //dockHistory = new QDockWidget();
    setGeometry(QRect(0, 339, 200, 90));
    dockHistoryContents = new QWidget(this);
    dockHistoryContents->setObjectName(QString::fromUtf8("dockHistoryContents"));
    dockHistoryContents->setGeometry(QRect(2, 22, 196, 66));
    vboxLayout = new QVBoxLayout(dockHistoryContents);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    listHistory = new KListWidget(dockHistoryContents);
    listHistory->setObjectName(QString::fromUtf8("listHistory"));
    listHistory->verticalScrollBar()->setValue(listHistory->verticalScrollBar()->maximum());
    
    
    txtFindHistory = new KListWidgetSearchLine(this,listHistory);
    txtFindHistory->setObjectName(QString::fromUtf8("txtFindHystory"));
    txtFindHistory->setProperty("showClearButton", QVariant(true));
    vboxLayout->addWidget(txtFindHistory);
    vboxLayout->addWidget(listHistory);

    setWidget(dockHistoryContents);




    //SQL import of the history
    QSqlQuery query;
    query.exec("SELECT COMMAND FROM THISTORY");
    
     while (query.next()) 
     {
	 addItem(query.value(0).toString(), false);
	*historyStringList << query.value(0).toString();
     }
    
	translateUi();
    }

/**
  History destructor
*/
History::~History()
{
  delete listHistory;
  delete vboxLayout;
  delete dockHistoryContents;
  /*delete dockHistory;*/
}

/**
  User interface strings
*/
void History::translateUi()
{
    setWindowTitle(QApplication::translate("MainWindow", "History", 0, QApplication::UnicodeUTF8));

    const bool __sortingEnabled1 = listHistory->isSortingEnabled();
    listHistory->setSortingEnabled(false);

    listHistory->setSortingEnabled(__sortingEnabled1);
}

/**
  the comamnd indexer. It take execute path from the $PATH system variable
  @param[in] command The command to add
*/
void History::addItem(QString command, bool insertDB)
{
  if (insertDB == true) {
    QSqlQuery query;
    query.exec("insert into THISTORY (COMMAND, DATE, TIME) values ('"+ command +"', '" + QString::number(time(NULL)) +"', 2)"); //TODO add corect time
  }
  //THISTORY (THISTORY_KEY  INTEGER PRIMARY KEY, COMMAND TEXT, DATE DATE, TIME double)
  listHistory->addItem(command);
  *historyStringList << command;
  //while (listHistory->item(listHistory->count() -1)->text() != command) {} //BUG Try to fix a bug, but it fail...
  listHistory->verticalScrollBar()->setValue(listHistory->verticalScrollBar()->maximum());
}