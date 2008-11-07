#ifndef DEFAULT_SCREEN
#define DEFAULT_SCREEN

#include <KPushButton>
#include <QLabel>
#include "../configSkeleton.h"
#include "commandList.h"
#include "history.h"

class DefaultScreen : public QWidget {
    Q_OBJECT
    public:
      DefaultScreen(QWidget* parent, KlingConfigSkeleton* config);
      KlingConfigSkeleton* config;
      KPushButton* btnOpenTerminal;
      KPushButton* btnOpenGestion;
      KPushButton* btnOpenEditor;
      KPushButton* btnOpenwebBrowser;
      KPushButton* btnOpenMonitor;
      QLabel* lblWelcome;
      CommandList* aCommandListDock;
      History* anHistoryDock;
      
  
    private slots:
      void btnOpenTerminalPressed();
      void btnOpenGestionPressed();
      void btnOpenEditorPressed();
      void btnOpenwebBrowserPressed();
      void btnOpenMonitorPressed();
      
    signals:
      void clicked(uint);
  };
#endif