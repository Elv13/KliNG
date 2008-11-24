#include "alias.h"
#include <QtSql>

  Alias::Alias() {
    edited = false;
  }
  
  Alias::Alias(QString name,QString command,bool enable, int key) {
    edited = false;
    this->key = key;
    this->command = command;
    this->name = name;
    this->enable = enable;
  }
  
  int Alias::getKey() {
    return key;
  }
  
  bool Alias::getEnable() {
    return enable;
  }
  
  void Alias::setKey(int key) {
    this->key = key;
  }
  
  void Alias::setEnable(bool value) {
    edited = true;
    enable = value;
  }
  
  QString Alias::getName() {
    return name;
  }
  
  QString Alias::getCommand() {
    return this->command;
  }
  
  QString Alias::getArg(int index) {
    if (index < args.count())
      return args[index];
    else
      return 0;
  }
  
  QVector<QString> Alias::getArgs() {
    return args;
  }
  
  void Alias::addArg(QString arg) {
    if (args.indexOf(arg) == -1) {
      args.push_back(arg);
      edited =true;
    }
  }
  
  void Alias::setName(QString name) {
    edited =true;
    this->name = name;
  }
  
  void Alias::setCommand(QString command2) {
    if (command2 != "") {
      this->edited = true;
      this->command = command2;
    }
  }
  
  void Alias::setArgs(QVector<QString> args) {
    this->args = args;
  }
  
  void Alias::save() {
    if (edited == true) {
      QSqlQuery query;
      if (this->key >= 0) {
        query.exec("update TALIAS SET COMMAND = '"+command.trimmed()+"', ENABLE = '"+QString::number(enable)+"', ALIAS = '"+name.trimmed()+"' WHERE TALIAS_KEY = "+QString::number(key)); 
      }
      else {
        query.exec("insert into TALIAS (ALIAS,COMMAND,ENABLE) values ('"+ this->name +"', '" + this->command +"', '"+ QString::number(this->enable) +"')"); 
        QSqlQuery query5;
        query5.exec("SELECT TALIAS_KEY FROM TALIAS ORDER BY TALIAS_KEY DESC");
        query5.next();
        this->key = query5.value(0).toString().toInt();
      }
      
      QVector<QString> oldArgs;
      QSqlQuery query2;
      query2.exec("SELECT ARGS FROM TARGS WHERE PARENT = '"+ QString::number(this->key) +"' AND TYPE = 1");
      while (query2.next()) {
        oldArgs.push_back(query2.value(0).toString());
      }
      
      for(int i =0; i < oldArgs.count(); i++) {
        if (args.indexOf(oldArgs[i]) == -1) {
          QSqlQuery query3;
          query3.exec("DELETE FROM TARGS WHERE PARENT = '"+QString::number(this->key)+"' AND ARGS = '"+oldArgs[i]+"' AND TYPE = 1");
        }
      }
      
      for(int i =0; i < args.count(); i++) {
        if (oldArgs.indexOf(args[i]) == -1) {
          QSqlQuery query3;
          query3.exec("INSERT INTO TARGS (PARENT,ARGS,TYPE) values ('"+QString::number(this->key)+"','"+args[i]+"',1)");
        }
      }
    }
  }
  
  QVector<Alias>* Alias::getAlias() {
    QVector<Alias>* aliasList = new QVector<Alias>;
    QSqlQuery query;
    query.exec("SELECT ALIAS,COMMAND,TALIAS_KEY,ENABLE FROM TALIAS");
    while (query.next())  {
      Alias* anAlias = new Alias(query.value(0).toString(),query.value(1).toString(),query.value(3).toBool(), query.value(2).toInt());
      QSqlQuery query2;
      query2.exec("SELECT ARGS FROM TARGS WHERE PARENT = '"+ query.value(2).toString() +"' AND TYPE = 1");
      QVector<QString> argsVector;
      while (query2.next()) {
        argsVector.push_back(query2.value(0).toString());
      }
      anAlias->setArgs(argsVector);
      aliasList->push_back(*anAlias);
    }
    return aliasList;
  }
  
  bool Alias::operator==(const QString& x) const {
    return (x == this->name);
  }
  
  bool Alias::operator==(const int& x) const {
    return (x == this->key);
  }
  
  bool operator==(Alias& x, QString& y) {
    return (x.getName() == y);
  }
  
  bool operator==(Alias& x, int y) {
    return (x.getKey() == y);
  }
  
  bool operator==(QString& y, Alias& x) {
    return (x.getName() == y);
  }
  
  bool operator==(int& y, Alias& x) {
    return (x.getKey() == y);
  }
  
  bool Alias::getEdited() {
    return edited;
  }
  
  int Alias::indexOf(QVector<Alias>* aliasList, int key) {
    bool found = false;
    int i =0;
    while ((found == false) && (i < aliasList->count())) {
      if ((*aliasList)[i] == key)
        found = true;
      else
        i++;
    }
    if (found == false) i = -1;
    return i;
  }
  