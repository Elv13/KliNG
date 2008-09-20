#include "term.h"

#include "../Shell.h"
#include "history.h"
#include "completer.h"
#include <signal.h>
#include "kcombobox.h"
#include "klineedit.h"
#include "kpushbutton.h"
#include <QtGui/QTextEdit>
#include <kicon.h>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QSpacerItem>
#include <QLabel>
#include <QPixmap>
#include <QScrollBar>
#include <QPoint>



Term::Term(History* aDockHistory, QWidget* parent, QStringList* commandStringList, QStringList* historyStringList) : QWidget(parent) {
    dockHistory = aDockHistory;
    //tabShell = new QWidget();
    setObjectName(QString::fromUtf8("tabShell"));
    setGeometry(QRect(0, 0, 520, 609));
    verticalLayout_6 = new QVBoxLayout(this);
    verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
    frame = new QFrame(this);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setMinimumSize(QSize(0, 20));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Plain);
    frame->setMinimumSize(QSize(0, 26));
    frame->setMaximumSize(QSize(16777215, 26));
    frame->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0px;padding:0px;border:0px;border-color:#808000;padding-top:-1px;spacing:0px;");
    frame->hide();
    horizontalLayout_3 = new QHBoxLayout(frame);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    kpushbutton_4 = new KPushButton(frame);
    kpushbutton_4->setObjectName(QString::fromUtf8("kpushbutton_4"));
    kpushbutton_4->setMinimumSize(QSize(22, 22));
    kpushbutton_4->setMaximumSize(QSize(22, 22));
    kpushbutton_4->setStyleSheet(QString::fromUtf8("background-color:  rgb(230, 255, 105);\n"
"border-style: outset;"));
    KIcon icon("window-close");
     kpushbutton_4->setIcon(icon);

   horizontalLayout_3->addWidget(kpushbutton_4);

    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));
    label->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0px;min-height:15px;font-size:12px;padding-top:1px");

    horizontalLayout_3->addWidget(label);

    klineedit_3 = new QLineEdit(frame);
    klineedit_3->setObjectName(QString::fromUtf8("klineedit_3"));
    klineedit_3->setProperty("showClearButton", QVariant(true));
    klineedit_3->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0px;padding:0px;border:1px;border-style:solid;border-color:#808000;spacing:0px;height:15px;min-height:15px;");

    horizontalLayout_3->addWidget(klineedit_3);

    kpushbutton_5 = new KPushButton(frame);
    kpushbutton_5->setObjectName(QString::fromUtf8("kpushbutton_5"));
    kpushbutton_5->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0;border:1;border-style:solid;border-color:#808000;padding-right:5;padding-left:5;spacing:0;min-height:15px");

    horizontalLayout_3->addWidget(kpushbutton_5);


    verticalLayout_6->addWidget(frame);
    
    hlCkbLayout = new QHBoxLayout();
    verticalLayout_6->addLayout(hlCkbLayout);

    ckbShowGUI = new QCheckBox;
    ckbShowGUI->setText("Show command interfaces");
    ckbShowGUI->setChecked(true);
    hlCkbLayout->addWidget(ckbShowGUI);
    
    ckbShowHiddenFile = new QCheckBox;
    ckbShowHiddenFile->setText("Show hidden files");
    ckbShowHiddenFile->setChecked(true);
    hlCkbLayout->addWidget(ckbShowHiddenFile);
    
    QSpacerItem* horizontalSpacer = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hlCkbLayout->addItem(horizontalSpacer);
    
    completerSplitter = new QSplitter(this);
    completerSplitter->setOrientation(Qt::Vertical);
    QList<int> sizeList;
    sizeList << 1 << 4;
    completerSplitter->setSizes(sizeList);
    completerSplitter->setOpaqueResize(false);
    verticalLayout_6->addWidget(completerSplitter);
    
    rtfCmdOutput = new QTextEdit(this);
    rtfCmdOutput->setObjectName(QString::fromUtf8("rtfCmdOutput"));
    rtfCmdOutput->setAcceptRichText(false);
    rtfCmdOutput->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
    rtfCmdOutput->hide(); //TODO remove this

    //verticalLayout_6->addWidget(rtfCmdOutput);
    completerSplitter->addWidget(rtfCmdOutput);
    

    fileBrowser = new FileBrowser(this, rtfCmdOutput);
    //verticalLayout_6->addWidget(fileBrowser);
    completerSplitter->addWidget(fileBrowser);

    hlCommand = new QHBoxLayout();
    hlCommand->setObjectName(QString::fromUtf8("hlCommand"));

    cmdStatus = new QLabel(this);
    cmdStatus->setObjectName(QString::fromUtf8("cmdStatus"));
    pxmCmdInactive = new QPixmap("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearI.png");
    
    cmdStatus->setPixmap(*pxmCmdInactive);
    cmdStatus->setMaximumSize(QSize(22, 22));
    cmdStatus->setMinimumSize(QSize(22, 22));

    hlCommand->addWidget(cmdStatus);

    txtCommand = new KLineEdit(this);
    txtCommand->setObjectName(QString::fromUtf8("txtCommand"));
    txtCommand->setProperty("showClearButton", QVariant(true));

    hlCommand->addWidget(txtCommand);



    cbbOutModifier = new KComboBox(this);
    cbbOutModifier->setObjectName(QString::fromUtf8("cbbOutModifier"));
    cbbOutModifier->addItem("   modifiers");
    cbbOutModifier->addItem("| grep <text>");
    cbbOutModifier->addItem("| less <text>");
    cbbOutModifier->addItem("| more");
    cbbOutModifier->addItem(">  <file>");
    cbbOutModifier->addItem(">>  <file>");

    hlCommand->addWidget(cbbOutModifier);

    kpushbutton_3 = new KPushButton(this);
    kpushbutton_3->setObjectName(QString::fromUtf8("kpushbutton_3"));
    kpushbutton_3->setMaximumSize(QSize(27, 27));
    KIcon icnKill("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/kill.png");
    kpushbutton_3->setIcon(icnKill);

    hlCommand->addWidget(kpushbutton_3);

    completer = new Completer(this, commandStringList, historyStringList);
    //completer->setMinimumSize(0,50);
    //completer->resize(completer->minimumSize());
    //completer->setMaximumSize(99999,70);
    //completer->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    completerSplitter->addWidget(completer);

    verticalLayout_6->addLayout(hlCommand);
    completer->hide();

    QObject::connect(kpushbutton_4, SIGNAL(clicked()), frame, SLOT(hide()));
    QObject::connect(klineedit_3, SIGNAL(returnPressed()), this, SLOT(searchCmdOutput()));
    QObject::connect(kpushbutton_5, SIGNAL(clicked()), this, SLOT(searchCmdOutput()));
    QObject::connect(txtCommand, SIGNAL(returnPressed()), this, SLOT(sendCommand()));
    QObject::connect(txtCommand, SIGNAL(textChanged(QString)), this, SLOT(cmdInfoChanged(QString)));
    QObject::connect(txtCommand, SIGNAL(textChanged(QString)), this, SLOT(resizeCompleter()));
    QObject::connect(this, SIGNAL(cmdInfo(QString,int)), completer, SLOT(updateCommand(QString,int)));
    QObject::connect(this, SIGNAL(cmdInfo(QString,int)), completer, SLOT(updateHistory(QString,int)));
    QObject::connect(this, SIGNAL(cmdInfo(QString,int)), completer, SLOT(updateFile(QString,int)));
    QObject::connect(fileBrowser, SIGNAL(addToHistory(QString)), this, SLOT(addToHistory(QString)));
    //QObject::connect(kpushbutton_3, SIGNAL(clicked()), this, SLOT(sendCommand()));

    label->setText("Search:");
    kpushbutton_5->setText("search");
    kpushbutton_3->setDisabled(true);


    

}

