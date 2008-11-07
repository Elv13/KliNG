#ifndef DEF_ADVANCED_SCRIPT_MANAGER
#define DEF_ADVANCED_SCRIPT_MANAGER
#include <QWidget>
#include <KPushButton>
#include <QTableWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QLabel>


QT_BEGIN_NAMESPACE

  class AdvancedScriptManager : public QWidget {
    Q_OBJECT

    public:
      AdvancedScriptManager(QWidget* parent);
      KPushButton* addScript;
      KPushButton* manageCategories;
      QTableWidget* tblScript;
      QTableWidget* tblExecute;
      QTableWidget* tblVersion;
      QLabel* lblDescription;
      QLabel* lblExecNb;
      QLabel* lblExecNbValue;
      QLabel* lblName;
      QLabel* lblNameValue;
      QLabel* lblCreation;
      QLabel* lblCreationValue;
      QLabel* lblNbEdition;
      QLabel* lblNbEditionValue;
      QLabel* lblLastEditDate;
      QLabel* lblLastEditDateValue;
      QLabel* lblMoyExecTime;
      QLabel* lblMoyExecTimeValue;
      QListWidget* lstCategories;
      QTabWidget* tabDetails;
      QWidget* tabDescriptionContent;
      QWidget* tabInfoContent;
      
    private:
      void loadCategories();
      void setupHeader();
      void setupHeaderLog();
      void displayScriptExecLog(QString name);
      void displayScriptVersion(QString name);
      void setupHeaderVersion();
    private slots:
      void loadScriptList(QListWidgetItem* current, QListWidgetItem* previous);
      void scriptSelected(int row, int coulmn);
  };
#endif