#include "defaultScreen.h"
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QDialog>
#include <QStringList>

#include "term.h"
#include "scriptEditor.h"
#include "executionMonitor.h"
#include "advancedScriptManager.h"
#include "webBrowser.h"

  DefaultScreen::DefaultScreen(QWidget* parent, KlingConfigSkeleton* config) {
    this->config = config;
    aCommandListDock = NULL;
    anHistoryDock = NULL;
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    setLayout(vLayout);
    
    lblWelcome = new QLabel;
    lblWelcome->setText("<u>Welcome to Kling, choose your activity:</u>");
    lblWelcome->setStyleSheet("margin-top:15px;margin-bottom:15px;");
    vLayout->addWidget(lblWelcome);
    
    btnOpenTerminal = new KPushButton;
    btnOpenTerminal->setText("Terminal");
    btnOpenTerminal->setIcon(KIcon("utilities-terminal"));
    btnOpenTerminal->setStyleSheet("text-align:left;padding-left:5px;");
    btnOpenTerminal->setIconSize(QSize(32,32));
    btnOpenTerminal->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(btnOpenTerminal);
    
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    btnOpenGestion = new KPushButton;
    btnOpenGestion->setText("Manager");
    btnOpenGestion->setIcon(KIcon("utilities-file-archiver"));
    btnOpenGestion->setIconSize(QSize(32,32));
    btnOpenGestion->setStyleSheet("text-align:left;padding-left:5px;");
    btnOpenGestion->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(btnOpenGestion);
    
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    btnOpenEditor = new KPushButton;
    btnOpenEditor->setText("Editor");
    btnOpenEditor->setIcon(KIcon("accessories-text-editor"));
    btnOpenEditor->setStyleSheet("text-align:left;padding-left:5px;");
    btnOpenEditor->setIconSize(QSize(32,32));
    btnOpenEditor->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(btnOpenEditor);
    
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    btnOpenwebBrowser = new KPushButton;
    btnOpenwebBrowser->setText("Web Browser");
    btnOpenwebBrowser->setIcon(KIcon("internet-web-browser"));
    btnOpenwebBrowser->setStyleSheet("text-align:left;padding-left:5px;");
    btnOpenwebBrowser->setIconSize(QSize(32,32));
    btnOpenwebBrowser->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(btnOpenwebBrowser);
    
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    btnOpenMonitor = new KPushButton;
    btnOpenMonitor->setText("Monitor");
    btnOpenMonitor->setIcon(KIcon("system-software-update"));
    btnOpenMonitor->setStyleSheet("text-align:left;padding-left:5px;");
    btnOpenMonitor->setIconSize(QSize(32,32));
    btnOpenMonitor->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(btnOpenMonitor);
    
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    
    QObject::connect(btnOpenTerminal, SIGNAL(clicked()), this, SLOT(btnOpenTerminalPressed()));
    QObject::connect(btnOpenGestion, SIGNAL(clicked()), this, SLOT(btnOpenGestionPressed()));
    QObject::connect(btnOpenEditor, SIGNAL(clicked()), this, SLOT(btnOpenEditorPressed()));
    QObject::connect(btnOpenwebBrowser, SIGNAL(clicked()), this, SLOT(btnOpenwebBrowserPressed()));
    QObject::connect(btnOpenMonitor, SIGNAL(clicked()), this, SLOT(btnOpenMonitorPressed()));
  }
  
  void DefaultScreen::btnOpenTerminalPressed() {
    QStringList* anHistoryList = new QStringList;
    QStringList* aCommandList = new QStringList;
    
    if (aCommandListDock == NULL)
      aCommandListDock = new CommandList(0, aCommandList);
    if (anHistoryDock == NULL)
      anHistoryDock = new History(anHistoryList, config);
    
    
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Terminal");
    aDialog->resize(780,530);
    Term* centralWidget = new Term(anHistoryDock, 0, aCommandListDock->commandList, anHistoryDock->historyStringList);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void DefaultScreen::btnOpenGestionPressed() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Current Task Monitor");
    aDialog->resize(780,530);
    ExecutionMonitor* centralWidget = new ExecutionMonitor(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void DefaultScreen::btnOpenEditorPressed() {
    QStringList* anHistoryList = new QStringList;
    QStringList* aCommandList = new QStringList;
    
    if (aCommandListDock == NULL)
      aCommandListDock = new CommandList(0, aCommandList);
    if (anHistoryDock == NULL)
      anHistoryDock = new History(anHistoryList, config);
  
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Script Editor");
    aDialog->resize(780,530);
    ScriptEditor* centralWidget = new ScriptEditor(0, *aCommandListDock->commandList);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void DefaultScreen::btnOpenwebBrowserPressed() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Web Browser");
    aDialog->resize(780,530);
    WebBrowser* centralWidget = new WebBrowser(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }
  
  void DefaultScreen::btnOpenMonitorPressed() {
    QDialog* aDialog = new QDialog;
    QVBoxLayout* aLayout = new QVBoxLayout;
    aDialog->setLayout(aLayout);
    aDialog->setWindowTitle("Script Manager");
    aDialog->resize(780,530);
    AdvancedScriptManager* centralWidget = new AdvancedScriptManager(0);
    aLayout->addWidget(centralWidget);
    aDialog->show();
  }