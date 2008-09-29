/**     @file Shell.cpp

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

#include  "Shell.h"
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
#include <KSaveFile>
#include <QColor>
#include <QBrush>
#include <QPalette>

#include <QThread>

using namespace std;

/**
  Shell constructor

  @param[in] parent The parent widget (nothing)
*/
Shell::Shell(QCheckBox* showGUI)
{
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
  Shell destructor
*/
Shell::~Shell()
{
  
}

/**
  Display an error string if the command fail

  @param[in] *msg
*/
void Shell::fatal_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
  When the prosess will be forked, it will call this function to execute the command

  @param[in] *to_me stdIn
  @param[in] *from_me stdOut
  @param[in] paramArray[] argv
*/
void Shell::forked_exec(int *to_me, int *from_me, char *paramArray[])
{
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
int Shell::execute(string command, bool needPostAnalyse, string toHighlight, bool showAllLine)
{

	string line;
	string originalcommand = command;
	int i = 0;
	pid_t pid, pidchild;
	int status;
	int to_cmd[2], from_cmd[2];
	int findStart;
	int j = 0;
	int paramNumber;
        QString commandOutput;


	char **paramArray = parseCommand(command, paramNumber);


	if (executionExeptions(paramArray, (paramNumber)) == false)
	{

	  if (pipe(to_cmd) == -1)
		  fatal_error("pipe(to_cmd)");
  
	  if (pipe(from_cmd) == -1)
		  fatal_error("pipe(from_cmd)");
  
  
  
  
  
	  printf("I am parent PID %d\n", getpid());
  
	  switch (pid = fork()) // Duplicate the prosess
	  {
	  case (pid_t) -1: //If it fail
		  fatal_error("fork");
	  case (pid_t) 0: //I am the fork
		  printf(" I am child PID=%d\n", getpid());
		  //system("echo commande executed by child > /tmp/test/testprogsys.txt");
		  forked_exec(to_cmd, from_cmd, paramArray);
  
	  // Par défaut il n'y a rien à faire
	  // default:
	  }


	  fork_pid = pid;

  
  
	  char bufferW[256];
	  if (close(from_cmd[1]) == -1)
		  fatal_error("close(from_cmd[1])");
  
	  if (close(to_cmd[0]) == -1)
		  printf("close(to_cmd[0])");
  
  
  
  
  
	  // Lire le résultat sur from_cmd[1]
	  //* Ces données sont celles que la commande a envoyé sur la sortie standard
  
	  char bufferR[4096];
	  ssize_t nr;
	  i = 0;
  
	  printf("    >>");


// 	  mainwindow->pxmCmdInactive->load("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearA.png");
// 	  mainwindow->cmdStatus->setPixmap(*mainwindow->pxmCmdInactive);
// 	  mainwindow->txtCommand->setDisabled(true);

	  
	  do 
	  { //TODO sa c'est cheap aussi, enlever ce brake et faire un while
                  string closeFont;
		  nr = read(from_cmd[0], bufferR, sizeof bufferR);
		  if (nr == -1)
			  fatal_error("read(bufferR)");
  
		  // Sortie de la boucle si il n'y a plus rien à lire
		  if (nr == 0)
			  break;
  
		  for (i = 0; i < nr; i++) 
		  {
			  // Traitement bateau de bufferR
			  if (bufferR[i] == '\n')
			  {
			  
			      if (line.find("[") != -1)
			      {
				closeFont = ajustSerialCode(line);
			      }
				
			      if (needPostAnalyse == false)
			      {
				  //printf("\n    >>%s", line.c_str()); //also print the outpup in the standarts std output of the application. -Reduce performances by 30%, use only for debugging-
				  //mainwindow->rtfCmdOutput->setHtml(mainwindow->rtfCmdOutput->toHtml() + "         " + line.c_str()); //TODO faire un insert
				  //mainwindow->rtfCmdOutput->append(QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line));
				  //mainwindow->rtfCmdOutput->textCursor().movePosition(QTextCursor::End);
				  //mainwindow->rtfCmdOutput->verticalScrollBar()->setValue(mainwindow->rtfCmdOutput->verticalScrollBar()->maximum());
				  //mainwindow->rtfCmdOutput->repaint(); //Cut performances by 90%, if someone find a better way, tell it!
				  emit newLine(QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line));
                                  commandOutput += QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line + "<br>" + closeFont + "\n");
			      }
			      else
			      {
				
				if (showAllLine == true)
				{
				  if (line.find(toHighlight) != -1)
				  {
				    emit newLine(QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + (highLight(line, toHighlight))));
                                    commandOutput += QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + (highLight(line, toHighlight)) + "<br>" + closeFont + "\n");
				  }
				  else
				  {
				    emit newLine(QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line));
                                    commandOutput += QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + line + "<br>" + closeFont + "\n");
				  }

				  //mainwindow->rtfCmdOutput->textCursor().movePosition(QTextCursor::End);
				  //mainwindow->rtfCmdOutput->verticalScrollBar()->setValue(mainwindow->rtfCmdOutput->verticalScrollBar()->maximum());
				  //mainwindow->rtfCmdOutput->repaint(); //Cut performances by 90%, if someone find a better way, tell it!
				}
				else
				{
				  if (line.find(toHighlight) != -1)
				  {
				    emit newLine(QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + (highLight(line, toHighlight))));
                                    commandOutput += QString::fromStdString("<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">" + (highLight(line, toHighlight)) + "<br>" + closeFont + "\n");
				    //mainwindow->rtfCmdOutput->verticalScrollBar()->setValue(mainwindow->rtfCmdOutput->verticalScrollBar()->maximum());
				    //mainwindow->rtfCmdOutput->repaint(); //Cut performances by 90%, if someone find a better way, tell it!
				  }
				}
			      }
			      line.clear();
			  }	
			  else
			  {
				  //printf("%x",bufferR[i]);
				  line += bufferR[i];
			  }
		  }
	  } 

	  while (nr > 0);

	  printf("\n");
