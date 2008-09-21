/**     @file man.h

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

        man.cpp header file

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_MAN
#define DEF_MAN


#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
//#include <QtGui/QTreeWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QToolBox>
#include "kpushbutton.h"
#include "kcombobox.h"
#include <QtSql>
#include <QLabel>
#include <QTableView>
#include <QHeaderView>
#include <QTextBrowser>
#include <QTableWidget>
/*#include <>
#include <>
#include <>
#include <>
#include <>*/


class Man  : public QDockWidget
{
  Q_OBJECT
  public:
    Man(QWidget* parent);
    ~Man();
    void translateUi();


    QWidget *dockManualContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlFindManPage;
    KComboBox *cbbManPagelist;
    KPushButton *btnFindManPage;
    QToolBox *tbManInfo;
    QWidget *pageManual;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *rtfManPage;
    QWidget *PageUsage;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tblUsage;
    QWidget *pageOptions;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tblOptions;

  private slots:
    void loadPage();


};
#endif
