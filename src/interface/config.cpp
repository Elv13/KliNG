#include "config.h"

#include <KLocale>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

Config::Config(QWidget* parent, KConfigSkeleton* aConfig) : KConfigDialog(parent, "settings", aConfig) {
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
    terminalLayout->addWidget(enableTerminal);
    
    showInTerminal = new QGroupBox();
    showInTerminal->setTitle("Enable by default in termianl");
    terminalLayout->addWidget(showInTerminal);
   
   terminalLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
   
   
   monitorCentralWidget = new QWidget();
   QVBoxLayout *monitorLayout = new QVBoxLayout;
   monitorCentralWidget->setLayout(monitorLayout);
   twGeneral->addTab(monitorCentralWidget,QString());
   twGeneral->setTabText(1, "Monitor");
   
   
    enableMonitor = new QCheckBox();
    enableMonitor->setText("Enable execution monitor");
    monitorLayout->addWidget(enableMonitor);
    
    showInMonitor = new QGroupBox();
    showInMonitor->setTitle("Enable by default in monitor");
    monitorLayout->addWidget(showInMonitor);
   
   monitorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
   
   
   editorCentralWidget = new QWidget();
   QVBoxLayout *editorLayout = new QVBoxLayout;
   editorCentralWidget->setLayout(editorLayout);
   twGeneral->addTab(editorCentralWidget,QString());
   twGeneral->setTabText(2, "Editor");
   
   
    enableEditor = new QCheckBox();
    enableEditor->setText("Enable editor");
    editorLayout->addWidget(enableEditor);
    
    showInEditor = new QGroupBox();
    showInEditor->setTitle("Enable by default in editor");
    editorLayout->addWidget(showInEditor);
   
   editorLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
   
   
   webBrowserCentralWidget = new QWidget();
   QVBoxLayout *webBrowserLayout = new QVBoxLayout;
   webBrowserCentralWidget->setLayout(webBrowserLayout);
   twGeneral->addTab(webBrowserCentralWidget,QString());
   twGeneral->setTabText(3, "Web Browser");
   
   
    enableWebBrowser = new QCheckBox();
    enableWebBrowser->setText("Enable web browser");
    webBrowserLayout->addWidget(enableWebBrowser);
    
    showInWebBrowser = new QGroupBox();
    showInWebBrowser->setTitle("Enable by default in web browser");
    webBrowserLayout->addWidget(showInWebBrowser);
   
   webBrowserLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));
   
   


    
    
    
    
    
    
    


   generalLayout->addWidget(twGeneral);
   
   pwiGeneral = addPage(generalCentralWidget, i18n("General") );
   pwiGeneral->setIcon( KIcon( "fork" ) );
   

   pwiAppearance = addPage(new QLabel("test2"), i18n("Appearance") );
   pwiAppearance->setIcon( KIcon( "format-text-color" ) );
   
   pwiPlugins = addPage(new QLabel("test3"), i18n("Plugins") );
   pwiPlugins->setIcon( KIcon( "vcs_add" ) );

   /*connect(dialog, SIGNAL(settingsChanged(const QString&)), this, SLOT(loadSettings()));
   connect(dialog, SIGNAL(settingsChanged(const QString&)), this, SLOT(loadSettings()));*/
   //show();

}
