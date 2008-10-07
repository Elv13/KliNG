/**     @file setup.cpp

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

        Setup dialog GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "setup.h"
#include "../manParser.h"

#include <iostream>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcombobox.h"
#include "kpushbutton.h"
#include "ktitlewidget.h"
#include <KLocalizedString>
#include <kicon.h>
#include <KMessageBox>
#include <KAboutData>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>

/**
  Setup constructor
*/
  Setup::Setup() {
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName( "/home/lepagee/dev/tp3-prog_sess2/kling.db" );
    if ( db->open())
      std::cout << "database corectly opened" << std::endl;
    else
      std::cout << "ERROR while opening the database, get ready for a crash" << std::endl;

    resize(750, 450);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(750, 450));
    setMaximumSize(QSize(750, 450));
    centralwidget = new QWidget();
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 0, 750, 450));
    horizontalLayout_2 = new QHBoxLayout(centralwidget);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    mainLayout = new QHBoxLayout();
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    sideImage = new QLabel(centralwidget);
    sideImage->setObjectName(QString::fromUtf8("sideImage"));
    sideImage->setMaximumSize(QSize(150, 450));
    sideImage->setPixmap(QPixmap("/home/lepagee/dev/tp3-prog_sess2/sideim.png"));
    mainLayout->addWidget(sideImage);

    setupLayout = new QFrame(centralwidget);
    setupLayout->setObjectName(QString::fromUtf8("setupLayout"));
    setupLayout->setFrameShape(QFrame::StyledPanel);
    setupLayout->setFrameShadow(QFrame::Raised);
    verticalLayout_4 = new QVBoxLayout(setupLayout);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    titleSetup = new KTitleWidget(setupLayout);
    titleSetup->setObjectName(QString::fromUtf8("titleSetup"));
    titleSetup->setMaximumSize(QSize(16777215, 50));
    titleSetup->setPixmap(KIcon("tools-wizard").pixmap(22, 22), KTitleWidget::ImageRight);
    verticalLayout_4->addWidget(titleSetup);

    Setup_Page4 = new QFrame(setupLayout);
    Setup_Page4->setObjectName(QString::fromUtf8("Setup_Page4"));
    Setup_Page4->setFrameShape(QFrame::StyledPanel);
    Setup_Page4->setFrameShadow(QFrame::Raised);
    messageSP4 = new QLabel(Setup_Page4);
    messageSP4->setObjectName(QString::fromUtf8("messageSP4"));
    messageSP4->setGeometry(QRect(0, 0, 501, 171));
    layoutWidget = new QWidget(Setup_Page4);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 170, 316, 93));
    verticalLayout_3 = new QVBoxLayout(layoutWidget);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    primaryLang = new QLabel(layoutWidget);
    primaryLang->setObjectName(QString::fromUtf8("primaryLang"));
    horizontalLayout_4->addWidget(primaryLang);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_4->addItem(horizontalSpacer_2);

    cbbPrimary = new KComboBox(layoutWidget);
    cbbPrimary->setObjectName(QString::fromUtf8("cbbPrimary"));
    cbbPrimary->setMinimumSize(QSize(100, 0));
    horizontalLayout_4->addWidget(cbbPrimary);
    verticalLayout_3->addLayout(horizontalLayout_4);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    seconderyLang = new QLabel(layoutWidget);
    seconderyLang->setObjectName(QString::fromUtf8("seconderyLang"));
    horizontalLayout_5->addWidget(seconderyLang);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_5->addItem(horizontalSpacer_3);

    cbbSecondery = new KComboBox(layoutWidget);
    cbbSecondery->setObjectName(QString::fromUtf8("cbbSecondery"));
    cbbSecondery->setEnabled(false);
    cbbSecondery->setMinimumSize(QSize(100, 0));
    horizontalLayout_5->addWidget(cbbSecondery);
    verticalLayout_3->addLayout(horizontalLayout_5);

    chkFetch = new QCheckBox(layoutWidget);
    chkFetch->setObjectName(QString::fromUtf8("chkFetch"));
    chkFetch->setChecked(true);
    verticalLayout_3->addWidget(chkFetch);
    verticalLayout_4->addWidget(Setup_Page4);

    Setup_Page1 = new QFrame(setupLayout);
    Setup_Page1->setObjectName(QString::fromUtf8("Setup_Page1"));
    Setup_Page1->setFrameShape(QFrame::StyledPanel);
    Setup_Page1->setFrameShadow(QFrame::Raised);
    messageSP1 = new QLabel(Setup_Page1);
    messageSP1->setObjectName(QString::fromUtf8("messageSP1"));
    messageSP1->setGeometry(QRect(10, 10, 501, 151));
    verticalLayout_4->addWidget(Setup_Page1);

    Setup_Page3 = new QFrame(setupLayout);
    Setup_Page3->setObjectName(QString::fromUtf8("Setup_Page3"));
    Setup_Page3->setFrameShape(QFrame::StyledPanel);
    Setup_Page3->setFrameShadow(QFrame::Raised);
    messageSP3 = new QLabel(Setup_Page3);
    messageSP3->setObjectName(QString::fromUtf8("messageSP3"));
    messageSP3->setGeometry(QRect(10, 10, 501, 71));
    verticalLayout_4->addWidget(Setup_Page3);

    Setup_Page2 = new QFrame(setupLayout);
    Setup_Page2->setObjectName(QString::fromUtf8("Setup_Page2"));
    Setup_Page2->setFrameShape(QFrame::StyledPanel);
    Setup_Page2->setFrameShadow(QFrame::Raised);
    verticalLayout_2 = new QVBoxLayout(Setup_Page2);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    txtLicence = new QTextBrowser(Setup_Page2);
    txtLicence->setObjectName(QString::fromUtf8("txtLicence"));
    verticalLayout_2->addWidget(txtLicence);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    rbAccept = new QRadioButton(Setup_Page2);
    rbAccept->setObjectName(QString::fromUtf8("rbAccept"));
    rbAccept->setChecked(true);
    verticalLayout->addWidget(rbAccept);

    rbDecline = new QRadioButton(Setup_Page2);
    rbDecline->setObjectName(QString::fromUtf8("rbDecline"));
    verticalLayout->addWidget(rbDecline);
    verticalLayout_2->addLayout(verticalLayout);
    verticalLayout_4->addWidget(Setup_Page2);

    Setup_Page5 = new QFrame(setupLayout);
    Setup_Page5->setObjectName(QString::fromUtf8("Setup_Page5"));
    Setup_Page5->setFrameShape(QFrame::StyledPanel);
    Setup_Page5->setFrameShadow(QFrame::Raised);
    messaheSP5 = new QLabel(Setup_Page5);
    messaheSP5->setObjectName(QString::fromUtf8("messaheSP5"));
    messaheSP5->setGeometry(QRect(0, 0, 501, 171));
    verticalLayout_4->addWidget(Setup_Page5);

    buttonLayout = new QHBoxLayout();
    buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
    btnHelp = new KPushButton(setupLayout);
    btnHelp->setObjectName(QString::fromUtf8("btnHelp"));
    btnHelp->setMinimumSize(QSize(91, 31));
    btnHelp->setMaximumSize(QSize(91, 31));
    KIcon icnHelp("help-contents");
    btnHelp->setIcon(icnHelp);
    btnHelp->setIconSize(QSize(22, 22));
    buttonLayout->addWidget(btnHelp);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(horizontalSpacer);

    btnFinish = new KPushButton(setupLayout);
    btnFinish->setObjectName(QString::fromUtf8("btnFinish"));
    btnFinish->setMinimumSize(QSize(91, 31));
    KIcon icnFinish("dialog-ok");
    btnFinish->setIcon(icnFinish);
    btnFinish->setIconSize(QSize(22, 22));
    buttonLayout->addWidget(btnFinish);

    btnPrevious = new KPushButton(setupLayout);
    btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
    btnPrevious->setMinimumSize(QSize(91, 31));
    btnPrevious->setMaximumSize(QSize(91, 31));
    KIcon icnPrevious("go-previous");
    btnPrevious->setIcon(icnPrevious);
    btnPrevious->setIconSize(QSize(22, 22));
    buttonLayout->addWidget(btnPrevious);

    btnNext = new KPushButton(setupLayout);
    btnNext->setObjectName(QString::fromUtf8("btnNext"));
    btnNext->setMinimumSize(QSize(91, 31));
    btnNext->setMaximumSize(QSize(91, 31));
    KIcon icnNext("go-next");
    btnNext->setIcon(icnNext);
    btnNext->setIconSize(QSize(22, 22));
    buttonLayout->addWidget(btnNext);

    btnScan = new KPushButton(setupLayout);
    btnScan->setObjectName(QString::fromUtf8("btnScan"));
    btnScan->setEnabled(true);
    btnScan->setMinimumSize(QSize(91, 31));
    KIcon icnScan("system-search");
    btnScan->setIcon(icnScan);
    btnScan->setIconSize(QSize(20, 20));
    buttonLayout->addWidget(btnScan);

    btnSkip = new KPushButton(setupLayout);
    btnSkip->setObjectName(QString::fromUtf8("btnSkip"));
    btnSkip->setEnabled(true);
    btnSkip->setMinimumSize(QSize(91, 31));
    KIcon icnSkip("window-close");
    btnSkip->setIcon(icnSkip);
    btnSkip->setIconSize(QSize(20, 20));
    buttonLayout->addWidget(btnSkip);
    verticalLayout_4->addLayout(buttonLayout);
    mainLayout->addWidget(setupLayout);
    horizontalLayout_2->addLayout(mainLayout);

    setCentralWidget(centralwidget);
    QWidget::setTabOrder(btnNext, btnHelp);
    QWidget::setTabOrder(btnHelp, btnPrevious);

    retranslateUi();
    QObject::connect(btnNext, SIGNAL(clicked()), this, SLOT(nextPage()));
    QObject::connect(btnPrevious, SIGNAL(clicked()), this, SLOT(previousPage()));
    QObject::connect(btnSkip, SIGNAL(clicked()), this, SLOT(skip()));
    QObject::connect(btnScan, SIGNAL(clicked()), this, SLOT(scan()));
    QObject::connect(btnFinish, SIGNAL(clicked()), this, SLOT(close()));

    page =1;
    btnFinish->hide();
    btnScan->hide();
    btnSkip->hide();
    Setup_Page1->show();
    Setup_Page2->hide();
    Setup_Page3->hide();
    Setup_Page4->hide();
    Setup_Page5->hide();
  }


