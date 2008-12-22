#include "termSession.h"

TermSession::TermSession(QWidget* parent =0) : QWidget( parent ) {
    count = 0;
    aDockHistory = 0;
    commandList = 0;
    aliasList = 0;
    defaultArgsList = 0;
    functionList = 0;
    historyStringList = 0;
    aLayout = new QHBoxLayout(this);
    this->setLayout(aLayout);
}

void TermSession::addTerm() {
  Term* aTerm = new Term(aDockHistory, this, commandList, aliasList, defaultArgsList, functionList, historyStringList);

  if (count == 0) {
    this->baseTerm = aTerm;
    this->aLayout->addWidget(baseTerm);
    count++;
  } 
  else if (count == 1) {
    delete this->aLayout;
    aLayout = new QHBoxLayout(this);
    termTab = new KTabWidget(this);
    termTab->setTabPosition(QTabWidget::South);
    termTab->setTabReorderingEnabled(true);
    termTab->setAutomaticResizeTabs(true);
    termTab->setHoverCloseButton(true);
    this->aLayout->addWidget(termTab);
    termTab->addTab(this->baseTerm, QString("Term "+ QString::number(count)));
    termTab->addTab(aTerm,QString("Term "+ QString::number(++count)));
  }
  else {
    termTab->addTab(aTerm,QString("Term "+ QString::number(++count)));
  }
}

void TermSession::addTerm(History* aDockHistory, QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList, QStringList* historyStringList) {
  if (this->commandList == 0) {
    printf("\n\nI am here \n\n");
    this->aDockHistory = aDockHistory;
    this->commandList = commandList;
    this->aliasList = aliasList;
    this->defaultArgsList = defaultArgsList;
    this->functionList = functionList;
    this->historyStringList = historyStringList;
  }
  
  Term* aTerm = new Term(aDockHistory, this, commandList, aliasList, defaultArgsList, functionList, historyStringList);
  
  if (count == 0) {
    this->baseTerm = aTerm;
    this->aLayout->addWidget(baseTerm);
    count++;
  } 
  else if (count == 1) {
    delete this->aLayout;
    aLayout = new QHBoxLayout(this);
    termTab = new KTabWidget(this);
    termTab->setTabPosition(QTabWidget::South);
    termTab->setTabReorderingEnabled(true);
    termTab->setAutomaticResizeTabs(true);
    termTab->setHoverCloseButton(true);
    this->aLayout->addWidget(termTab);
    termTab->addTab(this->baseTerm, QString("Term "+ QString::number(count)));
    termTab->addTab(aTerm,QString("Term "+ QString::number(++count)));
  }
  else {
    termTab->addTab(aTerm,QString("Term "+ QString::number(++count)));
  }
}

void TermSession::remTerm() {
  
}

Term* TermSession::getCurrentTerm() {
  return (Term*) termTab->currentWidget();
}
