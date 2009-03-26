#include "scriptMonitorItem.h"
#include <QDebug>

void ScriptMonitorItem::setupActions() {
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

void ScriptMonitorItem::endMe(QString time, QString key) {
  delete this;
}

void ScriptMonitorItem::endMe() {
  delete this;
}

void ScriptMonitorItem::setTty(VirtTtyThread* aTty) {
  currentTty = aTty;
  //QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), this, SLOT(endMe()));
}

void ScriptMonitorItem::connectTerm() {
  aDebugTerm = new DebugTerm(0);
  aDebugTerm->show();
  QObject::connect(currentTty->aVirtTTY, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));
  //QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), aDebugTerm, SLOT(signalEnd()));
}
  
void ScriptMonitorItem::sendCommand() {
  if (executionQueue.count() != 0) {
    qDebug() << "Going to execute: " << executionQueue[0] << "\n";
    if (aDebugTerm != 0) {
      disconnect(currentTty->aVirtTTY, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));
      aDebugTerm->signalNewCommand(rebuildCommand(executionQueue[0]));
    }
    qDebug() << "lineNumber:" << lineNumber << "currentLine: " << currentLine << "\n";
    progressBar->setValue((((float) currentLine)/((float) lineNumber))*100);
    currentTty = new VirtTtyThread(executionQueue[0]);
    lblCmd->setText("Current command: " + rebuildCommand(executionQueue[0]));
    if (executionQueue.size() > 1)
      lblNextCmd->setText("Next command: " + rebuildCommand(executionQueue[1]));
    else if (currentLine < lineNumber)
      lblNextCmd->setText("Next command: " + commandArray[currentLine]+1);
    else
      lblNextCmd->setText("Next command: -");
    //QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), this, SLOT(endMe()));
    QObject::connect(currentTty->aVirtTTY, SIGNAL(isOver(QString, QString)), this, SLOT(sendCommand()));
    if (aDebugTerm != 0)
      QObject::connect(currentTty->aVirtTTY, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));

    executionQueue.pop_front();
    signalNextLine();
    currentTty->start();
  }
  else {
    executeNextCommand();
  }
}
  
void ScriptMonitorItem::signalNextLine() {
  //lblNextCmd->setText(executionQueue.first()[0]);
}

void ScriptMonitorItem::executeNextCommand() {
  int i = countLine(command);
  signalNextLine();
  if (currentLine < lineNumber) {      
    evalCommand();
    currentLine++;
    //highlightLine(currentLine);
  }
  else if (aDebugTerm != 0) {
    endMe();
    aDebugTerm->signalEnd();
  }
  else {
    endMe();
  }
  /*if (currentLine == i) {
    setDebuggerMode(false);
  }*/
}

void ScriptMonitorItem::parseScript(QString script) {
  int i = countLine(script);

  //cout << i << endl;
  commandArray = new QString[i];

  int j =0;
  int k =0;
  
  while (script != "") {
    if ((script[j] == 0x0A) || (j == (script.size()-1))) {
      char* command = new char[j];
      commandArray[k] = script.mid(0,j).trimmed();
      script = script.mid((j+1), (script.size() - j -1));
      j = 0;
      k++;
      while (script[0] == 0x0A)
	script = script.mid(1, (script.size() -1));
    }
    else
      j++;
  }
  currentLine = 0;
  lineNumber = i;
  
  if (currentLine < lineNumber) {
    evalCommand();
  }
}

QString ScriptMonitorItem::rebuildCommand(QVector<QString> args) {
  QString result;
  for (int i =0; i < args.count();i++) {
    result += args[i] + " ";
  }
  return result;
}