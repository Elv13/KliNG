#include "session.h"
#include <QtSql>

  Session::Session() {
    edited = false;
    isNew = false;
    key = -1;
  }
  
  Session::Session(int key, QString name) {
    this->key = key;
    this->name = name;
    
    QSqlQuery query;
    query.exec("SELECT * FROM TSESSION_ITEM WHERE SESSION = "+QString::number(key));
    
    while (query.next()) {
      sessionItem* anItem = new sessionItem;
      anItem->key = query.value(0).toString().toInt();
      anItem->name = query.value(1).toString();
      anItem->icon = query.value(2).toString();
      anItem->path = query.value(3).toString();
      anItem->input = query.value(4).toString().toInt(); 
      anItem->type = query.value(5).toString().toInt(); 
      anItem->session = query.value(6).toString().toInt();
      anItem->command = query.value(7).toString();
      item.push_back(*anItem);
    }
  }
  
  QString Session::getName() {
    return name;
  }
  
  void Session::setKey(int key) {
    edited =true;
    this->key = key;
  }
  
  int Session::getKey() {
    return this->key;
  }
  
  QVector<sessionItem> Session::getItem() {
    return this->item;
  }
  
  void Session::setItem(QVector<sessionItem> item) {
    edited =true;
    this->item = item;
  }
  
  void Session::setName(QString name) {
    edited =true;
    this->name = name;
  }
  
  void Session::save() {
    if (edited == true) {
      QSqlQuery query;
      if (isNew == false) {
	if (key == -1) {
	  QSqlQuery query4;
	  query4.exec("insert INTO TSESSION (NAME) values '"+this->name+"'");
	  QSqlQuery query5;
	  query5.exec("SELECT TSESSION_KEY FROM TSESSION ORDER BY TSESSION_KEY DESC");
	  query5.next();
	  this->key = query5.value(0).toString().toInt();
	}
	else {
	  QSqlQuery query4;
	  query4.exec("update TSESSION_SET NAME = '"+this->name+"' WHERE TSESSION_KEY = " + QString::number(this->key));
	}
	for (int i =0;i < item.count(); i++) {
	  if (item[i].key != -1) {
	    query.exec("update TSESSION_ITEM SET NAME = '"+ item[i].name +"', ICON = '"+ item[i].icon +"', PATH = '"+ item[i].path +"', TYPE = "+QString::number(item[i].type)+ ", INPUT = "+ QString::number(item[i].input)+ ", SESSION = "+ QString::number(item[i].session) + ", COMMAND ='"+ item[i].command +"' WHERE TOPTION_KEY = "+QString::number(item[i].key)); 
	  }
	  else {
	    query.exec("insert into TSESSION_ITEM (NAME,ICON,PATH,TYPE,INPUT,SESSION,COMMAND) values ('"+ item[i].name +"', '"+ item[i].icon +"', '"+ item[i].path +"', "+QString::number(item[i].type)+ ", "+ QString::number(item[i].input)+ ", "+ QString::number(this->key) + ",'"+ item[i].command +"')");
	  }
	}
      }
      else {
	
      }
    }
  }