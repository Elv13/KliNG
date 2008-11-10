/**     @file VirtTTY.h

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

        Header of VirtTTY.cpp

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef DEF_VIRT_TTY
#define DEF_VIRT_TTY

#include <string>
#include <QString>
#include <QCheckBox>
#include <QVector>
#include <QThread>

using namespace std;

  class VirtTTY : public QObject {
    Q_OBJECT
    public:
      VirtTTY(QCheckBox* showGUI);
      ~VirtTTY();
      static void executeCommand();
      int execute(QVector<QString> args);
      void kill();
      static QString getResult(string command);
      static bool executeOnly(string command);
      int fork_pid;
      QString key;
    private:
      bool showGUI;
      void forked_exec(int *to_me, int *from_me, char* paramArray[]);
      void fatal_error(const char *msg);
      bool executionExeptions(char* paramArray[], int paramNumber);
      void exeption_cd(char path[]);
      QString ajustSerialCode(QString &line);
      QString replaceColorCode(QString line, QString code, QString color, QString bgcolor);
      char** parseCommand(QVector<QString> args);
      void saveOutput(QString* output);
    signals:
      void newLine(QString line);
      void isOver(QString time, QString key);
      void clearCmdOutput();
      void showFileBrowser(QString path, bool setPath);
  };

  class VirtTtyThread : public QThread {
    Q_OBJECT

    public:
      VirtTtyThread(QString command, QVector<QString> args, QObject *parent = 0, QCheckBox* showGUI = 0, QString key = 0) : QThread(parent) {
        aCommand = command;
        this->args = args;
        aVirtTTY = new VirtTTY(showGUI);
        aVirtTTY->key = key;
      }
      ~VirtTtyThread() {delete aVirtTTY;}
      void run() {
        aVirtTTY->execute(args);
      }
      VirtTTY* aVirtTTY;
    private:
      QString aCommand;
      QVector<QString> args;
  };

#endif
