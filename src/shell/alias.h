#ifndef DEF_ALIAS
#define DEF_ALIAS

#include <QVector>
#include <QString>

  class Alias {
    public:
      Alias();
      Alias(QString name,QString command,bool enable, int key);
      int getKey();
      bool getEnable();
      void setKey(int key);
      void setEnable(bool value);
      bool getEdited();
      QString getName();
      QString getCommand();
      QString getArg(int index);
      QVector<QString> getArgs();
      void addArg(QString arg);
      void setName(QString name);
      void setCommand(QString command2);
      void setArgs(QVector<QString> args);
      void save();
      static QVector<Alias>* getAlias();
      static int indexOf(QVector<Alias>* aliasList, int key);
      bool operator==(const QString&) const;
      bool operator==(const int&) const;
      
    private:
      bool enable;
      bool edited;
      int key;
      QString name;
      QString command;
      QVector<QString> args;
  };

  bool operator==(Alias& x, QString& y);
  bool operator==(Alias& x, int y);
  
  bool operator==(QString& y, Alias& x);
  bool operator==(int& y, Alias& x);
#endif