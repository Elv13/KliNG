/**     @file newCronJob.h

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

        newCronJob.cpp header file

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_NEWCRONJOB
#define  DEF_NEWCRONJOB

#include "../../mainwindow.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <kdialog.h>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include "kcombobox.h"
#include "klineedit.h"

  class NewCronJob : public KDialog {
    Q_OBJECT
    public:
      NewCronJob(QWidget* parent);
      ~NewCronJob();
      void retranslateUi();

      QWidget *centralwidget;
      QVBoxLayout *verticalLayout_4;
      QLabel *lblIntro;
      QSpacerItem *verticalSpacer_3;
      QHBoxLayout *horizontalLayout;
      QCheckBox *chkMinute;
      KLineEdit *txtMinute;
      QSpacerItem *horizontalSpacer;
      QCheckBox *chkHours;
      KLineEdit *txtHours;
      QSpacerItem *horizontalSpacer_2;
      QCheckBox *chkDow;
      KComboBox *cbbDow;
      QSpacerItem *horizontalSpacer_4;
      QCheckBox *chkDom;
      KLineEdit *txtDom;
      QCheckBox *chkMonth;
      QSpacerItem *horizontalSpacer_5;
      KComboBox *cbbMonth;
      QSpacerItem *verticalSpacer_4;
      QVBoxLayout *verticalLayout;
      QRadioButton *rbScript;
      QHBoxLayout *hlScript;
      QListWidget *lstCategories;
      QTableWidget *tblScript;
      QSpacerItem *verticalSpacer_2;
      QVBoxLayout *verticalLayout_2;
      QRadioButton *rbCommand;
      KLineEdit *txtCommand;
      QSpacerItem *verticalSpacer;
      QDialogButtonBox *buttonBox;
    
    private:

    private slots:
      void addAJob();
      void chkMinute_checked(int state);
      void chkHours_checked(int state);
      void chkDow_checked(int state);
      void chkDom_checked(int state);
      void chkMonth_checked(int state);
      void rbScript_checked();
      void rbCommand_checked();
      void loadScriptList(QListWidgetItem* current, QListWidgetItem* previous);
  };
#endif