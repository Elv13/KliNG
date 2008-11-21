/**     @file scriptEditor.h

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

        scriptEditor.cpp header

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/
#ifndef DEF_SHELL4
#define DEF_SHELL4

#include <QStringList>
#include <QVector>
#include <QThread>
#include "shell/processWatcher.h"

  class Shell  {  
    public:
      Shell(QStringList* commandList, QStringList* aliasList, QStringList* defaultArgsList, QStringList* functionList);
      ~Shell();
      int countLine(QString script);
      QVector<QString> parseCommand(QString command);
            
    protected:
      virtual void sendCommand();
      bool evalCondition(QString line);
      QString* commandArray;
      QString originalText;
      int currentLine;
      int lineNumber;
      int currentLineCount;
      QVector<bool*> ifVector;
      QVector<int*> loopVector;
      QStringList* commandList;
      QStringList* aliasList;
      QStringList* defaultArgsList;
      QStringList* functionList;
      QVector< QVector<QString> > executionQueue;
      bool loopUntilCondition();
      bool ifStatement();
      bool whileLoop();
      bool forLoop();
      bool untilLoop();
      bool doneStatement();
      bool elseStatement();
      bool elifStatement();
      bool fiStatement();
      bool evalCommand();
      virtual void signalNextLine();
      virtual void signalNewCommand(QString command);
      void checkCommand(QVector<QString> *args);
      void analyseCommand(QString command, QVector<QString> args);
      QVector< QVector<QString> > splitCommand(QVector<QString> original);
  };
  
  class LineCounter : public QThread {
    Q_OBJECT

    public:
        LineCounter(QObject *parent = 0, QString script = "") : QThread(parent) {
          this->script = script;
        }
        void run() {
          int i =0;
          script += "\n";
          for (int j = 0; j <= script.size(); j++) //TODO this is not efficient at all
                if ((script[j] == 0x0A)) 
                  i++;
          emit lineCount(i);
        }
        
    private:
          QString script;
          
    signals:
      void lineCount(int);
  };
#endif
