#define DBUS_API_SUBJECT_TO_CHANGE
#include <QThread>
#include <QHash>
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface/executionMonitor.h"
#include "interface/scriptMonitor.h"

struct JobInfo {
  int jobId;
  char* command;
  int secondLeft;
};

class DbusListener : public QThread {
  Q_OBJECT
  public:
    DbusListener(QObject* parent, ExecutionMonitor* aMonitor):QThread(parent){
      QObject::connect(this, SIGNAL(newMonitor(int, QString)), aMonitor, SLOT(addMonitor(int, QString)));
      QObject::connect(this, SIGNAL(updateMon(int, int)), aMonitor, SLOT(updateMonitor(int, int)));

    };
    void run();
  signals:
    void secLeft(int job, uint second);
    void newMonitor(int jobId, QString command);
    void updateMon(int jobId, int second);
  private:
    QHash<int, JobInfo> jobs;
    void manageQueue(DBusMessageIter args, DBusMessage* msg);
    void manageExec(DBusMessageIter args, DBusMessage* msg);
    void receive();
};