Term::~Term() {}

/**
  send the txtCommand text to the terminal emulator
*/
void Term::sendCommand() {
  completer->hide();
  if (txtCommand->text() != "") {
    pxmCmdInactive->load("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearA.png");
    cmdStatus->setPixmap(*pxmCmdInactive);
    txtCommand->setDisabled(true);
    kpushbutton_3->setDisabled(false);
    //Shell aShell(this);
    aThread = new ShellThread(txtCommand->text(), 0, ckbShowGUI);
    QObject::connect(aThread->aShell, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
    QObject::connect(aThread->aShell, SIGNAL(newLine(QString)), this, SLOT(updateCmdOutput(QString)));
    QObject::connect(aThread->aShell, SIGNAL(clearCmdOutput()), this, SLOT(clearCmdOutput()));
    QObject::connect(aThread->aShell, SIGNAL(showFileBrowser(QString, bool)), this, SLOT(showFileBrowser(QString, bool)));
    dockHistory->addItem(txtCommand->text(), true);
    //QSqlQuery query;
    //query.exec("insert into THISTORY (COMMAND, TIME) values ('"+ txtCommand->text() +"', 2)"); //TODO add corect time
    //aShell.analyseCommand((txtCommand->text().toStdString()));
    //ThreadExec aThread(this);
    //QObject::disconnect(aThread->aShell, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
    aThread->start();
    //aPid = aThread->aShell->fork_pid;
    QObject::connect(kpushbutton_3, SIGNAL(clicked()), this, SLOT(killPros()));
  }
}



/**
  the command line tab search box function
*/
void Term::searchCmdOutput() {

  if (klineedit_3->text() != "") {
	rtfCmdOutput->find(klineedit_3->text());
  }
}

void Term::updateCmdOutput(QString line){
  rtfCmdOutput->append(line);
  rtfCmdOutput->verticalScrollBar()->setValue(rtfCmdOutput->verticalScrollBar()->maximum());
}
void Term::resetCmdInputLine() {
  //rtfCmdOutput->append("\n");
  rtfCmdOutput->verticalScrollBar()->setValue(rtfCmdOutput->verticalScrollBar()->maximum());
  txtCommand->clear();
  pxmCmdInactive->load("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearI.png");
  cmdStatus->setPixmap(*pxmCmdInactive);
  kpushbutton_3->setDisabled(true);
  txtCommand->setEnabled(true);
  txtCommand->setFocus();
}

void Term::clearCmdOutput(){
  rtfCmdOutput->clear();
}

void Term::killPros() {	
  int aPid = aThread->aShell->fork_pid;
  printf("I am going do kill prosess number: %i \n",aThread->aShell->fork_pid);
  aThread->terminate();
  //delete aThread;
  kill(aPid, 9);
  resetCmdInputLine();
  
}

void Term::resizeCompleter() {
  if (completer->isHidden()) {
   completer->setGeometry (rtfCmdOutput->x() , rtfCmdOutput->y() + rtfCmdOutput->height() - 150, rtfCmdOutput->width(), 150 );
   completer->show();
  }
}

void Term::cmdInfoChanged(QString name) {
  emit cmdInfo(name, txtCommand->cursorPosition());
}

void Term::showFileBrowser(QString path, bool setPath) {
  fileBrowser->browserDir(path, setPath, ckbShowHiddenFile->isChecked());
  fileBrowser->show();
  rtfCmdOutput->hide();
  //ckbShowGUI->hide();
}

void Term::addToHistory(QString line) {
  dockHistory->addItem(line, true);
}