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
    edited =true;
    enable = value;
  }
  
  QString Alias::getName() {
    return name;
  }
  
  QString Alias::getCommand() {
    return command;
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
  
  void Alias::setCommand(QString command) {
    edited =true;
    this->command = command;
  }
  
  void Alias::setArgs(QVector<QString> args) {
    this->args = args;
  }
  
  void Alias::save() {
    if (edited == true) {
      QSqlQuery query;
      query.exec("UPDATE TALIAS SET (ALIAS,COMMAND,ENABLE) = ('"+ this->name +"', '" + this->command +"', '"+ this->enable +"') WHERE TALIAS_KEY = "+ this->key); 
      
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
          query3.exec("INSERT INTO TARGS (PARENT,ARGS,TYPE) value ('"+QString::number(this->key)+"','"+args[i]+"',1");
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
  