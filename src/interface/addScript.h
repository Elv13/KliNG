/**     @file main.cpp

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

        Header of addScript.cpp

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_ADDSCRIPT
#define DEF_ADDSCRIPT

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <KDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "kcombobox.h"
#include "klineedit.h"
#include "klistwidget.h"
#include "ktextedit.h"
#include "ktitlewidget.h"

  class AddScript : public KDialog {
    Q_OBJECT
    public:
      AddScript(QWidget *parent);
      ~AddScript();
      void retranslateUi();

      QWidget *centralwidget;
      QHBoxLayout *horizontalLayout_3;
      QHBoxLayout *hlCat;
      KListWidget *lstCategories;
      QVBoxLayout *verticalLayout_2;
      KTitleWidget *ktitlewidget;
      QSpacerItem *verticalSpacer;
      QHBoxLayout *horizontalLayout;
      QLabel *scriptName;
      QLabel* lblCat;
      KLineEdit *txtName;
      QHBoxLayout *horizontalLayout_2;
      QLabel *scriptLang;
      KComboBox *cbbScriptLang;
      KComboBox *cbbScriptCat;
      QSpacerItem *verticalSpacer_3;
      QVBoxLayout *verticalLayout;
      QLabel *scriptDes;
      KTextEdit *txtDes;
      QSpacerItem *verticalSpacer_2;
    private slots:
      void addAScript();
  };

#endif
