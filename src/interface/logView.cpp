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

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
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
    resize(568, 523);
    setMinimumSize(QSize(568, 0));
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 0, 568, 523));
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
    rtfViewer = new QTextBrowser(centralwidget);
    rtfViewer->setObjectName(QString::fromUtf8("rtfViewer"));

    horizontalLayout_3->addWidget(rtfViewer);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    verticalLayout->addLayout(horizontalLayout_2);

    QSqlQuery query;
    query.exec("SELECT * FROM THISTORY");
    QString strLine;
    while (query.next())  {
      //tm* dateTime;
      //struct stat status_buf;
      //stat(Name.toStdString().c_str(), &status_buf);
      QDateTime aDateTime;
      aDateTime.setTime_t(query.value(2).toString().toUInt());
      //dateTime = gmtime(aDateTime.toTime_t());
      QString date = aDateTime.toString("dd/MM/yyyy hh:mm:ss");
      
      strLine = query.value(1).toString() + " " + date;
      rtfViewer->append(strLine);
    }
    retranslateUi();
    
    
    
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
