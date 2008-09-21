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
#include <klistwidgetsearchline.h>

using namespace std;

/**
  CommandList constructor

  @param[in] parent The parent window
  @param[in] commandStringList List of all system command availible used for autocompletion
  @todo Use double click to insert command
*/

CommandList::CommandList(QWidget* parent, QStringList* commandStringList) : QDockWidget ( 0 )
{

    setGeometry(QRect(0, 435, 200, 122));
    dockCommandListContents = new QWidget(this);
    dockCommandListContents->setObjectName(QString::fromUtf8("dockCommandListContents"));
    dockCommandListContents->setGeometry(QRect(2, 22, 196, 98));
    verticalLayout_5 = new QVBoxLayout(dockCommandListContents);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    verticalLayout_5->setContentsMargins(0, 0, 0, 0);




    listCommand = new KListWidget(dockCommandListContents);
    listCommand->setObjectName(QString::fromUtf8("listCommand"));
    listCommand->setSortingEnabled(true);
    indexCommand(commandStringList);

    txtFindCommand = new KListWidgetSearchLine(dockCommandListContents,listCommand);
    txtFindCommand->setObjectName(QString::fromUtf8("txtFindCommand"));
    txtFindCommand->setProperty("showClearButton", QVariant(true));
    verticalLayout_5->addWidget(txtFindCommand);
    verticalLayout_5->addWidget(listCommand);

    setWidget(dockCommandListContents);
    translateUi();

}

/**
  CommandList destructor
*/
CommandList::~CommandList()
{
 delete listCommand;
 delete txtFindCommand;
 delete verticalLayout_5;
 delete dockCommandListContents;
}

/**
  CommandList user interface strings
*/
void CommandList::translateUi()
{
  setWindowTitle("System command list");
}


/**
  the comamnd indexer. It take execute path from the $PATH system variable
  @param[in] commandStringList List of all system command availible used for autocompletion
  @todo read more than the top folder (read recrusivelly)
  @bug add some non-executable file to the list
  @bug show duplicate command if the PATH contais a symlink
*/
void CommandList::indexCommand(QStringList* commandStringList)
{
    FILE *PATH = popen("echo $PATH ", "r" );

    char buffer[2000];
    string tmp;
    if ( PATH != NULL ) {
      while ( fgets( buffer, sizeof buffer, PATH ) != NULL )
      {
            string path = buffer;
            while (path.find(":") != -1)
            {
                string folder = "ls " + path.substr(0, path.find(":"));
                FILE *dirContent = popen(folder.c_str(), "r" );
                char buffer2[256];
                if ( dirContent != NULL ) {

                  while ( fgets( buffer2, sizeof buffer2, dirContent ) != NULL ) {
                      //cout << buffer2;
		      tmp = buffer2;
		      tmp = tmp.substr(0, tmp.size() -1);
		      //listCommand->addItem(tmp.c_str());
		      *commandStringList << tmp.c_str();
                  }
                  pclose( dirContent );
                }
                path = path.substr(path.find(":")+1, (path.size() - path.find(":") -1));
            }
      }
      pclose( PATH );
    }

    if (commandStringList->isEmpty() == false) {
      commandStringList->sort();
      listCommand->addItem(commandStringList->at(0));
      int i =1;
      while (i < commandStringList->size()) {
	if (commandStringList->at(i) == commandStringList->at(i-1)) {
	  commandStringList->removeAt(i);
	}
	else {
	  listCommand->addItem(commandStringList->at(i));
	  i++;
	}
      }
    }
}

