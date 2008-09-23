#include "config.h"

#include <KLocale>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

Config::Config(QWidget* parent, KlingConfigSkeleton* aConfigSkeleton) : KConfigDialog(parent, "settings", aConfigSkeleton) {
  configSkeleton = aConfigSkeleton;
  //KConfigSkeleton* someSettings = new  KConfigSkeleton();

   //if(KConfigDialog::showDialog("settings"))
   //  return;

   //KConfigDialog *dialog = new KConfigDialog(this, "settings", someSettings);
   resize(600,500);
   //dialog->setFaceType(KPageDialog::IconList);
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
    enableTerminal->setChecked(aConfigSkeleton->enableTerminal);

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
    enableMonitor->setChecked(aConfigSkeleton->enableMonitor);
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

   monitorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


   editorCentralWidget = new QWidget();
   QVBoxLayout *editorLayout = new QVBoxLayout;
   editorCentralWidget->setLayout(editorLayout);
   twGeneral->addTab(editorCentralWidget,QString());
   twGeneral->setTabText(2, "Editor");


    enableEditor = new QCheckBox();
    enableEditor->setText("Enable editor");
    enableEditor->setChecked(aConfigSkeleton->enableEditor);
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

   editorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


   webBrowserCentralWidget = new QWidget();
   QVBoxLayout *webBrowserLayout = new QVBoxLayout;
   webBrowserCentralWidget->setLayout(webBrowserLayout);
   twGeneral->addTab(webBrowserCentralWidget,QString());
   twGeneral->setTabText(3, "Web Browser");


    enableWebBrowser = new QCheckBox();
    enableWebBrowser->setText("Enable web browser");
    enableWebBrowser->setChecked(aConfigSkeleton->enableWebBrowser);
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

    webBrowserLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));




   generalLayout->addWidget(twGeneral);

   pwiGeneral = addPage(generalCentralWidget, i18n("General") );
   pwiGeneral->setIcon( KIcon( "fork" ) );

    QWidget* loggingCentralWidget = new QWidget();
    gridLogging = new QGridLayout();
    loggingCentralWidget->setLayout(gridLogging);

    lblMb = new QLabel();
    lblMb->setText("Amount of data to keep: ");
    gridLogging->addWidget(lblMb,0,0);

    spinMb = new QSpinBox();
    spinMb->setSuffix("mb");
    spinMb->setValue(aConfigSkeleton->ammountToKeep);
    gridLogging->addWidget(spinMb,0,1);

    lblMaxOutputSize = new QLabel();
    lblMaxOutputSize->setText("Keep command output smaller than: ");
    gridLogging->addWidget(lblMaxOutputSize,1,0);

    spinMaxOutputSize = new QSpinBox();
    spinMaxOutputSize->setValue(aConfigSkeleton->maxOutputSize);
    spinMaxOutputSize->setSuffix("kb");
    gridLogging->addWidget(spinMaxOutputSize,1,1);

    ckbAddToBash = new QCheckBox();
    ckbAddToBash->setText("Append to bash history");
    gridLogging->addWidget(ckbAddToBash,2,0);

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
    pluginButtonLayout->addWidget(btnAddPlugin);
    btnRemovePlugin = new KPushButton();
    btnRemovePlugin->setText("Remove");
    pluginButtonLayout->addWidget(btnRemovePlugin);
    btnInfoPlugin = new KPushButton();
    btnInfoPlugin->setText("Information");
    pluginButtonLayout->addWidget(btnInfoPlugin);
    btnPluginConfig = new KPushButton();
    btnPluginConfig->setText("Configure");
    pluginButtonLayout->addWidget(btnPluginConfig);
    btnDownloadPlugin = new KPushButton();
    btnDownloadPlugin->setText("Download new");
    pluginButtonLayout->addWidget(btnDownloadPlugin);

    pluginButtonLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));

   pwiPlugins = addPage(pluginCentralWidget, i18n("Plugins") );
   pwiPlugins->setIcon( KIcon( "vcs_add" ) );

   /*connect(dialog, SIGNAL(settingsChanged(const QString&)), this, SLOT(loadSettings()));
   connect(dialog, SIGNAL(settingsChanged(const QString&)), this, SLOT(loadSettings()));*/
   //show();

   connect( this, SIGNAL( okClicked() ), this, SLOT( saveConfig() ) );

}

void Config::saveConfig() {
    configSkeleton->enableTerminal = enableTerminal->isChecked();
    configSkeleton->enableMonitor = enableMonitor->isChecked();
    configSkeleton->enableEditor = enableEditor->isChecked();
    configSkeleton->enableWebBrowser = enableWebBrowser->isChecked();
    configSkeleton->showScriptBrowserTerminal = ckbShowScriptBrowserTerminal->isChecked();
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
    configSkeleton->writeConfig();

    configSkeleton->maxOutputSize = spinMaxOutputSize->value();
    configSkeleton->ammountToKeep = spinMb->value();
}

