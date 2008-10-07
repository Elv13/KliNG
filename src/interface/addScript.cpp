/**     @file addScript.cpp

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

        Add Script dialog

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "addScript.h"

#include "../Shell.h"
#include <iostream>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <KDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtSql>
#include <QSqlDatabase>
#include "kcombobox.h"
#include "klineedit.h"
#include "klistwidget.h"
#include "ktextedit.h"
#include "ktitlewidget.h"
#include "kicon.h"
#include <KStandardDirs>
#include <KSaveFile>
#include <KLocalizedString>


/**
  AddScript constructor

  @param[in] parent The parent widget (nothing)
*/
  AddScript::AddScript(QWidget *parent) : KDialog( parent ) {
    centralwidget = new QWidget;
    setMainWidget(centralwidget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(206, 24, 1000, 400));
    centralwidget->setMinimumSize(700, 400);

    setCaption( "Add new script" );
    setButtons( KDialog::Ok | KDialog::Cancel );
    horizontalLayout_3 = new QHBoxLayout(centralwidget);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    lstCategories = new KListWidget(this);
    KIcon icnNewScript("text-x-script");
    QListWidgetItem *__listItem = new QListWidgetItem(lstCategories);
    __listItem->setIcon(icnNewScript);
    KIcon icnFromTemplate("application-x-tar");
    QListWidgetItem *__listItem1 = new QListWidgetItem(lstCategories);
    __listItem1->setIcon(icnFromTemplate);
    KIcon icnNewTemplate("x-kde-nsplugin-generated");
    QListWidgetItem *__listItem2 = new QListWidgetItem(lstCategories);
    __listItem2->setIcon(icnNewTemplate);
    lstCategories->setObjectName(QString::fromUtf8("lstCategories"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(lstCategories->sizePolicy().hasHeightForWidth());
    lstCategories->setSizePolicy(sizePolicy);
    lstCategories->setMaximumSize(QSize(120, 16777215));
    lstCategories->setAlternatingRowColors(false);
    lstCategories->setTextElideMode(Qt::ElideMiddle);
    lstCategories->setMovement(QListView::Static);
    lstCategories->setFlow(QListView::TopToBottom);
    lstCategories->setResizeMode(QListView::Adjust);
    lstCategories->setSpacing(15);
    lstCategories->setViewMode(QListView::IconMode);
    horizontalLayout_3->addWidget(lstCategories);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    ktitlewidget = new KTitleWidget(this);
    ktitlewidget->setObjectName(QString::fromUtf8("ktitlewidget"));
    verticalLayout_2->addWidget(ktitlewidget);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);
    verticalLayout_2->addItem(verticalSpacer);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    scriptName = new QLabel(this);
    scriptName->setObjectName(QString::fromUtf8("scriptName"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(scriptName->sizePolicy().hasHeightForWidth());
    scriptName->setSizePolicy(sizePolicy1);
    horizontalLayout->addWidget(scriptName);

    txtName = new KLineEdit(this);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    horizontalLayout->addWidget(txtName);

    hlCat = new QHBoxLayout();
    lblCat = new QLabel(this);

    hlCat->addWidget(lblCat);
    cbbScriptCat = new KComboBox(this);

    QSqlQuery query;
    query.exec("SELECT NAME FROM TCATEGORIES");
    
    while (query.next()) 
      cbbScriptCat->addItem(query.value(0).toString());
      
    hlCat->addWidget(cbbScriptCat);

    verticalLayout_2->addLayout(horizontalLayout);
    verticalLayout_2->addLayout(hlCat);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    scriptLang = new QLabel(this);
    scriptLang->setObjectName(QString::fromUtf8("scriptLang"));
    sizePolicy1.setHeightForWidth(scriptLang->sizePolicy().hasHeightForWidth());
    scriptLang->setSizePolicy(sizePolicy1);
    lblCat->setSizePolicy(sizePolicy1);
    horizontalLayout_2->addWidget(scriptLang);

    cbbScriptLang = new KComboBox(this);
    cbbScriptLang->setObjectName(QString::fromUtf8("cbbScriptLang"));
    cbbScriptLang->setToolTip(i18n("Select your favorite scripting language"));
    horizontalLayout_2->addWidget(cbbScriptLang);
    verticalLayout_2->addLayout(horizontalLayout_2);
    
    verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    verticalLayout_2->addItem(verticalSpacer_3);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    scriptDes = new QLabel(this);
    scriptDes->setObjectName(QString::fromUtf8("scriptDes"));
    verticalLayout->addWidget(scriptDes);

    txtDes = new KTextEdit(this);
    txtDes->setObjectName(QString::fromUtf8("txtDes"));
    txtDes->setMinimumSize(QSize(0, 150));
    txtDes->setMaximumSize(QSize(16777215, 150));
    txtDes->setToolTip(i18n("Enter the description of this widget"));
    verticalLayout->addWidget(txtDes);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer_2);
    verticalLayout_2->addLayout(verticalLayout);
    horizontalLayout_3->addLayout(verticalLayout_2);

    ktitlewidget->raise();
    ktitlewidget->raise();
    scriptName->raise();
    cbbScriptLang->raise();
    scriptLang->raise();
    scriptDes->raise();
    txtName->raise();
    txtDes->raise();
    lstCategories->raise();

    connect( this, SIGNAL( okClicked() ), this, SLOT( addAScript() ) );
    retranslateUi();
  } 

/**
  CommandList user interface strings
*/
  void AddScript::retranslateUi() {
    const bool __sortingEnabled = lstCategories->isSortingEnabled();
    lstCategories->setSortingEnabled(false);
    lstCategories->item(0)->setText(i18n("Empty Script"));
    lstCategories->item(1)->setText(i18n("   Template  "));
    lstCategories->item(2)->setText(i18n("New Template"));

    lstCategories->setSortingEnabled(__sortingEnabled);
    ktitlewidget->setText(i18n("Add a new script"));
    scriptName->setText(i18n("Name:      "));
    scriptLang->setText(i18n("Type:       "));
    lblCat->setText(i18n("Categorie: "));
    scriptDes->setText(i18n("Description: "));
  }

/**
  AddScript destructor
*/
  AddScript::~AddScript() {
    delete verticalSpacer_2;
    delete txtDes;
    delete scriptDes;
    delete verticalLayout;
    delete verticalSpacer_3;
    delete cbbScriptLang;
    delete scriptLang;
    delete horizontalLayout_2;
    delete cbbScriptCat;
    delete lblCat;
    delete hlCat;
    delete txtName;
    delete scriptName;
    delete horizontalLayout;
    delete verticalSpacer;
    delete ktitlewidget;
    delete verticalLayout_2;
    delete lstCategories;
    delete horizontalLayout_3;
    delete centralwidget;
  }

/**
  Add a script to the DB and create the file
*/
  void AddScript::addAScript() {
    //TODO This function need to be rewriten, it is buggy, cheap and ugly.
    QSqlQuery query;
    
    if (txtName->text().right(3) == ".sh") { //TODO fix this duplicated code
      query.exec("insert into TSCRIPT (CATEGORIE,NAME,SCRIPT_DES) values ('"+ cbbScriptCat->itemText(cbbScriptCat->currentIndex()) +"','" + txtName->text() +"','" + txtDes->toPlainText() + "')");
      KSaveFile file(KStandardDirs::locateLocal("appdata", "/script/") + txtName->text().trimmed());
      file.open();
      QByteArray outputByteArray;
      outputByteArray.append(txtDes->toPlainText() );
      file.write(outputByteArray);
      file.finalize();
      file.close();
    }
    else {
      KSaveFile file(KStandardDirs::locateLocal("appdata", "/script/") + txtName->text().trimmed() + ".sh");
      query.exec("insert into TSCRIPT (CATEGORIE,NAME,SCRIPT_DES) values ('"+ cbbScriptCat->itemText(cbbScriptCat->currentIndex()) +"','" + txtName->text().trimmed() +".sh','" + txtDes->toPlainText() + "')");
      file.open();
      QByteArray outputByteArray;
      outputByteArray.append(txtDes->toPlainText() );
      file.write(outputByteArray);
      file.finalize();
      file.close();
    }
  }
