#ifndef DEF_SESSIONEDITOR
#define DEF_SESSIONEDITOR
#include <KTabWidget>
#include <KDialog>
#include <QVector>
#include <QStringList>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QVector>
#include <QListWidgetItem>
#include "term.h"
#include "history.h"
#include "../session.h"

class SessionEditor : public KDialog {
    Q_OBJECT
    public:
      SessionEditor(QWidget* parent, Session* aSession);
      
    private:
      QListWidget* lstSessionList;
      QLabel* lblIcon;
      QLabel* lblName;
      QLabel* lblType;
      QLabel* lblConnectionMethod;
      QLabel* lblPublicKey;
      QLabel* lblUsername;
      QLabel* lblPassword;
      QLabel* lblDefaultPath;
      QGroupBox* grbSshField;
      QPushButton* btnAddSession;
      QPushButton* btnRemSession;
      QPushButton* btnIcon;
      QLineEdit* txtSessionName;
      QComboBox* cbbSessionType;
      QComboBox* cbbConnectionMethod;
      QLineEdit* txtPublicKey;
      QLineEdit* txtUsername;
      QLineEdit* txtPassword;
      QLineEdit* txtDefaultPath;
      QComboBox* inputMethod;
      QLineEdit* txtDefaultCommand;
      QLabel* lblInputMethod;
      QLabel* lblDefaultCommand;
      
      Session* aSession;
      QVector<sessionItem> itemList;
      sessionItem* currentItem;
      
    private slots:
      void itemChanged(QListWidgetItem* item1, QListWidgetItem* item2);
      void apply();
      void updateCurrentName(QString text);
      void addItem();
  };
#endif