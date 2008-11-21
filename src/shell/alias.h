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
    QString getName();
    QString getCommand();
    QString getArg(int index);
    QVector<QString> getArgs();
    void addArg(QString arg);
    void setName(QString name);
    void setCommand(QString command);
    void setArgs(QVector<QString> args);
    void save();
    static QVector<Alias>* getAlias();
    
  private:
    bool enable;
    bool edited;
    int key;
    QString name;
    QString command;
    QVector<QString> args;
};

#endif