/**     @file sheduledTask.cpp

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

        sheduledTask dock widget GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "sheduledTask.h"
//#include "../../mainwindow.h"

#include "newCronJob.h"
#include "../cronparser.h"
#include <vector>
#include <iostream>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <KLocalizedString>
#include "kpushbutton.h"

using namespace std;

/**
  SheduledTask constructor

  @param[in] parent The parent window
*/
  SheduledTask::SheduledTask(QWidget* parent) : QDockWidget ( 0 ) {
    setObjectName("SheduledTask");
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed); //
    sizePolicy1.setHorizontalStretch(31); //
    sizePolicy1.setVerticalStretch(31); //
    //setGeometry(QRect(0, 181, 200, 152));
    /*QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy3);*/
    //setSizePolicy(sizePolicy4);
    //setMaximumSize(QSize(16777215, 16777215));
    //setBaseSize(QSize(0, 100));
    dockSheduledTaskContents = new QWidget(this);
    dockSheduledTaskContents->setObjectName(QString::fromUtf8("dockSheduledTaskContents"));
    dockSheduledTaskContents->setGeometry(QRect(2, 22, 196, 128));
    verticalLayout_10 = new QVBoxLayout(dockSheduledTaskContents);
    verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
    verticalLayout_10->setContentsMargins(0, 0, 0, 0);
    tlbvSheduledTask = new QTableWidget(dockSheduledTaskContents);
    tlbvSheduledTask->setObjectName(QString::fromUtf8("tlbvSheduledTask"));
    if (tlbvSheduledTask->columnCount() < 2)
        tlbvSheduledTask->setColumnCount(2);

    verticalLayout_10->addWidget(tlbvSheduledTask);

    hlShTskButton = new QHBoxLayout();
    hlShTskButton->setObjectName(QString::fromUtf8("hlShTskButton"));
    btnAddShTsk = new KPushButton(dockSheduledTaskContents);
    btnAddShTsk->setObjectName(QString::fromUtf8("btnAddShTsk"));
    sizePolicy1.setHeightForWidth(btnAddShTsk->sizePolicy().hasHeightForWidth());
    btnAddShTsk->setSizePolicy(sizePolicy1);
    btnAddShTsk->setMinimumSize(QSize(31, 31));
    btnAddShTsk->setMaximumSize(QSize(31, 31));
    KIcon icnNewTsk("list-add");
    btnAddShTsk->setIcon(icnNewTsk);
    hlShTskButton->addWidget(btnAddShTsk);

    btnDeleteShTsk = new KPushButton(dockSheduledTaskContents);
    btnDeleteShTsk->setObjectName(QString::fromUtf8("btnDeleteShTsk"));
    sizePolicy1.setHeightForWidth(btnDeleteShTsk->sizePolicy().hasHeightForWidth());
    btnDeleteShTsk->setSizePolicy(sizePolicy1);
    btnDeleteShTsk->setMinimumSize(QSize(31, 31));
    btnDeleteShTsk->setMaximumSize(QSize(31, 31));
    KIcon icnRemTsk("list-remove");
    btnDeleteShTsk->setIcon(icnRemTsk);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tlbvSheduledTask->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tlbvSheduledTask->setHorizontalHeaderItem(1, __colItem1);
    hlShTskButton->addWidget(btnDeleteShTsk);

    horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hlShTskButton->addItem(horizontalSpacer_21);
    verticalLayout_10->addLayout(hlShTskButton);

    fillTable();

    setWidget(dockSheduledTaskContents);
    QObject::connect(btnAddShTsk, SIGNAL(clicked()), this, SLOT(newCronJob()));
    translateUi();
  }

/**
  SheduledTask destructor
*/
  SheduledTask::~SheduledTask() {
    /*delete horizontalSpacer_21;
    delete btnDeleteShTsk;
    delete btnAddShTsk;
    delete hlShTskButton;
    delete tlbvSheduledTask;
    delete verticalLayout_10;
    delete dockSheduledTaskContents;*/
  }

/**
  User interface strings
*/
  void SheduledTask::translateUi() {
    setWindowTitle(QApplication::translate("MainWindow", "Sheduled tasks", 0, QApplication::UnicodeUTF8));
    tlbvSheduledTask->horizontalHeaderItem(0)->setText(QApplication::translate("MainWindow", "Date", 0, QApplication::UnicodeUTF8));
    tlbvSheduledTask->horizontalHeaderItem(1)->setText(QApplication::translate("MainWindow", "Command", 0, QApplication::UnicodeUTF8));
  }

/**
  Display the NewJob dialog
*/
  void SheduledTask::newCronJob() {
    NewCronJob* aCronJob = new NewCronJob(0);
    aCronJob->show();
    fillTable();
  }

/**
  Display all job in the table widget
*/
  void SheduledTask::fillTable() {
    CronParser aCronParser;
    vector<QString> allJobs = aCronParser.parseUserJob();
    tlbvSheduledTask->setRowCount(allJobs.size());
    for (int i = 0; i < allJobs.size(); i++) {
      QString thisJob = aCronParser.makeReadable(allJobs[i]); 
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(thisJob);
      tlbvSheduledTask->setItem((i), 0, aTableWidget);
      aTableWidget->setToolTip(thisJob.toStdString().c_str());

      QString thisJobCommand = aCronParser.getCommand(allJobs[i]); 
      QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(thisJobCommand);
      tlbvSheduledTask->setItem((i), 1, aTableWidget1);
      aTableWidget1->setToolTip(thisJobCommand.toStdString().c_str());
    }
  }
  