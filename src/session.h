#ifndef DEF_SESSION
#define DEF_SESSION

#include <QVector>
#include <QString>
#include <KIcon>

  struct sessionItem {
    int key;
    QString name;
    QString icon;
    QString path;
    int input; //TODO make an Enum
    int type; //TODO make an enum 
    int session;
    QString command;
  };

  class Session {
    public:
      Session();
      Session(int key, QString name);
      QString getName();
      void setName(QString name);
      void setKey(int key);
      int getKey();
      void setItem(QVector<sessionItem> item);
      QVector<sessionItem> getItem();
      void save();
      
    private:
      bool edited;
      bool isNew;
      int key;
      QString name;
      QVector<sessionItem> item;
  };
#endif