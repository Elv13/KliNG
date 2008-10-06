

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

        Display the stdout when in debug mode.

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "debugTerm.h"

#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

/**
  Debug constructor

  @param[in] parent The parent window
*/
  DebugTerm::DebugTerm(QWidget* parent) : QDockWidget ( 0 ) {
    //dockDebug = new QDockWidget();
    setFloating(true);
    setObjectName(QString::fromUtf8("dockDebugTerm"));
    setGeometry(QRect(200, 300, 600, 400));
    dockDebugTermContents = new QWidget(this);
    setWidget(dockDebugTermContents);
    dockDebugTermContents->setObjectName(QString::fromUtf8("dockDebugTermContents"));
    dockDebugTermContents->setGeometry(QRect(2, 22, 196, 66));
    verticalLayout_12 = new QVBoxLayout(dockDebugTermContents);
    verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
    verticalLayout_12->setContentsMargins(0, 0, 0, 0);
    
    rtfDegubTerm = new KTextBrowser(dockDebugTermContents);
    verticalLayout_12->addWidget(rtfDegubTerm);
    translateUi();
  }

/**
  Debug destructor
*/
  DebugTerm::~DebugTerm() {

  }

/**
  User interface string
*/
  void DebugTerm::translateUi() {
      setWindowTitle("Output");
  }

