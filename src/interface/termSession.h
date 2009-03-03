#ifndef DEF_TERMSESSION
#define DEF_TERMSESSION
#include <KTabWidget>
#include <QVector>
#include <QStringList>
#include <QHBoxLayout>
#include "term.h"
#include "history.h"
#include "executionMonitor.h"
#include "../virtTTY.h"

class TermSession : public QWidget {
    Q_OBJECT
    public:
      TermSession(QWidget* parent, ExecutionMonitor* anExecMonitor =0);
      uint count;
      
    private:
      KTabWidget* termTab;
      Term* baseTerm;
      History* aDockHistory;
      QStringList* commandList;
      QStringList* aliasList;
      QStringList* defaultArgsList;
      QStringList* functionList;
      QStringList* historyStringList;
      QHBoxLayout* aLayout;
      ExecutionMonitor* mainExecutionMonitor;
      
    public:
      Term* getCurrentTerm();
      void loadSession(QString name);
  
    public slots:
      void addTerm();
      void addTerm(History* aDockHistory, QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList, QStringList* historyStringList);
      void remTerm();
      void testConnect(QString text);
      
    /*private slots:*/
      void fowardSignals(QString name, VirtTtyThread* aThread);

    signals:
      void newCommand(QString name, VirtTtyThread* aThread);
      
  };
#endif