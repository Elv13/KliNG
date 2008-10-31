/**     @file commandList.h

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

        commandList.cpp header

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_COMMANDLIST
#define DEF_COMMANDLIST


#include <QtGui/QDockWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QStringList>
#include <klistwidgetsearchline.h>
#include "klistwidget.h"

  class CommandList  : public QDockWidget {
    public:
      CommandList(QWidget* parent, QStringList* commandStringList);
      ~CommandList();
      void translateUi();
      void indexCommand();

      QWidget *dockCommandListContents;
      QVBoxLayout *verticalLayout_5;
      KListWidgetSearchLine *txtFindCommand;
      KListWidget *listCommand;
      QStringList* commandList;
  };
#endif
