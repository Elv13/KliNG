/**     @file commandList.cpp

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

        CommandList dock GUI and a system command indexer (read the first level of all $PATH directory) 

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "commandList.h"
#include <iostream>

#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QStringList>
#include "klistwidget.h"
#include <KLocalizedString>
#include <klistwidgetsearchline.h>
#include <stdio.h>
#include <sys/types.h>
#include <getopt.h>

using namespace std;

/**
  CommandList constructor

  @param[in] parent The parent window
  @param[in] commandStringList List of all system command availible used for autocompletion
  @todo Use double click to insert command
*/
  CommandList::CommandList(QWidget* parent, QStringList* commandStringList) : QDockWidget ( 0 ) {
    commandList = commandStringList;
    setObjectName("CommandList");
    //setGeometry(QRect(0, 435, 200, 122));
    /*QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy3);*/
    dockCommandListContents = new QWidget(this);
    dockCommandListContents->setObjectName(QString::fromUtf8("dockCommandListContents"));
    dockCommandListContents->setGeometry(QRect(2, 22, 196, 98));
    verticalLayout_5 = new QVBoxLayout(dockCommandListContents);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    verticalLayout_5->setContentsMargins(0, 0, 0, 0);

    listCommand = new KListWidget(dockCommandListContents);
    listCommand->setObjectName(QString::fromUtf8("listCommand"));
    listCommand->setSortingEnabled(true);
    listCommand->setDragDropMode(QAbstractItemView::DragOnly);
    indexCommand();

    txtFindCommand = new KListWidgetSearchLine(this,listCommand);
    txtFindCommand->setObjectName(QString::fromUtf8("txtFindCommand"));
    txtFindCommand->setProperty("showClearButton", QVariant(true));
    txtFindCommand->setToolTip(i18n("Add a filter to the list bellow"));
    verticalLayout_5->addWidget(txtFindCommand);
    verticalLayout_5->addWidget(listCommand);

    setWidget(dockCommandListContents);
    translateUi();
  }

/**
  CommandList destructor
*/
  CommandList::~CommandList() {
    /*delete listCommand;
    delete txtFindCommand;
    delete verticalLayout_5;
    delete dockCommandListContents;*/
  }

/**
  CommandList user interface strings
*/
  void CommandList::translateUi() {
    setWindowTitle(i18n("System command list"));
  }


/**
  the comamnd indexer. It take execute path from the $PATH system variable
  @param[in] commandStringList List of all system command availible used for autocompletion
  @todo read more than the top folder (read recrusivelly)
  @bug add some non-executable file to the list
  @bug show duplicate command if the PATH contais a symlink
*/
  void CommandList::indexCommand() {
  
    QString path;
    extern char **environ;
    char **env;
    for (env = environ; *env != NULL; ++env) {
      QString anEnvVar = *env;
      if (anEnvVar.left(anEnvVar.indexOf("=")) == "PATH") {
        path = anEnvVar.right(anEnvVar.count() - anEnvVar.indexOf("=") -1);
      }
    }
    //FILE *PATH = popen("echo $PATH ", "r" );

    char buffer[2000];
    string tmp;
    if ( path.count() != 0 ) {
      while (path.indexOf(":") != -1) {
        QString folder = "ls " + path.left(path.indexOf(":"));
        FILE *dirContent = popen(folder.toStdString().c_str(), "r" );
        char buffer2[256];
        if ( dirContent != NULL ) {
          while ( fgets( buffer2, sizeof buffer2, dirContent ) != NULL ) {
            tmp = buffer2;
            tmp = tmp.substr(0, tmp.size() -1);
            *commandList << tmp.c_str();
          }
          pclose( dirContent );
        }
        path = path.mid(path.indexOf(":")+1, (path.count() - path.indexOf(":") -1));
      }
    }

    if (commandList->isEmpty() == false) {
      commandList->sort();
      listCommand->addItem(commandList->at(0));
      int i =1;
      while (i < commandList->size()) {
	if (commandList->at(i) == commandList->at(i-1)) {
	  commandList->removeAt(i);
	}
	else {
	  listCommand->addItem(commandList->at(i));
	  i++;
	}
      }
    }
  }

