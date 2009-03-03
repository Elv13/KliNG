#include "cronMonitorItem.h"
#include <KStandardDirs>

void CronMonitorItem::setupActions() {
  KPushButton* btnView = new KPushButton();
  btnView->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png")));
  btnView->setMinimumSize(40,22);
  actionLayout->addWidget(btnView);
  
  KPushButton* btnStartNow = new KPushButton();
  btnStartNow->setIcon(KIcon("arrow-right"));
  btnStartNow->setMinimumSize(40,22);
  actionLayout->addWidget(btnStartNow);
  
  KPushButton* btnPause = new KPushButton();
  btnPause->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/pause.png")));
  btnPause->setMinimumSize(40,22);
  actionLayout->addWidget(btnPause);
  
  KPushButton* btnStop = new KPushButton();
  btnStop->setIcon(KIcon("dialog-close"));
  btnStop->setMinimumSize(40,22);
  actionLayout->addWidget(btnStop);

  KPushButton* btnLater = new KPushButton();
  btnLater->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/clock.png")));
  btnLater->setMinimumSize(40,22);
  actionLayout->addWidget(btnLater);
  
  horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  actionLayout->addItem(horizontalSpacer);
}

void CronMonitorItem::endMe() {
  
}
