/**     @file man.cpp

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

        Dock man GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "man.h"
#include "../manParser.h"
#include "../../mainwindow.h"

#include <iostream>

#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
//#include <QtGui/QTreeWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QToolBox>
#include "kpushbutton.h"
#include "kcombobox.h"
#include <QtSql>
#include <QLabel>
#include <QTableView>
#include <QHeaderView>


/**
  Man constructor

  @param[in] parent The parent window
*/
Man::Man(MainWindow* parent)
{
  
//**************************************************************
//                 dockManual
//**************************************************************


    dockManual = new QDockWidget();
    dockManual->setObjectName(QString::fromUtf8("dockManual"));
    dockManual->setGeometry(QRect(783, 24, 201, 629));
    QSizePolicy sizePolicy5(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(dockManual->sizePolicy().hasHeightForWidth());
    dockManual->setSizePolicy(sizePolicy5);
    dockManual->setMinimumSize(QSize(200, 200));
    dockManual->setMaximumSize(QSize(16777215, 16777215));
    dockManual->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockManualContents = new QWidget(dockManual);
    dockManualContents->setObjectName(QString::fromUtf8("dockManualContents"));
    dockManualContents->setGeometry(QRect(2, 22, 197, 605));
    verticalLayout = new QVBoxLayout(dockManualContents);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    hlFindManPage = new QHBoxLayout();
    hlFindManPage->setObjectName(QString::fromUtf8("hlFindManPage"));
    cbbManPagelist = new KComboBox(dockManualContents);
    cbbManPagelist->setObjectName(QString::fromUtf8("cbbManPagelist"));
    cbbManPagelist->setEditable(true);
    cbbManPagelist->setMaxVisibleItems(50);
    cbbManPagelist->setInsertPolicy(QComboBox::NoInsert);
    cbbManPagelist->setAutoCompletion(false);
    cbbManPagelist->setTrapReturnKey(false);

    hlFindManPage->addWidget(cbbManPagelist);

    btnFindManPage = new KPushButton(dockManualContents);
    btnFindManPage->setObjectName(QString::fromUtf8("btnFindManPage"));
    btnFindManPage->setMaximumSize(QSize(60, 16777215));
    btnFindManPage->setSizeIncrement(QSize(0, 0));

    hlFindManPage->addWidget(btnFindManPage);


    verticalLayout->addLayout(hlFindManPage);

    tbManInfo = new QToolBox(dockManualContents);
    tbManInfo->setObjectName(QString::fromUtf8("tbManInfo"));
    QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(tbManInfo->sizePolicy().hasHeightForWidth());
    tbManInfo->setSizePolicy(sizePolicy6);
    tbManInfo->setBaseSize(QSize(240, 91));
    tbManInfo->setStyleSheet(QString::fromUtf8(""));
    tbManInfo->setLineWidth(1);
    pageManual = new QWidget();
    pageManual->setObjectName(QString::fromUtf8("pageManual"));
    pageManual->setGeometry(QRect(0, 0, 179, 469));
    verticalLayout_2 = new QVBoxLayout(pageManual);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    rtfManPage = new QTextBrowser(pageManual);
    rtfManPage->setObjectName(QString::fromUtf8("rtfManPage"));

    verticalLayout_2->addWidget(rtfManPage);

    tbManInfo->addItem(pageManual, QApplication::translate("MainWindow", "Manuel", 0, QApplication::UnicodeUTF8));
    PageUsage = new QWidget();
    PageUsage->setObjectName(QString::fromUtf8("PageUsage"));
    PageUsage->setGeometry(QRect(0, 0, 179, 469));
    verticalLayout_4 = new QVBoxLayout(PageUsage);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    tblUsage = new QTableWidget(PageUsage);
    if (tblUsage->columnCount() < 2)
        tblUsage->setColumnCount(2);
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblUsage->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblUsage->setHorizontalHeaderItem(1, __colItem1);
    tblUsage->setObjectName(QString::fromUtf8("tblUsage"));
    tblUsage->setMidLineWidth(0);
    tblUsage->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblUsage->setSelectionMode(QAbstractItemView::NoSelection);
    tblUsage->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    tblUsage->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    verticalLayout_4->addWidget(tblUsage);

    tbManInfo->addItem(PageUsage, QApplication::translate("MainWindow", "Usage", 0, QApplication::UnicodeUTF8));
    pageOptions = new QWidget();
    pageOptions->setObjectName(QString::fromUtf8("pageOptions"));
    pageOptions->setGeometry(QRect(0, 0, 179, 469));
    verticalLayout_3 = new QVBoxLayout(pageOptions);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    tblOptions = new QTableWidget(pageOptions);
    if (tblOptions->columnCount() < 2)
        tblOptions->setColumnCount(2);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblOptions->setHorizontalHeaderItem(0, __colItem2);
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    tblOptions->setHorizontalHeaderItem(1, __colItem3);
    tblOptions->setObjectName(QString::fromUtf8("tblOptions"));
    tblOptions->setEnabled(true);
    tblOptions->setDragEnabled(true);
    tblOptions->setDragDropMode(QAbstractItemView::DragOnly);
    tblOptions->setSelectionMode(QAbstractItemView::NoSelection);

    verticalLayout_3->addWidget(tblOptions);

    tbManInfo->addItem(pageOptions, QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));

    verticalLayout->addWidget(tbManInfo);
    tblUsage->verticalHeader()->hide();
    tblOptions->verticalHeader()->hide();
    

    dockManual->setWidget(dockManualContents);

    tbManInfo->setCurrentIndex(0);
    translateUi();

    QSqlQuery query;
    query.exec("SELECT TITLE FROM TMAN_PAGE");
    
     while (query.next()) 
     {
	 cbbManPagelist->addItem(query.value(0).toString());
     }
	 cbbManPagelist->model()->sort(0);
	 cbbManPagelist->setCurrentIndex(0);


     QObject::connect(cbbManPagelist, SIGNAL(currentIndexChanged(int)), this, SLOT(loadPage()));
}