/**
  User interface strings
*/
  void Setup::retranslateUi() {
    setWindowTitle(QApplication::translate("MainWindow", "Frist run setup", 0, QApplication::UnicodeUTF8));
    sideImage->setText(QString());
    titleSetup->setText(QApplication::translate("MainWindow", "First run wizard", 0, QApplication::UnicodeUTF8));
    messageSP4->setText(QApplication::translate("MainWindow", "<b>SystemSettings</b><br><br>APPLICATION_NAME will now\n"
"scan your computer to index every system command<br>and manual page avalible and add them to a data base for faster access. This spet<br> is highly recommanded and is totally safe. Absolutely no information will ever leave<br>the system, everyting is stored locally. In addition to that APPLICATION_NAME<br>can fetch from our server variours exemples of command to improve the documentation<br>avalible on the system. To proceep, press scan. Note that this operation may take<br>several minute.", 0, QApplication::UnicodeUTF8));
    primaryLang->setText(QApplication::translate("MainWindow", "Primary manual language:", 0, QApplication::UnicodeUTF8));
    seconderyLang->setText(QApplication::translate("MainWindow", "Secondary manual language:", 0, QApplication::UnicodeUTF8));
    cbbSecondery->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "English", 0, QApplication::UnicodeUTF8)
    );
    chkFetch->setText(QApplication::translate("MainWindow", "Fetch content from network.", 0, QApplication::UnicodeUTF8));
    messageSP1->setText(QApplication::translate("MainWindow", "<b>My application</b><br><br>Welcome to APPLICATION_NAME. This application will help your system administrator <br> to complete time consuming unix task faster and more efficiently than ever before. Using <br> this application, systems administrators will be able to automate almost everything using <br>the well tested bash language with some nice addition. In addition to that, this application <br> provide a next generation shell and other tool useful to administrate a Unix, BSD or Linux<br>system. To be able to use this application, few simple step are resquired, press the next<br>button to proceed.", 0, QApplication::UnicodeUTF8));
    messageSP3->setText(QApplication::translate("MainWindow", "<b>Default Path</b><br><br>Please specify where scripts and log will be stored on your system. Those file can be stored on <br>a remote computer using a SMB/CIFS network if you use the smaba is configured corectly on your system.", 0, QApplication::UnicodeUTF8));
    rbAccept->setText(QApplication::translate("MainWindow", "Accept", 0, QApplication::UnicodeUTF8));
    rbDecline->setText(QApplication::translate("MainWindow", "Decline", 0, QApplication::UnicodeUTF8));
    messaheSP5->setText(QApplication::translate("MainWindow", "The setup is now complete, press on finish to start the application.", 0, QApplication::UnicodeUTF8));
    btnHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    btnFinish->setText(QApplication::translate("MainWindow", "Finish", 0, QApplication::UnicodeUTF8));
    btnPrevious->setText(QApplication::translate("MainWindow", "Back", 0, QApplication::UnicodeUTF8));
    btnNext->setText(QApplication::translate("MainWindow", "Next", 0, QApplication::UnicodeUTF8));
    btnScan->setText(QApplication::translate("MainWindow", "Scan", 0, QApplication::UnicodeUTF8));
    btnSkip->setText(QApplication::translate("MainWindow", "Skip", 0, QApplication::UnicodeUTF8));
    txtLicence->setText(QApplication::translate("MainWindow", "<h3><a name=''SEC1'' href=''gpl-2.0.html#TOC1''>GNU GENERAL PUBLIC LICENSE</a></h3> <p> Version 2, June 1991 </p> <pre> Copyright (C) 1989, 1991 Free Software Foundation, Inc.  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed. </pre> <h3><a name=''SEC2'' href=''gpl-2.0.html#TOC2''>Preamble</a></h3> <p> The licenses for most software are designed to take away your freedom to share and change it.  By contrast, the GNU General Public License is intended to guarantee your freedom to share and change free software--to make sure the software is free for all its users.  This General Public License applies to most of the Free Software Foundation's software and to any other program whose authors commit to using it.  (Some other Free Software Foundation software is covered by the GNU Lesser General Public License instead.)  You can apply"));
  } // retranslateUi


