/**     @file Shell.h

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

        Header of Shell.cpp

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_SHELL
#define DEF_SHELL

//#include "../mainwindow.h"
#include <string>
#include <QString>
#include <QCheckBox>

#include <QThread>

using namespace std;

class Shell : public QObject
{
    Q_OBJECT
    public:
        Shell(QCheckBox* showGUI);
	~Shell();
        static void executeCommand();
	void analyseCommand(string command);
	void kill();
	static string getResult(string command);
	static bool executeOnly(string command);
	int fork_pid;
	QString key;
   private:
        bool showGUI;
   
	void forked_exec(int *to_me, int *from_me, char* paramArray[]);
	void fatal_error(const char *msg);
	bool executionExeptions(char* paramArray[], int paramNumber);
	void exeption_cd(char path[]);
	int execute(string command, bool needPostAnalyse, string toHighlight, bool showAllLine);
	string highLight(string line, string toHighlight);
	string ajustSerialCode(string &line);
	string replaceColorCode(string line, string code, string color, string bgcolor);
	char** parseCommand(string command, int &paramNumber);
        void saveOutput(QString* output);
	//MainWindow* mainwindow;
  signals:
	void newLine(QString line);
	void isOver(QString time, QString key);
	void clearCmdOutput();
        void showFileBrowser(QString path, bool setPath);
};

class ShellThread : public QThread {
    Q_OBJECT

    public:
        ShellThread(QString command, QObject *parent = 0, QCheckBox* showGUI = 0, QString key = 0) : QThread(parent) {
	  aCommand = command;
	  aShell = new Shell(showGUI);
	  aShell->key = key;
	}
	~ShellThread() {delete aShell;}
        void run() {
	  aShell->analyseCommand(aCommand.toStdString());
	  //TODO QObject::disconnect(aShell, SIGNAL(isOver()), this, SLOT(resetCmdInputLine()));
	  //TODO QObject::disconnect(aThread->aShell, SIGNAL(newLine(QString)), this, SLOT(updateCmdOutput(QString)));
        }
      Shell* aShell;
    private:
      QString aCommand;

};

#endif
