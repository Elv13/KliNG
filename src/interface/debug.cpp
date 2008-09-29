

/**     @file debug.cpp

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

        Display environement and local variables

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "debug.h"

#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <stdio.h>
#include <sys/types.h>
#include <getopt.h>



/**
  Debug constructor

  @param[in] parent The parent window
*/
Debug::Debug(QWidget* parent) : QDockWidget ( 0 )
{
    //dockDebug = new QDockWidget();
    setObjectName(QString::fromUtf8("dockDebug"));
    setGeometry(QRect(0, 563, 200, 90));
    dockDebugContents = new QWidget(this);
    dockDebugContents->setObjectName(QString::fromUtf8("dockDebugContents"));
    dockDebugContents->setGeometry(QRect(2, 22, 196, 66));
    verticalLayout_12 = new QVBoxLayout(dockDebugContents);
    verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
    verticalLayout_12->setContentsMargins(0, 0, 0, 0);
    tbldebug = new QTableWidget(dockDebugContents);
    if (tbldebug->columnCount() < 2)
        tbldebug->setColumnCount(2);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tbldebug->setHorizontalHeaderItem(0, __colItem4);
    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    tbldebug->setHorizontalHeaderItem(1, __colItem5);
    tbldebug->setObjectName(QString::fromUtf8("tbldebug"));
    tbldebug->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    tbldebug->verticalHeader()->hide();

    verticalLayout_12->addWidget(tbldebug);

    setWidget(dockDebugContents);
    
    unsigned int rowCount =0;
    extern char **environ;
    char **env;
    for (env = environ; *env != NULL; ++env) {
      tbldebug->setRowCount(++rowCount);
      tbldebug->setRowHeight((rowCount-1), 20);
      puts (*env);
      QString anEnvVar = *env;
      
      QTableWidgetItem* anEnvVarName = new QTableWidgetItem();
      anEnvVarName->setText(anEnvVar.left(anEnvVar.indexOf("=")).insert(0,"$"));
      anEnvVarName->setToolTip(anEnvVar.left(anEnvVar.indexOf("=")).insert(0,"$"));
      tbldebug->setItem(rowCount-1,0,anEnvVarName);
      
      QTableWidgetItem* anEnvVarValue = new QTableWidgetItem();
      anEnvVarValue->setText(anEnvVar.right(anEnvVar.count() - anEnvVar.indexOf("=") -1));
      anEnvVarValue->setToolTip(anEnvVar.right(anEnvVar.count() - anEnvVar.indexOf("=")-1));
      tbldebug->setItem(rowCount-1,1,anEnvVarValue);
      
    }

    translateUi();
}

/**
  Debug destructor
*/
Debug::~Debug()
{
  delete tbldebug;
  delete verticalLayout_12;
  delete dockDebugContents;
}

/**
  User interface string
*/
void Debug::translateUi()
{
    setWindowTitle("Variables");
    tbldebug->horizontalHeaderItem(0)->setText("Variable");
    tbldebug->horizontalHeaderItem(1)->setText("Value");
}

