#include "advancedScriptManager.h"
#include <QGridLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QScrollArea>
#include <QtSql>
#include <QSqlDatabase>
#include <QDateTime>
#include <KStandardDirs>
#include <QHeaderView>
#include "miniClasses.h"

  AdvancedScriptManager::AdvancedScriptManager(QWidget* parent) : QWidget(parent) {
    
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    setLayout(hLayout);
    
    QVBoxLayout* vLayout2 = new QVBoxLayout(this);
    hLayout->addLayout(vLayout2);
    
    lstCategories = new QListWidget;
    lstCategories->setMaximumSize(200,9999);
    lstCategories->setMinimumSize(0,0);
    vLayout2->addWidget(lstCategories);
    
    addScript = new KPushButton;
    addScript->setText("Add Script");
    vLayout2->addWidget(addScript);
    
    manageCategories = new KPushButton;
    manageCategories->setText("Manage Categories");
    vLayout2->addWidget(manageCategories);
    
    
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    hLayout->addLayout(vLayout);
    
    tblScript = new QTableWidget;
    if (tblScript->columnCount() < 7)
      tblScript->setColumnCount(7);
    tblScript->verticalHeader()->hide();
    tblScript->setSelectionBehavior(QAbstractItemView::SelectRows);
    vLayout->addWidget(tblScript);
    
    tabDetails = new QTabWidget;
    tabDetails->setMaximumSize(9999,175);
    vLayout->addWidget(tabDetails);
    
    tabDescriptionContent = new QWidget;
    tabDetails->addTab(tabDescriptionContent, "Description");
    
    QVBoxLayout* vLayout3 = new QVBoxLayout(tabDescriptionContent);
    tabDescriptionContent->setLayout(vLayout3);
    
    lblDescription = new QLabel();
    lblDescription->setAlignment(Qt::AlignTop);
    lblDescription->setWordWrap(true);
    
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setFrameShape(QFrame::StyledPanel);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(lblDescription);
    vLayout3->addWidget(scrollArea);
    
    
    tabInfoContent = new QWidget;
    tabDetails->addTab(tabInfoContent, "Information");
    
    QGridLayout* aGridLayout = new QGridLayout();
    tabInfoContent->setLayout(aGridLayout);
    
    lblName = new QLabel("<b>Script name: </b>");
    lblName->setWordWrap(true);
    aGridLayout->addWidget(lblName,0,0);
    lblNameValue = new QLabel();
    lblNameValue->setWordWrap(true);
    aGridLayout->addWidget(lblNameValue,0,1);
    
    lblExecNb = new QLabel("<b>Executed: </b>");
    lblExecNb->setWordWrap(true);
    aGridLayout->addWidget(lblExecNb,1,0);
    lblExecNbValue = new QLabel("0 time");
    lblExecNbValue->setWordWrap(true);
    aGridLayout->addWidget(lblExecNbValue,1,1);

    lblCreation = new QLabel("<b>Created: </b>");
    lblCreation->setWordWrap(true);
    aGridLayout->addWidget(lblCreation,0,2);
    lblCreationValue = new QLabel();
    lblCreationValue->setWordWrap(true);
    aGridLayout->addWidget(lblCreationValue,0,3);
    
    lblNbEdition = new QLabel("<b>Edited: </b>");
    lblNbEdition->setWordWrap(true);
    aGridLayout->addWidget(lblNbEdition,1,2);
    lblNbEditionValue = new QLabel("0 time");
    lblNbEditionValue->setWordWrap(true);
    aGridLayout->addWidget(lblNbEditionValue,1,3);
    
    lblLastEditDate = new QLabel("<b>Last edition: </b>");
    lblLastEditDate->setWordWrap(true);
    aGridLayout->addWidget(lblLastEditDate,2,0);
    lblLastEditDateValue = new QLabel();
    lblLastEditDateValue->setWordWrap(true);
    aGridLayout->addWidget(lblLastEditDateValue,2,1);
    
    lblMoyExecTime = new QLabel("<b>Moy. exec time:");
    lblMoyExecTime->setWordWrap(true);
    aGridLayout->addWidget(lblMoyExecTime,2,2);
    lblMoyExecTimeValue = new QLabel();
    lblMoyExecTimeValue->setWordWrap(true);
    aGridLayout->addWidget(lblMoyExecTimeValue,2,3);
    
    aGridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 0,4);
    
    aGridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding), 3,0);
    
    tblVersion = new QTableWidget;
    tblVersion->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblVersion->setColumnCount(2);
    tblVersion->verticalHeader()->hide();
    tabDetails->addTab(tblVersion, "Versions");
    
    tblExecute = new QTableWidget; 
    tblExecute->setColumnCount(4);
    tblExecute->verticalHeader()->hide();
    tblExecute->setSelectionBehavior(QAbstractItemView::SelectRows);
    setupHeaderLog();
    tabDetails->addTab(tblExecute, "Log");
    
    connect( lstCategories, SIGNAL( currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(loadScriptList(QListWidgetItem*, QListWidgetItem*)));
    connect( tblScript, SIGNAL( cellClicked ( int, int)), this, SLOT(scriptSelected(int, int)));
    
    loadCategories();
    setupHeader();
    setupHeaderVersion();
    lstCategories->setCurrentRow(0);
    //loadScriptList("Backup");
  }

  void AdvancedScriptManager::loadCategories() {
    QSqlQuery query;
    query.exec("SELECT NAME FROM TCATEGORIES");
    
    while (query.next()) 
      lstCategories->addItem(query.value(0).toString());
  }
  
  void AdvancedScriptManager::loadScriptList(QListWidgetItem* current, QListWidgetItem* previous) {
    setupHeader();
    QSqlQuery query;
    query.exec("SELECT TSCRIPT_KEY,NAME,DATE_CRE,DATE_MOD FROM TSCRIPT WHERE CATEGORIE = '" + lstCategories->currentItem()->text() + "'");
    int i =1;
    while (query.next())  {
        tblScript->setRowCount(i);
        QTableWidgetItem* aTableWidget = new QTableWidgetItem(query.value(1).toString());
        tblScript->setItem((i-1), 0, aTableWidget);
        tblScript->setRowHeight ((i-1), 20 );


        QDateTime aDateTime;
        
        aDateTime.setTime_t(query.value(2).toString().toUInt());
        QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(aDateTime.toString("dd/MM/yyyy hh:mm:ss"));
        tblScript->setItem((i-1), 1, aTableWidget1);
        
        aDateTime.setTime_t(query.value(3).toString().toUInt());
        QTableWidgetItem* aTableWidget2 = new QTableWidgetItem(aDateTime.toString("dd/MM/yyyy hh:mm:ss"));
        tblScript->setItem((i-1), 2, aTableWidget2);
        
        PlayButton* aPlayButton =  new PlayButton(0);
        aPlayButton->id = query.value(0).toString().toUInt();
        tblScript->setCellWidget((i-1), 4, aPlayButton);
        
        EditButton* anEditButton =  new EditButton(0);
        anEditButton->id = query.value(0).toString().toUInt();
        tblScript->setCellWidget((i-1), 5, anEditButton);
        
        RemoveButton* aRemoveButton =  new RemoveButton(0);
        aRemoveButton->id = query.value(0).toString().toUInt();
        tblScript->setCellWidget((i-1), 6, aRemoveButton);
        
        i++;
    }
    if (tblScript->rowCount() > 0) {
      tblScript->setCurrentCell(0,0);
      scriptSelected(0,0);
    }
  }
  
  void AdvancedScriptManager::setupHeader() {
    tblScript->setRowCount(0);
    tblScript->clear();
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(1, __colItem1);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(2, __colItem2);
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(3, __colItem3);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(4, __colItem4);
    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(5, __colItem5);
    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    tblScript->setHorizontalHeaderItem(6, __colItem6);
    tblScript->horizontalHeaderItem(0)->setText("Name");
    tblScript->horizontalHeaderItem(1)->setText("Created");
    tblScript->horizontalHeaderItem(2)->setText("Editied");
    tblScript->horizontalHeaderItem(3)->setText("Executed");
    tblScript->horizontalHeaderItem(4)->setText("P");
    tblScript->horizontalHeaderItem(5)->setText("E");
    tblScript->horizontalHeaderItem(6)->setText("R");
    tblScript->setColumnWidth(0,240);
    tblScript->setColumnWidth(1,100);
    tblScript->setColumnWidth(2,100);
    tblScript->setColumnWidth(3,100);
    tblScript->setColumnWidth(4,30);
    tblScript->setColumnWidth(5,30);
    tblScript->setColumnWidth(6,30);
    
  }
  
  void AdvancedScriptManager::setupHeaderLog() {
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblExecute->setHorizontalHeaderItem(0, __colItem);
    tblExecute->horizontalHeaderItem(0)->setText("Name");
    tblExecute->setColumnWidth(0,300); //FIXME
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblExecute->setHorizontalHeaderItem(1, __colItem1);
    tblExecute->horizontalHeaderItem(1)->setText("Start");
    tblExecute->setColumnWidth(1,130);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblExecute->setHorizontalHeaderItem(2, __colItem4);
    tblExecute->horizontalHeaderItem(2)->setText("End");
    tblExecute->setColumnWidth(2,130);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblExecute->setHorizontalHeaderItem(3, __colItem2);
    tblExecute->horizontalHeaderItem(3)->setText("Output");
    tblExecute->setColumnWidth(3,80);
  }
  
  void AdvancedScriptManager::scriptSelected(int row, int coulmn) {
    QSqlQuery query;
    //sqlite3 kling.db  "create table TSCRIPT (TSCRIPT_KEY  INTEGER PRIMARY KEY, CATEGORIE TEXT, NAME TEXT, DATE_CRE TEXT, DATE_MOD TEXT, SCRIPT_DES TEXT );"
    query.exec("SELECT * FROM TSCRIPT WHERE NAME = '" + tblScript->item(row, 0)->text() + "'");
    query.next();
    QString description = query.value(5).toString();
    while (description.indexOf("@[^@") != -1)
      description.replace(description.indexOf("@[^@"), 4, "'");
    while (description.indexOf("@[^^@") != -1)
      description.replace(description.indexOf("@[^^@"), 5, 0x22);
    lblDescription->setText(description);
    displayScriptExecLog(query.value(2).toString());
    displayScriptVersion(query.value(2).toString());
    lblNameValue->setText(query.value(2).toString());
    
    QDateTime aDateTime;
        
    aDateTime.setTime_t(query.value(3).toString().toUInt());
    lblCreationValue->setText(aDateTime.toString("dd/MM/yyyy hh:mm:ss"));
    
    aDateTime.setTime_t(query.value(4).toString().toUInt());
    lblLastEditDateValue->setText(aDateTime.toString("dd/MM/yyyy hh:mm:ss"));
    
    QSqlQuery query2;
    query2.exec("SELECT COUNT(*) FROM TSCRIPT_HISTORY WHERE SCRIPT = '" + tblScript->item(row, 0)->text() + "'");
    query2.next();
    lblExecNbValue->setText(query2.value(0).toString() + " time");
  }
  
  void AdvancedScriptManager::setupHeaderVersion() {
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblVersion->setHorizontalHeaderItem(0, __colItem);
    tblVersion->horizontalHeaderItem(0)->setText("Used until");
    tblVersion->setColumnWidth(0,560); //FIXME
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblVersion->setHorizontalHeaderItem(1, __colItem2);
    tblVersion->horizontalHeaderItem(1)->setText("View");
    tblVersion->setColumnWidth(1,80); //FIXME
  }
  
  void AdvancedScriptManager::displayScriptExecLog(QString name) {
    tblExecute->clear();
    setupHeaderLog();
    tblExecute->setRowCount(0);
    unsigned int rowCount =0;
    QSqlQuery query;
    query.exec("SELECT * FROM TSCRIPT_HISTORY WHERE SCRIPT = '" + name + "'");
    QString strLine;
    int i =0;
    int totalTime = 0;
    KIcon icnEye(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png"));
    while (query.next())  {
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

      tblExecute->setRowCount(++rowCount);
      tblExecute->setItem(rowCount-1,0,anItem);
      tblExecute->setItem(rowCount-1,1,aDateStart);
      tblExecute->setItem(rowCount-1,2,aDateEnd);
      tblExecute->setCellWidget(rowCount-1, 3, btnView);
      tblExecute->setRowHeight(rowCount-1, 20);
      
      i++;
      totalTime += query.value(3).toString().toUInt() - query.value(2).toString().toUInt();
    }
    
    if (i != 0)
      lblMoyExecTimeValue->setText(QString::number(totalTime / i) + " second"); 
    else
       lblMoyExecTimeValue->setText("N/A");
  }
  
  void AdvancedScriptManager::displayScriptVersion(QString name) {
    tblVersion->clear();
    setupHeaderVersion();
    tblVersion->setRowCount(0);
    unsigned int rowCount =0;
    QSqlQuery query;
    query.exec("SELECT * FROM TSCRIPT_VERSION WHERE NAME = '" + name + "'");
    QString strLine;
    KIcon icnEye(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png"));
    int i =0;
    while (query.next())  {
      QTableWidgetItem* anItem = new QTableWidgetItem();
      QTableWidgetItem* aDate = new QTableWidgetItem();
      
      QDateTime aDateTime;
      aDateTime.setTime_t(query.value(2).toString().toUInt());
      QString date = aDateTime.toString("dd/MM/yyyy hh:mm:ss");
      
      aDate->setText(date);
      anItem->setText(query.value(1).toString());
      
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

      tblVersion->setRowCount(++rowCount);
      tblVersion->setItem(rowCount-1,0,aDate);
      tblVersion->setCellWidget(rowCount-1, 1, btnView);
      tblVersion->setRowHeight(rowCount-1, 20);
      i++;
    }
    lblNbEditionValue->setText(QString::number(i) + " time");
  }