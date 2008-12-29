#include "termSession.h"
#include <QtSql>
#include <QSqlDatabase>

TermSession::TermSession(QWidget* parent =0) : QWidget( parent ) {
    termTab = 0;
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
    connect(termTab , SIGNAL( doubleClicked() ), this, SLOT( addTerm() ));
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

void TermSession::loadSession(QString name) {
  if (termTab == 0) {
    delete this->aLayout;
    aLayout = new QHBoxLayout(this);
    termTab = new KTabWidget(this);
    termTab->setTabPosition(QTabWidget::South);
    termTab->setTabReorderingEnabled(true);
    termTab->setAutomaticResizeTabs(true);
    termTab->setHoverCloseButton(true);
    this->aLayout->addWidget(termTab);
    termTab->addTab(this->baseTerm, QString("Term "+ QString::number(count)));
  }
  QSqlQuery query;
  query.exec("SELECT TSESSION_KEY FROM TSESSION WHERE NAME = '" + name + "'");
  
  query.next();
  int index = query.value(0).toString().toInt();
  
  QSqlQuery query2;
  query2.exec("SELECT NAME,ICON,PATH,TYPE,INPUT,COMMAND FROM TSESSION_ITEM WHERE SESSION =" + QString::number(index));
  printf("SELECT NAME,ICON,PATH,TYPE,INPUT,COMMAND FROM TSESSION_ITEM WHERE SESSION = %d\n",index);
  while (query2.next())  {
    Term* aTerm = new Term(aDockHistory, this, commandList, aliasList, defaultArgsList, functionList, historyStringList);
    termTab->addTab(aTerm,query2.value(0).toString());
    aTerm->setWorkingDirectory(query2.value(2).toString());
    aTerm->execute(query2.value(5).toString());
  }
}