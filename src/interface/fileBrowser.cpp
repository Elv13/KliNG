#define _FILE_OFFSET_BITS 64
#include "fileBrowser.h"
#include <QStringList>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>

  FileBrowser::FileBrowser(QWidget* parent, QTextEdit* term) : QWidget(parent) {
    parentTerm = term;
    browserLayout = new QVBoxLayout(this);
    lblCurrentDir = new QLabel(this);
    lblCurrentDir->setText("test");
    browserLayout->addWidget(lblCurrentDir);
    
    tblDetailsView = new QTableWidget(this);
    tblDetailsView->verticalHeader()->hide();
    tblDetailsView->setColumnCount(4);
    setupHeader();
    browserLayout->addWidget(tblDetailsView);
    
    btnBackToStandardMode = new KPushButton(this);
    btnBackToStandardMode->setText("Return to terminal");
    btnBackToStandardMode->setIcon(KIcon("go-previous"));
    browserLayout->addWidget(btnBackToStandardMode);

    icnFolder = new KIcon("folder");
    icnFile = new KIcon("text-x-generic");
    
    connect( tblDetailsView, SIGNAL( itemDoubleClicked (QTableWidgetItem*) ), this, SLOT( openDir(QTableWidgetItem*) ) );
    connect( btnBackToStandardMode, SIGNAL( clicked () ), this, SLOT( backToStandardMode_clicked() ) );
    
    browserDir("/home/lepagee", true, true);
  }

  bool FileBrowser::browserDir(QString path, bool setPWD, bool showHidden) {  
    showHiddenFile = showHidden;
    clearMe();
    unsigned int rowCount =0;
    unsigned int currentRow =0;
    QStringList UNKNOWN;
    QStringList FIFO;
    QStringList CHR;
    QStringList DIR;
    QStringList BLK;
    QStringList REG;
    QStringList LNK;
    QStringList SOCK;
    QStringList WHT;
    
    if (path[0] == '/') 
      currentDir = path;
    else 
      currentDir =  get_current_dir_name() + path;
    
    if (setPWD == true) {
      chdir(currentDir.toStdString().c_str());
      emit addToHistory("cd " +currentDir);
    }

    struct dirent **namelist;
    int n;   
    int i=0;
    n = scandir(path.toStdString().c_str(), &namelist, 0, alphasort);
    if (n < 0)
      perror("scandir");
    else
      while((n - i) > 0) {
        if (namelist[i]->d_type == DT_UNKNOWN) 
          UNKNOWN << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_FIFO) 
          FIFO << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_CHR) 
          CHR << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_DIR) 
          DIR << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_BLK) 
          BLK << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_REG) 
          REG << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_LNK) 
          LNK << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_SOCK) 
          SOCK << namelist[i]->d_name;
        else if (namelist[i]->d_type == DT_WHT) 
          WHT << namelist[i]->d_name;
        i++;
      }
      
      int hiddenItem =0;
      if (path.right(1) != "/")
        path += "/";
      QStringList* fileList[] = {&DIR , &UNKNOWN , &FIFO , &CHR ,&BLK , &REG , &LNK , &SOCK , &WHT};
      for (int j=0; j < 8; j++ ) {
        for (int k=0; k < fileList[j]->size(); k++) {
          if (((showHidden == false) && (fileList[j]->at(k)[0] != '.')) || (showHidden == true)) {
            QTableWidgetItem* aFile = new QTableWidgetItem();
            //aFile->setFlags(Qt::ItemIsSelectable);
            switch (j) {
              case 0:
                aFile->setIcon(*icnFolder);
                aFile->setText(fileList[j]->at(k));
                break;
              default:
                aFile->setIcon(*icnFile);
                aFile->setText(fileList[j]->at(k));
            }
            tblDetailsView->setRowCount(++rowCount);
            tblDetailsView->setItem(rowCount-1,0,aFile);
            
            QTableWidgetItem* aFileSize = new QTableWidgetItem();
            aFileSize->setText(getSize(path+fileList[j]->at(k),false));
            tblDetailsView->setItem(rowCount-1,1,aFileSize);
            
            QTableWidgetItem* aFilePermissions = new QTableWidgetItem();
            aFilePermissions->setText(getPermission(path+fileList[j]->at(k)));
            tblDetailsView->setItem(rowCount-1,2,aFilePermissions);
            
            QTableWidgetItem* aFileModDate = new QTableWidgetItem();
            aFileModDate->setText(getFileModDate(path+fileList[j]->at(k)));
            tblDetailsView->setItem(rowCount-1,3,aFileModDate);
          }
          
          if (fileList[j]->at(k)[0] == '.')
            hiddenItem++;
        }
      }
    lblCurrentDir->setText("<b>" + currentDir + "</b> (" + QString::number(rowCount -2) + " total item, " + QString::number(hiddenItem - 2) + " hidden, " + QString::number(rowCount - hiddenItem) + " visible)");
  }

  bool FileBrowser::enterDir(QString name) {
    //TODO //will calculte a better path (no more ../dir/../dir2
  }

  QString FileBrowser::getCurrentDir() {
    
  }

  void FileBrowser::clearMe() {
    tblDetailsView->clear();
    tblDetailsView->setRowCount(0);
    setupHeader();
  }

  bool FileBrowser::isReadable() {
    
  }

  bool FileBrowser::isWritable() {
    
  }

  bool FileBrowser::isExecutable() {
    
  }

  QString FileBrowser::getPermission(QString fileName) {
    QString accesses[] = {"...", "..x", ".w.", ".wx", "r..", "r.x", "rw.", "rwx"};
    struct stat status_buf;
    stat(fileName.toStdString().c_str(), &status_buf);
    //return accesses[status_buf.st_mode];
    QString buffer;
    for(int i = 6; i >= 0; i -=3)
      buffer += accesses[(status_buf.st_mode >> i) & 7] + QString("-");
    buffer.chop(1);
    return buffer;
  }

  QString FileBrowser::getSize(QString fileName, bool rawData) {
    struct stat status_buf;
    stat(fileName.toStdString().c_str(), &status_buf);
    if(rawData == true)
      return QString(QString::number(status_buf.st_size));
    else {
      double size;
      if (status_buf.st_size > 1024) {
        size = status_buf.st_size / 1024;
        if (size > 1024) {
          size = size /1024;
          if (size > 1024) {
            size = size /1024;
            if (size > 1024) {
              size = size /1024;
              return QString(QString::number(size, 'f', 2) + "T");
            }
            else
              return QString(QString::number(size, 'f', 2) + "G");
          }
          else
            return QString(QString::number(size, 'f', 2) + "M");
        }
        else
          return QString(QString::number(size, 'f', 2) + "K");
      }
      else
        size = status_buf.st_size;
        return QString(QString::number(size, 'f', 2));
    }
  }

  QString FileBrowser::getFileModDate(QString Name) {
    tm* dateTime;
    struct stat status_buf;
    stat(Name.toStdString().c_str(), &status_buf);
    dateTime = gmtime(&status_buf.st_mtime);
    return QString(QString::number(dateTime->tm_mday) + "/" + QString::number(dateTime->tm_mon) + "/" + QString::number(dateTime->tm_year) + " " + QString::number(dateTime->tm_hour) + ":" + QString::number(dateTime->tm_min) + ":" + QString::number(dateTime->tm_sec));
  }

  KIcon FileBrowser::getIcon(QString fileName) {
    
  }

  void FileBrowser::openDir(QTableWidgetItem * item) {
    if (currentDir.right(1) != "/")
      currentDir += "/";
    browserDir(currentDir + item->text(), true, showHiddenFile);
  }

  void FileBrowser::backToStandardMode_clicked() {
    this->hide();
    parentTerm->show();
  }

  void FileBrowser::setupHeader() {
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    tblDetailsView->setHorizontalHeaderItem(0, __colItem);
    tblDetailsView->horizontalHeaderItem(0)->setText("Name");
    tblDetailsView->setColumnWidth(0,400); //FIXME
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    tblDetailsView->setHorizontalHeaderItem(1, __colItem1);
    tblDetailsView->horizontalHeaderItem(1)->setText("Size");
    tblDetailsView->setColumnWidth(1,75);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    tblDetailsView->setHorizontalHeaderItem(2, __colItem2);
    tblDetailsView->horizontalHeaderItem(2)->setText("Permissions");
    tblDetailsView->setColumnWidth(2,80);
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    tblDetailsView->setHorizontalHeaderItem(3, __colItem3);
    tblDetailsView->horizontalHeaderItem(3)->setText("Modification");
    tblDetailsView->setColumnWidth(3,140);
  }
