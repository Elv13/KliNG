#ifndef DEF_EXECUTION_MONITOR
#define DEF_EXECUTION_MONITOR
#include "scriptMonitor.h"
#include <QWidget>
#include <QLabel>
#include <QtGui/QVBoxLayout>
#include <QScrollArea>

QT_BEGIN_NAMESPACE

  class ExecutionMonitor : public QWidget {
    Q_OBJECT

    public:
      ExecutionMonitor(QWidget* parent);
      QWidget* display;
      QWidget* stat;
      QLabel* lblExecuted;
      QLabel* lblExecutedValue;
      QLabel* lblCommandExecuted;
      QLabel* lblCommandExecutedValue;
      QLabel* errorToday;
      QLabel* errorTodayValue;
      QVBoxLayout* horizontalLayout_4;
      QScrollArea *scrollArea;
      
    private:
      int executedScriptNb;
      int cmdExecutedScriptNb;
      
    public slots:
      void launchScript(QString name, QString content);
      void incrCommand();
      
  };
#endif