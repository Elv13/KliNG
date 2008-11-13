#include "config.h"

#include <KLocale>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QInputDialog>
#include <KLocalizedString>
#include <QtSql>
#include <QSqlDatabase>

  Config::Config(QWidget* parent, KlingConfigSkeleton* aConfigSkeleton) : KConfigDialog(parent, "settings", aConfigSkeleton) {
    configSkeleton = aConfigSkeleton;
    resize(600,500);
    
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

    QWidget* generalCentralWidget = new QWidget();
    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalCentralWidget->setLayout(generalLayout);
    twGeneral = new QTabWidget(generalCentralWidget);

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
    generalLayout->addWidget(twGeneral);
    
    managerCentralWidget = new QWidget();
    
    gridManager = new QGridLayout;
    managerCentralWidget->setLayout(gridManager);
    
    ckbEnableManager = new QCheckBox;
    ckbEnableManager->setText("Enable script manager");
    ckbEnableManager->setChecked((configSkeleton->scriptManagerTabOrder == -1) ? false : true);
    gridManager->addWidget(ckbEnableManager,0,0);
    
    twGeneral->addTab(managerCentralWidget,QString());
    twGeneral->setTabText(4, "Script Manager");

    pwiMode = addPage(generalCentralWidget, i18n("Mode") );
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
    
    tblAlias = new QTableWidget();
    tblAlias->setColumnCount(2);
    tblAlias->verticalHeader()->hide();
    tblAlias->horizontalHeader()->hide();
    tblAlias->setSelectionBehavior(QAbstractItemView::SelectRows);
    QSqlQuery query;
    query.exec("SELECT ALIAS,COMMAND,ARGS FROM TALIAS");
    int i =1;
    while (query.next())  {
      tblAlias->setRowCount(i);
      tblAlias->setRowHeight(i-1,20);
      QTableWidgetItem* aTableWidget = new QTableWidgetItem(query.value(0).toString());
      tblAlias->setItem(i-1,0,aTableWidget);
      
      QTableWidgetItem* aTableWidget1 = new QTableWidgetItem(query.value(1).toString() + " " + query.value(2).toString());
      tblAlias->setItem(i-1,1,aTableWidget1);
      
      i++;
    }
    gridAliasList->addWidget(tblAlias,0,0,2,1);
    
    gridAlias->addWidget(grbAliasList,0,0);
        
    QGridLayout* gridAliasOpt = new QGridLayout;
    
    QGroupBox* grbAliasOpt = new QGroupBox();
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
    tblCmdDefaultArgs->setColumnCount(5);
    tblCmdDefaultArgs->setRowCount(5);
    
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(0, __colItem);
    tblCmdDefaultArgs->horizontalHeaderItem(0)->setText("Command");
    
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(1, __colItem1);
    tblCmdDefaultArgs->horizontalHeaderItem(1)->setText("Arg 1");
    
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(2, __colItem2);
    tblCmdDefaultArgs->horizontalHeaderItem(2)->setText("Arg 2");
    
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(3, __colItem3);
    tblCmdDefaultArgs->horizontalHeaderItem(3)->setText("Arg 3");
    
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    tblCmdDefaultArgs->setHorizontalHeaderItem(4, __colItem4);
    tblCmdDefaultArgs->horizontalHeaderItem(4)->setText("Arg 4");
    
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
   
    QGroupBox* grbFunctionBody = new QGroupBox;
    grbFunctionBody->setTitle("Body");
    gridFunction->addWidget(grbFunctionBody,2,0,1,2);
    
    QGridLayout* gridFunctionBody = new QGridLayout();
    grbFunctionBody->setLayout(gridFunctionBody);
    
    rtfFunctionEditor = new KTextEdit();
    gridFunctionBody->addWidget(rtfFunctionEditor,0,0);
    
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


    pwiAppearance = addPage(new QLabel("test2"), i18n("Appearance") );
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
    btnAddPlugin->setIcon(KIcon("list-add"));
    pluginButtonLayout->addWidget(btnAddPlugin);
    btnRemovePlugin = new KPushButton();
    btnRemovePlugin->setText("Remove");
    btnRemovePlugin->setIcon(KIcon("edit-delete"));
    pluginButtonLayout->addWidget(btnRemovePlugin);
    btnInfoPlugin = new KPushButton();
    btnInfoPlugin->setText("Information");
    btnInfoPlugin->setIcon(KIcon("help-about"));
    pluginButtonLayout->addWidget(btnInfoPlugin);
    btnPluginConfig = new KPushButton();
    btnPluginConfig->setText("Configure");
    btnPluginConfig->setIcon(KIcon("configure"));
    pluginButtonLayout->addWidget(btnPluginConfig);
    btnDownloadPlugin = new KPushButton();
    btnDownloadPlugin->setText("Download new");
    btnDownloadPlugin->setIcon(KIcon("document-open-remote"));
    pluginButtonLayout->addWidget(btnDownloadPlugin);
    pluginButtonLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
    pwiPlugins = addPage(pluginCentralWidget, i18n("Plugins") );
    pwiPlugins->setIcon( KIcon( "vcs_add" ) );

    connect( this, SIGNAL( okClicked() ), this, SLOT( saveConfig() ) );
    connect( btnUp, SIGNAL( clicked() ), this, SLOT( moveTabUp() ) );
    connect( btnDown, SIGNAL( clicked() ), this, SLOT( moveTabDown() ) );
    connect( btnAddExcludedCommand, SIGNAL( pressed() ), this, SLOT( addLogExclude() ) );
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