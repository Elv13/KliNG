#ifndef DEF_COMMANDE_MONITOR_ITEM
#define DEF_COMMANDE_MONITOR_ITEM
#include "abstractMonitor.h"
#include "../virtTTY.h"
#include "debugTerm.h"
#include <QtGui/QSpacerItem>
#include <KPushButton>
#include <KIcon>
#include <QTimer>

class CommandMonitorItem: public AbstractMonitorItem {
  Q_OBJECT
  public:
    CommandMonitorItem(QWidget* parent, QString name) : AbstractMonitorItem(parent,name) {setupActions();QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(incrementTimer()));
    timer->start(1000);}
    void setTty(VirtTtyThread* aTty);
  private:
    void setupActions();
    VirtTtyThread* currentTty;
  private slots:
    void endMe();
    void connectTerm();
};
#endif