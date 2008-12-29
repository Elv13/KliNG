#ifndef DEF_TERMSESSION
#define DEF_TERMSESSION
#include <KTabWidget>
#include <QVector>
#include <QStringList>
#include <QHBoxLayout>
#include "term.h"
#include "history.h"

class TermSession : public QWidget {
    Q_OBJECT
    public:
      TermSession(QWidget* parent);
      uint count;
      
    private:
      KTabWidget* termTab;
      Term* baseTerm;
      History* aDockHistory;
      QStringList* commandList;
      QStringList* aliasList;
      QStringList* defaultArgsList;
      QStringList* functionList;
      QStringList* historyStringList;
      QHBoxLayout* aLayout;
      
    public:
      Term* getCurrentTerm();
      void loadSession(QString name);
  
    public slots:
      void addTerm();
      void addTerm(History* aDockHistory, QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList, QStringList* historyStringList);
      void remTerm();
      
  };
#endif