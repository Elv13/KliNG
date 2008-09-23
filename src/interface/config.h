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
#include <QCheckBox>
#include <KIcon>
#include <QTabWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QListWidget>
#include <QSpinBox>
#include "../configSkeleton.h"

QT_BEGIN_NAMESPACE

class Config : public KConfigDialog
{
      Q_OBJECT

  public:
    Config(QWidget* parent, KlingConfigSkeleton* aConfig);
    ~Config(){}
    
  private:
    KlingConfigSkeleton* configSkeleton;
    KPageWidgetItem* pwiGeneral;
    KPageWidgetItem* pwiLogging;
    KPageWidgetItem* pwiAppearance;
    KPageWidgetItem* pwiPlugins;
    QTabWidget* twGeneral;
    QWidget* termianlCentralWidget;
    QWidget* monitorCentralWidget;
    QWidget* editorCentralWidget;
    QWidget* webBrowserCentralWidget;
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
    
    QGridLayout* gridLogging;
    QSpinBox* spinMb;
    QLabel* lblMb;
    QSpinBox* spinMaxOutputSize;
    QLabel* lblMaxOutputSize;
    QCheckBox* ckbAddToBash;
    
    QListWidget* pluginList;
    KPushButton* btnAddPlugin;
    KPushButton* btnRemovePlugin;
    KPushButton* btnInfoPlugin;
    KPushButton* btnPluginConfig;
    KPushButton* btnDownloadPlugin;
    
  private slots:
    void saveConfig();
    /*void openDir(QTableWidgetItem* item);
    void backToStandardMode_clicked();
    
  signals:
    void addToHistory(QString);*/
    
};
#endif
