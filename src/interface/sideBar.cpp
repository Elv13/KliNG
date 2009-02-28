/**     @file sideBar.cpp

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

        Editor sideBar widget

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9
*/

#include "sideBar.h"
#include <iostream>
//#include "../../mainwindow.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QFrame>
#include <KLocalizedString>
#include "kpushbutton.h"
#include <kicon.h>
#include <KStandardDirs>

/**
  SideBar constructor

  @param[in] parent The parent widget (nothing)
*/
  SideBar::SideBar(unsigned int absLineNB, SideBar* previousItem, QWidget* parent) : QWidget(parent),QTableWidgetItem() {
    debugState= false;
    previousSBItem= NULL;
    nextSBItem = NULL;
    aFrame = new QFrame;
    lineNumber = new QLabel;
    btnDebug = new  KPushButton;

    lineNumber->setMaximumSize(QSize(120, 12));
    btnDebug->setObjectName(QString::fromUtf8("btnDebug"));
    btnDebug->setMinimumSize(QSize(12, 12));
    btnDebug->setMaximumSize(QSize(12, 12));

    lineNumber->setStyleSheet(QString::fromUtf8("margin:0; border: 0px; border-radius: 0px; padding: 0px; spacing:0;"));
    aFrame->setStyleSheet(QString::fromUtf8("margin:0; border: 0px; border-radius: 0px; padding: 0px; width: 12px; height: 12px;spacing:0;"));
    btnDebug->setStyleSheet(QString::fromUtf8("margin-top: 0; margin-bottom: 0; margin-left: 0; margin-right: 0; border: 0px; border-radius: 0px; padding: 0px; width: 12px; height: 12px;spacing:0;"));

    lineNumber->setStyleSheet(QString::fromUtf8("margin-top: 0; margin-bottom: 0; margin-left: 0; margin-right: 0; border: 0px; border-radius: 0px; padding: 0px; width: 12px; height: 12px;spacing:0;"));
    aFrame->setFrameShape(QFrame::NoFrame);
    aFrame->setFrameStyle ( 0 );

    icnBP = new  KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/bp.png"));
    icnEmpty = new  KIcon(KStandardDirs::locate( "appdata", "pixmap/null.png"));
    icnArrow = new  KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/arrow.png"));
    icnArrowBP = new  KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/arrowBP.png"));

  
    if (previousItem != NULL) {
      previousSBItem = previousItem;
      relLineNumber =  previousSBItem->relLineNumber +1;
      lineNumber->setText(QString::number(relLineNumber));
      nextSBItem = previousSBItem->nextSBItem;
      previousSBItem->nextSBItem = this;
    }
    else {
      lineNumber->setText("1");
      relLineNumber = 1; 
    }
    
    aFrame->setMinimumSize(QSize(12, 12));
    aFrame->setMaximumSize(QSize(12, 12));
    hboxLayout = new QHBoxLayout(this);
    hboxLayout->setContentsMargins(3, 2, 0, 0);
    hboxLayout->setSizeConstraint (QLayout::SetMinimumSize);
    hboxLayout->addWidget(lineNumber);
    hboxLayout->addWidget(btnDebug);


    QObject::connect(btnDebug, SIGNAL(clicked()), this, SLOT(changeState()));
  }
  
  SideBar::SideBar(SideBar* toClone) {
    SideBar(1, toClone->previousSBItem, 0);
    debugState= toClone->debugState;
    previousSBItem= toClone->previousSBItem;
    nextSBItem = toClone->nextSBItem;
  }

/**
  SideBar destructor
*/
  /*SideBar::~SideBar() {
    delete lineNumber;
    delete btnDebug;
    delete icnBP;
    delete icnEmpty;
  }*/

/**
  React to state change
*/
  void SideBar::changeState() {	
    if (debugState == false) {
      debugState= true;
      btnDebug->setIcon(*icnBP);
    }
    else {
      btnDebug->setIcon(*icnEmpty);
      debugState=false;
    }
  }
