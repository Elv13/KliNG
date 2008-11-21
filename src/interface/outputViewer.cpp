#include "outputViewer.h"

#include <QtGui/QVBoxLayout>
#include <KStandardDirs>
#include <KIO/NetAccess>
#include <QFile>
#include <QTextStream>
#include <KPushButton>
#include <KLocalizedString>
#include <KIcon>
#include <QtSql>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QFont>
#include <QGraphicsTextItem>

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
    
    //BEGINING test graphic view

    
    QGraphicsScene* scene = new QGraphicsScene;
    QBrush aBrush(QColor("#3333dd"));
    QBrush aBrush2(QColor("#cccccc"));
    QFont aFont;
    aFont.setPixelSize(8);
    scene->addLine(25, 5, 25, 100,QPen(aBrush2,2));
    scene->addLine(25, 103, (10*20+40), 103,QPen(aBrush2,2));
    QGraphicsTextItem* cpuLabel = scene->addText("CPU%");
    cpuLabel->setPos(3,55);
    cpuLabel->rotate(270);
    (scene->addText("Second"))->setPos(((10*20+30)/2)-35,103);
    char fakeProsess[10] = {74,82,68,57,25,58,82,67,26,92};
    for (int i =0; i < 10; i++) {
      QGraphicsRectItem* anItem = new QGraphicsRectItem((i*20)+30,100 - fakeProsess[i],15,fakeProsess[i]);
      anItem->setBrush(aBrush);
      anItem->setToolTip("CPU usage: "+QString::number(fakeProsess[i])+"% \nMemory usage: N/A\nRun since: "+QString::number(i*15)+" second");
      scene->addItem(anItem);
      scene->addLine((i*20)+38, 101, (i*20)+38, 105,QPen(aBrush2,2));
    }
    
   
   
    
    QGraphicsView* aGraphicView = new QGraphicsView(scene);
    aGraphicView->setMaximumSize(99999,131);
    aGraphicView->setMinimumSize(0,131);
    aGraphicView->setAlignment(Qt::AlignLeft);
    
    centralLayout->addWidget(aGraphicView);
    
 
    //END test graphic view
    
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
