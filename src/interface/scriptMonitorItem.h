#ifndef DEF_SCRIPT_MONITOR_ITEM
#define DEF_SCRIPT_MONITOR_ITEM
#include "abstractMonitor.h"
#include "../virtTTY.h"
#include "../shell.h"
#include "debugTerm.h"
#include <QtGui/QSpacerItem>
#include <KPushButton>
#include <KIcon>
#include <QTimer>
#include "completer.h"
#include "history.h"
#include "fileBrowser.h"

class ScriptMonitorItem: public AbstractMonitorItem, public Shell {
  Q_OBJECT
  public:
    ScriptMonitorItem(QWidget* parent, QString command, History* aDockHistory, QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList, QStringList* historyStringList) : AbstractMonitorItem(parent,command),Shell(commandList,aliasList,defaultArgsList,functionList) {
      setupActions();
      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(incrementTimer()));
      timer->start(1000);
      analyseCommand(command, parseCommand(command));
    }
    void setTty(VirtTtyThread* aTty);
  private:
    void setupActions();
    VirtTtyThread* currentTty;
  private slots:
    void endMe();
    void connectTerm();
};
#endif