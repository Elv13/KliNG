#include "outputViewer.h"

#include <QtGui/QVBoxLayout>
#include <KStandardDirs>
#include <KIO/NetAccess>
#include <QFile>
#include <QTextStream>
#include <KPushButton>
#include <KIcon>
#include <QtSql>

OutputViewer::OutputViewer(QWidget *parent, uint id) : KDialog( parent ) {
    this->id = id;
    setCaption( "View output #" + id );
    setButtons( KDialog::User1 | KDialog::User2 | KDialog::Ok );
    
    button(KDialog::User1)->setText("Keep");
    button(KDialog::User1)->setCheckable(true);
    QSqlQuery query;
    query.exec("SELECT KEEP FROM THISTORY WHERE THISTORY_KEY = " + QString::number(id));
    
    query.next();
    button(KDialog::User1)->setChecked(query.value(0).toBool());
    button(KDialog::User1)->setIcon(KIcon("document-encrypt"));
    
    button(KDialog::User2)->setIcon(KIcon("edit-delete"));
    button(KDialog::User2)->setText("Delete");
    
    resize(700,450);
    QWidget* centralwidget = new QWidget;
    QVBoxLayout* centralLayout = new QVBoxLayout(centralwidget);
    centralwidget->setLayout(centralLayout);
    setMainWidget(centralwidget);
    
    centralTextBrowser = new KTextBrowser();
    centralLayout->addWidget(centralTextBrowser);
    
    QString tmpFile;
    if(KIO::NetAccess::download(KStandardDirs::locateLocal("appdata", "/output/"+QString::number(id)), tmpFile, this)) {
      QFile file(tmpFile);
      file.open(QIODevice::ReadOnly);
      centralTextBrowser->setText(QTextStream(&file).readAll());

      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else {
      centralTextBrowser->setPlainText("File not found! Please do not delete those file manually, if you thing this is a bug, report it.");
    }
    
    connect(button(KDialog::User1), SIGNAL(toggled(bool)), this, SLOT(setKeep(bool)));
}

void OutputViewer::setKeep(bool value) {
    QSqlQuery query;
    query.exec("update THISTORY SET KEEP = '" + QString::number(value) + "' WHERE THISTORY_KEY = " + QString::number(id));
}
