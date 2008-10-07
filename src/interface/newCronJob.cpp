/**     @file newCronJob.cpp

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

         newCronJob dialog GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/#include "newCronJob.h"

#include <iostream> //TODO useless


#include "../cronparser.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <KDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <KLocalizedString>
//#include <KXmlGuiWindow>
#include <QtSql>
#include <QSqlDatabase>
#include "kcombobox.h"
#include "klineedit.h"



/**
  NewCronJob constructor

  @param[in] parent The parent widget (nothing)
*/
  NewCronJob::NewCronJob(QWidget *parent) : KDialog( parent ) {
    setCaption( "Add new job" );
    setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Apply );
    centralwidget = new QWidget;
    setMainWidget(centralwidget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(206, 24, 400, 500));
    verticalLayout_4 = new QVBoxLayout(centralwidget);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    lblIntro = new QLabel();
    lblIntro->setObjectName(QString::fromUtf8("lblIntro"));
    verticalLayout_4->addWidget(lblIntro);
    
    verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);
    verticalLayout_4->addItem(verticalSpacer_3);
    
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    chkMinute = new QCheckBox();
    chkMinute->setObjectName(QString::fromUtf8("chkMinute"));
    horizontalLayout->addWidget(chkMinute);
    
    txtMinute = new KLineEdit();
    txtMinute->setObjectName(QString::fromUtf8("txtMinute"));
    txtMinute->setEnabled(false);

    txtMinute->setMaximumSize(QSize(41, 30));
    horizontalLayout->addWidget(txtMinute);
    
    horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    
    horizontalLayout->addItem(horizontalSpacer);
    chkHours = new QCheckBox();
    chkHours->setObjectName(QString::fromUtf8("chkHours"));
    horizontalLayout->addWidget(chkHours);
    
    txtHours = new KLineEdit();
    txtHours->setObjectName(QString::fromUtf8("txtHours"));
    txtHours->setEnabled(false);
    txtHours->setMaximumSize(QSize(41, 30));
    horizontalLayout->addWidget(txtHours);
    
    horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_2);
    
    chkDow = new QCheckBox();
    chkDow->setObjectName(QString::fromUtf8("chkDow"));
    horizontalLayout->addWidget(chkDow);
    
    cbbDow = new KComboBox();
    cbbDow->setObjectName(QString::fromUtf8("cbbDow"));
    cbbDow->setEnabled(false);
    horizontalLayout->addWidget(cbbDow);
    
    horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_4);
    chkDom = new QCheckBox();
    chkDom->setObjectName(QString::fromUtf8("chkDom"));
    horizontalLayout->addWidget(chkDom);
    
    txtDom = new KLineEdit();
    txtDom->setObjectName(QString::fromUtf8("txtDom"));
    txtDom->setEnabled(false);
    txtDom->setMaximumSize(QSize(41, 30));
    horizontalLayout->addWidget(txtDom);
    
    chkMonth = new QCheckBox();
    chkMonth->setObjectName(QString::fromUtf8("chkMonth"));
    horizontalLayout->addWidget(chkMonth);
    
    horizontalSpacer_5 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_5);
    
    cbbMonth = new KComboBox();
    cbbMonth->setObjectName(QString::fromUtf8("cbbMonth"));
    cbbMonth->setEnabled(false);
    horizontalLayout->addWidget(cbbMonth);
    verticalLayout_4->addLayout(horizontalLayout);
    
    verticalSpacer_4 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);
    verticalLayout_4->addItem(verticalSpacer_4);
    
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    rbScript = new QRadioButton();
    rbScript->setObjectName(QString::fromUtf8("rbScript"));
    rbScript->setChecked(true);
    verticalLayout->addWidget(rbScript);
    
    hlScript = new QHBoxLayout();
    hlScript->setObjectName(QString::fromUtf8("hlScript"));
    lstCategories = new QListWidget();
    lstCategories->setObjectName(QString::fromUtf8("lstCategories"));
    lstCategories->setMaximumSize(150, 200);

    QSqlQuery query;
    query.exec("SELECT NAME FROM TCATEGORIES");
    
     while (query.next()) 
        lstCategories->addItem(query.value(0).toString());

    hlScript->addWidget(lstCategories);
    
    tblScript = new QTableWidget();
    tblScript->setObjectName(QString::fromUtf8("tblScript"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (tblScript->columnCount() < 2)
      tblScript->setColumnCount(2);
    hlScript->addWidget(tblScript);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(1, __colItem1);
    tblScript->setColumnWidth ( 1, 460 );
    verticalLayout->addLayout(hlScript);
    verticalLayout_4->addLayout(verticalLayout);
    
    verticalSpacer_2 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);
    verticalLayout_4->addItem(verticalSpacer_2);
    
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    rbCommand = new QRadioButton();
    rbCommand->setObjectName(QString::fromUtf8("rbCommand"));
    verticalLayout_2->addWidget(rbCommand);
    
    txtCommand = new KLineEdit();
    txtCommand->setObjectName(QString::fromUtf8("txtCommand"));
    txtCommand->setDisabled(true);
    verticalLayout_2->addWidget(txtCommand);
    verticalLayout_4->addLayout(verticalLayout_2);
    
    verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout_4->addItem(verticalSpacer);

    lblIntro->raise();
    
    retranslateUi();
    connect( this, SIGNAL( okClicked() ), this, SLOT( addAJob() ) );

    connect( chkMinute, SIGNAL( stateChanged(int) ), this, SLOT( chkMinute_checked(int) ) );
    connect( chkHours, SIGNAL( stateChanged(int) ), this, SLOT( chkHours_checked(int) ) );
    connect( chkDow, SIGNAL( stateChanged(int) ), this, SLOT( chkDow_checked(int) ) );
    connect( chkDom, SIGNAL( stateChanged(int) ), this, SLOT( chkDom_checked(int) ) );
    connect( chkMonth, SIGNAL( stateChanged(int) ), this, SLOT( chkMonth_checked(int) ) );
    connect( rbScript, SIGNAL( clicked() ), this, SLOT( rbScript_checked() ) );
    connect( rbCommand, SIGNAL( clicked() ), this, SLOT( rbCommand_checked() ) );
    connect( lstCategories, SIGNAL( currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(loadScriptList(QListWidgetItem*, QListWidgetItem*)));
  } // setupUi

/**
  CommandList user interface strings
*/
  void NewCronJob::retranslateUi() {
    lblIntro->setText(QApplication::translate("", "To add a new job, specify the date and the script/command to run.", 0, QApplication::UnicodeUTF8));
    chkMinute->setText(QApplication::translate("", "Minute: ", 0, QApplication::UnicodeUTF8));
    txtMinute->setText(QApplication::translate("", "All", 0, QApplication::UnicodeUTF8));
    chkHours->setText(QApplication::translate("", "Hours: ", 0, QApplication::UnicodeUTF8));
    txtHours->setText(QApplication::translate("", "All", 0, QApplication::UnicodeUTF8));
    chkDow->setText(QApplication::translate("", "Day (week): ", 0, QApplication::UnicodeUTF8));
    cbbDow->insertItems(0, QStringList()
      << QApplication::translate("", "Mon", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Tue", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Wed", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Thu", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Fri", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Sat", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Sun", 0, QApplication::UnicodeUTF8)
    );
    chkDom->setText(QApplication::translate("", "Day (month): ", 0, QApplication::UnicodeUTF8));
    txtDom->setText(QApplication::translate("", "All", 0, QApplication::UnicodeUTF8));
    chkMonth->setText(QApplication::translate("", "Month: ", 0, QApplication::UnicodeUTF8));
    cbbMonth->insertItems(0, QStringList()
      << QApplication::translate("", "Jan", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Feb", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Mar", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Apr", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "May", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Jun", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Jul", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Aug", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Sep", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Oct", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Nov", 0, QApplication::UnicodeUTF8)
      << QApplication::translate("", "Dec", 0, QApplication::UnicodeUTF8)
    );
    rbScript->setText(QApplication::translate("", "Script", 0, QApplication::UnicodeUTF8));
    rbCommand->setText(QApplication::translate("", "Custom command", 0, QApplication::UnicodeUTF8));
    tblScript->horizontalHeaderItem(0)->setText(QApplication::translate("", "Name", 0, QApplication::UnicodeUTF8));
    tblScript->horizontalHeaderItem(1)->setText(QApplication::translate("", "Description", 0, QApplication::UnicodeUTF8));
  } // retranslateUi

/**
  NewCronJob destructor
*/
  NewCronJob::~NewCronJob() {
    delete verticalSpacer;
    delete txtCommand;
    delete rbCommand;
    delete verticalSpacer_2;
    delete tblScript;
    delete lstCategories;
    delete hlScript;
    delete rbScript;
    delete verticalLayout;
    delete verticalSpacer_4;
    delete cbbMonth;
    delete chkMonth;
    delete txtDom;
    delete chkDow;
    delete verticalLayout;
    delete horizontalSpacer_2;
    delete txtHours;
    delete chkHours;
    delete horizontalSpacer;
    delete txtMinute;
    delete chkMinute;
    delete horizontalLayout;
    delete verticalSpacer_3;
    delete lblIntro;
    delete verticalLayout_4;
    delete centralwidget;
  }

/**
  Call the cronparser to add a job
*/
  void NewCronJob::addAJob() {
    CronParser aCronParser;
    aCronParser.addJob(this);
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::chkMinute_checked(int state) {
    if (state == Qt::Checked) {
      txtMinute->setEnabled(true);
      txtMinute->clear();
      txtMinute->setFocus();
    }
    else if (state == Qt::Unchecked) {
      txtMinute->setEnabled(false);
      txtMinute->setText("All");
    }
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::chkHours_checked(int state) {
    if (state == Qt::Checked) {
      txtHours->setEnabled(true);
      txtHours->clear();
      txtHours->setFocus();
    }
    else if (state == Qt::Unchecked) {
      txtHours->setEnabled(false);
      txtHours->setText("All");
    }
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::chkDow_checked(int state) {
    if (state == Qt::Checked)
      cbbDow->setEnabled(true);
    else if (state == Qt::Unchecked)
      cbbDow->setEnabled(false);
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::chkMonth_checked(int state) {
    if (state == Qt::Checked)
      cbbMonth->setEnabled(true);
    else if (state == Qt::Unchecked)
      cbbMonth->setEnabled(false);
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::chkDom_checked(int state) {
    if (state == Qt::Checked) {
      txtDom->setEnabled(true);
      txtDom->clear();
      txtDom->setFocus();
    }
    else if (state == Qt::Unchecked) {
      txtDom->setEnabled(false);
      txtDom->setText("All");
    }
  }

/**
  React to the state checkbox change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::rbScript_checked() {
    if (rbScript->isChecked() == true) {
      hlScript->setEnabled(true);
      txtCommand->setEnabled(false);
      lstCategories->setEnabled(true);
      tblScript->setEnabled(true);
    }
  }

/**
  React to the state radio button change

  @param[in] state Useless but nessessary, int emmited by the event
*/
  void NewCronJob::rbCommand_checked() {
    if (rbCommand->isChecked() == true) {
      txtCommand->setEnabled(true);
      hlScript->setEnabled(false);
      lstCategories->setEnabled(false);
      tblScript->setEnabled(false);
    }
  }

/**
  React to the state checkbox change

  @param[in] current QListWidgetItem (emmited by state change)
  @param[in] previous QListWidgetItem
*/
  void NewCronJob::loadScriptList(QListWidgetItem* current, QListWidgetItem* previous) {
    tblScript->clear();
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(1, __colItem1);
    tblScript->horizontalHeaderItem(0)->setText(QApplication::translate("", "Name", 0, QApplication::UnicodeUTF8));
    tblScript->horizontalHeaderItem(1)->setText(QApplication::translate("", "Description", 0, QApplication::UnicodeUTF8));
    QSqlQuery query;
    query.exec("SELECT NAME,SCRIPT_DES FROM TSCRIPT WHERE CATEGORIE = '" + lstCategories->currentItem()->text() + "'");
    int i =1;
    while (query.next())  {
        tblScript->setRowCount(i);
        QTableWidgetItem* aTableWidget = new QTableWidgetItem(query.value(0).toString());
        tblScript->setItem((i-1), 0, aTableWidget);
        tblScript->setRowHeight ((i-1), 20 );

        QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(query.value(1).toString());
        tblScript->setItem((i-1), 1, aTableWidget1);
        i++;
    }
  }