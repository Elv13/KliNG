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

#include "scriptMonitor.h"

#include "../Shell.h"
#include "../thread.h"
#include <iostream>
#include <QString>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "kled.h"

using namespace std;

/**
  ScriptMonitor constructor

  @param[in] parent The parent widget (nothing)
*/
ScriptMonitor::ScriptMonitor(QWidget* parent, std::string script, std::string scriptName) : QFrame(parent)
{

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    isRunning = new KLed(this);
    isRunning->setObjectName(QString::fromUtf8("isRunning"));

    horizontalLayout->addWidget(isRunning);

    lblTitle = new QLabel(this);
    lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
    lblTitle->setText("<b>"+ QString::fromStdString(scriptName) +"</b>");

    horizontalLayout->addWidget(lblTitle);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    lblTime = new QLabel(this);
    lblTime->setObjectName(QString::fromUtf8("lblTime"));

    horizontalLayout->addWidget(lblTime);


    verticalLayout->addLayout(horizontalLayout);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    lblCmd = new QLabel(this);
    lblCmd->setObjectName(QString::fromUtf8("lblCmd"));

    verticalLayout->addWidget(lblCmd);

    lblNextCmd = new QLabel(this);
    lblNextCmd->setObjectName(QString::fromUtf8("lblNextCmd"));

    verticalLayout->addWidget(lblNextCmd);

    progressBar = new QProgressBar(this);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(24);

    verticalLayout->addWidget(progressBar);


    verticalLayout_2->addLayout(verticalLayout);
    setStyleSheet(QString::fromUtf8("background-color:grey;"));

    retranslateUi();
}

/**
  CommandList user interface strings
*/
void ScriptMonitor::retranslateUi()
{

  lblTime->setText(QApplication::translate("Dialog", "0:24", 0, QApplication::UnicodeUTF8));
  lblCmd->setText(QApplication::translate("Dialog", "Current command: echo salut", 0, QApplication::UnicodeUTF8));
  lblNextCmd->setText(QApplication::translate("Dialog", "Next Command: echo sa va?", 0, QApplication::UnicodeUTF8));
} // retranslateUi

/**
  ScriptMonitor destructor
*/
ScriptMonitor::~ScriptMonitor()
{
  /*delete progressBar;
  delete lblNextCmd;
  delete lblCmd;
  delete verticalSpacer;
  delete lblTitle;
  delete isRunning;
  delete horizontalLayout;
  delete verticalLayout;
  delete verticalLayout_2;*/
}

/**
  React to the state checkbox change

  @param[in] script the script text
*/
void ScriptMonitor::launchScript(string script) //TODO This is not bash compliant, if, while, for and until are not implemented yet
{

 aThread = new ThreadExec(this,script);

  QObject::connect(aThread, SIGNAL(progress(int)), progressBar, SLOT(setValue (int)));
  QObject::connect(aThread, SIGNAL(isOver()), this, SLOT(endMe())); //I don't call the destructor because it is not only this signal that can call it, if the program is closed, it will do a segFault.
  QObject::connect(aThread, SIGNAL(currentLine(QString)), this, SLOT(disCurrentLine(QString)));
  QObject::connect(aThread, SIGNAL(nextLine(QString)), this, SLOT(disNextLine(QString)));

  aThread->start();
}

void ScriptMonitor::endMe()
{
  delete aThread;
  delete this;
}

void ScriptMonitor::disCurrentLine(QString line)
{
  lblCmd->setText("Current command: " + line);
}

void ScriptMonitor::disNextLine(QString line)
{
  lblNextCmd->setText("Next command: " + line);
}