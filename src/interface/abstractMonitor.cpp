/**     @file scriptMonitor.cpp

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

        Monitor widget able to display the execution state of a script

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "abstractMonitor.h"

#include <QString>
#include <QtGui/QSpacerItem>
#include <QtGui/QHBoxLayout>
#include <KLocalizedString>
#include <QColor>
#include <QBrush>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <time.h>
#include "kled.h"


/**
  ScriptMonitor constructor

  @param[in] parent The parent widget (nothing)
*/
  AbstractMonitorItem::AbstractMonitorItem(QWidget* parent, QString scriptName) : QFrame(parent) {
    second =0;
    this->scriptName = scriptName;
    QPalette aPalette;
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
    mainLayout = new QGridLayout(this);
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    actionLayout = new QHBoxLayout();
    isRunning = new KLed(this);
    isRunning->setObjectName(QString::fromUtf8("isRunning"));
    mainLayout->addWidget(isRunning,0,0);

    lblTitle = new QLabel(this);
    lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
    lblTitle->setText("<b>"+ scriptName +"</b>");
    lblTitle->setStyleSheet("background-color:transparent;border-radius:0;");
    mainLayout->addWidget(lblTitle,0,1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mainLayout->addItem(horizontalSpacer,0,2);

    lblTime = new QLabel(this);
    lblTime->setObjectName(QString::fromUtf8("lblTime"));
    mainLayout->addWidget(lblTime,0,3);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer,1,0);

    lblCmd = new QLabel(this);
    lblCmd->setObjectName(QString::fromUtf8("lblCmd"));
    lblCmd->setStyleSheet("background-color:transparent;border-radius:0;");
    lblCmd->setText("Current command: - ");
    mainLayout->addWidget(lblCmd,2,0,1,4);

    lblNextCmd = new QLabel(this);
    lblNextCmd->setObjectName(QString::fromUtf8("lblNextCmd"));
    lblNextCmd->setStyleSheet("background-color:transparent;border-radius:0;");
    lblNextCmd->setText("Next command: - ");
    mainLayout->addWidget(lblNextCmd,3,0,1,4);

    progressBar = new QProgressBar(this);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(0);
    progressBar->setStyleSheet("background-color:" + aPalette.button().color().name() + ";border-radius:0;color:black;text-align:center;");

    mainLayout->addWidget(progressBar,4,0,1,4);

    mainLayout->addLayout(actionLayout,5,0,1,4);


    //string defaultColor = aPalette.button().color().name();
    setStyleSheet("background-color:qlineargradient( y1:0, y2:1,stop:0 " + aPalette.window().color().name() + ", stop:1 " + aPalette.button().color().name() + ");border-radius:10;border-color:black;border-width:1px;");

  }

  void AbstractMonitorItem::updateCurrentLine(QString line) {
    lblCmd->setText("Current command: " + line);
  }

  void AbstractMonitorItem::updateNextLine(QString line) {
    lblNextCmd->setText("Next command: " + line);
  }

  void AbstractMonitorItem::incrementTimer() {
    second++;
    QTime aTime(0,0,second,0);
    lblTime->setText(aTime.toString("hh:mm:ss"));
  }

  void AbstractMonitorItem::setupActions() {
    /*Overload this function in child widget*/
  }

  void AbstractMonitorItem::endMe() {
    //QSqlQuery query;
    //query.exec("update TSCRIPT_HISTORY SET TIME_END = '" + QString::number(time(NULL)) + "' WHERE TSCRIPT_HISTORY_KEY = " + QString::number(key)); 
    //delete aThread;
    delete this;
  }