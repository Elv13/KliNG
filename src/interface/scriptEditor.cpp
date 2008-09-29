#include "../../mainwindow.h"
#include "../Shell.h"
#include "debugTerm.h"


/**
  Launch a debugging session
*/
    void MainWindow::startDebugging()
    {
      isDebugging = true;
      txtScriptEditor->setReadOnly(true);
          btnDbgNextLine->setDisabled(false);
          btnDbgSkipLine->setDisabled(false);
          btnDgbNextBP->setDisabled(false);
          btnStopDebug->setDisabled(false);
          btnDebug->setDisabled(true);
          btnPaste->setDisabled(true);
          btnCopy->setDisabled(true);
          btnCut->setDisabled(true);
          btnComment->setDisabled(true);
          btnUncomment->setDisabled(true);
          
      
      aDebugTerm = new DebugTerm(0);
      aDebugTerm->show();

      int i =0;

      string script = txtScriptEditor->toPlainText().trimmed().toStdString();
      script = script + "\n";

      for (int j = 0; j <= script.size(); j++) //Count the script line
      {
            if ((script[j] == 0x0A) && (script[j+1] != 0x0A)) i++;
      } 

      cout << i << endl;
      commandArray = new string[i];

      int j =0;
      int k =0;
      
      while (script != "")
      {
            if ((script[j] == 0x0A) || (j == (script.size()-1)))
            {
              char* command = new char[j];
              commandArray[k] = script.substr(0,j);
              script = script.substr((j+1), (script.size() - j -1));
              j = 0;
              k++;
              while (script[0] == 0x0A)
              {
                    script = script.substr(1, (script.size() -1));
              }
        }
        else
        {
          j++;
        }
      }
      
      sbCurrentLine = firstSBItem;
      currentLine = 0;
      lineNumber = i;
      cout << "Debbug state: " << sbCurrentLine->debugState << endl;
      while ((currentLine < lineNumber) && (sbCurrentLine->debugState == false))
      {
            cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
            if (sbCurrentLine->previousSBItem != NULL) sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
            sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
            sendCommand(commandArray[currentLine].c_str());
            sbCurrentLine = sbCurrentLine->nextSBItem;
            currentLine++;
      }
      if (currentLine == i)
      {
            isDebugging = false;
            txtScriptEditor->setReadOnly(false);
            btnDbgNextLine->setDisabled(true);
            btnDbgSkipLine->setDisabled(true);
            btnDgbNextBP->setDisabled(true);
            btnStopDebug->setDisabled(true);
            btnDebug->setDisabled(false);
            btnPaste->setDisabled(false);
            btnCopy->setDisabled(false);
            btnCut->setDisabled(false);
            btnComment->setDisabled(false);
            btnUncomment->setDisabled(false);
            //delete aDebugTerm;
      }
    }

/**
  End the debugging session manually
*/
    void MainWindow::stopDebugging()
    {
      isDebugging = false;
      txtScriptEditor->setReadOnly(false);
      btnDbgNextLine->setDisabled(true);
      btnDbgSkipLine->setDisabled(true);
      btnDgbNextBP->setDisabled(true);
      btnStopDebug->setDisabled(true);
      btnDebug->setDisabled(false);
      btnPaste->setDisabled(false);
      btnCopy->setDisabled(false);
      btnCut->setDisabled(false);
      btnComment->setDisabled(false);
      btnUncomment->setDisabled(false);
      //delete aDebugTerm;
    }


/**
  Function called when you press on the btnNextLine button. Execute the next line.
*/
    void MainWindow::dbgNextLine()
    {
      if (currentLine != (lineNumber +1 ))
      {
                cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
            if (sbCurrentLine->previousSBItem != NULL)
            {
              if (sbCurrentLine->previousSBItem->debugState == true) 
                  {
                    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
                  }
                  else
                  {
                    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
                  }
            }

            
            if (sbCurrentLine->debugState == true) 
                {
                  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
                }
                else
                {
                  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
                }


            sendCommand(commandArray[currentLine].c_str());
            sbCurrentLine = sbCurrentLine->nextSBItem;
            currentLine++;
      }
      else
      {
            isDebugging = false;
            txtScriptEditor->setReadOnly(false);
            btnDbgNextLine->setDisabled(true);
            btnDbgSkipLine->setDisabled(true);
            btnDgbNextBP->setDisabled(true);
            btnStopDebug->setDisabled(true);
            btnDebug->setDisabled(false);
            btnPaste->setDisabled(false);
            btnCopy->setDisabled(false);
            btnCut->setDisabled(false);
            btnComment->setDisabled(false);
            btnUncomment->setDisabled(false);
            //delete aDebugTerm;
      }
    }

