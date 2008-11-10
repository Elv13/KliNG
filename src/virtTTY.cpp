/**     @file VirtTTY.cpp

	This file is part of the Kling project
	Copyright (C) 2008 Emmanuel Lepage Vallee <elv1313@gmail.com>
	
	This software is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 or 3 of the License, or (at your option) any later version.

	This software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public License
	along with this library; see the file COPYING.LIB.  If not, write to
	the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA 02111-1307, USA.
	___________________

        Terminal emulator able to interact with GUI

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include  "virtTTY.h"
#include  <iostream>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <sys/wait.h>
#include  <sys/types.h>
#include  <time.h>
#include  <QString>
#include <QScrollBar>
#include <KStandardDirs>
#include <KLocalizedString>
#include <KSaveFile>
#include <QColor>
#include <QBrush>
#include <QPalette>

#include <QThread>
#include <QDebug>

/**
  VirtTTY constructor
  //DEPRECATED
  @param[in] parent The parent widget (nothing)
*/
  VirtTTY::VirtTTY(QCheckBox* showGUI) {
    if (showGUI != 0) {
      if (showGUI->isChecked() == true) 
        this->showGUI = true;
      else
        this->showGUI = false;
    }
    else {
      this->showGUI = false;
    }
    // mainwindow = parent;
  }

/**
  VirtTTY destructor
*/
  VirtTTY::~VirtTTY() {
    
  }

/**
  Display an error string if the command fail

  @param[in] *msg
*/
  void VirtTTY::fatal_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
  }

/**
  When the prosess will be forked, it will call this function to execute the command

  @param[in] *to_me stdIn
  @param[in] *from_me stdOut
  @param[in] paramArray[] argv
*/
  void VirtTTY::forked_exec(int *to_me, int *from_me, char *paramArray[]) {
    if (dup2(to_me[0], STDIN_FILENO) == -1)
      fatal_error("dup2(to_me[0])");

    if (dup2(from_me[1], STDOUT_FILENO) == -1)
      fatal_error("dup2(from_me[1])");

    if (close(to_me[0]) == -1)
      fatal_error("close(to_me[0])");

    if (close(to_me[1]) == -1)
      fatal_error("close(to_me[1])");

    if (close(from_me[0]) == -1)
      fatal_error("close(from_me[0])");

    if (close(from_me[1]) == -1)
      fatal_error("close(from_me[1])");

    execvp(paramArray[0], paramArray);
    fatal_error("execvp(paramArray)");
    exit(EXIT_FAILURE);
  }

