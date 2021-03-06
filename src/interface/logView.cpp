/**     @file logView.cpp

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

        Log viewer, disabled for version 0.0.9
	-NOT OVER-

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9
*/

#include "logView.h"
#include "outputViewer.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <KPushButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <KStandardDirs>
#include <KIcon>
#include <QHeaderView>
#include <kcombobox.h>
#include <kpushbutton.h>
#include <kseparator.h>
#include <kdialog.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QDateTime>
#include <QTextStream>
#include <KIO/NetAccess>
#include <KFileDialog>
#include <KLocalizedString>
#include <sys/klog.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>


QT_BEGIN_NAMESPACE


/**
  LogView constructor
*/
  LogView::LogView(QWidget* parent, KlingConfigSkeleton* aConfigSkeleton) : KDialog( parent ) {
    config = aConfigSkeleton;
    setButtons( KDialog::Ok );
    if (objectName().isEmpty())
      setObjectName(QString::fromUtf8("logView"));
    resize(925, 750);
    setMinimumSize(QSize(568, 0));
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 0, 925, 750));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    setMainWidget(centralwidget);
    
    hlControl = new QHBoxLayout();
    hlControl->setObjectName(QString::fromUtf8("hlControl"));
    cbbLog = new KComboBox(centralwidget);
    cbbLog->setObjectName(QString::fromUtf8("cbbLog"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cbbLog->sizePolicy().hasHeightForWidth());
    cbbLog->setSizePolicy(sizePolicy);
    hlControl->addWidget(cbbLog);

    sldLenght = new QSlider(centralwidget);
    sldLenght->setObjectName(QString::fromUtf8("sldLenght"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(sldLenght->sizePolicy().hasHeightForWidth());
    sldLenght->setSizePolicy(sizePolicy1);
    sldLenght->setMinimumSize(QSize(150, 0));
    sldLenght->setMaximumSize(QSize(150, 16777215));
    sldLenght->setMaximum(5);
    sldLenght->setPageStep(5);
    sldLenght->setOrientation(Qt::Horizontal);
    sldLenght->setInvertedAppearance(false);
    hlControl->addWidget(sldLenght);

    kseparator = new KSeparator(centralwidget);
    kseparator->setObjectName(QString::fromUtf8("kseparator"));
    kseparator->setOrientation(Qt::Vertical);
    hlControl->addWidget(kseparator);
    verticalLayout->addLayout(hlControl);

    tblViewer = new QTableWidget(this);
    tblViewer->verticalHeader()->hide();
    tblViewer->setColumnCount(4);
    setupHeader();
    verticalLayout->addWidget(tblViewer);
    
    lstLog = new QListWidget(this);
    lstLog->hide();
    verticalLayout->addWidget(lstLog);
    
    txtFindLine = new KListWidgetSearchLine(this,lstLog);
    txtFindLine->setObjectName(QString::fromUtf8("txtFindLine"));
    txtFindLine->setProperty("showClearButton", QVariant(true));
    txtFindLine->hide();
    verticalLayout->addWidget(txtFindLine);
    
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_2->addItem(horizontalSpacer);
    verticalLayout->addLayout(horizontalLayout_2);
    
    graphWidget = new QWidget();
    graphWidget->setMaximumSize(99999,140);
    setupGraph();
    verticalLayout->addWidget(graphWidget);

    QObject::connect(cbbLog, SIGNAL(currentIndexChanged(int)), this, SLOT(switchMode(int)));
    QObject::connect(sldLenght, SIGNAL(sliderMoved(int)), this, SLOT(delayChanged(int)));
    retranslateUi();
    displayCommandHistory(0);
  } // setupUi

/**
  User interface strings
*/
  void LogView::retranslateUi() {
    setCaption( "Log" );
    cbbLog->insertItems(0, QStringList()
     << QApplication::translate("logView", "Command history", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "Script hisory", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "dmesg", 0, QApplication::UnicodeUTF8) 
     << QApplication::translate("logView", "------------", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("logView", "Add a new log", 0, QApplication::UnicodeUTF8)
     );
     cbbLog->insertItems(3,  config->fileToWatch);
  } 


/**
  LogView destructor
*/
  LogView::~LogView() {

  }

  void LogView::displayCommandHistory(char level) {
    tblViewer->clear();
    setupHeader();
    unsigned int rowCount =0;
    QSqlQuery query;
    query.exec("SELECT * FROM THISTORY");
    QString strLine;
    KIcon icnEye(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png"));
    while (query.next())  {
      if (config->logExcludeList.indexOf(getCommand(query.value(1).toString())) == -1) {
        QTableWidgetItem* anItem = new QTableWidgetItem();
        QTableWidgetItem* aDateStart = new QTableWidgetItem();
        QTableWidgetItem* aDateEnd = new QTableWidgetItem();
        
        QDateTime aDateTime;
        aDateTime.setTime_t(query.value(2).toString().toUInt());
        QString date = aDateTime.toString("dd/MM/yyyy hh:mm:ss");
        
        aDateStart->setText(date);
        anItem->setText(query.value(1).toString());
        
        QDateTime aDateTime2;
        aDateTime2.setTime_t(query.value(3).toString().toUInt());
        QString date2 = aDateTime2.toString("dd/MM/yyyy hh:mm:ss");
        aDateEnd->setText(date2);
        
        OutputViewerButton* btnView = new OutputViewerButton(0);
        btnView->setText("View");
        btnView->setIcon(icnEye);
        btnView->setStyleSheet("margin:-5px;spacing:0px;height:25px;min-height:25px;max-height:25px;");
        btnView->setMinimumSize(80, 25);
        btnView->setMaximumSize(9999, 25);
        btnView->id = query.value(0).toInt();
        if (KStandardDirs::exists(KStandardDirs::locateLocal("appdata", "/output/"+QString::number(query.value(0).toInt()))) == false)
          btnView->setDisabled(true);
        QObject::connect(btnView, SIGNAL(clicked(uint)), this, SLOT(showOutput(uint)));

        tblViewer->setRowCount(++rowCount);
        tblViewer->setItem(rowCount-1,0,anItem);
        tblViewer->setItem(rowCount-1,1,aDateStart);
        tblViewer->setItem(rowCount-1,2,aDateEnd);
        tblViewer->setCellWidget(rowCount-1, 3, btnView);
        tblViewer->setRowHeight(rowCount-1, 20);
      }
    }
  }

  void LogView::displayScriptHistory(char level) {
    tblViewer->clear();
    setupHeader();
    unsigned int rowCount =0;
    QSqlQuery query;
    query.exec("SELECT * FROM TSCRIPT_HISTORY");
    QString strLine;
    KIcon icnEye(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png"));
    while (query.next())  {
      if (config->logExcludeList.indexOf(getCommand(query.value(1).toString())) == -1) {
        QTableWidgetItem* anItem = new QTableWidgetItem();
        QTableWidgetItem* aDateStart = new QTableWidgetItem();
        QTableWidgetItem* aDateEnd = new QTableWidgetItem();
        
        QDateTime aDateTime;
        aDateTime.setTime_t(query.value(2).toString().toUInt());
        QString date = aDateTime.toString("dd/MM/yyyy hh:mm:ss");
        
        aDateStart->setText(date);
        anItem->setText(query.value(1).toString());
        
        QDateTime aDateTime2;
        aDateTime2.setTime_t(query.value(3).toString().toUInt());
        QString date2 = aDateTime2.toString("dd/MM/yyyy hh:mm:ss");
        aDateEnd->setText(date2);
        
        OutputViewerButton* btnView = new OutputViewerButton(0);
        btnView->setText("View");
        btnView->setIcon(icnEye);
        btnView->setStyleSheet("margin:-5px;spacing:0px;height:25px;min-height:25px;max-height:25px;");
        btnView->setMinimumSize(80, 25);
        btnView->setMaximumSize(9999, 25);
        btnView->id = query.value(0).toInt();
        if (KStandardDirs::exists(KStandardDirs::locateLocal("appdata", "/output/script/"+QString::number(query.value(0).toInt()))) == false)
          btnView->setDisabled(true);
        QObject::connect(btnView, SIGNAL(clicked(uint)), this, SLOT(showOutput(uint)));

        tblViewer->setRowCount(++rowCount);
        tblViewer->setItem(rowCount-1,0,anItem);
        tblViewer->setItem(rowCount-1,1,aDateStart);
        tblViewer->setItem(rowCount-1,2,aDateEnd);
        tblViewer->setCellWidget(rowCount-1, 3, btnView);
        tblViewer->setRowHeight(rowCount-1, 20);
      }
    }
  }

  void LogView::showOutput(uint id) {
    OutputViewer* anOutputViewer = new OutputViewer(this, id);
    anOutputViewer->show();
  }

  QString LogView::getCommand(QString command) {
    if (command.trimmed().indexOf(" ") == -1) 
      return command;
    else 
      return command.trimmed().mid(0, command.trimmed().indexOf(" "));
  }

  void LogView::setupHeader() {
    tblViewer->setRowCount(0);
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(0, __colItem);
    tblViewer->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblViewer->horizontalHeaderItem(0)->setText("Name");
    tblViewer->setColumnWidth(0,540); //FIXME
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(1, __colItem1);
    tblViewer->horizontalHeaderItem(1)->setText("Start");
    tblViewer->setColumnWidth(1,130);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(2, __colItem4);
    tblViewer->horizontalHeaderItem(2)->setText("End");
    tblViewer->setColumnWidth(2,130);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblViewer->setHorizontalHeaderItem(3, __colItem2);
    tblViewer->horizontalHeaderItem(3)->setText("Output");
    tblViewer->setColumnWidth(3,80);
  }

  void LogView::switchMode(int mode) {
    if (COMMAND_HISTORY == mode) {
      lstLog->hide();
      txtFindLine->hide();
      tblViewer->show();
      displayCommandHistory(1);
    }
    else if (SCRIPT_HISTORY  == mode) {
      lstLog->hide();
      txtFindLine->hide();
      tblViewer->show();
      displayScriptHistory(1);
    }
    else if (DMESG  == mode) {
      lstLog->show();
      txtFindLine->show();
      tblViewer->hide();
      showDmesg();
    }
    else {
      if ((cbbLog->currentText() != "Add a new log") && (cbbLog->currentText() != "------------")) {
        lstLog->show();
        txtFindLine->show();
        tblViewer->hide();
        showLog(config->fileToWatch[mode - 3]);
      }
      else if (cbbLog->currentText() == "Add a new log")
        addLog();
    }
  }

  void LogView::showDmesg() {
    lstLog->clear();
    char buf[65553];
    int bufsize = 65553;
    int cmd = 3;
    int n = klogctl(cmd, buf, bufsize);
    fillList(buf);
  }

  void LogView::showLog(QString path) {
    QString tmpFile;
    if(KIO::NetAccess::download(path, tmpFile, this)) {
      QFile file(tmpFile);
      file.open(QIODevice::ReadOnly);
      QString content = QTextStream(&file).readAll();
      fillList(content);
      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else
      lstLog->addItem("Permission denied");
  }
  
  void LogView::fillList(QString text) {
    while (text.isEmpty() == false) {
      if (text.indexOf(0x0A) != -1) {
        lstLog->addItem(text.left(text.indexOf(0x0A)));
        text = text.right(text.size() - text.indexOf(0x0A) -1);
      }
      else {
        lstLog->addItem(text);
        text.clear();
      }
    }
  }
  
  void LogView::addLog() {
    config->fileToWatch << KFileDialog::getOpenFileName();
    config->writeConfig();
  }
  
  void LogView::setupGraph() {
    QHBoxLayout* aLayout = new QHBoxLayout;
    graphWidget->setLayout(aLayout);
  
    //Pie graph
    QGraphicsScene* scene2 = new QGraphicsScene;
    QGraphicsView* aGraphicView2 = new QGraphicsView(scene2);
    aGraphicView2->setMaximumSize(200,131);
    aGraphicView2->setMinimumSize(200,131);
    aLayout->addWidget(aGraphicView2);
    
    QBrush brushArray[7] = {QBrush(QColor("#ffdd11")),QBrush(QColor("#ff1111")),QBrush(QColor("#f4a111")),QBrush(QColor("#00ff11")),QBrush(QColor("#ff1961")),QBrush(QColor("#ff00ff")),QBrush(QColor("#0000ff"))};
    
    for (int i =0; i < 7; i++) {
      QGraphicsRectItem* anItem = new QGraphicsRectItem(110,(i*15),10,10);
      anItem->setBrush(brushArray[i]);
      scene2->addItem(anItem);
      (scene2->addText("ls"))->setPos(125,(i*15)-6);
    }
    
    QGraphicsRectItem* anItem2 = new QGraphicsRectItem(183,0,12,12);
    scene2->addItem(anItem2);
    
    QGraphicsEllipseItem* anEclipse = new QGraphicsEllipseItem(5,0,100,100);
    anEclipse->setBrush(brushArray[0]);
    anEclipse->setStartAngle(180*16);
    anEclipse->setSpanAngle(270*16);
    scene2->addItem(anEclipse);
    
    QGraphicsEllipseItem* anEclipse2 = new QGraphicsEllipseItem(5,0,100,100);
    anEclipse2->setBrush(brushArray[1]);
    anEclipse2->setStartAngle(90*16);
    anEclipse2->setSpanAngle(90*16);
    scene2->addItem(anEclipse2);
    

    //Historygram
    const int monthNumber = 12;
    const int barWidth =25;
    const int margin = 30;
    const int spacing = 30;
    
    QGraphicsScene* scene = new QGraphicsScene;
    QBrush aBrush(QColor("#3333dd"));
    QBrush aBrush2(QColor("#cccccc"));
    QFont aFont;
    aFont.setPixelSize(8);
    scene->addLine(25, 5, 25, 100,QPen(aBrush2,2));
    scene->addLine(25, 103, monthNumber*spacing+margin, 103,QPen(aBrush2,2));
    QGraphicsTextItem* cpuLabel = scene->addText("command");
    cpuLabel->setPos(3,95);
    cpuLabel->rotate(270);
    char fakeProsess[monthNumber] = {74,82,68,57,25,58,82,90,26,92,90,90};
    QString month[12] = {"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
    for (int i =0; i < monthNumber; i++) {
      QGraphicsRectItem* anItem = new QGraphicsRectItem((i*spacing)+margin,100 - fakeProsess[i],barWidth,fakeProsess[i]);
      anItem->setBrush(aBrush);
      anItem->setToolTip(QString::number(fakeProsess[i]));
      scene->addItem(anItem);
      scene->addLine((i*spacing)+margin+(barWidth/2), 101, (i*spacing)+margin+(barWidth/2), 105,QPen(aBrush2,2));
      (scene->addText(month[i]))->setPos((i*spacing+margin)-2,103);
    }
    
   
   
    
    QGraphicsView* aGraphicView = new QGraphicsView(scene);
    aGraphicView->setMaximumSize(99999,131);
    aGraphicView->setMinimumSize(0,131);
    aGraphicView->setAlignment(Qt::AlignLeft);
    
    aLayout->addWidget(aGraphicView);
  }
  
  void LogView::delayChanged(int delay) {
    if (delay == 0) {
      sldLenght->setToolTip("Day");
      //sldLenght->showToolTip();
    }
    else if (delay == 1) {
      sldLenght->setToolTip("Week");
      //sldLenght->showToolTip();
    }
    else if (delay == 2) {
      sldLenght->setToolTip("Month");
      //sldLenght->showToolTip();
    }
    else if (delay == 3) {
      sldLenght->setToolTip("Year");
      //sldLenght->showToolTip();
    }
    else if (delay == 4) {
      sldLenght->setToolTip("Ever");
      //sldLenght->showToolTip();
    }
  }