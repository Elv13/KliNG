#include "shell.h"
#include "virtTTY.h"
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>

  Shell::Shell(QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList) {
    this->commandList = commandList;
    this->aliasList = aliasList;
    this->defaultArgsList = defaultArgsList;
    this->functionList = functionList;
  }
  
  Shell::~Shell() {
  
  }

  bool Shell::evalCondition(QString line) {
    line = line.mid(line.indexOf("[")+1, (line.count() - (line.indexOf("[")+1)));
    line = line.left(line.indexOf("]")).trimmed();

    line = "test " + line;
    char buffer[30];
    FILE *JOB = popen(line.toStdString().c_str(), "r" );
    
    if ( JOB != NULL ) 
      while ( fgets( buffer, sizeof buffer, JOB ) != NULL ) {}
      
    bool toReturn = pclose(JOB);
    return !toReturn;
  }

  bool Shell::loopUntilCondition() {
    currentLine++;
    while ((commandArray[currentLine].trimmed().left(2).toLower() != "fi") && (commandArray[currentLine].trimmed().left(4).toLower() != "elif") && (commandArray[currentLine].trimmed().left(4).toLower() != "else")) {
      currentLine++;
      signalNextLine();
    }
    return false;
  }
  
  bool Shell::ifStatement() {
    bool* tmp = new bool;
    *tmp = false;
    ifVector.append(tmp);
    if (evalCondition(commandArray[currentLine])) {
      *ifVector.last() = true;
      currentLine++;
      signalNextLine();
      evalCommand();
    }
    else {
      loopUntilCondition();
      
      if (commandArray[currentLine].trimmed().left(2).toLower() == "fi")
        fiStatement();
      else if (commandArray[currentLine].trimmed().left(4).toLower() == "elif")
        elifStatement();
      else if (commandArray[currentLine].trimmed().left(4).toLower() == "else")
        elseStatement();
    }
  }
  
  bool Shell::whileLoop() {
    if (loopVector.count() == 0) {
      int* tmp = new int;
      *tmp = currentLine;
      loopVector.append(tmp);
    }
    else if (*loopVector.last() != currentLine) {
      int* tmp = new int;
      *tmp = currentLine;
      loopVector.append(tmp);
    }
    
    if (evalCondition(commandArray[currentLine])) {
      currentLine++;
      signalNextLine();
      evalCommand();
    }
    else {
      loopVector.pop_back();
      while (commandArray[currentLine].trimmed().left(4).toLower() != "done") {
        currentLine++;
        signalNextLine();
      }
      currentLine++;
      signalNextLine();
      evalCommand();
    }
  }
  
  bool Shell::forLoop() {
    
  }
  
  bool Shell::untilLoop() {
    if (loopVector.count() == 0) {
      int* tmp = new int;
      *tmp = currentLine;
      loopVector.append(tmp);
      currentLine++;
      signalNextLine();
      evalCommand();
    }
    else if (*loopVector.last() != currentLine) {
      int* tmp = new int;
      *tmp = currentLine;
      loopVector.append(tmp);
      currentLine++;
      signalNextLine();
      evalCommand();
    }
    
    if (evalCondition(commandArray[currentLine])) {
      currentLine++;
      signalNextLine();
      evalCommand();
    }
    else {
      loopVector.pop_back();
      while (commandArray[currentLine].trimmed().left(4).toLower() != "done") {
        currentLine++;
        signalNextLine();
      }
      currentLine++;
      signalNextLine();
      evalCommand();
    }
  }
  
  bool Shell::doneStatement() { 
    if (loopVector.size() != 0) {
      //sbCurrentLine = firstSBItem;
      for (int i =0; i < *loopVector.last();i++) {
        //sbCurrentLine = sbCurrentLine->nextSBItem;
        //if ((currentLine < lineNumber) && (sbCurrentLine->debugState == false))
        //  signalNextLine();
      }
      currentLine = *loopVector.last();
      evalCommand();
    }
    else {
      currentLine++;
      evalCommand();
    }
    
  }
  
  bool Shell::elseStatement() {
    if (*ifVector.last() == true) {
      while (commandArray[currentLine].trimmed().left(2).toLower() != "fi")
        loopUntilCondition();
      fiStatement();
    }
    else if (*ifVector.last() == false) {
      currentLine++;
      //highlightLine(currentLine);
      signalNextLine();
      evalCommand();
    }
    else {
      loopUntilCondition();
      if (commandArray[currentLine].trimmed().left(2).toLower() == "fi") {
        fiStatement();
      }
    }
  }
  
  bool Shell::elifStatement() {
    if (*ifVector.last() == true) {
      while (commandArray[currentLine].trimmed().left(2).toLower() != "fi")
        loopUntilCondition();
      fiStatement();
    }
    else if ((evalCondition(commandArray[currentLine])) && (*ifVector.last() == false)) {
          *ifVector.last() = true;
          currentLine++;
          //highlightLine(currentLine);
          signalNextLine();
          evalCommand();
    }
    else {
      loopUntilCondition();
      
      if (commandArray[currentLine].trimmed().left(2).toLower() == "fi") {
        fiStatement();
      }
      else if (commandArray[currentLine].trimmed().left(4).toLower() == "elif") {
        elifStatement();
      }
      else if (commandArray[currentLine].trimmed().left(4).toLower() == "else") {
        elseStatement();
      }
    }
  }
  
  bool Shell::fiStatement() {
    ifVector.pop_back();
    currentLine++;
    //highlightLine(currentLine);
    signalNextLine();
    evalCommand();
  }
  
  bool Shell::evalCommand() {
    if (commandArray[currentLine].trimmed().left(1).toLower() == "#") { 
      currentLine++;
      //highlightLine(currentLine);
      signalNextLine();
      //sendCommand(commandArray[currentLine].toStdString().c_str());
      analyseCommand(commandArray[currentLine],parseCommand(commandArray[currentLine]));
    }
    else if (commandArray[currentLine].trimmed().left(2).toLower() == "if") {                            
      ifStatement();
    }
    else if (commandArray[currentLine].trimmed().left(5).toLower() == "while") {                            
      whileLoop();
    }
    else if (commandArray[currentLine].trimmed().left(4).toLower() == "elif") {                            
      elifStatement();
    }
    else if (commandArray[currentLine].trimmed().left(4).toLower() == "else") {            
      elseStatement();
    }
    else if (commandArray[currentLine].trimmed().left(5).toLower() == "until") {                            
      evalCondition(commandArray[currentLine]);
    }
    else if (commandArray[currentLine].trimmed().left(3).toLower() == "for") {                            
      evalCondition(commandArray[currentLine]);
    }
    else if (commandArray[currentLine].trimmed().left(4).toLower() == "done") {                            
      doneStatement();
    }
    else if (commandArray[currentLine].trimmed().left(2).toLower() == "fi") {                            
      fiStatement();
    }
    else {
      //TODO add back sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      analyseCommand(commandArray[currentLine],parseCommand(commandArray[currentLine]));
      //TODO add back sbCurrentLine = sbCurrentLine->nextSBItem;
      //signalNextLine();
    }
  }
  
  void Shell::sendCommand(QString command) {
    VirtTtyThread* aThread = new VirtTtyThread(command,parseCommand(command));
    aThread->start();
  }
  
  void Shell::signalNextLine(){}
  
  int Shell::countLine(QString script) {
    int i =0;

    script += "\n";

    for (int j = 0; j <= script.size(); j++) { //Count the script line
          if ((script[j] == 0x0A) && (script[j+1] != 0x0A)) 
            i++;
    } 
    return i;
  }

  QVector<QString> Shell::parseCommand(QString command) {
    int counter;
    int i = 0;
    QString tmp;
    counter = 0;
    tmp = command;
    tmp = tmp.trimmed();
    QVector<QString> argsVec;

    //BEGINING test exaustively
    while (!tmp.isEmpty()) {
       if (((tmp.indexOf("\"") < tmp.indexOf(" ")) && (tmp.indexOf("\"") != -1)) || ((tmp.indexOf("\"") != -1) && (tmp.indexOf(" ") == -1))) {
        if (tmp[0] != '\"') {
          argsVec.push_back(tmp.left(tmp.indexOf("\"") -1));
          tmp = tmp.remove(0, tmp.indexOf("\"") -1);
        }
        tmp = tmp.remove(0,1);
        argsVec.push_back(tmp.left(tmp.indexOf("\"")));
        tmp.remove(0,  tmp.indexOf("\""));
      }
      else if (((tmp.indexOf("`") < tmp.indexOf(" ")) && (tmp.indexOf("`") != -1)) || ((tmp.indexOf("`") != -1) && (tmp.indexOf(" ") == -1))) {
        if (tmp[0] != '`') {
          argsVec.push_back(tmp.left(tmp.indexOf("`") -1));
          tmp = tmp.remove(0, tmp.indexOf("`") -1);
        }
        tmp = tmp.remove(0,1);
        argsVec.push_back(tmp.mid(1, tmp.indexOf("`")));
        tmp.remove(0,  tmp.indexOf("`"));
      }
      else if (((tmp.indexOf("'") < tmp.indexOf(" ")) && (tmp.indexOf("'") != -1)) || ((tmp.indexOf("'") != -1) && (tmp.indexOf(" ") == -1))) {
        if (tmp[0] != '\'') {
          argsVec.push_back(tmp.left(tmp.indexOf("'") -1));
          tmp = tmp.remove(0, tmp.indexOf("'"));
        }
        tmp = tmp.remove(0,1);
        argsVec.push_back(tmp.mid(1, tmp.indexOf("'")));
        tmp.remove(0,  tmp.indexOf("'"));
      }
      else if (tmp.indexOf(" ") == -1) {
        argsVec.push_back(tmp);
        tmp.clear();
      }
      else if (tmp.indexOf(" ") == 0) {
        tmp = tmp.trimmed();
      }
      else {
        argsVec.push_back(tmp.left(tmp.indexOf(" ")));
        tmp.remove(0,  tmp.indexOf(" "));
      }
    }
    //END test

    checkCommand(&argsVec);
    
    return argsVec;
  }
  
  void Shell::checkCommand(QVector<QString> *args) {
    if (commandList->indexOf(args->at(0)) != -1) {
      if (args->at(0) == "ls")
        args->push_back("--color");
      else if (aliasList->indexOf(args->at(0)) != -1) {
        QSqlQuery query;
        query.exec("SELECT COMMAND,ARGS FROM TALIAS WHERE ALIAS = '"+ args->at(0) +"'");
        args->pop_front();
        while (query.next())  {
          args->push_front(query.value(1).toString());
          args->push_front(query.value(0).toString());
        }
      }
    }
    //TODO add file check here
    else {
      signalNewCommand("Command not found!");
    }
  }
  
  /**
  Look if the grep contain a |, > or  >>
  @param[in] command the command
  */
  void Shell::analyseCommand(QString command, QVector<QString> args) {
    if (command.indexOf("|") != -1) {
      signalNewCommand("<b><font color=\"#008000\">" + command.left(command.indexOf("|")) + "</font> <font color=\"#000000\">|</font> <font color=\"#FF8000\">" + command.mid((command.indexOf("|") +1), ( command.size() - command.indexOf("|"))) + "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      if (command.mid(command.indexOf("|"), (command.size() - command.indexOf("|"))).indexOf("grep ") == -1) {
        //TODO
      }
      else {
        QString toHighlight = command.mid(command.indexOf("|")+1, (command.size() - command.indexOf("|")-1));
        toHighlight = toHighlight.mid((toHighlight.indexOf("grep ")+5), (toHighlight.size() - (toHighlight.indexOf("grep ")+5)));
        if (toHighlight[0] == '\"') {
          //TODO
        }
        else {
          toHighlight = toHighlight.left(toHighlight.indexOf(" "));
        }
        sendCommand(command);
      }
    }
    else {
      if (command.indexOf(">>") != -1) {
        signalNewCommand("<b><font color=\"#008000\">" + command.left(command.indexOf(">>")) + "</font> <font color=\"#000000\">>></font> <font color=\"#FF8000\">" + command.mid((command.indexOf(">>") +2), ( command.size() - command.indexOf(">>"))) + "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      else if (command.indexOf(">") != -1) {
        signalNewCommand("<b><font color=\"#008000\">" + command.left(command.indexOf(">")) + "</font> <font color=\"#000000\">></font> <font color=\"#FF8000\">" + command.mid((command.indexOf(">") +1), ( command.size() - command.indexOf(">")))+ "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      else {
        signalNewCommand("<b><font color=\"#008000\">" + command + "</font>" + "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      sendCommand(command);
    }
  }
  
  void Shell::signalNewCommand(QString command) {}