/**
  Function called when you press on the btnSkipLine button. Execute the line after the next one.
*/
    void MainWindow::dbgSkipLine()
    {
      sbCurrentLine = sbCurrentLine->nextSBItem;
          currentLine++;
      if (currentLine != (lineNumber +1 ))
      {
                cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
            if (sbCurrentLine->previousSBItem != NULL)
            {
              if (sbCurrentLine->previousSBItem->debugState == true) 
                  {
                    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
                  }
                  else
                  {
                    sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
                  }
            }

            if (sbCurrentLine->previousSBItem->previousSBItem != NULL)
            {
              if (sbCurrentLine->previousSBItem->previousSBItem->debugState == true) 
                  {
                    sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
                  }
                  else
                  {
                    sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
                  }
            }

            
            if (sbCurrentLine->debugState == true) 
                {
                  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
                }
                else
                {
                  sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
                }


            sendCommand(commandArray[currentLine].c_str());
            sbCurrentLine = sbCurrentLine->nextSBItem;
            currentLine++;
      }
      else
      {
            isDebugging = false;
            txtScriptEditor->setReadOnly(false);
            btnDbgNextLine->setDisabled(true);
            btnDbgSkipLine->setDisabled(true);
            btnDgbNextBP->setDisabled(true);
            btnStopDebug->setDisabled(true);
            btnDebug->setDisabled(false);
            btnPaste->setDisabled(false);
            btnCopy->setDisabled(false);
            btnCut->setDisabled(false);
            btnComment->setDisabled(false);
            btnUncomment->setDisabled(false);
            //delete aDebugTerm;
      }
    }

/**
  Function called when you press on the btnToNextBP button. Execute all command until it find an other breakpoint
*/
    void MainWindow::dbgGoToNextBP()
    {
          cout << "je suis vivant" << endl;
          while ((currentLine < lineNumber) && (sbCurrentLine->debugState == false))
      {
            cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
            if (sbCurrentLine->previousSBItem != NULL) sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
            sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
            sendCommand(commandArray[currentLine].c_str());
            sbCurrentLine = sbCurrentLine->nextSBItem;
            currentLine++;
      }
      if (currentLine == lineNumber)
      {
            isDebugging = false;
            txtScriptEditor->setReadOnly(false);
            btnDbgNextLine->setDisabled(true);
            btnDbgSkipLine->setDisabled(true);
            btnDgbNextBP->setDisabled(true);
            btnStopDebug->setDisabled(true);
            btnDebug->setDisabled(false);
            btnPaste->setDisabled(false);
            btnCopy->setDisabled(false);
            btnCut->setDisabled(false);
            btnComment->setDisabled(false);
            btnUncomment->setDisabled(false);
            //delete aDebugTerm;
      }
    }


/**
  Function called when you press on the btnComment button. Add a # at position 0 of the line
*/
    void MainWindow::commentLine()
    {
      if (txtScriptEditor->textCursor().hasSelection())
      {
            string aScript = txtScriptEditor->toPlainText().toStdString().substr(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
            string commentedScript;
            while (aScript.find("\n") != -1)
            {
              commentedScript += "#" + aScript.substr(0, aScript.find("\n"))+ "\n";
              aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n") -1));
            cout << commentedScript << endl;
            }
            commentedScript += "#" + aScript;
            
            cout << commentedScript << endl;
            txtScriptEditor->textCursor().removeSelectedText();
            txtScriptEditor->textCursor().insertText(commentedScript.c_str());
      }
      else
      {
            txtScriptEditor->insertPlainText("#");
      }
      txtScriptEditor->setFontPointSize ( 14 );
    }

/**
  Function called when you press on the btnUncomment button. Remove a # at position 0 of the line
*/
    void MainWindow::uncommentLine()
    {
      if (txtScriptEditor->textCursor().hasSelection())
      {
            string aScript = txtScriptEditor->toPlainText().toStdString().substr(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
            string commentedScript;
            while (aScript.find("\n") != -1)
            {
              if (aScript[aScript.find("\n")+1] == '#')
              {
                commentedScript += aScript.substr(1, aScript.find("\n"));
                aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n") -1));
                cout << commentedScript << endl;
              }
              else
              {
                commentedScript += aScript.substr(0, aScript.find("\n")+1);
                aScript = aScript.substr(aScript.find("\n")+1, (aScript.size() - aScript.find("\n")-1));
                cout << commentedScript << endl;
              }
            }

            if (aScript[0] == '#') commentedScript += aScript.substr(1, (aScript.size() -1));
            else commentedScript += aScript.substr(0, (aScript.size()));
            
            txtScriptEditor->textCursor().removeSelectedText();
            txtScriptEditor->textCursor().insertText(commentedScript.c_str());
      }
      /*else //TODO make it work again
      {
            //txtScriptEditor->insertPlainText("#");
      }*/
      txtScriptEditor->setFontPointSize ( 14 );
    }
    
    void MainWindow::sendCommand(QString command) {
      ShellThread* aThread = new ShellThread(command);
      //QObject::connect(aThread->aShell, SIGNAL(isOver(QString, QString)), this, SLOT(resetCmdInputLine()));
      //QObject::connect(aThread->aShell, SIGNAL(isOver(QString, QString)), this, SLOT(updateDate(QString, QString)));
      QObject::connect(aThread->aShell, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));
      //QObject::connect(aThread->aShell, SIGNAL(clearCmdOutput()), this, SLOT(clearCmdOutput()));
      //QObject::connect(aThread->aShell, SIGNAL(showFileBrowser(QString, bool)), this, SLOT(showFileBrowser(QString, bool)));
      aThread->start();
    }