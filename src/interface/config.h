#ifndef DEF_CONFIG
#define DEF_CONFIG

#include <KConfigDialog>
#include <KConfigSkeleton>
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

QT_BEGIN_NAMESPACE

class Config : public KConfigDialog
{
      Q_OBJECT

  public:
    Config(QWidget* parent, KConfigSkeleton* aConfig);
    ~Config(){}
    
  private:
    KPageWidgetItem* pwiGeneral;
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
    
  /*private slots:
    void openDir(QTableWidgetItem* item);
    void backToStandardMode_clicked();
    
  signals:
    void addToHistory(QString);*/
    
};
#endif
