/**     @file sideBar.h

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

        sideBar.cpp header file

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_SIDEBAR
#define DEF_SIDEBAR
#include "sideBar.h"

//#include "../../mainwindow.h"
#include <QtGui/QHBoxLayout>
#include <QTableWidgetItem>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QFrame>
#include "kpushbutton.h"
#include <kicon.h>

QT_BEGIN_NAMESPACE
  class SideBar : public QWidget, public QTableWidgetItem {
        Q_OBJECT

    public:
      SideBar(unsigned int absLineNB, SideBar* previousItem, QWidget* parent);
      SideBar(SideBar* toClone);
      //~SideBar();

      int relLineNumber;
      int absLineNumber;
      bool debugState;
      QHBoxLayout* hboxLayout;
      QLabel* lineNumber;
      KPushButton* btnDebug;
      QLabel* codeFolding;
      SideBar* previousSBItem;
      SideBar* nextSBItem;
      QFrame* aFrame;
      KIcon* icnBP;
      KIcon* icnEmpty;
      KIcon* icnArrow;
      KIcon* icnArrowBP;

    private slots:
      void changeState();
  };
#endif