/**
   Display the next setup page
*/
  void Setup::nextPage() {
    switch (page) {
      case 1:
        Setup_Page1->hide();
        Setup_Page2->show();
        page++;
      break;
      case 2:
        if (rbAccept->isChecked() == false) {
          int answer = KMessageBox::questionYesNo( 0, i18n( "Are you sure you want to quit Kling?" ), i18n( "Alert!" ));
          if (answer == KMessageBox::Yes)
            close();
        }
        else {
          Setup_Page2->hide();
          Setup_Page3->show();
          page++;
        }
      break;
      case 3:
        Setup_Page3->hide();
        Setup_Page4->show();
        btnScan->show();
        btnSkip->show();
        btnScan->setFocus();
        btnNext->hide();
        //btnPrevious->hide();
        page++;
      break;
      case 4:
        btnSkip->hide();
        btnScan->hide();
        Setup_Page4->hide();
        Setup_Page5->show();
        btnNext->hide();
        btnFinish->show();
        page++;
      break;
    }
  }
    
/**
   Display the previous setup page
  @todo if the system have been scanned, clean the DB before scanning it again
*/
  void Setup::previousPage() {
    switch (page) {
      case 2:
        Setup_Page1->show();
        Setup_Page2->hide();
        page--;
      break;
      case 3:
        Setup_Page2->show();
        Setup_Page3->hide();
        page--;
      break;
      case 4:
        btnSkip->hide();
        btnScan->hide();
        btnNext->show();
        Setup_Page3->show();
        Setup_Page4->hide();
        page--;
      break;
      case 5:
        Setup_Page4->show();
        Setup_Page5->hide();
        btnSkip->show();
        btnScan->show();
        btnFinish->hide();
        page--;
      break;
    }
  }

/**
   ask confirmation for skipping the system scan
*/
  void Setup::skip() {
    int answer = KMessageBox::warningYesNo( 0, i18n( "Are you sure you want to skip the scan. You will not be able to use most of the autocompletion system." ), i18n( "Warning" ));

    if (answer == KMessageBox::Yes) {
          Setup_Page4->hide();
	  Setup_Page5->show();
	  btnSkip->hide();
	  btnScan->hide();
	  btnNext->hide();
	  btnFinish->show();
	  page++;
    }
  }

/**
   call the system scanner
*/
  void Setup::scan() {
    ManParser::parseAllManPage();
    Setup_Page4->hide();
    Setup_Page5->show();
    btnSkip->hide();
    btnScan->hide();
    btnNext->hide();
    btnFinish->show();
    page++;
  }