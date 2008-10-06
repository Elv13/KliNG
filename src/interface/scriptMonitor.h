/**     @file scriptMonitor.h

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

        scriptMonitor.cpp header file

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_SCRIPTMONITOR
#define DEF_SCRIPTMONITOR

#include <iostream>
#include "../thread.h"
#include "../../mainwindow.h"
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
  class ScriptMonitor : public QFrame {
    Q_OBJECT
    public:
      ScriptMonitor(QWidget* parent, QString scriptName);
      ~ScriptMonitor();
      void retranslateUi();
      QVBoxLayout *verticalLayout_2;
      QVBoxLayout *verticalLayout;
      QHBoxLayout *horizontalLayout;
      KLed *isRunning;
      QLabel *lblCmd;
      QSpacerItem *horizontalSpacer;
      QLabel *lblNextCmd;
      QSpacerItem *verticalSpacer;
      QLabel *lblTitle;
      QLabel *lblTime;
      QProgressBar *progressBar;
      void launchScript(std::string script);
    private:
      ThreadExec* aThread;
    private slots:
      void endMe();
      void disCurrentLine(QString line);
      void disNextLine(QString line);
  };
#endif
