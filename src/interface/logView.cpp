/**     @file logView.cpp

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

        Log viewer, disabled for version 0.0.9
	-NOT OVER-

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "logView.h"
#include "outputViewer.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <KPushButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <KStandardDirs>
#include <KIcon>
#include <QHeaderView>
#include <kcombobox.h>
#include <kpushbutton.h>
#include <kseparator.h>
#include <kdialog.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QDateTime>

QT_BEGIN_NAMESPACE


/**
  LogView constructor
*/
LogView::LogView(QWidget* parent) : KDialog( parent )
{
    setButtons( KDialog::Ok );
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("logView"));
    resize(674, 523);
    setMinimumSize(QSize(568, 0));
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 0, 674, 674));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    setMainWidget(centralwidget);
    
    hlControl = new QHBoxLayout();
    hlControl->setObjectName(QString::fromUtf8("hlControl"));
    cbbLog = new KComboBox(centralwidget);
    cbbLog->setObjectName(QString::fromUtf8("cbbLog"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cbbLog->sizePolicy().hasHeightForWidth());
    cbbLog->setSizePolicy(sizePolicy);

    hlControl->addWidget(cbbLog);

    sldLenght = new QSlider(centralwidget);
    sldLenght->setObjectName(QString::fromUtf8("sldLenght"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(sldLenght->sizePolicy().hasHeightForWidth());
    sldLenght->setSizePolicy(sizePolicy1);
    sldLenght->setMinimumSize(QSize(150, 0));
    sldLenght->setMaximumSize(QSize(150, 16777215));
    sldLenght->setMaximum(5);
    sldLenght->setPageStep(5);
    sldLenght->setOrientation(Qt::Horizontal);
    sldLenght->setInvertedAppearance(false);

    hlControl->addWidget(sldLenght);

    kseparator = new KSeparator(centralwidget);
    kseparator->setObjectName(QString::fromUtf8("kseparator"));
    kseparator->setOrientation(Qt::Vertical);

    hlControl->addWidget(kseparator);


    verticalLayout->addLayout(hlControl);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    
    /*rtfViewer = new QTextBrowser(centralwidget);
    rtfViewer->setObjectName(QString::fromUtf8("rtfViewer"));
    horizontalLayout_3->addWidget(rtfViewer);*/
    
    tblViewer = new QTableWidget(this);
    tblViewer->verticalHeader()->hide();
    tblViewer->setColumnCount(4);
    
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(0, __colItem);
    tblViewer->horizontalHeaderItem(0)->setText("Name");
    tblViewer->setColumnWidth(0,312); //FIXME
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(1, __colItem1);
    tblViewer->horizontalHeaderItem(1)->setText("Start");
    tblViewer->setColumnWidth(1,130);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(2, __colItem4);
    tblViewer->horizontalHeaderItem(2)->setText("End");
    tblViewer->setColumnWidth(2,130);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(3, __colItem2);
    tblViewer->horizontalHeaderItem(3)->setText("Output");
    tblViewer->setColumnWidth(3,80);
    
    horizontalLayout_3->addWidget(tblViewer);

    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    verticalLayout->addLayout(horizontalLayout_2);


    retranslateUi();
    fillTable(0,0);
    
    
    } // setupUi

/**
  User interface strings
*/
void LogView::retranslateUi()
{
     setCaption( "Log" );
    cbbLog->insertItems(0, QStringList()
     << QApplication::translate("logView", "Script log", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "Command log", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "Command Output", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "Actions", 0, QApplication::UnicodeUTF8)
    );
    //btnClose->setText(QApplication::translate("logView", "Close", 0, QApplication::UnicodeUTF8));
    //Q_UNUSED(logView);
} // retranslateUi


/**
  LogView destructor
*/
LogView::~LogView()
{

}

void LogView::fillTable(char kind, char level) {
    unsigned int rowCount =0;
    QSqlQuery query;
    query.exec("SELECT * FROM THISTORY");
    QString strLine;
    KIcon icnEye(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png"));
    while (query.next())  {
      QTableWidgetItem* anItem = new QTableWidgetItem();
      QTableWidgetItem* aDateStart = new QTableWidgetItem();
      QTableWidgetItem* aDateEnd = new QTableWidgetItem();
      
      QDateTime aDateTime;
      aDateTime.setTime_t(query.value(2).toString().toUInt());
      //dateTime = gmtime(aDateTime.toTime_t());
      QString date = aDateTime.toString("dd/MM/yyyy hh:mm:ss");
      
      aDateStart->setText(date);
      anItem->setText(query.value(1).toString());
      
      QDateTime aDateTime2;
      aDateTime2.setTime_t(query.value(3).toString().toUInt());
      //dateTime = gmtime(aDateTime.toTime_t());
      QString date2 = aDateTime2.toString("dd/MM/yyyy hh:mm:ss");
      
      aDateEnd->setText(date2);
      
      OutputViewerButton* btnView = new OutputViewerButton(0);
      btnView->setText("View");
      btnView->setIcon(icnEye);
      btnView->setStyleSheet("margin:-5px;spacing:0px;height:25px;min-height:25px;max-height:25px;");
      btnView->setMinimumSize(80, 25);
      btnView->setMaximumSize(9999, 25);
      btnView->id = query.value(0).toInt();
      QObject::connect(btnView, SIGNAL(clicked(uint)), this, SLOT(showOutput(uint)));
      
      
      tblViewer->setRowCount(++rowCount);
      tblViewer->setItem(rowCount-1,0,anItem);
      tblViewer->setItem(rowCount-1,1,aDateStart);
      tblViewer->setItem(rowCount-1,2,aDateEnd);
      tblViewer->setCellWidget(rowCount-1, 3, btnView);
      tblViewer->setRowHeight(rowCount-1, 20);
      
    }
}

void LogView::showOutput(uint id) {
  OutputViewer* anOutputViewer = new OutputViewer(this, id);
  anOutputViewer->show();
}