#include "sessionLoader.h"
#include <QtSql>
#include <QSqlDatabase>

SessionLoader::SessionLoader(QWidget* parent, TermSession* aTermSession) : KDialog(parent) {
  this->aTermSession = aTermSession;
  setCaption( "Add new job" );
  setButtons( KDialog::Ok | KDialog::Cancel );
  
  lstSession = new QListWidget();
  setMainWidget(lstSession);
  lstSession->setGeometry(QRect(206, 24, 150, 150));
  QSqlQuery query;
  query.exec("SELECT NAME FROM TSESSION");
  
  while (query.next()) {
    lstSession->addItem(query.value(0).toString());
    //lstSession->setCurrentIndex(0);
  }

  connect( this, SIGNAL( okClicked() ), this, SLOT( loadSession() ) );
}

void SessionLoader::loadSession() {
  aTermSession->loadSession(lstSession->currentItem()->text());
}