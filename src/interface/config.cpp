#include "config.h"
#include "miniClasses.h"
#include "../shell/alias.h"
#include "../session.h"
#include "miniClasses.h"
#include "sessionEditor.h"
#include "skinDemo.h"

#include <KLocale>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QInputDialog>
#include <KLocalizedString>
#include <QtSql>
#include <QSqlDatabase>

#include <KColorCombo>
#include <QColor>
#include <QBrush>
#include <QPalette>

  Config::Config(QWidget* parent, KlingConfigSkeleton* aConfigSkeleton) : KConfigDialog(parent, "settings", aConfigSkeleton) {
    currentAliasIndex = -1;
    configSkeleton = aConfigSkeleton;
    resize(600,500);
    newAliasCount =0;
    
    generalCentral = new QWidget();
    
    QGridLayout* gridGeneral =  new QGridLayout;
    generalCentral->setLayout(gridGeneral);
    
    lstTabOrder = new QListWidget;
    gridGeneral->addWidget(lstTabOrder,0,0,1,2);
    
    btnUp = new KPushButton;
    btnUp->setText("Move up");
    btnUp->setIcon(KIcon("arrow-up"));
    gridGeneral->addWidget(btnUp,1,0);
    
    btnDown = new KPushButton;
    btnDown->setText("Move down");
    btnDown->setIcon(KIcon("arrow-down"));
    gridGeneral->addWidget(btnDown,1,1);
    
    for (int l =0; l < 5; l++) {
      if (aConfigSkeleton->terminalTabOrder == l)
        lstTabOrder->addItem("Terminal");
      else if (aConfigSkeleton->monitorTabOrder == l)
        lstTabOrder->addItem("Monitor");
      else if (aConfigSkeleton->editorTabOrder == l)
        lstTabOrder->addItem("Editor");
      else if (aConfigSkeleton->webbrowserTabOrder == l)
        lstTabOrder->addItem("Web Browser");
      else if (aConfigSkeleton->scriptManagerTabOrder == l)
        lstTabOrder->addItem("Script Manager");
    }
    
    pwiGeneral = addPage(generalCentral, i18n("General") );
    pwiGeneral->setIcon( KIcon( "configure" ) );

    //QWidget* generalCentralWidget = new QWidget();
    //QVBoxLayout *generalLayout = new QVBoxLayout;
    //generalCentralWidget->setLayout(generalLayout);
    twGeneral = new QTabWidget();

    termianlCentralWidget = new QWidget();
    QVBoxLayout *terminalLayout = new QVBoxLayout;
    termianlCentralWidget->setLayout(terminalLayout);
    twGeneral->addTab(termianlCentralWidget,QString());
    twGeneral->setTabText(0, "Terminal");


    enableTerminal = new QCheckBox();
    enableTerminal->setText("Enable terminal");
    enableTerminal->setChecked((configSkeleton->terminalTabOrder == -1) ? false : true);
    terminalLayout->addWidget(enableTerminal);

    showInTerminal = new QGroupBox();
    showInTerminal->setTitle("Enable by default in termianl");
    terminalLayout->addWidget(showInTerminal);

    gridTerminal = new QGridLayout(showInTerminal);
    ckbShowScriptBrowserTerminal = new QCheckBox();
    ckbShowScriptBrowserTerminal->setText("Script Browser");
    ckbShowScriptBrowserTerminal->setChecked(aConfigSkeleton->showScriptBrowserTerminal);
    gridTerminal->addWidget(ckbShowScriptBrowserTerminal,0,0);

    ckbShowScheduledTaskTerminal = new QCheckBox();
    ckbShowScheduledTaskTerminal->setText("Schedules task");
    ckbShowScheduledTaskTerminal->setChecked(aConfigSkeleton->showScheduledTaskTerminal);
    gridTerminal->addWidget(ckbShowScheduledTaskTerminal,1,0);

    ckbShowCommandListTerminal = new QCheckBox();
    ckbShowCommandListTerminal->setText("Command List");
    ckbShowCommandListTerminal->setChecked(aConfigSkeleton->showCommandListTerminal);
    gridTerminal->addWidget(ckbShowCommandListTerminal,2,0);

    ckbShowHistoryTerminal = new QCheckBox();
    ckbShowHistoryTerminal->setText("History");
    ckbShowHistoryTerminal->setChecked(aConfigSkeleton->showHistoryTerminal);
    gridTerminal->addWidget(ckbShowHistoryTerminal,0,1);

    ckbShowManPageTerminal = new QCheckBox();
    ckbShowManPageTerminal->setText("Man Page");
    ckbShowManPageTerminal->setChecked(aConfigSkeleton->showManPageTerminal);
    gridTerminal->addWidget(ckbShowManPageTerminal,1,1);

    QCheckBox* ckbShowDebugTerminal = new QCheckBox();
    ckbShowDebugTerminal->setText("Debug");
    ckbShowDebugTerminal->setChecked(aConfigSkeleton->showDebugTerminal);
    gridTerminal->addWidget(ckbShowDebugTerminal,2,1);

    otherTerminalOpts = new QGroupBox();
    otherTerminalOpts->setTitle("Other options");
    terminalLayout->addWidget(otherTerminalOpts);

    gridTerminalOpts = new QGridLayout(otherTerminalOpts);

    ckbEnableUIDefault = new QCheckBox();
    ckbEnableUIDefault->setText("Enable alternative command interface");
    ckbEnableUIDefault->setChecked(aConfigSkeleton->enableUIDefault);
    gridTerminalOpts->addWidget(ckbEnableUIDefault,0,0);

    ckbFmShowHidden = new QCheckBox();
    ckbFmShowHidden->setText("Show hidden file in file browser");
    ckbFmShowHidden->setChecked(aConfigSkeleton->fmShowHidden);
    gridTerminalOpts->addWidget(ckbFmShowHidden,1,0);

    ckbEnableCompleter = new QCheckBox();
    ckbEnableCompleter->setText("Use the advanced autocompleter");
    ckbEnableCompleter->setChecked(aConfigSkeleton->enableCompleter);
    gridTerminalOpts->addWidget(ckbEnableCompleter,2,0);

    terminalLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


    monitorCentralWidget = new QWidget();
    QVBoxLayout *monitorLayout = new QVBoxLayout;
    monitorCentralWidget->setLayout(monitorLayout);
    twGeneral->addTab(monitorCentralWidget,QString());
    twGeneral->setTabText(1, "Monitor");


    enableMonitor = new QCheckBox();
    enableMonitor->setText("Enable execution monitor");
    enableMonitor->setChecked((configSkeleton->monitorTabOrder == -1) ? false : true);
    monitorLayout->addWidget(enableMonitor);

    showInMonitor = new QGroupBox();
    showInMonitor->setTitle("Enable by default in monitor");
    monitorLayout->addWidget(showInMonitor);

    gridMonitor = new QGridLayout(showInMonitor);

    ckbShowScriptBrowserMonitor = new QCheckBox();
    ckbShowScriptBrowserMonitor->setText("Script Browser");
    ckbShowScriptBrowserMonitor->setChecked(aConfigSkeleton->showScriptBrowserMonitor);
    gridMonitor->addWidget(ckbShowScriptBrowserMonitor,0,0);

    ckbShowScheduledTaskMonitor = new QCheckBox();
    ckbShowScheduledTaskMonitor->setText("Schedules task");
    ckbShowScheduledTaskMonitor->setChecked(aConfigSkeleton->showScheduledTaskMonitor);
    gridMonitor->addWidget(ckbShowScheduledTaskMonitor,1,0);

    ckbShowCommandListMonitor = new QCheckBox();
    ckbShowCommandListMonitor->setText("Command List");
    ckbShowCommandListMonitor->setChecked(aConfigSkeleton->showCommandListMonitor);
    gridMonitor->addWidget(ckbShowCommandListMonitor,2,0);

    ckbShowHistoryMonitor = new QCheckBox();
    ckbShowHistoryMonitor->setText("History");
    ckbShowHistoryMonitor->setChecked(aConfigSkeleton->showHistoryMonitor);
    gridMonitor->addWidget(ckbShowHistoryMonitor,0,1);

    ckbShowManPageMonitor = new QCheckBox();
    ckbShowManPageMonitor->setText("Man Page");
    ckbShowManPageMonitor->setChecked(aConfigSkeleton->showManPageMonitor);
    gridMonitor->addWidget(ckbShowManPageMonitor,1,1);

    QCheckBox* ckbShowDebugMonitor = new QCheckBox();
    ckbShowDebugMonitor->setText("Debug");
    ckbShowDebugMonitor->setChecked(aConfigSkeleton->showDebugMonitor);
    gridMonitor->addWidget(ckbShowDebugMonitor,2,1);

    monitorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


    editorCentralWidget = new QWidget();
    QVBoxLayout *editorLayout = new QVBoxLayout;
    editorCentralWidget->setLayout(editorLayout);
    twGeneral->addTab(editorCentralWidget,QString());
    twGeneral->setTabText(2, "Editor");


    enableEditor = new QCheckBox();
    enableEditor->setText("Enable editor");
    enableEditor->setChecked((configSkeleton->editorTabOrder == -1) ? false : true);
    editorLayout->addWidget(enableEditor);

    showInEditor = new QGroupBox();
    showInEditor->setTitle("Enable by default in editor");
    editorLayout->addWidget(showInEditor);

    gridEditor = new QGridLayout(showInEditor);

    ckbShowScriptBrowserEditor = new QCheckBox();
    ckbShowScriptBrowserEditor->setText("Script Browser");
    ckbShowScriptBrowserEditor->setChecked(aConfigSkeleton->showScriptBrowserEditor);
    gridEditor->addWidget(ckbShowScriptBrowserEditor,0,0);

    ckbShowScheduledTaskEditor = new QCheckBox();
    ckbShowScheduledTaskEditor->setText("Schedules task");
    ckbShowScheduledTaskEditor->setChecked(aConfigSkeleton->showScheduledTaskEditor);
    gridEditor->addWidget(ckbShowScheduledTaskEditor,1,0);

    ckbShowCommandListEditor = new QCheckBox();
    ckbShowCommandListEditor->setText("Command List");
    ckbShowCommandListEditor->setChecked(aConfigSkeleton->showCommandListEditor);
    gridEditor->addWidget(ckbShowCommandListEditor,2,0);

    ckbShowHistoryEditor = new QCheckBox();
    ckbShowHistoryEditor->setText("History");
    ckbShowHistoryEditor->setChecked(aConfigSkeleton->showHistoryEditor);
    gridEditor->addWidget(ckbShowHistoryEditor,0,1);

    ckbShowManPageEditor = new QCheckBox();
    ckbShowManPageEditor->setText("Man Page");
    ckbShowManPageEditor->setChecked(aConfigSkeleton->showManPageEditor);
    gridEditor->addWidget(ckbShowManPageEditor,1,1);

    QCheckBox* ckbShowDebugEditor = new QCheckBox();
    ckbShowDebugEditor->setText("Debug");
    ckbShowDebugEditor->setChecked(aConfigSkeleton->showDebugEditor);
    gridEditor->addWidget(ckbShowDebugEditor,2,1);

    editorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


    webBrowserCentralWidget = new QWidget();
    QVBoxLayout *webBrowserLayout = new QVBoxLayout;
    webBrowserCentralWidget->setLayout(webBrowserLayout);
    twGeneral->addTab(webBrowserCentralWidget,QString());
    twGeneral->setTabText(3, "Web Browser");


    enableWebBrowser = new QCheckBox();
    enableWebBrowser->setText("Enable web browser");
    enableWebBrowser->setChecked((configSkeleton->webbrowserTabOrder == -1) ? false : true);
    webBrowserLayout->addWidget(enableWebBrowser);

    showInWebBrowser = new QGroupBox();
    showInWebBrowser->setTitle("Enable by default in web browser");
    webBrowserLayout->addWidget(showInWebBrowser);

    gridWebBrowser = new QGridLayout(showInWebBrowser);

    ckbShowScriptBrowserWebBrowser = new QCheckBox();
    ckbShowScriptBrowserWebBrowser->setText("Script Browser");
    ckbShowScriptBrowserWebBrowser->setChecked(aConfigSkeleton->showScriptBrowserWebBrowser);
    gridWebBrowser->addWidget(ckbShowScriptBrowserWebBrowser,0,0);

    ckbShowScheduledTaskrWebBrowser = new QCheckBox();
    ckbShowScheduledTaskrWebBrowser->setText("Schedules task");
    ckbShowScheduledTaskrWebBrowser->setChecked(aConfigSkeleton->showScheduledTaskrWebBrowser);
    gridWebBrowser->addWidget(ckbShowScheduledTaskrWebBrowser,1,0);

    ckbShowCommandListrWebBrowser = new QCheckBox();
    ckbShowCommandListrWebBrowser->setText("Command List");
    ckbShowCommandListrWebBrowser->setChecked(aConfigSkeleton->showCommandListrWebBrowser);
    gridWebBrowser->addWidget(ckbShowCommandListrWebBrowser,2,0);

    ckbShowHistoryrWebBrowser = new QCheckBox();
    ckbShowHistoryrWebBrowser->setText("History");
    ckbShowHistoryrWebBrowser->setChecked(aConfigSkeleton->showHistoryrWebBrowser);
    gridWebBrowser->addWidget(ckbShowHistoryrWebBrowser,0,1);

    ckbShowManPagerWebBrowser = new QCheckBox();
    ckbShowManPagerWebBrowser->setText("Man Page");
    ckbShowManPagerWebBrowser->setChecked(aConfigSkeleton->showManPagerWebBrowser);
    gridWebBrowser->addWidget(ckbShowManPagerWebBrowser,1,1);

    QCheckBox* ckbShowDebugWebBrowser = new QCheckBox();
    ckbShowDebugWebBrowser->setText("Debug");
    ckbShowDebugWebBrowser->setChecked(aConfigSkeleton->showDebugWebBrowser);
    gridWebBrowser->addWidget(ckbShowDebugWebBrowser,2,1);
    webBrowserLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //generalLayout->addWidget(twGeneral);
    
    managerCentralWidget = new QWidget();
    
    gridManager = new QGridLayout;
    managerCentralWidget->setLayout(gridManager);
    
    ckbEnableManager = new QCheckBox;
    ckbEnableManager->setText("Enable script manager");
    ckbEnableManager->setChecked((configSkeleton->scriptManagerTabOrder == -1) ? false : true);
    gridManager->addWidget(ckbEnableManager,0,0);
    
    twGeneral->addTab(managerCentralWidget,QString());
    twGeneral->setTabText(4, "Script Manager");

    pwiMode = addPage(twGeneral, i18n("Mode") );
    pwiMode->setIcon( KIcon( "fork" ) );
    
    QTabWidget* termTabWidget = new QTabWidget();
    
    QWidget* aliasTab = new QWidget();
    QGridLayout* gridAlias = new QGridLayout;
    aliasTab->setLayout(gridAlias);
    
    QGridLayout* gridAliasList = new QGridLayout;
    
    QGroupBox* grbAliasList = new QGroupBox();
    grbAliasList->setTitle("Alias list");
    grbAliasList->setLayout(gridAliasList);
    
    btnAddAlias = new KPushButton();
    btnAddAlias->setText("Add");
    btnAddAlias->setIcon(KIcon("list-add"));
    gridAliasList->addWidget(btnAddAlias,0,1);
    
    btnRemoveAlias = new KPushButton();
    btnRemoveAlias->setText("Remove");
    btnRemoveAlias->setIcon(KIcon("list-remove"));
    gridAliasList->addWidget(btnRemoveAlias,1,1);
    
    gridAliasList->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding),2,1);
    
    tblAlias = new QTableWidget();
    tblAlias->setColumnCount(3);
    tblAlias->verticalHeader()->hide();
    tblAlias->horizontalHeader()->hide();
    tblAlias->setSelectionBehavior(QAbstractItemView::SelectRows);
    //QSqlQuery query;
    //query.exec("SELECT ALIAS,COMMAND,TALIAS_KEY,ENABLE FROM TALIAS");
    //int i =1;
    int largestAlias =0;
    int largestArgsSet =0;
    /*while (query.next())  {
      tblAlias->setRowCount(i);
      tblAlias->setRowHeight(i-1,20);
      if (query.value(0).toString().count() > largestAlias)
        largestAlias = query.value(0).toString().count();
      
      QCheckBox* aCheckBox = new QCheckBox;
      aCheckBox->setToolTip("Enable");
      tblAlias->setCellWidget(i-1, 0, aCheckBox);
      
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(query.value(0).toString());
      tblAlias->setItem(i-1,1,aTableWidget);
      QString args;
      QSqlQuery query2;
      query2.exec("SELECT ARGS FROM TARGS WHERE PARENT = '"+ query.value(2).toString() +"' AND TYPE = 1");
      while (query2.next()) {
	args += " " + query2.value(0).toString();
      }
      
      if (args.count() > largestArgsSet)
        largestArgsSet = args.count();
      QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(query.value(1).toString() + " " + args);
      tblAlias->setItem(i-1,2,aTableWidget1);
      
      aCheckBox->setChecked(query.value(3).toBool());
      i++;
    }*/
    
          
    aliasList = *Alias::getAlias();
    
    for (int i =0; i < aliasList.count(); i++) {
      tblAlias->setRowCount(i);
      tblAlias->setRowHeight(i-1,20);
      if (aliasList[i].getName().count() > largestAlias)
        largestAlias = aliasList[i].getName().count();
      
      AliasCheckBox* aCheckBox = new AliasCheckBox(0);
      aCheckBox->id = aliasList[i].getKey();
      aCheckBox->setToolTip("Enable");
      tblAlias->setCellWidget(i-1, 0, aCheckBox);
      
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(aliasList[i].getName());
      tblAlias->setItem(i-1,1,aTableWidget);
      
      QString args;
      QVector<QString> argList = aliasList[i].getArgs();
      for (int j=0; j < argList.count(); j++) {
        args += " " + argList[j];
      }
      
      if (args.count() > largestArgsSet)
        largestArgsSet = args.count();
      QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(aliasList[i].getCommand() + " " + args);
      tblAlias->setItem(i-1,2,aTableWidget1);
      
      aCheckBox->setChecked(aliasList[i].getEnable());
    }
    
    tblAlias->setColumnWidth(0,20);
    tblAlias->setColumnWidth(1, largestAlias*10);
    tblAlias->setColumnWidth(2, largestArgsSet*10);
    gridAliasList->addWidget(tblAlias,0,0,3,1);
    
    gridAlias->addWidget(grbAliasList,0,0);
        
    QGridLayout* gridAliasOpt = new QGridLayout;
    
    grbAliasOpt = new QGroupBox();
    grbAliasOpt->setTitle("Alias Options");
    grbAliasOpt->setLayout(gridAliasOpt);
    grbAliasOpt->setDisabled(true);
    gridAlias->addWidget(grbAliasOpt,1,0);
    
    txtCommand = new KLineEdit();
    gridAliasOpt->addWidget(txtCommand,0,0,1,2);
    
    lstAliasArgs = new QListWidget();
    gridAliasOpt->addWidget(lstAliasArgs,1,0,1,2);
    
    btnAddAliasArgs = new KPushButton();
    btnAddAliasArgs->setText("Add");
    btnAddAliasArgs->setIcon(KIcon("list-add"));
    gridAliasOpt->addWidget(btnAddAliasArgs,2,0);
    
    btnRemoveAliasArgs = new KPushButton();
    btnRemoveAliasArgs->setText("Remove");
    btnRemoveAliasArgs->setIcon(KIcon("list-remove"));
    gridAliasOpt->addWidget(btnRemoveAliasArgs,2,1);
    
    termTabWidget->addTab(aliasTab,"Alias");
    
    tblCmdDefaultArgs = new QTableWidget();
    tblCmdDefaultArgs->setColumnCount(7);
    tblCmdDefaultArgs->verticalHeader()->hide();
    tblCmdDefaultArgs->setSelectionBehavior(QAbstractItemView::SelectRows);
    QSqlQuery query2;
    query2.exec("SELECT COMMAND,TDEFAULT_ARGS_KEY,ENABLE FROM TDEFAULT_ARGS");
    int j =1;
    while (query2.next())  {
      tblCmdDefaultArgs->setRowCount(j);
      tblCmdDefaultArgs->setRowHeight(j-1,20);
      
      RemoveButton* aRemoveButton = new RemoveButton(0);
      aRemoveButton->id = j-1;
      tblCmdDefaultArgs->setCellWidget(j-1,0,aRemoveButton);
      connect(aRemoveButton , SIGNAL( clicked(int) ), tblCmdDefaultArgs, SLOT( removeRow(int) ));
      
      QCheckBox* aCheckBox = new QCheckBox;
      aCheckBox->setToolTip("Enable");
      tblCmdDefaultArgs->setCellWidget(j-1, 1, aCheckBox);
      
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(query2.value(0).toString());
      tblCmdDefaultArgs->setItem(j-1,2,aTableWidget);
      QSqlQuery query3;
      query3.exec("SELECT ARGS FROM TARGS WHERE PARENT = '"+ query2.value(1).toString() +"' AND TYPE = 2");
      int k =3;
      while (query3.next()) {
	QTableWidgetItem* aTableWidget2 = new QTableWidgetItem(query3.value(0).toString());
	tblCmdDefaultArgs->setItem(j-1,k,aTableWidget2);
	k++;
      }
      
      aCheckBox->setChecked(query2.value(2).toBool());
      j++;
    }
    
    tblCmdDefaultArgs->setColumnWidth(0,25);
    tblCmdDefaultArgs->setColumnWidth(1,25);
    
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(2, __colItem);
    tblCmdDefaultArgs->horizontalHeaderItem(2)->setText("Command");
    
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(3, __colItem1);
    tblCmdDefaultArgs->horizontalHeaderItem(3)->setText("Arg 1");
    
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(4, __colItem2);
    tblCmdDefaultArgs->horizontalHeaderItem(4)->setText("Arg 2");
    
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(5, __colItem3);
    tblCmdDefaultArgs->horizontalHeaderItem(5)->setText("Arg 3");
    
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(6, __colItem4);
    tblCmdDefaultArgs->horizontalHeaderItem(6)->setText("Arg 4");
    
    termTabWidget->addTab(tblCmdDefaultArgs,"Default Args");
    
    QWidget* functionTab = new QWidget();
    termTabWidget->addTab(functionTab,"Function");
    
    QGridLayout* gridFunction = new QGridLayout();
    functionTab->setLayout(gridFunction);
    
    lstFunctionList = new QListWidget();
    gridFunction->addWidget(lstFunctionList,0,0,2,1);
    
    btnAddFunction = new KPushButton();
    btnAddFunction->setText("Add");
    btnAddFunction->setIcon(KIcon("list-add"));
    gridFunction->addWidget(btnAddFunction,0,1);
    
    btnRemoveFunction = new KPushButton();
    btnRemoveFunction->setText("Remove");
    btnRemoveFunction->setIcon(KIcon("list-remove"));
    gridFunction->addWidget(btnRemoveFunction,1,1);
    
    //gridFunction->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding),2,1);
   
    QGroupBox* grbFunctionBody = new QGroupBox;
    grbFunctionBody->setTitle("Body");
    gridFunction->addWidget(grbFunctionBody,2,0,1,2);
    
    QGridLayout* gridFunctionBody = new QGridLayout();
    grbFunctionBody->setLayout(gridFunctionBody);
    
    rtfFunctionEditor = new KTextEdit();
    gridFunctionBody->addWidget(rtfFunctionEditor,0,0);

    QSizePolicy sizePolicy1(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QSizePolicy sizePolicy2(QSizePolicy::Expanding,QSizePolicy::Expanding);
    
    QWidget* completerTab = new QWidget();
    termTabWidget->addTab(completerTab,"Completer");
    
    QGridLayout* gridCompleter = new QGridLayout();
    completerTab->setLayout(gridCompleter);
    
    grbList = new QGroupBox();
    grbList->setTitle("Strings");
    gridCompleter->addWidget(grbList);
    
    QGridLayout* gridString = new QGridLayout();
    grbList->setLayout(gridString);
    
    grbRules = new QGroupBox();
    grbRules->setTitle("Rules");
    gridCompleter->addWidget(grbRules);
    
    QGridLayout* gridRules = new QGridLayout();
    grbRules->setLayout(gridRules);
    
    tblString = new QTableWidget();
    gridString->addWidget(tblString,0,0,1,2);
    
    btnAddString = new QPushButton();
    btnAddString->setText("Add");
    gridString->addWidget(btnAddString,1,0);
    
    btnDelString = new QPushButton();
    btnDelString->setText("Remove");
    gridString->addWidget(btnDelString,1,1);
    
    lstRules = new QListWidget();
    gridRules->addWidget(lstRules,0,0,1,3);
    
    btnAddRules = new QPushButton();
    btnAddRules->setText("Add");
    gridRules->addWidget(btnAddRules,1,0,1,1);
    
    btnDelRules = new QPushButton();
    btnDelRules->setText("Remove");
    gridRules->addWidget(btnDelRules,1,1,1,1);
    
    btnEditRules = new QPushButton();
    btnEditRules->setText("Edit");
    gridRules->addWidget(btnEditRules,1,2,1,1);
    
    QWidget* sessionTab = new QWidget();
    termTabWidget->addTab(sessionTab,"Session");

    QGridLayout* gridSession = new QGridLayout();
    sessionTab->setLayout(gridSession);

    lstSession = new QListWidget();
    gridSession->addWidget(lstSession,0,0,1,3);
    
    QSqlQuery query55;
    query55.exec("SELECT * FROM TSESSION");
    
    while (query55.next()) {
      SessionListItem* anItem = new SessionListItem();
      Session* aSession = new Session(query55.value(0).toString().toInt(),query55.value(1).toString());
      anItem->aSession = aSession;
      anItem->setText(query55.value(1).toString());
      lstSession->addItem(anItem);
    }
    
    btnAddSession = new QPushButton();
    btnAddSession->setText("Add");
    gridSession->addWidget(btnAddSession,1,0);
    
    btnDelSession = new QPushButton();
    btnDelSession->setText("Remove");
    gridSession->addWidget(btnDelSession,1,1);
    
    btnEditSession = new QPushButton();
    btnEditSession->setText("Edit");
    gridSession->addWidget(btnEditSession,1,2);
    
    pwiTerm = addPage(termTabWidget, i18n("Terminal") );
    pwiTerm->setIcon( KIcon( "utilities-terminal" ) );

    QWidget* loggingCentralWidget = new QWidget();
    gridLogging = new QGridLayout();
    loggingCentralWidget->setLayout(gridLogging);

    ckbEnableLogging = new QCheckBox();
    ckbEnableLogging->setText("Enable output logging");
    gridLogging->addWidget(ckbEnableLogging,0,0);
    
    lblMb = new QLabel();
    lblMb->setText("Amount of data to keep: ");
    gridLogging->addWidget(lblMb,1,0);

    spinMb = new QSpinBox();
    spinMb->setSuffix("mb");
    spinMb->setValue(aConfigSkeleton->ammountToKeep);
    gridLogging->addWidget(spinMb,1,1);

    lblMaxOutputSize = new QLabel();
    lblMaxOutputSize->setText("Keep command output smaller than: ");
    gridLogging->addWidget(lblMaxOutputSize,2,0);

    spinMaxOutputSize = new QSpinBox();
    spinMaxOutputSize->setValue(aConfigSkeleton->maxOutputSize);
    spinMaxOutputSize->setSuffix("kb");
    gridLogging->addWidget(spinMaxOutputSize,2,1);

    ckbAddToBash = new QCheckBox();
    ckbAddToBash->setText("Append to bash history");
    gridLogging->addWidget(ckbAddToBash,3,0);

    btnCleanLog = new KPushButton();
    btnCleanLog->setText("Clear log now");
    gridLogging->addWidget(btnCleanLog,4,0);

    btnClearHistory = new KPushButton();
    btnClearHistory->setText("Clear history now");
    gridLogging->addWidget(btnClearHistory,4,1);

    lblExclude = new QLabel();
    lblExclude->setText("Exclude from advanced logging:");
    gridLogging->addWidget(lblExclude, 5,0);

    lstExclude = new QListWidget();
    lstExclude->addItems(aConfigSkeleton->logExcludeList);
    gridLogging->addWidget(lstExclude,6,0,1,2);

    QHBoxLayout* anHLayout = new QHBoxLayout();
    btnAddExcludedCommand = new KPushButton();
    btnAddExcludedCommand->setText("Add");
    btnAddExcludedCommand->setIcon(KIcon("list-add"));
    anHLayout->addWidget(btnAddExcludedCommand);

    btnRemoveExcludedCommand = new KPushButton();
    btnRemoveExcludedCommand->setText("Remove");
    btnRemoveExcludedCommand->setIcon(KIcon("list-remove"));
    anHLayout->addWidget(btnRemoveExcludedCommand);
    anHLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum));
    gridLogging->addLayout(anHLayout,7,0,1,2);
   
    gridLogging->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding),3,0);
    pwiLogging = addPage(loggingCentralWidget, i18n("Logging") );
    pwiLogging->setIcon( KIcon( "chronometer" ) );

    QTabWidget* tabAppearance = new QTabWidget();
    
    QWidget* tabTerminalAppearance = new QWidget();
    tabAppearance->addTab(tabTerminalAppearance,"Terminal");
    QVBoxLayout *terminal3Layout = new QVBoxLayout;
    tabTerminalAppearance->setLayout(terminal3Layout);
    
    grbTerminalAppearence = new QGroupBox;
    grbTerminalAppearence->setTitle("Skin");
    grbTerminalAppearence->setCheckable(true);
    QVBoxLayout *terminal2Layout = new QVBoxLayout;
    grbTerminalAppearence->setLayout(terminal2Layout);
    
    tblTerminalAppearence = new QTableWidget;
    tblTerminalAppearence->setRowCount(10);
    tblTerminalAppearence->setColumnCount(2);
    tblTerminalAppearence->setColumnWidth(0,230);
    tblTerminalAppearence->setColumnWidth(1,140);
    tblTerminalAppearence->verticalHeader()->hide();
    tblTerminalAppearence->horizontalHeader()->hide();
    
    QPalette aPalette;
    SkinDemo* aSkinDemo1 = new SkinDemo(this,aPalette.base().color().name(),aPalette.text().color().name(),12,"arial",false,"#008000","#C5C5C5");
    tblTerminalAppearence->setCellWidget(0,1,aSkinDemo1);
    QTableWidgetItem* aTableWidget343 = new QTableWidgetItem("Default");
    tblTerminalAppearence->setItem(0,0,aTableWidget343);
    
    SkinDemo* aSkinDemo5 = new SkinDemo(this,"#FFFFFF","#000000",12,"courrier",false,"#008000","#252525");
    tblTerminalAppearence->setCellWidget(1,1,aSkinDemo5);
    QTableWidgetItem* aTableWidget349 = new QTableWidgetItem("Light");
    tblTerminalAppearence->setItem(1,0,aTableWidget349);
    
    SkinDemo* aSkinDemo2 = new SkinDemo(this,"#000000","#00FF00",12,"courrier",false,"#FFFFFF","#FFFFFF");
    tblTerminalAppearence->setCellWidget(2,1,aSkinDemo2);
    QTableWidgetItem* aTableWidget344 = new QTableWidgetItem("Old School");
    tblTerminalAppearence->setItem(2,0,aTableWidget344);
    
    SkinDemo* aSkinDemo3 = new SkinDemo(this,"#000000","#FF4400",12,"courrier",false,"#FF0000","#BB0000");
    tblTerminalAppearence->setCellWidget(3,1,aSkinDemo3);
    QTableWidgetItem* aTableWidget345 = new QTableWidgetItem("Blood");
    tblTerminalAppearence->setItem(3,0,aTableWidget345);
    
    SkinDemo* aSkinDemo6 = new SkinDemo(this,"#000000","#DDDDDD",12,"courrier",false,"#008000","#C5C5C5");
    tblTerminalAppearence->setCellWidget(4,1,aSkinDemo6);
    QTableWidgetItem* aTableWidget346 = new QTableWidgetItem("Dark");
    tblTerminalAppearence->setItem(4,0,aTableWidget346);
    
    SkinDemo* aSkinDemo7 = new SkinDemo(this,"#F7F799","#111111",12,"courrier",false,"#008000","#252525");
    tblTerminalAppearence->setCellWidget(5,1,aSkinDemo7);
    QTableWidgetItem* aTableWidget347 = new QTableWidgetItem("Soft");
    tblTerminalAppearence->setItem(5,0,aTableWidget347);
    
    terminal2Layout->addWidget(tblTerminalAppearence);
    terminal3Layout->addWidget(grbTerminalAppearence);
    
    
    grbCustomTerminalAppearence = new QGroupBox;
    grbCustomTerminalAppearence->setTitle("Custom Skin");
    grbCustomTerminalAppearence->setCheckable(true);
    QVBoxLayout *customTerminalLayout = new QVBoxLayout;
    grbCustomTerminalAppearence->setLayout(customTerminalLayout);
    
    tblCustomTerminalAppearence = new QTableWidget;
    customTerminalLayout->addWidget(tblCustomTerminalAppearence);
    terminal3Layout->addWidget(grbCustomTerminalAppearence);
    tblCustomTerminalAppearence->setRowCount(10);
    tblCustomTerminalAppearence->setColumnCount(2);
    tblCustomTerminalAppearence->setColumnWidth(0,280);
    tblCustomTerminalAppearence->setColumnWidth(1,90);
    tblCustomTerminalAppearence->verticalHeader()->hide();
    tblCustomTerminalAppearence->horizontalHeader()->hide();
    
    QTableWidgetItem* aTableWidget = new QTableWidgetItem("Background color");
    tblCustomTerminalAppearence->setItem(0,0,aTableWidget);
    tblCustomTerminalAppearence->setRowHeight(0,18);
    KColorCombo* backgroundColor = new KColorCombo();
    tblCustomTerminalAppearence->setCellWidget(0,1,backgroundColor);
    
    QTableWidgetItem* aTableWidget1 = new QTableWidgetItem("Text color");
    tblCustomTerminalAppearence->setItem(1,0,aTableWidget1);
    tblCustomTerminalAppearence->setRowHeight(1,18);
    KColorCombo* textColor = new KColorCombo();
    tblCustomTerminalAppearence->setCellWidget(1,1,textColor);
    textColor->setCurrentIndex(17);
    textColor->repaint();
    
    QWidget* tabEditorAppearance = new QWidget();
    tabAppearance->addTab(tabEditorAppearance,"Editor");
    QVBoxLayout *editor3Layout = new QVBoxLayout;
    tabEditorAppearance->setLayout(editor3Layout);
    
    grbEditorAppearence = new QGroupBox;
    grbEditorAppearence->setTitle("Skin");
    grbEditorAppearence->setCheckable(true);
    QVBoxLayout *editor2Layout = new QVBoxLayout;
    grbEditorAppearence->setLayout(editor2Layout);
    
    tblEditorAppearence = new QTableWidget;
    editor2Layout->addWidget(tblEditorAppearence);
    editor3Layout->addWidget(grbEditorAppearence);
    tblEditorAppearence->setColumnCount(2);
    tblEditorAppearence->setRowCount(10);
    
    grbCustomEditorAppearence = new QGroupBox;
    grbCustomEditorAppearence->setTitle("Custom Skin");
    grbCustomEditorAppearence->setCheckable(true);
    QVBoxLayout *customEditorLayout = new QVBoxLayout;
    grbCustomEditorAppearence->setLayout(customEditorLayout);
    
    tblCustomEditorAppearence = new QTableWidget;
    customEditorLayout->addWidget(tblCustomEditorAppearence);
    editor3Layout->addWidget(grbCustomEditorAppearence);
    tblCustomEditorAppearence->setRowCount(10);
    tblCustomEditorAppearence->setColumnCount(2);
    tblCustomEditorAppearence->setColumnWidth(0,280);
    tblCustomEditorAppearence->setColumnWidth(1,90);
    tblCustomEditorAppearence->verticalHeader()->hide();
    tblCustomEditorAppearence->horizontalHeader()->hide();
    
    QTableWidgetItem* aTableWidget2 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(0,0,aTableWidget2);
    tblCustomEditorAppearence->setRowHeight(0,18);
    KColorCombo* backgroundColor2 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(0,1,backgroundColor2);
    
    QTableWidgetItem* aTableWidget3 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(1,0,aTableWidget3);
    tblCustomEditorAppearence->setRowHeight(1,18);
    KColorCombo* backgroundColor3 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(1,1,backgroundColor3);
    
    QTableWidgetItem* aTableWidget4 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(2,0,aTableWidget4);
    tblCustomEditorAppearence->setRowHeight(2,18);
    KColorCombo* backgroundColor4 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(2,1,backgroundColor4);
    
    QTableWidgetItem* aTableWidget5 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(3,0,aTableWidget5);
    tblCustomEditorAppearence->setRowHeight(3,18);
    KColorCombo* backgroundColor5 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(3,1,backgroundColor5);
    
    QTableWidgetItem* aTableWidget6 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(4,0,aTableWidget6);
    tblCustomEditorAppearence->setRowHeight(4,18);
    KColorCombo* backgroundColor6 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(4,1,backgroundColor6);
    
    QTableWidgetItem* aTableWidget7 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(5,0,aTableWidget7);
    tblCustomEditorAppearence->setRowHeight(5,18);
    KColorCombo* backgroundColor7 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(5,1,backgroundColor7);
    
    QTableWidgetItem* aTableWidget8 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(6,0,aTableWidget8);
    tblCustomEditorAppearence->setRowHeight(6,18);
    KColorCombo* backgroundColor8 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(6,1,backgroundColor8);
    
    QTableWidgetItem* aTableWidget9 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(7,0,aTableWidget9);
    tblCustomEditorAppearence->setRowHeight(7,18);
    KColorCombo* backgroundColor9 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(7,1,backgroundColor9);
    
    QTableWidgetItem* aTableWidget10 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(8,0,aTableWidget10);
    tblCustomEditorAppearence->setRowHeight(8,18);
    KColorCombo* backgroundColor10 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(8,1,backgroundColor10);
    
    QTableWidgetItem* aTableWidget11 = new QTableWidgetItem("Background color");
    tblCustomEditorAppearence->setItem(9,0,aTableWidget11);
    tblCustomEditorAppearence->setRowHeight(9,18);
    KColorCombo* backgroundColor11 = new KColorCombo();
    tblCustomEditorAppearence->setCellWidget(9,1,backgroundColor11);
    
    pwiAppearance = addPage(tabAppearance, i18n("Appearance") );
    pwiAppearance->setIcon( KIcon( "format-text-color" ) );

    QWidget* pluginCentralWidget = new QWidget();
    QHBoxLayout *pluginLayout = new QHBoxLayout;
    pluginCentralWidget->setLayout(pluginLayout);

    pluginList = new QListWidget();
    pluginLayout->addWidget(pluginList);

    QVBoxLayout *pluginButtonLayout = new QVBoxLayout;
    pluginLayout->addLayout(pluginButtonLayout);
    btnAddPlugin = new KPushButton();
    btnAddPlugin->setText("Add");
    btnAddPlugin->setStyleSheet("text-align:left;");
    btnAddPlugin->setIcon(KIcon("list-add"));
    pluginButtonLayout->addWidget(btnAddPlugin);
    btnRemovePlugin = new KPushButton();
    btnRemovePlugin->setText("Remove");
    btnRemovePlugin->setStyleSheet("text-align:left;");
    btnRemovePlugin->setIcon(KIcon("edit-delete"));
    pluginButtonLayout->addWidget(btnRemovePlugin);
    btnInfoPlugin = new KPushButton();
    btnInfoPlugin->setText("Information");
    btnInfoPlugin->setStyleSheet("text-align:left;");
    btnInfoPlugin->setIcon(KIcon("help-about"));
    pluginButtonLayout->addWidget(btnInfoPlugin);
    btnPluginConfig = new KPushButton();
    btnPluginConfig->setText("Configure");
    btnPluginConfig->setStyleSheet("text-align:left;");
    btnPluginConfig->setIcon(KIcon("configure"));
    pluginButtonLayout->addWidget(btnPluginConfig);
    btnDownloadPlugin = new KPushButton();
    btnDownloadPlugin->setText("Download new");
    btnDownloadPlugin->setStyleSheet("text-align:left;");
    btnDownloadPlugin->setIcon(KIcon("document-open-remote"));
    pluginButtonLayout->addWidget(btnDownloadPlugin);
    pluginButtonLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
    pwiPlugins = addPage(pluginCentralWidget, i18n("Plugins") );
    pwiPlugins->setIcon( KIcon( "vcs_add" ) );

    connect( this, SIGNAL( okClicked() ), this, SLOT( saveConfig() ) );
    connect( btnUp, SIGNAL( clicked() ), this, SLOT( moveTabUp() ) );
    connect( btnDown, SIGNAL( clicked() ), this, SLOT( moveTabDown() ) );
    connect( btnAddExcludedCommand, SIGNAL( pressed() ), this, SLOT( addLogExclude() ) );
    connect( tblAlias, SIGNAL( cellClicked ( int, int)), this, SLOT(loadAlias(int, int)));
    connect( btnAddAliasArgs, SIGNAL( clicked() ), this, SLOT(addAliasArgs()));
    connect( btnRemoveAliasArgs, SIGNAL( clicked() ), this, SLOT(removeAliasArgs()));
    connect( btnRemoveAlias, SIGNAL( clicked() ), this, SLOT(removeAlias()));
    connect( btnAddAlias, SIGNAL( clicked() ), this, SLOT(addAlias()));
    connect( btnAddSession, SIGNAL( clicked() ), this, SLOT(addSession()));
    connect( btnEditSession, SIGNAL( clicked() ), this, SLOT(editSession()));
  }
  
  void Config::moveTabUp() {
    if (lstTabOrder->currentRow() != 0) {
      QString tmp = lstTabOrder->currentItem()->text();
      lstTabOrder->item(lstTabOrder->currentRow())->setText(lstTabOrder->item(lstTabOrder->currentRow() - 1)->text());
      lstTabOrder->item(lstTabOrder->currentRow() - 1)->setText(tmp);
      lstTabOrder->setCurrentRow(lstTabOrder->currentRow() - 1);
    }
  }
  
  void Config::moveTabDown() {
    if (lstTabOrder->count() > lstTabOrder->currentRow() +1) {
      QString tmp = lstTabOrder->currentItem()->text();
      lstTabOrder->item(lstTabOrder->currentRow())->setText(lstTabOrder->item(lstTabOrder->currentRow() + 1)->text());
      lstTabOrder->item(lstTabOrder->currentRow() +1)->setText(tmp);
      lstTabOrder->setCurrentRow(lstTabOrder->currentRow() + 1);
    }
  }

  void Config::saveConfig() {
  
    for (int l =0; l < lstTabOrder->count(); l++) {
      if (lstTabOrder->item(l)->text() == "Terminal")
        configSkeleton->terminalTabOrder = l;
      else if (lstTabOrder->item(l)->text() == "Monitor")
        configSkeleton->monitorTabOrder = l;
      else if (lstTabOrder->item(l)->text() == "Editor")
        configSkeleton->editorTabOrder = l;
      else if (lstTabOrder->item(l)->text() == "Web Browser")
        configSkeleton->webbrowserTabOrder = l;
      else if (lstTabOrder->item(l)->text() == "Script Manager")
        configSkeleton->scriptManagerTabOrder = l;
    }
    //configSkeleton->enableTerminal = enableTerminal->isChecked();
    if (!enableTerminal->isChecked()) {
      configSkeleton->terminalTabOrder = -1;
    }
    else if (configSkeleton->terminalTabOrder == -1) {
      configSkeleton->terminalTabOrder = countActiveMode();
    }
    
    //configSkeleton->enableMonitor = enableMonitor->isChecked();
    if (!enableMonitor->isChecked()) {
      configSkeleton->monitorTabOrder = -1;
    }
    else if (configSkeleton->monitorTabOrder == -1) {
      configSkeleton->monitorTabOrder = countActiveMode();
    }
    //configSkeleton->enableEditor = enableEditor->isChecked();
    if (!enableEditor->isChecked()) {
      configSkeleton->editorTabOrder = -1;
    }
    else if (configSkeleton->editorTabOrder == -1) {
      configSkeleton->editorTabOrder = countActiveMode();
    }
    //configSkeleton->enableWebBrowser = enableWebBrowser->isChecked();
    if (!enableWebBrowser->isChecked()) {
      configSkeleton->webbrowserTabOrder = -1;
    }
    else if (configSkeleton->webbrowserTabOrder == -1) {
      configSkeleton->webbrowserTabOrder = countActiveMode();
    }
    
    if (!ckbEnableManager->isChecked()) {
      configSkeleton->scriptManagerTabOrder = -1;
    }
    else if (configSkeleton->webbrowserTabOrder == -1) {
      configSkeleton->scriptManagerTabOrder = countActiveMode();
    }
    
    configSkeleton->showScriptBrowserTerminal = ckbShowScriptBrowserTerminal->isChecked();
    /*if !() {
      
    }*/
    configSkeleton->showScheduledTaskTerminal = ckbShowScheduledTaskTerminal->isChecked();
    configSkeleton->showCommandListTerminal = ckbShowCommandListTerminal->isChecked();
    configSkeleton->showHistoryTerminal = ckbShowHistoryTerminal->isChecked();
    configSkeleton->showManPageTerminal = ckbShowManPageTerminal->isChecked();
    configSkeleton->enableUIDefault = ckbEnableUIDefault->isChecked();
    configSkeleton->fmShowHidden = ckbFmShowHidden->isChecked();
    configSkeleton->enableCompleter = ckbEnableCompleter->isChecked();
    configSkeleton->showScriptBrowserMonitor = ckbShowScriptBrowserMonitor->isChecked();
    configSkeleton->showScheduledTaskMonitor = ckbShowScheduledTaskMonitor->isChecked();
    configSkeleton->showCommandListMonitor = ckbShowCommandListMonitor->isChecked();
    configSkeleton->showHistoryMonitor = ckbShowHistoryMonitor->isChecked();
    configSkeleton->showManPageMonitor = ckbShowManPageMonitor->isChecked();
    configSkeleton->showScriptBrowserEditor = ckbShowScriptBrowserEditor->isChecked();
    configSkeleton->showScheduledTaskEditor = ckbShowScheduledTaskEditor->isChecked();
    configSkeleton->showCommandListEditor = ckbShowCommandListEditor->isChecked();
    configSkeleton->showHistoryEditor = ckbShowHistoryEditor->isChecked();
    configSkeleton->showManPageEditor = ckbShowManPageEditor->isChecked();
    configSkeleton->showScriptBrowserWebBrowser = ckbShowScriptBrowserWebBrowser->isChecked();
    configSkeleton->showScheduledTaskrWebBrowser = ckbShowScheduledTaskrWebBrowser->isChecked();
    configSkeleton->showCommandListrWebBrowser = ckbShowCommandListrWebBrowser->isChecked();
    configSkeleton->showHistoryrWebBrowser = ckbShowHistoryrWebBrowser->isChecked();
    configSkeleton->showManPagerWebBrowser = ckbShowManPagerWebBrowser->isChecked();
    
    configSkeleton->maxOutputSize = spinMaxOutputSize->value();
    configSkeleton->ammountToKeep = spinMb->value();
    
    configSkeleton->writeConfig();
    saveAlias();
    saveSession();

  }

  void Config::addLogExclude() {
    bool ok;
    QString text = QInputDialog::getText(this, "Exclude a command", "Exclude the following command from advance logging", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      configSkeleton->logExcludeList << text;
      configSkeleton->writeConfig();
      lstExclude->addItem(text);
    }
  }

  int Config::countActiveMode() {
    int i =0;
    if (configSkeleton->terminalTabOrder != -1)
      i++;
    if (configSkeleton->monitorTabOrder != -1)
      i++;
    if (configSkeleton->editorTabOrder != -1)
      i++;
    if (configSkeleton->webbrowserTabOrder != -1)
      i++;
    if (configSkeleton->scriptManagerTabOrder != -1)
      i++;
    return i;
  }

  void Config::loadAlias(int x, int y) {
    updateArg();
    
    lstAliasArgs->clear();
    grbAliasOpt->setEnabled(true);
    int aliasIndex = Alias::indexOf(&aliasList, ((AliasCheckBox*) tblAlias->cellWidget(tblAlias->currentRow(),0))->id);
    txtCommand->setText(aliasList[aliasIndex].getCommand());
    QVector<QString> argsList = aliasList[aliasIndex].getArgs();
    for (int i = 0; i < argsList.count(); i++) {
      lstAliasArgs->addItem(argsList[i]);
    }
    /*QString alias =tblAlias->item(x, 1)->text();
    QSqlQuery query;
    query.exec("SELECT COMMAND,TALIAS_KEY FROM TALIAS WHERE ALIAS = '"+ alias +"'");
    while (query.next())  {
      txtCommand->setText(query.value(0).toString());
      QSqlQuery query2;
      query2.exec("SELECT ARGS FROM TARGS WHERE PARENT = '"+ query.value(1).toString() +"' AND TYPE = 1");
      while (query2.next()) {
	lstAliasArgs->addItem(query2.value(0).toString());
      }
    }*/
    currentAliasIndex = tblAlias->currentRow();
  }
  
  void Config::addAliasArgs() {
    bool ok;
    QString result = QInputDialog::getText(this, "Add Argument", "Add a new argument:", QLineEdit::Normal, "", &ok);
    if (ok && !result.isEmpty()) {
      lstAliasArgs->addItem(result);
    }
  }
  
  void Config::removeAliasArgs() {
    lstAliasArgs->takeItem(lstAliasArgs->currentRow());
  }
  
  void Config::removeAlias() {
    tblAlias->removeRow(tblAlias->currentRow());
  }
  
  void Config::addAlias() {
    bool ok;
    QString result = QInputDialog::getText(this, "Add Alias", "Add a new alias:", QLineEdit::Normal, "", &ok);
    if (ok && !result.isEmpty()) {
      Alias* aNewAlias = new Alias();
      aNewAlias->setName(result);
      aNewAlias->setKey(--newAliasCount);
      aliasList.push_back(*aNewAlias);
      
      tblAlias->setRowCount(tblAlias->rowCount() + 1);
      
      AliasCheckBox* aCheckBox = new AliasCheckBox(0);
      aCheckBox->setToolTip("Enable");
      aCheckBox->id = newAliasCount;
      
      tblAlias->setCellWidget(tblAlias->rowCount()-1, 0, aCheckBox);
      tblAlias->setRowHeight(tblAlias->rowCount()-1,20);
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(result);
      tblAlias->setItem(tblAlias->rowCount()-1,1,aTableWidget);
    }
  }
  
  void Config::saveAlias() {
    updateArg();
    for (int i=0; i < tblAlias->rowCount(); i++) {
      int index = Alias::indexOf(&aliasList, ((AliasCheckBox*) tblAlias->cellWidget(i, 0))->id);
      if(index != -1) {
        if (aliasList[index].getEdited() == true) {
          aliasList[index].save();
        }
      }
    }
  }
  
  void Config::updateArg() {
    if (currentAliasIndex != -1) {
      int aliasIndex = Alias::indexOf(&aliasList, ((AliasCheckBox*) tblAlias->cellWidget(currentAliasIndex,0))->id);
      if (aliasIndex == -1)
        return;
      
      aliasList[aliasIndex].setCommand(txtCommand->text());
      QVector<QString> argsList = aliasList[aliasIndex].getArgs();
      
      for (int i = 0; i < lstAliasArgs->count(); i++) {
        if (argsList.indexOf(lstAliasArgs->item(i)->text()) == -1)
         argsList << lstAliasArgs->item(i)->text();
      }
      
      QStringList newArgList;
      for (int i = 0; i < lstAliasArgs->count(); i++) {
        newArgList << lstAliasArgs->item(i)->text();
      }
      
      for (int i = 0; i < argsList.count(); i++) {
        if (newArgList.indexOf(argsList[i]) == -1)
          argsList.remove(i);
      }
      aliasList[aliasIndex].setEnable(((AliasCheckBox*) tblAlias->cellWidget(currentAliasIndex,0))->isChecked());
      aliasList[aliasIndex].setArgs(argsList);
    }
  }
  
  void Config::editSession() {
    if (lstSession->currentItem() != 0) {
      SessionListItem* anItem = (SessionListItem*) lstSession->currentItem();
      Session* aSession = anItem->aSession;
      SessionEditor* aSessionEditor = new SessionEditor(this,aSession);
      aSessionEditor->show();
    }
  }
  
  void Config::addSession() {
    bool ok;
    QString text = QInputDialog::getText(this, "Exclude a command", "Exclude the following command from advance logging", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      SessionListItem* anItem = new SessionListItem();
      anItem->setText(text);
      Session* aSession = new Session();
      aSession->setName(text);
      anItem->aSession = aSession;
      lstSession->addItem(anItem);
      lstSession->setCurrentItem(anItem);
      SessionEditor* aSessionEditor = new SessionEditor(this,aSession);
      aSessionEditor->show();
    }
  }
  
  void Config::saveSession() {
    for (int i =0; i < lstSession->count();i++)
      ((SessionListItem*)lstSession->item(i))->aSession->save();
  }