/**
  Man destructor
*/
Man::~Man()
{
  delete tblOptions;
  delete verticalLayout_3;
  delete pageOptions;
  delete tblUsage;
  delete verticalLayout_4;
  delete PageUsage;
  delete rtfManPage;
  delete verticalLayout_2;
  delete pageManual;
  delete btnFindManPage;
  delete cbbManPagelist;
  delete hlFindManPage;
  delete verticalLayout;
  delete dockManualContents;
  delete dockManual;
}

/**
  User interface string
*/
void Man::translateUi()
{
      dockManual->setWindowTitle(QApplication::translate("MainWindow", "Manual", 0, QApplication::UnicodeUTF8));
    btnFindManPage->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
    rtfManPage->setHtml(QApplication::translate("MainWindow", "<center><h1>Welcome to kling</h1></center>", 0, QApplication::UnicodeUTF8));
    tbManInfo->setItemText(tbManInfo->indexOf(pageManual), QApplication::translate("MainWindow", "Manuel", 0, QApplication::UnicodeUTF8));
    tblUsage->horizontalHeaderItem(0)->setText(QApplication::translate("MainWindow", "Exemple", 0, QApplication::UnicodeUTF8));
    tblUsage->horizontalHeaderItem(1)->setText(QApplication::translate("MainWindow", "Description", 0, QApplication::UnicodeUTF8));
    tbManInfo->setItemText(tbManInfo->indexOf(PageUsage), QApplication::translate("MainWindow", "Usage", 0, QApplication::UnicodeUTF8));
    tblOptions->horizontalHeaderItem(0)->setText(QApplication::translate("MainWindow", "Option", 0, QApplication::UnicodeUTF8));
    tblOptions->horizontalHeaderItem(1)->setText(QApplication::translate("MainWindow", "Description", 0, QApplication::UnicodeUTF8));
    tbManInfo->setItemText(tbManInfo->indexOf(pageOptions), QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
}

/**
  Load a manPage from /usr/share/man. Also load usage, examples and options
*/
void Man::loadPage()
{
  tblOptions->clear();
  tblOptions->setRowCount(0);
  QSqlQuery query;
  query.exec("SELECT PATH FROM TMAN_PAGE WHERE TITLE = '"+ cbbManPagelist->itemText(cbbManPagelist->currentIndex())+"'");
  
    while (query.next()) 
    {
	system("mkdir /tmp/man");
	std::string cmdCopy = "cp " + query.value(0).toString().toStdString() + " /tmp/man/";
	std::string name;
	std::string command;
	system(cmdCopy.c_str());

	if (query.value(0).toString().toStdString().find(".bz2") != -1)
	{	
	    name = query.value(0).toString().toStdString().substr( query.value(0).toString().toStdString().find_last_of("/") +1, (query.value(0).toString().toStdString().size() - query.value(0).toString().toStdString().find_last_of("/") -1));
	    command =  "bunzip2 -d /tmp/man/" + name;
	    name = name.substr(0, name.find(".bz2"));
	}
	else
	{

	}
	system(command.c_str());
	rtfManPage->setHtml(ManParser::parseManPage(name).c_str());
    }

    QSqlQuery query2;
    query2.exec("SELECT OPT_NAME,OPT_DES FROM TOPTION WHERE COMMAND = '"+ cbbManPagelist->itemText(cbbManPagelist->currentIndex())+"'");
    int row = 1;
    tblOptions->setColumnCount(2);
    while (query2.next()) 
    {
	tblOptions->setRowCount(row);

	QWidget* aWidget = new QWidget(tblOptions); //Dirty hack to fix a QT bug
	QLabel* aTableWidget = new QLabel(aWidget);
	aTableWidget->setText(query2.value(0).toString());
	tblOptions->setCellWidget((row-1), 0, aWidget);
	aWidget->setToolTip(query2.value(0).toString());
	
	QWidget* aWidget2 = new QWidget(tblOptions); //Dirty hack to fix a QT bug
	QLabel* aTableWidget2 = new QLabel(aWidget2);
	aTableWidget2->setText(query2.value(1).toString());
	tblOptions->setCellWidget((row-1), 1, aWidget2);
	aWidget2->setToolTip(query2.value(1).toString());
	tblOptions->setRowHeight(row-1, 25);
	row++;
    }

    QSqlQuery query3;
    query3.exec("SELECT USAGE,USAGE_DES FROM TUSAGE WHERE COMMAND = '"+ cbbManPagelist->itemText(cbbManPagelist->currentIndex())+"'");
    int row2 = 1;
    tblUsage->setColumnCount(2);
    while (query3.next()) 
    {
	tblUsage->setRowCount(row2);

	QWidget* aWidget = new QWidget(tblUsage);
	QLabel* aTableWidget = new QLabel(aWidget);
	aTableWidget->setObjectName(QString::fromUtf8("aTableLabel"));
	aTableWidget->setText(QApplication::translate("MainWindow", query3.value(0).toString().toStdString().c_str(), 0, QApplication::UnicodeUTF8));
	tblUsage->setCellWidget((row2-1), 0, aWidget);
	aWidget->setToolTip(query3.value(0).toString());
	
	QWidget* aWidget2 = new QWidget(tblUsage);
	QLabel* aTableWidget2 = new QLabel(aWidget2);
	aTableWidget2->setText(query3.value(1).toString());
	tblUsage->setCellWidget((row2-1), 1, aWidget2);
	aWidget2->setToolTip(query3.value(1).toString());
	tblUsage->setRowHeight(row2-2, 25);
	row2++;
    }

}
