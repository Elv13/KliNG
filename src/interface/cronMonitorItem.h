#ifndef DEF_CRON_MONITOR_ITEM
#define DEF_CRON_MONITOR_ITEM
#include "abstractMonitor.h"
#include <QtGui/QSpacerItem>
#include <KPushButton>
#include <KIcon>

class CronMonitorItem: public AbstractMonitorItem {
  public:
    CronMonitorItem(QWidget* parent, QString name) : AbstractMonitorItem(parent,name) {setupActions();}
  private:
    void setupActions();
  private slots:
    void endMe();
};
#endif