/**
  fork and get the stdOut of the forked prosess

  @param[in] command the command string
  @param[in] needPostAnalyse if the stdOut line need to be parser
  @param[in] toHighlight if the command contain a | grep
  @param[in] showAllLine if it need to display line with a grep match only
*/
  int VirtTTY::execute(QVector<QString> args) {
    QString line;
    int i = 0;
    pid_t pid, pidchild;
    int status;
    int to_cmd[2], from_cmd[2];
    int findStart;
    int j = 0;
    int paramNumber;
    QString commandOutput;
    char **paramArray = parseCommand(args);
          
    if (executionExeptions(paramArray, (paramNumber)) == false) {
      if (pipe(to_cmd) == -1)
        fatal_error("pipe(to_cmd)");
    
      if (pipe(from_cmd) == -1)
        fatal_error("pipe(from_cmd)");
    
      switch (pid = fork()) { // Duplicate the prosess
        case (pid_t) -1: //If it fail
          fatal_error("fork");
        case (pid_t) 0: //I am the fork
          forked_exec(to_cmd, from_cmd, paramArray);
      }

      fork_pid = pid;

      char bufferW[256];
      if (close(from_cmd[1]) == -1)
        fatal_error("close(from_cmd[1])");
    
      if (close(to_cmd[0]) == -1)
        printf("close(to_cmd[0])");
    
      // read result from from_cmd[1]
      char bufferR[4096];
      ssize_t nr;
      i = 0;

      do { 
        QString closeFont;
        nr = read(from_cmd[0], bufferR, sizeof bufferR);
        if (nr == -1)
          fatal_error("read(bufferR)");
    
        // Nothing to read anymore
        if (nr == 0)
          break;
    
        for (i = 0; i < nr; i++)  {
          // Traitement bateau de bufferR
          if (bufferR[i] == '\n') {
            if (line.indexOf("[") != -1)
              closeFont = ajustSerialCode(line);
              
            emit newLine("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line);
            commandOutput += "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line + "<br>" + closeFont + "\n";
            line.clear();
          }
          else {
            line += bufferR[i];
          }
        }
      }

      while (nr > 0);
      emit isOver(QString::number(time(NULL)), key);
      saveOutput(&commandOutput);
    
      if (close(to_cmd[1]) == -1)
              fatal_error("close(to_cmd[1])");
      if (close(from_cmd[0]) == -1)
              fatal_error("close(from_cmd[0])");

      pidchild = wait(NULL);
    }
    return 0;
  }


/** //DEPRECATED
  Execute a command differently

  @param[in] paramArray[] ARGV
  @param[in] paramNumber ARGC
  @return if the command was an exeption
*/
  bool VirtTTY::executionExeptions(char* paramArray[], int paramNumber) {
    bool isExeption = false;

    if (strcmp(paramArray[0], "cd") == 0) {
      if (showGUI == true)  {
        emit showFileBrowser(QString(paramArray[1]), true);
        emit isOver(QString::number(time(NULL)), key);
      }
      else 
        exeption_cd(paramArray[1]);
      isExeption = true;
    }
    else if (strcmp(paramArray[0], "clear") == 0) {
      emit clearCmdOutput();
    }
    else if (strcmp(paramArray[0], "ls") == 0) {
      if (showGUI == true) {
        isExeption = true;
        emit showFileBrowser(QString(paramArray[1]), false);
        emit isOver(QString::number(time(NULL)), key);
      }     
    }
    return isExeption;
  }

/** //DEPRECATED
  Basic implementation of the CD command, not availible by default

  @param[in] parent the path
*/
  void VirtTTY::exeption_cd(char path[]) {
    QString aString = "<b><font color=\"#008000\">cd ";

    if(chdir(path) == -1) {
      aString = "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">";
      aString += path;
      aString += i18n(": No such directory");
      emit newLine(aString);
    }
    else {
      aString = "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">The working directory is now ";
      aString += path;
      emit newLine(aString);
    }
    emit isOver(QString::number(time(NULL)), key);
  }

/**
  Find vt100 color code

  @param[in] line the stdOut line
*/
  QString VirtTTY::ajustSerialCode(QString &line) {
    QPalette aPalette;
    QString defaultColor = aPalette.text().color().name ();
    int i =0;
    //Text color
    while (line.indexOf("[01;34m") != -1) { line = replaceColorCode(line, "[01;34m", "blue", ""); i++; }
    while (line.indexOf("[00m") != -1) { line = replaceColorCode(line, "[00m", defaultColor, ""); i++; }//TODO may be a bug
    while (line.indexOf("[01;35m") != -1) { line = replaceColorCode(line, "[01;35m", "#FF00FF", ""); i++; }
    while (line.indexOf("[01;31m") != -1) { line = replaceColorCode(line, "[01;31m", "green", ""); i++; }
    while (line.indexOf("[01;32m") != -1) { line = replaceColorCode(line, "[01;32m", "#00FF00", ""); i++; }
    while (line.indexOf("[01;36m") != -1) { line = replaceColorCode(line, "[01;36m", "cyan", ""); i++; }
    //Background color
    while (line.indexOf("[00;34m") != -1) { line = replaceColorCode(line, "[00;34m", "black", "blue"); i++; }
    while (line.indexOf("[00m") != -1) { line = replaceColorCode(line, "[00m", "white", "black"); i++; }
    while (line.indexOf("[00;35m") != -1) { line = replaceColorCode(line, "[00;35m", "black", "#FF00FF"); i++; }
    while (line.indexOf("[00;31m") != -1) { line = replaceColorCode(line, "[00;31m", "black", "green"); i++; }
    while (line.indexOf("[30;42") != -1) { line = replaceColorCode(line, "[30;42", "black", "green"); i++; }
    while (line.indexOf("[00;32m") != -1) { line = replaceColorCode(line, "[00;32m", "black", "#00FF00"); i++; }
    while (line.indexOf("[40;33m") != -1) { line = replaceColorCode(line, "[40;33m", "yellow", "black"); i++; }
    while (line.indexOf("[37;41m") != -1) { line = replaceColorCode(line, "[37;41m", "white", "red"); i++; }
    while (line.indexOf("[40;33;01m") != -1) { line = replaceColorCode(line, "[40;33;01m", "yellow", "black"); i++; }
    while (line.indexOf("[34;42m") != -1) { line = replaceColorCode(line, "[34;42m", "#5C5CFF", "#00FF00"); i++; }
    while (line.indexOf("[32m") != -1) { line = replaceColorCode(line, "[32m", "#00CD00", ""); i++; }
    while (line.indexOf("[33;01m") != -1) { line = replaceColorCode(line, "[33;01m", "yellow", "");  i++; }//bold
    while (line.indexOf("[31;01m") != -1) { line = replaceColorCode(line, "[31;01m", "red", "");  i++; }//bold
    while (line.indexOf("[34;01m") != -1) { line = replaceColorCode(line, "[34;01m", "#5C5CFF", ""); i++; } //bold //directory
    while (line.indexOf("[32;01m") != -1) { line = replaceColorCode(line, "[32;01m", "#00FF00", ""); i++; }
    while (line.indexOf("[39;49;00m") != -1) { line = replaceColorCode(line, "[39;49;00m", defaultColor, ""); i++; } //TODO may be a bug
    while (line.indexOf("[0m") != -1) { line = replaceColorCode(line, "[0m", defaultColor, ""); i++; }//TODO may be a bug
    
    QString toReturn;
    for (int j =0; j < i; j++) 
      toReturn += "</font>";
      
    return toReturn;
  }

/**
  Replace vt100 code with HTML

  @param[in] line the stdOut line
  @param[in] code the vt100 code
  @param[in] color the text color to use
  @param[in] bgcolor the bg color to use
*/
  QString VirtTTY::replaceColorCode(QString line, QString code, QString color, QString bgcolor) {
    line = line.left(line.indexOf(code)) + "<font color=" + color + " style=\"background-color:" + bgcolor +"; \">" + line.mid((line.indexOf(code)+code.size()),(line.size() -(line.indexOf(code)+code.size())));
    return line;
  }


/**
  ThreadExec constructor

  @param[in] command the command
  @param[in] paramNumber argc
*/
  char** VirtTTY::parseCommand(QVector<QString> args) {
    char** paramArray = new char* [args.count() + 1]; 
    for (int j=0; j < args.count(); j++) {
      char* arg = new char[args[j].count()];
      strcpy(arg,args[j].toStdString().c_str());
      paramArray[j] = arg;
    }
    paramArray[args.count()] = NULL;
    
    return paramArray;
  }

/**
  Execute a command

  @param[in] command the command to execute
  @return the stdOut
*/
  QString VirtTTY::getResult(string command) {
    QString output;
    char buffer[3000];
    FILE *JOB = popen(command.c_str(), "r" );
    
    if ( JOB != NULL ) {
      while ( fgets( buffer, sizeof buffer, JOB ) != NULL ) {
        if (buffer[0] != 0x23)
          output += buffer;
      }
    }
    return output;
  }


/**
  ThreadExec constructor

  @param[in] command the command
*/
  bool VirtTTY::executeOnly(string command) {
    pid_t pid;
    int status;
    switch (pid = fork()) { //Duplicate the prosess
      case (pid_t)0: { //If i am the fork, execute the command
        system(command.c_str()); //TODO replace some kind of exec, it will be less cheap
        exit(33);
      }
      default: {
        wait(&status); //if i am the parent, wait until the child die
        //TODO analyse the return code when the exec will be there
      }
    }
    return true; //TODO When the status will be impleted, return failure or success
  }

  void VirtTTY::saveOutput(QString* output) {
    if ((output->trimmed().isEmpty() == false) && (output->trimmed() != "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\"><br>")) {
      KSaveFile file(KStandardDirs::locateLocal("appdata", "/output/") + key);
      file.open();

      QByteArray outputByteArray;
      outputByteArray.append(*output);
      file.write(outputByteArray);
      file.finalize();
      file.close();
    }
  }
  