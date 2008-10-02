#include "completer.h"

#include <QtCore/QVariant>
//#include <QtGui/QAction>
//#include <QtGui/QApplication>
//#include <QtGui/QButtonGroup>
#include <unistd.h>
#include <dirent.h>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <KPushButton>
#include <QBrush>
#include <QColor>
#include <QStringList>

Completer::Completer(QWidget* parent, QStringList* slCommandList, QStringList* slHistory) : QWidget(parent) {
    stringListCommand = slCommandList;
    stringListHistory = slHistory;
    //setBaseSize(9999,40);
    //setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    filteredFile.isEmpty = true;
    //resize(564, 229);
    
    setMaximumSize(9999,170);

    icnFolder = new KIcon("folder");
    icnFile = new KIcon("text-x-generic");
    icnClock = new KIcon("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/clock.png");
    icnExec = new KIcon("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearI.png");
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    chkCommand = new QCheckBox(this);
    chkCommand->setObjectName(QString::fromUtf8("chkCommand"));
    chkCommand->setChecked(true);

    horizontalLayout->addWidget(chkCommand);

    line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    horizontalLayout->addWidget(line);

    chkHistory = new QCheckBox(this);
    chkHistory->setObjectName(QString::fromUtf8("chkHistory"));
    chkHistory->setChecked(true);

    horizontalLayout->addWidget(chkHistory);

    line_2 = new QFrame(this);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);

    horizontalLayout->addWidget(line_2);

    chkPath = new QCheckBox(this);
    chkPath->setObjectName(QString::fromUtf8("chkPath"));
    chkPath->setChecked(true);

    horizontalLayout->addWidget(chkPath);

    line_3 = new QFrame(this);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::VLine);
    line_3->setFrameShadow(QFrame::Sunken);

    horizontalLayout->addWidget(line_3);

    chkOptions = new QCheckBox(this);
    chkOptions->setObjectName(QString::fromUtf8("chkOptions"));
    chkOptions->setChecked(true);

    horizontalLayout->addWidget(chkOptions);

    line_4 = new QFrame(this);
    line_4->setObjectName(QString::fromUtf8("line_4"));
    line_4->setFrameShape(QFrame::VLine);
    line_4->setFrameShadow(QFrame::Sunken);

    horizontalLayout->addWidget(line_4);

    chkOther = new QCheckBox(this);
    chkOther->setObjectName(QString::fromUtf8("chkOther"));
    chkOther->setChecked(true);

    horizontalLayout->addWidget(chkOther);

    line_5 = new QFrame(this);
    line_5->setObjectName(QString::fromUtf8("line_5"));
    line_5->setFrameShape(QFrame::VLine);
    line_5->setFrameShadow(QFrame::Sunken);

    horizontalLayout->addWidget(line_5);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    btnClose = new KPushButton(this);
    btnClose->setText("Close");
    btnClose->setIcon(KIcon("dialog-close"));

    horizontalLayout->addWidget(btnClose);


    verticalLayout->addLayout(horizontalLayout);


    topLvlTvItemFont= new QFont();
    topLvlTvItemFont->setBold(true);

    QColor* aQColor = new QColor("#17569D");

    topLvlTvItemBrush = new QBrush(*aQColor);

    //topLvlTvItemBrush->setColor(Qt::red);

    QSize* aSize = new QSize();
    aSize->setHeight(20);

    tvCompletion = new QTreeWidget(this);
    QTreeWidgetItem *__treeItem = new QTreeWidgetItem(tvCompletion);
    __treeItem->setBackground(0, *topLvlTvItemBrush);

    QTreeWidgetItem *__treeItem1 = new QTreeWidgetItem(tvCompletion);

    new QTreeWidgetItem(tvCompletion);
    new QTreeWidgetItem(tvCompletion);
    new QTreeWidgetItem(tvCompletion);

    tvCompletion->setObjectName(QString::fromUtf8("tvCompletion"));
    tvCompletion->setAutoExpandDelay(0);
    tvCompletion->setIndentation(0);
    //tvCompletion->setAnimated(true);
    tvCompletion->setWordWrap(true);

    verticalLayout->addWidget(tvCompletion);
    setAutoFillBackground(true);

    QMetaObject::connectSlotsByName(this);

    //MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    chkCommand->setText("Command");
    chkHistory->setText("History");
    chkPath->setText("Path/File");
    chkOptions->setText("Options");
    chkOther->setText("Other");
    tvCompletion->headerItem()->setText(0, "Item");
    tvCompletion->headerItem()->setText(1, "Description");

    const bool __sortingEnabled = tvCompletion->isSortingEnabled();
    tvCompletion->setSortingEnabled(false);
    tvCompletion->topLevelItem(0)->setText(0, "Command");
    tvCompletion->topLevelItem(0)->setBackground(0, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(0)->setBackground(1, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(0)->setForeground(0, QBrush(QColor(0,0,0)));
    tvCompletion->topLevelItem(0)->setFont(0, *topLvlTvItemFont);
    tvCompletion->topLevelItem(0)->setSizeHint(0, *aSize);
    tvCompletion->topLevelItem(0)->setExpanded(true);
    tvCompletion->topLevelItem(1)->setText(0, "History");
    tvCompletion->topLevelItem(1)->setExpanded(true);
    tvCompletion->topLevelItem(1)->setBackground(0, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(1)->setBackground(1, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(1)->setForeground(0, QBrush(QColor(0,0,0)));
    tvCompletion->topLevelItem(1)->setFont(0, *topLvlTvItemFont);
    tvCompletion->topLevelItem(2)->setSizeHint(0, *aSize);
    tvCompletion->topLevelItem(2)->setText(0, "Path/File");
    tvCompletion->topLevelItem(2)->setExpanded(true);
    tvCompletion->topLevelItem(2)->setBackground(0, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(2)->setBackground(1, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(2)->setForeground(0, QBrush(QColor(0,0,0)));
    tvCompletion->topLevelItem(2)->setFont(0, *topLvlTvItemFont);
    tvCompletion->topLevelItem(2)->setSizeHint(0, *aSize);
    tvCompletion->topLevelItem(2)->setExpanded(true);
    tvCompletion->topLevelItem(3)->setText(0, "Options");
    tvCompletion->topLevelItem(3)->setBackground(0, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(3)->setBackground(1, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(3)->setForeground(0, QBrush(QColor(0,0,0)));
    tvCompletion->topLevelItem(3)->setFont(0, *topLvlTvItemFont);
    tvCompletion->topLevelItem(3)->setSizeHint(0, *aSize);
    tvCompletion->topLevelItem(4)->setText(0, "Other");
    tvCompletion->topLevelItem(4)->setExpanded(true);
    tvCompletion->topLevelItem(4)->setBackground(0, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(4)->setBackground(1, *topLvlTvItemBrush);
    tvCompletion->topLevelItem(4)->setForeground(0, QBrush(QColor(0,0,0)));
    tvCompletion->topLevelItem(4)->setFont(0, *topLvlTvItemFont);
    tvCompletion->topLevelItem(4)->setSizeHint(0, *aSize);


    connect( chkCommand, SIGNAL( stateChanged(int) ), this, SLOT( chkCommand_checked(int) ) );
    connect( chkHistory, SIGNAL( stateChanged(int) ), this, SLOT( chkHistory_checked(int) ) );
    connect( chkPath, SIGNAL( stateChanged(int) ), this, SLOT( chkPath_checked(int) ) );
    connect( chkOptions, SIGNAL( stateChanged(int) ), this, SLOT( chkOptions_checked(int) ) );
    connect( chkOther, SIGNAL( stateChanged(int) ), this, SLOT( chkOther_checked(int) ) );
    connect( btnClose, SIGNAL( clicked() ), this, SLOT( hide() ) );


    //updateFile("/home/lepagee/",13);
}

Completer::~Completer() {}

void Completer::chkCommand_checked(int state) {
  if (state == Qt::Checked)
  {
    tvCompletion->topLevelItem(0)->setHidden(false);
  }
  else if (state == Qt::Unchecked)
  {
    tvCompletion->topLevelItem(0)->setHidden(true);
  }
}


void Completer::chkHistory_checked(int state) {
  if (state == Qt::Checked)
  {
    tvCompletion->topLevelItem(1)->setHidden(false);
  }
  else if (state == Qt::Unchecked)
  {
    tvCompletion->topLevelItem(1)->setHidden(true);
  }
}


void Completer::chkPath_checked(int state) {
  if (state == Qt::Checked)
  {
    tvCompletion->topLevelItem(2)->setHidden(false);
  }
  else if (state == Qt::Unchecked)
  {
    tvCompletion->topLevelItem(2)->setHidden(true);
  }
}


void Completer::chkOptions_checked(int state) {
  if (state == Qt::Checked)
  {
    tvCompletion->topLevelItem(3)->setHidden(false);
  }
  else if (state == Qt::Unchecked)
  {
    tvCompletion->topLevelItem(3)->setHidden(true);
  }
}


void Completer::chkOther_checked(int state) {
  if (state == Qt::Checked)
  {
    tvCompletion->topLevelItem(4)->setHidden(false);
  }
  else if (state == Qt::Unchecked)
  {
    tvCompletion->topLevelItem(4)->setHidden(true);
  }
}

void Completer::updateCommand(QString name, int index=0) {
  tvCompletion->topLevelItem(0)->setHidden(false);
  /*if (name.size() == 0) {
    this->hide();
  }*/

  while (tvCompletion->topLevelItem(0)->childCount()) {
    tvCompletion->topLevelItem(0)->removeChild(tvCompletion->topLevelItem(0)->child(0));
  }
  if (chkCommand->isChecked() == true)
    tvCompletion->topLevelItem(0)->setHidden(false);

  if (getCurrentParamPosition(name, index) == 0) {
    int i =0;
    QString command = getParam(name, index);
    
    if (command.size() == 0)
      filteredCommand.clear();
    else if (filteredCommand.isEmpty()) {
      while (i < stringListCommand->size()) {
        if (stringListCommand->at(i).left(command.size()) == command) {
          QTreeWidgetItem* aCommand = new QTreeWidgetItem(tvCompletion->topLevelItem(0));
          aCommand->setIcon(0,*icnExec);
          aCommand->setText(0,stringListCommand->at(i));
          filteredCommand << stringListCommand->at(i);
        }
        i++;
      }
    } 
    else {
      while (i < filteredCommand.size()) {
        if (filteredCommand[i].left(command.size()) == command) {
          QTreeWidgetItem* aCommand = new QTreeWidgetItem(tvCompletion->topLevelItem(0));
          aCommand->setIcon(0,*icnExec);
          aCommand->setText(0,filteredCommand[i]);
          //i++;
        }
        /*else {
          filteredCommand.removeAt(i);
        }*/
        i++;
      }
    }
  }
  else {
    tvCompletion->topLevelItem(0)->setHidden(true);
  }
  if (tvCompletion->topLevelItem(01)->childCount() == false) 
    tvCompletion->topLevelItem(0)->setHidden(true);
}

void Completer::updateHistory(QString name, int index =0) {

  while (tvCompletion->topLevelItem(1)->childCount()) {
    tvCompletion->topLevelItem(1)->removeChild(tvCompletion->topLevelItem(1)->child(0));
  }
  
  if (chkHistory->isChecked() == true)
    tvCompletion->topLevelItem(1)->setHidden(false);

  int i =0;

  if (name.size() == 0)
    filteredHistory.clear();
  else if (filteredHistory.isEmpty()) {
    while (i < stringListHistory->size()) {
      if (stringListHistory->at(i).left(name.size()) == name) {

	if (filteredHistory.indexOf(stringListHistory->at(i)) == -1)
	  filteredHistory << stringListHistory->at(i);
      }
      i++;
    }

    for (int j=0; j < filteredHistory.size(); j++) {
      	QTreeWidgetItem* anHistory = new QTreeWidgetItem(tvCompletion->topLevelItem(1));
	anHistory->setIcon(0,*icnClock);
	anHistory->setText(0,filteredHistory[j]);
    }
  } 
  else {
    while (i < filteredHistory.size()) {
      if (filteredHistory[i].left(name.size()) == name) {
	QTreeWidgetItem* anHistory = new QTreeWidgetItem(tvCompletion->topLevelItem(1));
	anHistory->setIcon(0,*icnClock);
	anHistory->setText(0,filteredHistory[i]);
	//i++;
      }
      /*else {
	printf("I removed: %d \n",i);
	filteredCommand.removeAt(i);
      }*/
      i++;
    }
  }
  if (tvCompletion->topLevelItem(1)->childCount() == false)
    tvCompletion->topLevelItem(1)->setHidden(true);
}


void Completer::updateFile(QString name, int index =0) {
  bool showHidden = false;
  
  while (tvCompletion->topLevelItem(2)->childCount()) {
    tvCompletion->topLevelItem(2)->removeChild(tvCompletion->topLevelItem(2)->child(0));
  }
  
  if (chkPath->isChecked() == true)
    tvCompletion->topLevelItem(2)->setHidden(false);
  
  QString path = getParam(name,index);
  
  
  if (path.right(1) == "/") {
    clearPath();
  }
  else if (path == "") {
      clearPath();
      path = "./";
  }
  
  if (filteredFile.isEmpty == true) {
    filteredFile.isEmpty = false;
    struct dirent **namelist;
    int n;    
    n = scandir(path.toStdString().c_str(), &namelist, 0, alphasort);
    int file;
    if (n < 0)
        perror("scandir");
    else
        while(n--) {
	  printf("NAME: %s   TYPE: %d\n", namelist[n]->d_name,namelist[n]->d_type);
	  if (namelist[n]->d_type == DT_UNKNOWN) {
	    filteredFile.UNKNOWN << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_FIFO) {
	    filteredFile.FIFO << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_CHR) {
	    filteredFile.CHR << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_DIR) {
	    printf("I am here \n");
	    filteredFile.DIR << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_BLK) {
	    filteredFile.BLK << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_REG) {
	    filteredFile.REG << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_LNK) {
	    filteredFile.LNK << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_SOCK) {
	    filteredFile.SOCK << namelist[n]->d_name;
	  }
	  else if (namelist[n]->d_type == DT_WHT) {
	    filteredFile.WHT << namelist[n]->d_name;
	  }
        }
    for (int j=0; j < filteredFile.DIR.size(); j++) {
      if (((showHidden == false) && (filteredFile.DIR[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFolder);
	aFile->setText(0,filteredFile.DIR[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.DIR[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.REG.size(); j++) {
      if (((showHidden == false) && (filteredFile.REG[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.REG[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.REG[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.FIFO.size(); j++) {
      if (((showHidden == false) && (filteredFile.FIFO[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.FIFO[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.FIFO[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.CHR.size(); j++) {
      if (((showHidden == false) && (filteredFile.CHR[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.CHR[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.CHR[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.BLK.size(); j++) {
      if (((showHidden == false) && (filteredFile.BLK[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.BLK[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.BLK[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.LNK.size(); j++) {
      if (((showHidden == false) && (filteredFile.LNK[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.LNK[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.LNK[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.SOCK.size(); j++) {
      if (((showHidden == false) && (filteredFile.SOCK[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.SOCK[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.SOCK[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.WHT.size(); j++) {
      if (((showHidden == false) && (filteredFile.WHT[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.WHT[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.WHT[j]);
        }
      }
    }
    for (int j=0; j < filteredFile.UNKNOWN.size(); j++) {
      if (((showHidden == false) && (filteredFile.UNKNOWN[j][0] == '.')) == false) {
      	QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
	aFile->setIcon(0,*icnFile);
	aFile->setText(0,filteredFile.UNKNOWN[j]+ "/");
        if (path.indexOf("/") != -1) {
          aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) +filteredFile.UNKNOWN[j]);
        }
      }
    }


  } 
  else {
    QStringList* fileList[] = {&filteredFile.DIR ,&filteredFile.UNKNOWN ,&filteredFile.FIFO ,&filteredFile.CHR ,&filteredFile.BLK ,&filteredFile.REG ,&filteredFile.LNK ,&filteredFile.SOCK ,&filteredFile.WHT};
    for (int j=0; j < 8; j++ ) {
      for (int k=0; k < fileList[j]->size(); k++) {
        QString fileName;
        if (path.indexOf("/") != -1) 
          fileName = path.mid(path.lastIndexOf("/") +1, path.size() -1);
        else 
          fileName = path;
        
        if (fileName[0] == '/') {
          fileName.remove(0,1);
        }
        
        
        printf("%s \n",fileName.toStdString().c_str());
        if (fileName == fileList[j]->at(k).left(fileName.size())) {
          QTreeWidgetItem* aFile = new QTreeWidgetItem(tvCompletion->topLevelItem(2));
          switch (j) {
            case 0:
              aFile->setIcon(0,*icnFolder);
              aFile->setText(0,fileList[j]->at(k));
              break;
            default:
              aFile->setIcon(0,*icnFile);
              aFile->setText(0,fileList[j]->at(k));
          }
          if (path.indexOf("/") != -1) {
            aFile->setText(1,path.mid(0,path.lastIndexOf("/")+1) + fileList[j]->at(k));
          }
        }
      }
    }
  }
  if (tvCompletion->topLevelItem(2)->childCount() == false) //TODO fix this
    tvCompletion->topLevelItem(2)->setHidden(true);
}

int Completer::getCurrentParamPosition(QString line, int index) {
  if ((line.indexOf(" ") > index) || (line.indexOf(" ") == -1))
    return 0;
  else 
    return 1; //TODO make this`
}

/**
  Return the current parameter at "index" in the line.
*/
QString Completer::getParam(QString line, int index) {
  if ((line.indexOf(" ") == -1) || (line.indexOf(" ") > index))
    return line.mid(0, index);
  else {
    //printf("\n LastIndexOf=%d\n Line=%s",line.lastIndexOf(' ', index-1),line.toStdString().c_str());
    //QString test = line.mid(line.lastIndexOf(" ", index-1)+1, index);
    //printf("\n %s \n Index: %d \n", test.toStdString().c_str(), index);
    //system("read");
    return line.mid(line.lastIndexOf(" ", index-1)+1, index);
  }
}

void Completer::clearPath() {
  filteredFile.UNKNOWN.clear();
  filteredFile.FIFO.clear();
  filteredFile.CHR.clear();
  filteredFile.DIR.clear();
  filteredFile.BLK.clear();
  filteredFile.REG.clear();
  filteredFile.LNK.clear();
  filteredFile.SOCK.clear();
  filteredFile.WHT.clear();
  filteredFile.isEmpty = true; 
}