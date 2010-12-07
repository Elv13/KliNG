#include "commandMonitorItem.h"
#include <KStandardDirs>

void CommandMonitorItem::setupActions() {
  KPushButton* btnView = new KPushButton();
  btnView->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/eye.png")));
  btnView->setMinimumSize(40,22);
  btnView->setStyleSheet("border: 1px black solid;border-color:#555555;border-style:solid;border-radius:3px;");
  actionLayout->addWidget(btnView);
  QObject::connect(btnView, SIGNAL(clicked()), this, SLOT(connectTerm()));
  
  KPushButton* btnStartNow = new KPushButton();
  btnStartNow->setIcon(KIcon("arrow-right"));
  btnStartNow->setMinimumSize(40,22);
  btnStartNow->setStyleSheet("border: 1px black solid;border-color:#555555;border-style:solid;border-radius:3px;");
  actionLayout->addWidget(btnStartNow);
  
  KPushButton* btnPause = new KPushButton();
  btnPause->setIcon(KIcon(KStandardDirs::locate( "appdata", "pixmap/22x22/pause.png")));
  btnPause->setMinimumSize(40,22);
  btnPause->setStyleSheet("border: 1px black solid;border-color:#555555;border-style:solid;border-radius:3px;");
  actionLayout->addWidget(btnPause);
  
  KPushButton* btnStop = new KPushButton();
  btnStop->setIcon(KIcon("dialog-close"));
  btnStop->setMinimumSize(40,22);
  btnStop->setStyleSheet("border: 1px black solid;border-color:#555555;border-style:solid;border-radius:3px;");
  actionLayout->addWidget(btnStop);
  
  horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  actionLayout->addItem(horizontalSpacer);
}

void CommandMonitorItem::endMe() {
  delete this;
}

void CommandMonitorItem::setTty(VirtTtyThread* aTty) {
  currentTty = aTty;
  QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), this, SLOT(endMe()));
}

void CommandMonitorItem::connectTerm() {
  DebugTerm* aDebugTerm = new DebugTerm(0);
  aDebugTerm->show();
  QObject::connect(currentTty->aVirtTTY, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));
  QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), aDebugTerm, SLOT(signalEnd()));
}
