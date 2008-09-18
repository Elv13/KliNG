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

        Will be used by the script debugger, actuallt totally useless

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "debug.h"
#include "../../mainwindow.h"

#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QTableView>


/**
  Debug constructor

  @param[in] parent The parent window
*/
Debug::Debug(MainWindow* parent)
{
    dockDebug = new QDockWidget();
    dockDebug->setObjectName(QString::fromUtf8("dockDebug"));
    dockDebug->setGeometry(QRect(0, 563, 200, 90));
    dockDebugContents = new QWidget(dockDebug);
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

    verticalLayout_12->addWidget(tbldebug);

    dockDebug->setWidget(dockDebugContents);

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
  delete dockDebug;
}

/**
  User interface string
*/
void Debug::translateUi()
{
    dockDebug->setWindowTitle(QApplication::translate("MainWindow", "Debug", 0, QApplication::UnicodeUTF8));
    tbldebug->horizontalHeaderItem(0)->setText(QApplication::translate("MainWindow", "Variable", 0, QApplication::UnicodeUTF8));
    tbldebug->horizontalHeaderItem(1)->setText(QApplication::translate("MainWindow", "Value", 0, QApplication::UnicodeUTF8));
}

