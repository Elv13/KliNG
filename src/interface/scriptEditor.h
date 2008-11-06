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
#ifndef DEF_SCRIPTEDITOR2
#define DEF_SCRIPTEDITOR2

#include <KPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <KTextEdit>
#include <KLineEdit>
#include <QLabel>
#include <QThread>
#include <QStringList>
#include <QVector>
#include "syntax/bash.h"
#include "sideBar.h"
#include "debugTerm.h"

QT_BEGIN_NAMESPACE

  class ScriptEditor : public QWidget {
    Q_OBJECT
    
    public:
      ScriptEditor(QWidget* parent, QStringList commandList);
      
      QVBoxLayout *verticalLayout_7;
      QHBoxLayout *hlControl2;
      KPushButton *btnPrevious;
      KPushButton *bntNext;
      QFrame *line;
      KPushButton *btnSave;
      KPushButton *btnPrint;
      QFrame *line_2;
      KPushButton *btnComment;
      KPushButton *btnUncomment;
      KPushButton *btnCopy;
      KPushButton *btnCut;
      KPushButton *btnPaste;
      QFrame *line_3;
      KPushButton *btnDebug;
      KPushButton *btnStopDebug;
      KPushButton *btnDbgNextLine;
      KPushButton *btnDbgSkipLine;
      KPushButton *btnDgbNextBP;
      QSpacerItem *horizontalSpacer;
      QScrollArea *scrollArea;
      QWidget *scrollAreaWidgetContents_2;
      QHBoxLayout *textEditLayout;
      QFrame *frame_3;
      QSpacerItem *verticalSpacer_12;
      QVBoxLayout *verticalLayout_29;
      KTextEdit *txtScriptEditor;
      QFrame *frame_2;
      QHBoxLayout *horizontalLayout_5;
      KPushButton *kpushbutton_6;
      QLabel *label_2;
      KLineEdit *klineedit_4;
      KPushButton *kpushbutton_7;
      QTableWidget* lineNBSideBar;
      QString fileName;
      BashSyntaxHighlighter* bashHighlighter;
            
    private:
      void sendCommand(QString command);
      int countLine(QString script);
      void setDebuggerMode(bool value);
      bool evalCondition(QString line);
      void highlightLine(int number);
      QString* commandArray;
      QString originalText;
      bool isDebugging;
      int currentLine;
      int lineNumber;
      int sbLineNB2;
      int currentLineCount;
      SideBar* firstSBItem;
      SideBar* lastSBItem;
      SideBar* sbCurrentLine;
      DebugTerm* aDebugTerm;
      
      //Interpreter
      QVector<bool*> ifVector;
      QVector<int*> loopVector;
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
      
    private slots:
      void startDebugging();
      void stopDebugging();
      void dbgNextLine();
      void dbgSkipLine();
      void dbgGoToNextBP();
      void commentLine();
      void uncommentLine();
      void openFile();
      void saveFileAs(const QString &outputFileName);
      void openFile(const QString &inputFileName);
      void saveFile();
      void saveFileAs();
      void setFileName(QString name);
      void setText(QString script);
      void textChanged();
      void updateLineCount(int lineCount);
      void executeNextCommand();
  };
  
  class EditorThread : public QThread {
    Q_OBJECT

    public:
        EditorThread(QObject *parent = 0, QString script = "") : QThread(parent) {
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