// 	  mainwindow->txtCommand->clear();
// 	  mainwindow->pxmCmdInactive->load("/home/lepagee/dev/tp3-prog_sess2/pixmap/22x22/gearI.png");
// 	  mainwindow->cmdStatus->setPixmap(*mainwindow->pxmCmdInactive);
// 	  mainwindow->txtCommand->setEnabled(true);
	  emit isOver(QString::number(time(NULL)), key);
          saveOutput(&commandOutput);
  
  
	  if (close(to_cmd[1]) == -1)
		  fatal_error("close(to_cmd[1])");
	  if (close(from_cmd[0]) == -1)
		  fatal_error("close(from_cmd[0])");
  
	  pidchild = wait(NULL);
	  printf(" Death of child PID=%d\n", pidchild);
	}


	
	return 0;
}


/**
  Execute a command differently

  @param[in] paramArray[] ARGV
  @param[in] paramNumber ARGC
  @return if the command was an exeption
*/
bool Shell::executionExeptions(char* paramArray[], int paramNumber)
{
  bool isExeption = false;
  string commandName = paramArray[0];
  
    if (strcmp(paramArray[0], "cd") == 0)
    {
      if (showGUI == true)  {
        emit showFileBrowser(QString(paramArray[1]), true);
        emit isOver(QString::number(time(NULL)), key);
      }
      else 
        exeption_cd(paramArray[1]);
      isExeption = true;
    }
    else if (strcmp(paramArray[0], "clear") == 0)
    {
      //mainwindow->rtfCmdOutput->clear();
      emit clearCmdOutput();
    }
    else if (strcmp(paramArray[0], "ls") == 0) {
      if (showGUI == true) {
        isExeption = true;
        emit showFileBrowser(QString(paramArray[1]), false);
        emit isOver(QString::number(time(NULL)), key);
      }
      //int i =0;
      //while (paramArray[i] != NULL) i++;
      
    }
    /*else if (strcmp(paramArray[0], "ls") == 0)
    {
      printf("\nMon esti de gaffe: %d \n", paramNumber);
      paramArray = (char**) realloc(paramArray, sizeof(char*)*(paramNumber+1));
      char* enableColor = new char[7];
      strcpy(enableColor, "--color");
      strcpy(paramArray[0], "ls");
      paramArray[1] = enableColor;
      paramArray[2] = NULL;
      paramArray[3] = NULL;
      printf("ICI:  %s \n %s \n", paramArray[0],paramArray[1]);
    }*/

  return isExeption;
}

