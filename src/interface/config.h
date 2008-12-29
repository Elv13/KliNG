#ifndef DEF_CONFIG
#define DEF_CONFIG

#include <KConfigDialog>
#include <KPageWidgetItem>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <KPushButton>
#include <KTextEdit>
#include <KLineEdit>
#include <QCheckBox>
#include <KIcon>
#include <QTabWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QListWidget>
#include <QSpinBox>
#include <QComboBox>
#include "../shell/alias.h"
#include "../configSkeleton.h"

  QT_BEGIN_NAMESPACE

  class Config : public KConfigDialog {
        Q_OBJECT

    public:
      Config(QWidget* parent, KlingConfigSkeleton* aConfig);
      ~Config(){}
      
    private:
      KlingConfigSkeleton* configSkeleton;
      KPageWidgetItem* pwiGeneral;
      KPageWidgetItem* pwiMode;
      KPageWidgetItem* pwiTerm;
      KPageWidgetItem* pwiLogging;
      KPageWidgetItem* pwiAppearance;
      KPageWidgetItem* pwiPlugins;
      QTabWidget* twGeneral;
      QWidget* termianlCentralWidget;
      QWidget* monitorCentralWidget;
      QWidget* editorCentralWidget;
      QWidget* webBrowserCentralWidget;
      QWidget* managerCentralWidget;
      QCheckBox* enableTerminal;
      QCheckBox* enableMonitor;
      QCheckBox* enableEditor;
      QCheckBox* enableWebBrowser;
      QGroupBox* showInTerminal;
      QGroupBox* showInMonitor;
      QGroupBox* showInEditor;
      QGroupBox* showInWebBrowser;
      QGroupBox* otherTerminalOpts;
      QGridLayout* gridTerminal;
      QGridLayout* gridMonitor;
      QGridLayout* gridEditor;
      QGridLayout* gridWebBrowser;
      QGridLayout* gridTerminalOpts;
      QGridLayout* gridManager;
      QCheckBox* ckbShowScriptBrowserTerminal;
      QCheckBox* ckbShowScheduledTaskTerminal;
      QCheckBox* ckbShowCommandListTerminal;
      QCheckBox* ckbShowHistoryTerminal;
      QCheckBox* ckbShowManPageTerminal;
      QCheckBox* ckbEnableUIDefault;
      QCheckBox* ckbFmShowHidden;
      QCheckBox* ckbEnableCompleter;
      QCheckBox* ckbShowScriptBrowserMonitor;
      QCheckBox* ckbShowScheduledTaskMonitor;
      QCheckBox* ckbShowCommandListMonitor;
      QCheckBox* ckbShowHistoryMonitor;
      QCheckBox* ckbShowManPageMonitor;
      QCheckBox* ckbShowScriptBrowserEditor;
      QCheckBox* ckbShowScheduledTaskEditor;
      QCheckBox* ckbShowCommandListEditor;
      QCheckBox* ckbShowHistoryEditor;
      QCheckBox* ckbShowManPageEditor;
      QCheckBox* ckbShowScriptBrowserWebBrowser;
      QCheckBox* ckbShowScheduledTaskrWebBrowser;
      QCheckBox* ckbShowCommandListrWebBrowser;
      QCheckBox* ckbShowHistoryrWebBrowser;
      QCheckBox* ckbShowManPagerWebBrowser;
      QCheckBox* ckbShowDebugTerminal;
      QCheckBox* ckbShowDebugMonitor;
      QCheckBox* ckbShowDebugEditor;
      QCheckBox* ckbShowDebugWebBrowser;
      QCheckBox* ckbEnableManager;
      
      QGridLayout* gridLogging;
      QSpinBox* spinMb;
      QLabel* lblMb;
      QSpinBox* spinMaxOutputSize;
      QLabel* lblMaxOutputSize;
      QCheckBox* ckbAddToBash;
      KPushButton* btnCleanLog;
      KPushButton* btnClearHistory;
      QLabel* lblExclude;
      QListWidget* lstExclude;
      QCheckBox* ckbEnableLogging;
      KPushButton* btnAddExcludedCommand;
      KPushButton* btnRemoveExcludedCommand;
      
      QTableWidget* tblAlias;
      QGroupBox* grbAliasOpt;
      KLineEdit* txtCommand;
      QListWidget* lstAliasArgs;
      KPushButton* btnAddAliasArgs;
      KPushButton* btnRemoveAliasArgs;
      KPushButton* btnAddAlias;
      KPushButton* btnRemoveAlias;
      
      QTableWidget* tblCmdDefaultArgs;
      
      QListWidget* lstFunctionList;
      KPushButton* btnAddFunction;
      KPushButton* btnRemoveFunction;
      KTextEdit* rtfFunctionEditor;
      
      QListWidget* pluginList;
      KPushButton* btnAddPlugin;
      KPushButton* btnRemovePlugin;
      KPushButton* btnInfoPlugin;
      KPushButton* btnPluginConfig;
      KPushButton* btnDownloadPlugin;
      
      QWidget* generalCentral;
      QListWidget* lstTabOrder;
      KPushButton* btnUp;
      KPushButton* btnDown;
      
      QGroupBox* grbTerminalAppearence;
      QGroupBox* grbCustomTerminalAppearence;
      QGroupBox* grbEditorAppearence;
      QGroupBox* grbCustomEditorAppearence;
      QTableWidget* tblTerminalAppearence;
      QTableWidget* tblCustomTerminalAppearence;
      QTableWidget* tblEditorAppearence;
      QTableWidget* tblCustomEditorAppearence;
      
      QVector<Alias> aliasList;
      signed int newAliasCount;
      int currentAliasIndex;

      QGroupBox* grbList;
      QGroupBox* grbRules;
      QTableWidget* tblString;
      QPushButton* btnAddString;
      QPushButton* btnDelString;
      QListWidget* lstRules;
      QPushButton* btnAddRules;
      QPushButton* btnDelRules;
      QPushButton* btnEditRules;

      QListWidget* lstSession;
      QPushButton* btnAddSession;
      QPushButton* btnDelSession;
      QPushButton* btnEditSession;
      
    private slots:
      void saveConfig();
      void addLogExclude();
      void moveTabUp();
      void moveTabDown();
      void loadAlias(int x, int y);
      void addAliasArgs();
      void removeAliasArgs();
      void removeAlias();
      void addAlias();
      void addSession();
      void editSession();
      
    private:
      int countActiveMode();
      void saveAlias();
      void updateArg();
  };
#endif
