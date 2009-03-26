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
#include <KIO/NetAccess>
#include <KStandardDirs>
#include <QTextStream>
#include <QFile>
#include "completer.h"
#include "history.h"
#include "fileBrowser.h"
#include "term.h"

class ScriptMonitorItem: public AbstractMonitorItem, public Shell {
  Q_OBJECT
  public:
    ScriptMonitorItem(QWidget* parent, QString command) : AbstractMonitorItem(parent,command),Shell(Term::commandList,Term::aliasList,Term::defaultArgsList,Term::functionList),aDebugTerm(0) {
      setupActions();
      command;
      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(incrementTimer()));
      timer->start(1000);
      currentTty = new VirtTtyThread();
      QString inputFileName = KStandardDirs::locateLocal("appdata", "/script/") + command;
      QString tmpFile;
      if(KIO::NetAccess::download(inputFileName, tmpFile, this)) {
        QFile file(tmpFile);
        file.open(QIODevice::ReadOnly);
        QString script = (QTextStream(&file).readAll());
	this->command =script;
	parseScript(script);
	//analyseCommand(commandArray[0], parseCommand(commandArray[0]));
        KIO::NetAccess::removeTempFile(tmpFile);
      }
      else {
        //KMessageBox::error(this,
        //KIO::NetAccess::lastErrorString());
      }
      
    }
    void setTty(VirtTtyThread* aTty);
  private:
    void setupActions();
    void executeNextCommand();
    void signalNextLine();
    void parseScript(QString script);
    QString rebuildCommand(QVector<QString> args);
    DebugTerm* aDebugTerm;
    VirtTtyThread* currentTty;
    QString command;
  private slots:
    void endMe(QString time, QString key);
    void endMe();
    void connectTerm();
    void sendCommand();
};
#endif