/**
  Basic implementation of the CD command, not availible by default

  @param[in] parent the path
*/
void Shell::exeption_cd(char path[])
{
  QString aString = "<b><font color=\"#008000\">cd ";
  /*aString += path;
  aString += "</font></b>";
  emit newLine(aString);*/
  if(chdir(path) == -1)
  {
    aString = "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">";
    aString += path;
    aString += ": No such directory";
    emit newLine(aString);
  }
  else
  {
    aString = "<img src=\"/home/lepagee/dev/tp3-prog_sess2/pixmap/margin.png\">The working directory is now ";
    aString += path;
    emit newLine(aString);
  }
  //mainwindow->rtfCmdOutput->verticalScrollBar()->setValue(mainwindow->rtfCmdOutput->verticalScrollBar()->maximum());
  //mainwindow->txtCommand->clear();
  emit isOver(QString::number(time(NULL)), key);
}

/**
  Look if the grep contain a |, > or  >>

  @param[in] command the command
*/
void Shell::analyseCommand(string command)
{
//TODO ammener executionExeption ici et séparer le parseur de argv


    if (command.find("|") != -1)
    {
      emit newLine("<b><font color=\"#008000\">" + QString::fromStdString(command.substr(0, command.find("|"))) + "</font> <font color=\"#000000\">|</font> <font color=\"#FF8000\">" + QString::fromStdString(command.substr((command.find("|") +1), ( command.size() - command.find("|"))))+ "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      if (command.substr(command.find("|"), (command.size() - command.find("|"))).find("grep ") == -1)
      {
  
      }
      else
      {
	string toHighlight = command.substr(command.find("|")+1, (command.size() - command.find("|")-1));
	toHighlight = toHighlight.substr((toHighlight.find("grep ")+5), (toHighlight.size() - (toHighlight.find("grep ")+5)));
	if (toHighlight[0] == '\"')
	{
	  
	}
	else
	{
	  toHighlight = toHighlight.substr(0, toHighlight.find(" "));
	}
	execute(command.substr(0, command.find("|")), true, toHighlight, false);
      }
      
    }
    else
    {
      if (command.find(">>") != -1)
      {
	cout << "rentreici";
	emit newLine("<b><font color=\"#008000\">" + QString::fromStdString(command.substr(0, command.find(">>"))) + "</font> <font color=\"#000000\">>></font> <font color=\"#FF8000\">" + QString::fromStdString(command.substr((command.find(">>") +2), ( command.size() - command.find(">>"))))+ "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      else if (command.find(">") != -1)
      {
	cout << "rentreici";
	emit newLine("<b><font color=\"#008000\">" + QString::fromStdString(command.substr(0, command.find(">"))) + "</font> <font color=\"#000000\">></font> <font color=\"#FF8000\">" + QString::fromStdString(command.substr((command.find(">") +1), ( command.size() - command.find(">"))))+ "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      else
      {
	emit newLine("<b><font color=\"#008000\">" + QString::fromStdString(command) + "</font>" + "<font color=\"#C5C5C5\"> ("+  get_current_dir_name() + ")</font>" + "</b>");
      }
      execute(command, false, "", true);
  

    //mainwindow->txtCommand->setFocus();
  }
}

/**
  When  the command contain | grep, this command will highligth all keywords

  @param[in] line the stdOut line
  @param[in] toHighlight the keyword(s)
*/
string Shell::highLight(string line, string toHighlight)
{
  long cursorPosition = 0;
  while (line.substr(cursorPosition, (line.size() - cursorPosition)).find(toHighlight) != -1)
  {
    line = line.substr(0, (line.substr(cursorPosition, (line.size() - cursorPosition)).find(toHighlight) + cursorPosition)) + "<b style=\"background-color:red; \">" + toHighlight + "</b>" + line.substr((line.substr(cursorPosition, (line.size() - cursorPosition)).find(toHighlight) + cursorPosition + toHighlight.size()), (line.size() - (line.substr(cursorPosition, (line.size() - cursorPosition)).find(toHighlight) + cursorPosition + toHighlight.size())));
    cursorPosition = line.substr(cursorPosition, (line.size() - cursorPosition)).find(toHighlight) + cursorPosition + toHighlight.size() + 4;
  }
  
  //line = "<div style=\"margin-left: 50px;text-indent:50px;\">           " + line + "</div>"; //TODO make it work

  return line;
}

/**
  Find vt100 color code

  @param[in] line the stdOut line
*/
string Shell::ajustSerialCode(string &line)
{
  QPalette aPalette;
  string defaultColor = aPalette.text().color().name ().toStdString();
  int i =0;
  //Text color
  while (line.find("[01;34m") != -1) { line = replaceColorCode(line, "[01;34m", "blue", ""); i++; }
  while (line.find("[00m") != -1) { line = replaceColorCode(line, "[00m", defaultColor, ""); i++; }//TODO may be a bug
  //while (line.find("[00m") != -1) line = replaceColorCode(line, "[00m", "black", "");
  while (line.find("[01;35m") != -1) { line = replaceColorCode(line, "[01;35m", "#FF00FF", ""); i++; }
  while (line.find("[01;31m") != -1) { line = replaceColorCode(line, "[01;31m", "green", ""); i++; }
  while (line.find("[01;32m") != -1) { line = replaceColorCode(line, "[01;32m", "#00FF00", ""); i++; }
  while (line.find("[01;36m") != -1) { line = replaceColorCode(line, "[01;36m", "cyan", ""); i++; }
  //Background color
  while (line.find("[00;34m") != -1) { line = replaceColorCode(line, "[00;34m", "black", "blue"); i++; }
  while (line.find("[00m") != -1) { line = replaceColorCode(line, "[00m", "white", "black"); i++; }
  while (line.find("[00;35m") != -1) { line = replaceColorCode(line, "[00;35m", "black", "#FF00FF"); i++; }
  while (line.find("[00;31m") != -1) { line = replaceColorCode(line, "[00;31m", "black", "green"); i++; }
  while (line.find("[30;42") != -1) { line = replaceColorCode(line, "[30;42", "black", "green"); i++; }
  while (line.find("[00;32m") != -1) { line = replaceColorCode(line, "[00;32m", "black", "#00FF00"); i++; }
  while (line.find("[40;33m") != -1) { line = replaceColorCode(line, "[40;33m", "yellow", "black"); i++; }
  while (line.find("[37;41m") != -1) { line = replaceColorCode(line, "[37;41m", "white", "red"); i++; }
  while (line.find("[40;33;01m") != -1) { line = replaceColorCode(line, "[40;33;01m", "yellow", "black"); i++; }
  while (line.find("[34;42m") != -1) { line = replaceColorCode(line, "[34;42m", "#5C5CFF", "#00FF00"); i++; }
  //Other (duplicated and outdated) color combinaisons 
  while (line.find("[32m") != -1) { line = replaceColorCode(line, "[32m", "#00CD00", ""); i++; }
  while (line.find("[33;01m") != -1) { line = replaceColorCode(line, "[33;01m", "yellow", "");  i++; }//bold
  while (line.find("[31;01m") != -1) { line = replaceColorCode(line, "[31;01m", "red", "");  i++; }//bold
  while (line.find("[34;01m") != -1) { line = replaceColorCode(line, "[34;01m", "#5C5CFF", ""); i++; } //bold //directory
  while (line.find("[32;01m") != -1) { line = replaceColorCode(line, "[32;01m", "#00FF00", ""); i++; }
  while (line.find("[39;49;00m") != -1) { line = replaceColorCode(line, "[39;49;00m", defaultColor, ""); i++; } //TODO may be a bug
  //while (line.find("[39;49;00m") != -1) line = replaceColorCode(line, "[39;49;00m", "black", "");
  while (line.find("[0m") != -1) { line = replaceColorCode(line, "[0m", defaultColor, ""); i++; }//TODO may be a bug
  //while (line.find("[0m") != -1) line = replaceColorCode(line, "[0m", "black", "");
  /*#5C5CFFwhile (line.find("[01;36m") != -1) line = replaceColorCode(line, "", "", "");
  while (line.find("[01;36m") != -1) line = replaceColorCode(line, "", "", "");  
  while (line.find("[01;36m") != -1) line = replaceColorCode(line, "", "", "");*/
  
  string toReturn;
  
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
string Shell::replaceColorCode(string line, string code, string color, string bgcolor)
{
  line = line.substr(0, line.find(code)) + "<font color=" + color + " style=\"background-color:" + bgcolor +"; \">" + line.substr((line.find(code)+code.size()),(line.size() -(line.find(code)+code.size())));
  return line;
}


/**
  ThreadExec constructor

  @param[in] command the command
  @param[in] paramNumber argc
*/
char** Shell::parseCommand(string command, int &paramNumber)
{
    int counter;
    int i = 0;
    string tmp;
    counter = 0;

    tmp = command;
    while (tmp.find(" ") != -1) 
    {
	    counter++;
	    tmp = tmp.substr((tmp.find(" ") + 1), (tmp.length() - tmp.find(" ") - 1));
    }
    counter++;

    char** paramArray = new char* [counter + 2]; //FR Je peux pas les deleter, il ne m'appariennent plus après le fork (voir execvp)
    paramNumber = counter + 2;

    i = 0;
    while (command.find(" ") != -1) 
    {
	    int paramLenght = command.find(" ");
	    char* param = new char[paramLenght + 1]; //FR Je peux pas les deleter, il ne m'appariennent plus après le fork (voir execvp)
	    strcpy(param, command.substr(0, paramLenght).c_str());
	    paramArray[i] = param;
	    command =
		    command.substr((paramLenght + 1),
				    (command.length() -
				    paramLenght - 1));
	    i++;
    }

    int paramLenght = command.length();
    char* param = new char[paramLenght + 1];//FR Je peux pas les deleter, il ne m'appariennent plus après le fork (voir execvp)
    strcpy(param, command.c_str());
    paramArray[i] = param;
    paramArray[i+1] = NULL;

    //paramNumber = counter + 2;
    return paramArray;
}

/**
  Execute a command

  @param[in] command the command to execute
  @return the stdOut
*/
string Shell::getResult(string command)
{
  string output;
  char buffer[3000];


  FILE *JOB = popen(command.c_str(), "r" );
  if ( JOB != NULL ) {
    while ( fgets( buffer, sizeof buffer, JOB ) != NULL )
    {
	if (buffer[0] != 0x23)
	{
	  output += buffer;
	}
    }
  }
  return output;
}


/**
  ThreadExec constructor

  @param[in] command the command
*/
bool Shell::executeOnly(string command)
{
  pid_t pid;
  int status;
  switch (pid = fork()) //Duplicate the prosess
  {
    case (pid_t)0: //If i am the fork, execute the command
    {
      system(command.c_str()); //TODO replace some kind of exec, it will be less cheap
      exit(33);
    }
    default:
    {
      wait(&status); //if i am the parent, wait until the child die
      //TODO analyse the return code when the exec will be there
    }
  }
  return true; //TODO When the status will be impleted, return failure or success
}

void Shell::saveOutput(QString* output) {
  KSaveFile file(KStandardDirs::locateLocal("appdata", "/output/") + key);
  file.open();

  QByteArray outputByteArray;
  outputByteArray.append(*output);
  file.write(outputByteArray);
  file.finalize();
  file.close();

  //fileName = outputFileName;
}
      