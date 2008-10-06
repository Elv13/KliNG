#ifndef COMPLETER_H
#define COMPLETER_H

#include <QtCore/QVariant>
//#include <QtGui/QAction>
//#include <QtGui/QApplication>
//#include <QtGui/QButtonGroup>
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
#include <QFont>
#include <QStringList>
#include <KIcon>

  struct FilteredFileStruct {
    bool isEmpty;
    QStringList UNKNOWN;
    QStringList FIFO;
    QStringList CHR;
    QStringList DIR;
    QStringList BLK;
    QStringList REG;
    QStringList LNK;
    QStringList SOCK;
    QStringList WHT;
  };

  class Completer : public QWidget {
    Q_OBJECT

    public:
      Completer(QWidget* parent, QStringList* slCommandList, QStringList* slHistory);
      ~Completer();
      
      QWidget *centralwidget;
      QVBoxLayout *verticalLayout;
      QHBoxLayout *horizontalLayout;
      QCheckBox *chkCommand;
      QFrame *line;
      QCheckBox *chkHistory;
      QFrame *line_2;
      QCheckBox *chkPath;
      QFrame *line_3;
      QCheckBox *chkOptions;
      QFrame *line_4;
      QCheckBox *chkOther;
      QFrame *line_5;
      QSpacerItem *horizontalSpacer;
      QTreeWidget *tvCompletion;
      QBrush* topLvlTvItemBrush;
      QFont* topLvlTvItemFont;
      KPushButton* btnClose;
      KIcon* icnClock;
      KIcon* icnExec;
      KIcon* icnFolder;
      KIcon* icnFile;
      QStringList* stringListCommand;
      QStringList* stringListHistory;
      QStringList filteredCommand;
      QStringList filteredHistory;
      FilteredFileStruct filteredFile;
      
    private:
      int getCurrentParamPosition(QString line, int index);
      QString getParam(QString line, int index);
      void clearPath();


    private slots:
      void chkCommand_checked(int state);
      void chkHistory_checked(int state);
      void chkPath_checked(int state);
      void chkOptions_checked(int state);
      void chkOther_checked(int state);
      void updateCommand(QString name, int index);
      void updateHistory(QString name, int index);
      void updateFile(QString name, int index);
  };
#endif