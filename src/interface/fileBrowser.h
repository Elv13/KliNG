#ifndef DEF_FILEBROWSER
#define DEF_FILEBROWSER
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <KPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <KIcon>

QT_BEGIN_NAMESPACE

  class FileBrowser : public QWidget {
    Q_OBJECT

    public:
      FileBrowser(QWidget* parent, QTextEdit* term);
      bool browserDir(QString path, bool setPWD, bool showHidden);
      bool enterDir(QString name);
      QString getCurrentDir();
      
    private:
      QLabel* lblCurrentDir;
      QVBoxLayout* browserLayout;
      QTableWidget* tblDetailsView;
      KPushButton* btnBackToStandardMode;
      //QCheckBox* ckbHideThisMode;
      KIcon* icnFolder;
      KIcon* icnFile;
      QString currentDir;
      QTextEdit* parentTerm;
      bool showHiddenFile;
      
      void clearMe();
      bool isReadable();
      bool isWritable();
      bool isExecutable();
      void setupHeader();
      QString getPermission(QString fileName);
      QString getSize(QString fileName, bool rawData);
      QString getFileModDate(QString Name);
      KIcon getIcon(QString fileName);
      
    private slots:
      void openDir(QTableWidgetItem* item);
      void backToStandardMode_clicked();
      
    signals:
      void addToHistory(QString);
  };
#endif
