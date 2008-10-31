//include "../../mainwindow.h"
#include "../Shell.h"
#include "debugTerm.h"
#include "scriptEditor.h"
#include <KStandardDirs>
#include <QFile>
#include <KIcon>
#include <KSaveFile>
#include <KFileDialog>
#include <QTextStream>
#include <KIO/NetAccess>
#include <KMessageBox>
#include <KLocalizedString>
#include <QHeaderView>
#include <QtSql>
#include <QSqlDatabase>
#include <time.h>
// count

  ScriptEditor::ScriptEditor(QWidget* parent) : QWidget(parent) {
    inCondition = 0;
    isDebugging = false;
    verticalLayout_7 = new QVBoxLayout(this);
    verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
    hlControl2 = new QHBoxLayout();
    hlControl2->setObjectName(QString::fromUtf8("hlControl2"));
    
    btnPrevious = new KPushButton(this);
    btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
    btnPrevious->setMinimumSize(QSize(31, 31));
    btnPrevious->setMaximumSize(QSize(31, 31));
    KIcon icnEditUndo("edit-undo");
    btnPrevious->setIcon(icnEditUndo);
    hlControl2->addWidget(btnPrevious);

    bntNext = new KPushButton(this);
    bntNext->setObjectName(QString::fromUtf8("bntNext"));
    bntNext->setMinimumSize(QSize(31, 31));
    bntNext->setMaximumSize(QSize(31, 31));
    KIcon icnEditRedo("edit-redo");
    bntNext->setIcon(icnEditRedo);
    hlControl2->addWidget(bntNext);

    line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    hlControl2->addWidget(line);

    btnSave = new KPushButton(this);
    btnSave->setObjectName(QString::fromUtf8("btnSave"));
    btnSave->setMinimumSize(QSize(31, 31));
    btnSave->setMaximumSize(QSize(31, 31));
    KIcon icnDocSave("document-save");
    btnSave->setIcon(icnDocSave);
    hlControl2->addWidget(btnSave);

    btnPrint = new KPushButton(this);
    btnPrint->setObjectName(QString::fromUtf8("btnPrint"));
    btnPrint->setMinimumSize(QSize(31, 31));
    btnPrint->setMaximumSize(QSize(31, 31));
    KIcon icnDocPrint("document-print");
    btnPrint->setIcon(icnDocPrint);
    hlControl2->addWidget(btnPrint);

    line_2 = new QFrame(this);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);
    hlControl2->addWidget(line_2);

    btnComment = new KPushButton(this);
    btnComment->setObjectName(QString::fromUtf8("btnComment"));
    btnComment->setMinimumSize(QSize(31, 31));
    btnComment->setMaximumSize(QSize(31, 31));
    KIcon icon5(KStandardDirs::locate( "appdata", "pixmap/22x22/comment.png"));
    btnComment->setIcon(icon5);
    btnComment->setIconSize(QSize(12, 12));
    hlControl2->addWidget(btnComment);

    btnUncomment = new KPushButton(this);
    btnUncomment->setObjectName(QString::fromUtf8("btnUncomment"));
    btnUncomment->setMinimumSize(QSize(31, 31));
    btnUncomment->setMaximumSize(QSize(31, 31));
    KIcon icon6(KStandardDirs::locate( "appdata", "pixmap/22x22/uncomment.png"));
    btnUncomment->setIcon(icon6);
    btnUncomment->setIconSize(QSize(14, 14));
    hlControl2->addWidget(btnUncomment);

    btnCopy = new KPushButton(this);
    btnCopy->setObjectName(QString::fromUtf8("btnCopy"));
    btnCopy->setMinimumSize(QSize(31, 31));
    btnCopy->setMaximumSize(QSize(31, 31));
    KIcon icnEditCopy("edit-copy");
    btnCopy->setIcon(icnEditCopy);
    hlControl2->addWidget(btnCopy);

    btnCut = new KPushButton(this);
    btnCut->setObjectName(QString::fromUtf8("btnCut"));
    btnCut->setMinimumSize(QSize(31, 31));
    btnCut->setMaximumSize(QSize(31, 31));
    KIcon icnEditCut("edit-cut");
    btnCut->setIcon(icnEditCut);
    hlControl2->addWidget(btnCut);

    btnPaste = new KPushButton(this);
    btnPaste->setObjectName(QString::fromUtf8("btnPaste"));
    btnPaste->setMinimumSize(QSize(31, 31));
    btnPaste->setMaximumSize(QSize(31, 31));
    KIcon icnEditPaste("edit-paste");
    btnPaste->setIcon(icnEditPaste);
    hlControl2->addWidget(btnPaste);

    line_3 = new QFrame(this);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::VLine);
    line_3->setFrameShadow(QFrame::Sunken);
    hlControl2->addWidget(line_3);

    btnDebug = new KPushButton(this);
    btnDebug->setObjectName(QString::fromUtf8("btnDebug"));
    btnDebug->setMinimumSize(QSize(31, 31));
    btnDebug->setMaximumSize(QSize(31, 31));
    KIcon icnArrowRight("arrow-right");
    btnDebug->setIcon(icnArrowRight);
    hlControl2->addWidget(btnDebug);

    btnStopDebug = new KPushButton(this);
    btnStopDebug->setObjectName(QString::fromUtf8("btnStopDebug"));
    btnStopDebug->setMinimumSize(QSize(31, 31));
    btnStopDebug->setMaximumSize(QSize(31, 31));
    btnStopDebug->setIcon(KIcon("window-close"));
    hlControl2->addWidget(btnStopDebug);

    btnDbgNextLine = new KPushButton(this);
    btnDbgNextLine->setObjectName(QString::fromUtf8("btnDbgNextLine"));
    btnDbgNextLine->setMinimumSize(QSize(31, 31));
    btnDbgNextLine->setMaximumSize(QSize(31, 31));
    KIcon icon11(KStandardDirs::locate( "appdata", "pixmap/22x22/nextline.png"));
    btnDbgNextLine->setIcon(icon11);
    btnDbgNextLine->setIconSize(QSize(16, 16));
    hlControl2->addWidget(btnDbgNextLine);

    btnDbgSkipLine = new KPushButton(this);
    btnDbgSkipLine->setObjectName(QString::fromUtf8("btnDbgSkipLine"));
    btnDbgSkipLine->setMinimumSize(QSize(31, 31));
    btnDbgSkipLine->setMaximumSize(QSize(31, 31));
    KIcon icon12(KStandardDirs::locate( "appdata", "pixmap/22x22/skipline.png"));
    btnDbgSkipLine->setIcon(icon12);
    btnDbgSkipLine->setIconSize(QSize(16, 16));
    hlControl2->addWidget(btnDbgSkipLine);

    btnDgbNextBP = new KPushButton(this);
    btnDgbNextBP->setObjectName(QString::fromUtf8("btnDgbNextBP"));
    btnDgbNextBP->setMinimumSize(QSize(31, 31));
    btnDgbNextBP->setMaximumSize(QSize(31, 31));
    KIcon icon13(KStandardDirs::locate( "appdata", "pixmap/22x22/run.png"));
    btnDgbNextBP->setIcon(icon13);
    btnDgbNextBP->setIconSize(QSize(16, 16));
    hlControl2->addWidget(btnDgbNextBP);

    horizontalSpacer = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hlControl2->addItem(horizontalSpacer);

    verticalLayout_7->addLayout(hlControl2);

    scrollArea = new QScrollArea(this);
    scrollArea->setContentsMargins(0, 0, 0, 0);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setStyleSheet(QString::fromUtf8("margin:0px;border:0px;padding:0px;spacing:0px;"));
    scrollArea->setFrameShape(QFrame::StyledPanel);
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents_2 = new QWidget();
    scrollAreaWidgetContents_2->setContentsMargins(0, 0, 0, 0);
    scrollAreaWidgetContents_2->setStyleSheet(QString::fromUtf8("margin:0px;border:0px;padding:0px;spacing:0px;"));
    scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
    scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 493, 1010));
    textEditLayout = new QHBoxLayout(scrollAreaWidgetContents_2);
    textEditLayout->setContentsMargins(0, 0, 0, 0);
    textEditLayout->setSpacing(0);
    textEditLayout->setObjectName(QString::fromUtf8("textEditLayout"));

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    
    lineNBSideBar = new QTableWidget(0);
    textEditLayout->addWidget(lineNBSideBar);
    lineNBSideBar->setSizePolicy(sizePolicy);
    lineNBSideBar->setMaximumWidth(35);
    lineNBSideBar->setMinimumWidth(35);
    lineNBSideBar->setStyleSheet("margin:0px;border:0px;padding:0px;spacing:0px;");
    
    firstSBItem = new SideBar(1, NULL,lineNBSideBar );
    lastSBItem = firstSBItem;
    if (lineNBSideBar->columnCount() < 1)
        lineNBSideBar->setColumnCount(1);
        
    lineNBSideBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNBSideBar->setRowHeight (0, 20 );
    lineNBSideBar->setColumnWidth(0, 35);
    lineNBSideBar->setCellWidget ( 0, 0, firstSBItem );
    lineNBSideBar->verticalHeader()->hide();
    lineNBSideBar->horizontalHeader()->hide();
    
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);

    txtScriptEditor = new KTextEdit(scrollAreaWidgetContents_2);
    txtScriptEditor->setSizePolicy(sizePolicy2);
    txtScriptEditor->setDisabled(true);
    txtScriptEditor->setFontPointSize ( 14 );
    txtScriptEditor->setObjectName(QString::fromUtf8("txtScriptEditor"));
    txtScriptEditor->setMinimumSize(QSize(0, 1000));
    txtScriptEditor->setStyleSheet(QString::fromUtf8("margin:0px;border:0px;padding:0px;spacing:0px;"));
    txtScriptEditor->setFrameShape(QFrame::StyledPanel);
    txtScriptEditor->setLineWidth(1);
    txtScriptEditor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    txtScriptEditor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    txtScriptEditor->setLineWrapMode(QTextEdit::NoWrap);
    txtScriptEditor->setLineWrapColumnOrWidth(100);
    txtScriptEditor->setAcceptRichText(true);
    textEditLayout->addWidget(txtScriptEditor);

    scrollArea->setWidget(scrollAreaWidgetContents_2);

    verticalLayout_7->addWidget(scrollArea);

    frame_2 = new QFrame(this);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setMinimumSize(QSize(0, 26));
    frame_2->setMaximumSize(QSize(16777215, 26));
    frame_2->setStyleSheet(QString::fromUtf8(""));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    frame_2->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0px;padding:0px;border:0px;border-color:#808000;padding-top:0px;spacing:0px;");
    frame_2->hide();
    horizontalLayout_5 = new QHBoxLayout(frame_2);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    kpushbutton_6 = new KPushButton(frame_2);
    kpushbutton_6->setObjectName(QString::fromUtf8("kpushbutton_6"));
    kpushbutton_6->setMinimumSize(QSize(22, 22));
    kpushbutton_6->setMaximumSize(QSize(22, 22));
    kpushbutton_6->setStyleSheet(QString::fromUtf8("background-color:  rgb(230, 255, 105);\n"
"border-style: outset;"));
    kpushbutton_6->setIcon(KIcon("window-close"));
    horizontalLayout_5->addWidget(kpushbutton_6);

    label_2 = new QLabel(frame_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0px;min-height:15px;font-size:12px;padding-top:1px");
    horizontalLayout_5->addWidget(label_2);

    klineedit_4 = new KLineEdit(frame_2);
    klineedit_4->setObjectName(QString::fromUtf8("klineedit_4"));
    klineedit_4->setProperty("showClearButton", QVariant(true));
    klineedit_4->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0px;padding:0px;border:1px;border-style:solid;border-color:#808000;spacing:0px;height:15px;min-height:15px;");
    horizontalLayout_5->addWidget(klineedit_4);

    kpushbutton_7 = new KPushButton(frame_2);
    kpushbutton_7->setObjectName(QString::fromUtf8("kpushbutton_7"));
    kpushbutton_7->setStyleSheet("background-color:  rgb(230, 255, 105);margin:0;padding:0;border:1;border-style:solid;border-color:#808000;padding-right:5;padding-left:5;spacing:0;min-height:15px;margin-right:5px;");
    horizontalLayout_5->addWidget(kpushbutton_7);

    verticalLayout_7->addWidget(frame_2);
    
    QObject::connect(kpushbutton_6, SIGNAL(clicked()), frame_2, SLOT(hide()));
    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(btnCopy, SIGNAL(clicked()), txtScriptEditor, SLOT(copy()));
    QObject::connect(btnPaste, SIGNAL(clicked()), txtScriptEditor, SLOT(paste()));
    QObject::connect(btnCut, SIGNAL(clicked()), txtScriptEditor, SLOT(cut()));
    QObject::connect(bntNext, SIGNAL(clicked()), txtScriptEditor, SLOT(redo()));
    QObject::connect(btnPrevious, SIGNAL(clicked()), txtScriptEditor, SLOT(undo()));
    QObject::connect(btnDebug, SIGNAL(clicked()), this, SLOT(startDebugging()));
    QObject::connect(btnStopDebug, SIGNAL(clicked()), this, SLOT(stopDebugging()));
    QObject::connect(btnDbgNextLine, SIGNAL(clicked()), this, SLOT(dbgNextLine()));
    QObject::connect(btnDbgSkipLine, SIGNAL(clicked()), this, SLOT(dbgSkipLine()));
    QObject::connect(btnDgbNextBP, SIGNAL(clicked()), this, SLOT(dbgGoToNextBP()));
    QObject::connect(btnComment, SIGNAL(clicked()), this, SLOT(commentLine()));
    QObject::connect(btnUncomment, SIGNAL(clicked()), this, SLOT(uncommentLine()));
    QObject::connect(txtScriptEditor, SIGNAL(textChanged()), this, SLOT(textChanged()));

    btnDbgNextLine->setDisabled(true);
    btnDbgSkipLine->setDisabled(true);
    btnDgbNextBP->setDisabled(true);
    btnStopDebug->setDisabled(true);
    
    label_2->setText("Filter:");
    kpushbutton_7->setText("search");
  }

/**
  Launch a debugging session
*/
  void ScriptEditor::startDebugging() {
    setDebuggerMode(true);
    aDebugTerm = new DebugTerm(0);
    aDebugTerm->show();

    QString script = txtScriptEditor->toPlainText().toAscii();
    int i = countLine(txtScriptEditor->toPlainText().toAscii());

    //cout << i << endl;
    commandArray = new QString[i];

    int j =0;
    int k =0;
    
    while (script != "") {
      if ((script[j] == 0x0A) || (j == (script.size()-1))) {
        char* command = new char[j];
        commandArray[k] = script.mid(0,j).trimmed();
        script = script.mid((j+1), (script.size() - j -1));
        j = 0;
        k++;
        while (script[0] == 0x0A)
          script = script.mid(1, (script.size() -1));
      }
      else
        j++;
    }
    
    sbCurrentLine = firstSBItem;
    currentLine = 0;
    lineNumber = i;
    //cout << "Debbug state: " << sbCurrentLine->debugState << endl;
    if ((currentLine < lineNumber) && (sbCurrentLine->debugState == false)) {
      //cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
      if (sbCurrentLine->previousSBItem != NULL) 
        sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
      sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      sendCommand(commandArray[currentLine].toStdString().c_str());
      sbCurrentLine = sbCurrentLine->nextSBItem;
      currentLine++;
    }
    if (currentLine == i) {
      setDebuggerMode(false);
    }
  }

/**
  End the debugging session manually
*/
  void ScriptEditor::stopDebugging() {
    setDebuggerMode(false);
  }


/**
  Function called when you press on the btnNextLine button. Execute the next line.
*/
  void ScriptEditor::dbgNextLine() {
    if (currentLine != (lineNumber +1 )) {
      //cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
      if (sbCurrentLine->previousSBItem != NULL) {
        if (sbCurrentLine->previousSBItem->debugState == true) 
          sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
        else
          sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
      }

      if (sbCurrentLine->debugState == true) 
        sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
      else
        sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);

      if (commandArray[currentLine] != "")
        sendCommand(commandArray[currentLine].toStdString().c_str());
      
      sbCurrentLine = sbCurrentLine->nextSBItem;
      currentLine++;
    }
    else {
      setDebuggerMode(false);
      //delete aDebugTerm;
    }
  }

/**
  Function called when you press on the btnSkipLine button. Execute the line after the next one.
*/
  void ScriptEditor::dbgSkipLine() {
    sbCurrentLine = sbCurrentLine->nextSBItem;
    currentLine++;
    if (currentLine != (lineNumber +1 )) {
      //cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
      if (sbCurrentLine->previousSBItem != NULL) {
        if (sbCurrentLine->previousSBItem->debugState == true) 
          sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
        else 
          sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
      }

      if (sbCurrentLine->previousSBItem->previousSBItem != NULL) {
        if (sbCurrentLine->previousSBItem->previousSBItem->debugState == true) 
          sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnBP);
        else
          sbCurrentLine->previousSBItem->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
      }
        
      if (sbCurrentLine->debugState == true) 
        sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrowBP);
      else
        sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);

      sendCommand(commandArray[currentLine].toStdString().c_str());
      sbCurrentLine = sbCurrentLine->nextSBItem;
      currentLine++;
    }
    else {
      setDebuggerMode(false);
      //delete aDebugTerm;
    }
  }

/**
  Function called when you press on the btnToNextBP button. Execute all command until it find an other breakpoint
*/
  void ScriptEditor::dbgGoToNextBP() {
    while ((currentLine < lineNumber) && (sbCurrentLine->debugState == false)) {
      //cout << &sbCurrentLine << ": "<< sbCurrentLine->debugState << endl;
      if (sbCurrentLine->previousSBItem != NULL) sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
      sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      sendCommand(commandArray[currentLine].toStdString().c_str());
      sbCurrentLine = sbCurrentLine->nextSBItem;
      currentLine++;
    }
    if (currentLine == lineNumber) {
      setDebuggerMode(false);
      //delete aDebugTerm;
    }
  }


/**
  Function called when you press on the btnComment button. Add a # at position 0 of the line
*/
  void ScriptEditor::commentLine() {
    if (txtScriptEditor->textCursor().hasSelection()) {
      QString aScript = txtScriptEditor->toPlainText().mid(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
      QString commentedScript;
      while (aScript.indexOf("\n") != -1) {
        commentedScript += "#" + aScript.left(aScript.indexOf("\n"))+ "\n";
        aScript = aScript.mid(aScript.indexOf("\n")+1, (aScript.size() - aScript.indexOf("\n") -1));
      }
      commentedScript += "#" + aScript;
      
      txtScriptEditor->textCursor().removeSelectedText();
      txtScriptEditor->textCursor().insertText(commentedScript);
    }
    else 
      txtScriptEditor->insertPlainText("#");
    txtScriptEditor->setFontPointSize ( 14 );
  }

/**
  Function called when you press on the btnUncomment button. Remove a # at position 0 of the line
*/
  void ScriptEditor::uncommentLine() {
    if (txtScriptEditor->textCursor().hasSelection()) {
      QString aScript = txtScriptEditor->toPlainText().mid(txtScriptEditor->textCursor().selectionStart(), (txtScriptEditor->textCursor().selectionEnd() - txtScriptEditor->textCursor().selectionStart()));
      QString commentedScript;
      while (aScript.indexOf("\n") != -1) {
        if (aScript[aScript.indexOf("\n")+1] == '#') {
          commentedScript += aScript.mid(1, aScript.indexOf("\n"));
          aScript = aScript.mid(aScript.indexOf("\n")+1, (aScript.size() - aScript.indexOf("\n") -1));
        }
        else {
          commentedScript += aScript.mid(aScript.indexOf("\n")+1);
          aScript = aScript.mid(aScript.indexOf("\n")+1, (aScript.size() - aScript.indexOf("\n")-1));
        }
      }

      if (aScript[0] == '#') 
        commentedScript += aScript.mid(1, (aScript.size() -1));
      else 
        commentedScript += aScript.left((aScript.size()));
      
      txtScriptEditor->textCursor().removeSelectedText();
      txtScriptEditor->textCursor().insertText(commentedScript);
    }
    /*else //TODO make it work again
    {
          //txtScriptEditor->insertPlainText("#");
    }*/
    txtScriptEditor->setFontPointSize ( 14 );
  }
    
  void ScriptEditor::sendCommand(QString command) {
    ShellThread* aThread = new ShellThread(command);
    //QObject::connect(aThread->aShell, SIGNAL(isOver(QString, QString)), this, SLOT(resetCmdInputLine()));
    //QObject::connect(aThread->aShell, SIGNAL(isOver(QString, QString)), this, SLOT(updateDate(QString, QString)));
    QObject::connect(aThread->aShell, SIGNAL(newLine(QString)), aDebugTerm->rtfDegubTerm, SLOT(append(QString)));
    QObject::connect(aThread->aShell, SIGNAL(isOver(QString, QString)), this, SLOT(executeNextCommand()));
    //QObject::connect(aThread->aShell, SIGNAL(clearCmdOutput()), this, SLOT(clearCmdOutput()));
    //QObject::connect(aThread->aShell, SIGNAL(showFileBrowser(QString, bool)), this, SLOT(showFileBrowser(QString, bool)));
    aThread->start();
  }
  
  void ScriptEditor::saveFileAs(const QString &outputFileName) {
    KSaveFile file(outputFileName);
    file.open();

    QByteArray outputByteArray;
    outputByteArray.append(txtScriptEditor->toPlainText());
    file.write(outputByteArray);
    file.finalize();
    file.close();

    fileName = outputFileName;
  }

/**
  Default KDE file saving funtion
*/
  void ScriptEditor::saveFileAs() {
    saveFileAs(KFileDialog::getSaveFileName());
  }

/**
  Default KDE file saving funtion
*/
  void ScriptEditor::saveFile() {
    QSqlQuery query;
    query.exec("insert into TSCRIPT_VERSION (NAME,DATE) values ('"+ fileName.right(fileName.count() - fileName.lastIndexOf("/") -1) +"','" + QString::number(time(NULL)) + "')");
    
    QSqlQuery query2;
    query2.exec("SELECT TSCRIPT_VERSION_KEY FROM TSCRIPT_VERSION ORDER BY TSCRIPT_VERSION_KEY DESC" ); //TODO add top 1
    query2.next();
      
    QFile::copy(fileName,KStandardDirs::locateLocal("appdata","/backup/")+query2.value(0).toString());
    
    if(!fileName.isEmpty())
      saveFileAs(fileName);
    else
      saveFileAs();
  }

/**
  Default KDE file opening funtion
*/
  void ScriptEditor::openFile() {
    openFile(KFileDialog::getOpenFileName());
  }

/**
  Default KDE file opening funtion 
*/
  void ScriptEditor::openFile(const QString &inputFileName) {
    QString tmpFile;
    if(KIO::NetAccess::download(inputFileName, tmpFile, this)) {
      QFile file(tmpFile);
      file.open(QIODevice::ReadOnly);
      txtScriptEditor->setPlainText(QTextStream(&file).readAll());
      fileName = inputFileName;

      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else {
      KMessageBox::error(this,
      KIO::NetAccess::lastErrorString());
    }
  }
  
  void ScriptEditor::setFileName(QString name) {
    fileName = name;
  }
  
  void ScriptEditor::setText(QString script) {
    txtScriptEditor->setPlainText(script.trimmed());
    int lineCount = countLine(script.trimmed());
    updateLineCount(lineCount);
  }
  
  int ScriptEditor::countLine(QString script) {
    int i =0;

    script += "\n";

    for (int j = 0; j <= script.size(); j++) { //Count the script line
          if ((script[j] == 0x0A) && (script[j+1] != 0x0A)) 
            i++;
    } 
    return i;
  }
  
  
 void ScriptEditor::textChanged() {
   EditorThread* aThread = new EditorThread(this, txtScriptEditor->toPlainText());
   QObject::connect(aThread, SIGNAL(lineCount(int)), this, SLOT(updateLineCount(int)));
   aThread->run();
 }
 
 void ScriptEditor::updateLineCount(int lineCount) {
   if (lineCount != currentLineCount) {
    currentLineCount=lineCount;
      /*SideBar* anSBItem = firstSBItem->nextSBItem;
      SideBar* anSBItem2 = firstSBItem->nextSBItem;
      while (anSBItem != NULL) { //TODO I don't know if Qt really have a garbage collector or I am just crazy, every time I do a delete, it crash
        anSBItem2 = anSBItem;
        anSBItem->nextSBItem;
        //delete anSBItem2;
      }*/
      lastSBItem = firstSBItem;
      lineNBSideBar->setRowCount(1);
      lineNBSideBar->setRowHeight (0, 20 );
      lineNBSideBar->clear();   
      lineNBSideBar->setCellWidget ( 0, 0, new SideBar(firstSBItem));
      if (lineCount > 10000) {
        lineNBSideBar->setMaximumWidth(75);
        lineNBSideBar->setMinimumWidth(75);
        lineNBSideBar->setColumnWidth(0, 75);
      }
      else if (lineCount > 1000) {
        lineNBSideBar->setMaximumWidth(65);
        lineNBSideBar->setMinimumWidth(65);
        lineNBSideBar->setColumnWidth(0, 65);
      }
      else if (lineCount > 100) {
        lineNBSideBar->setMaximumWidth(55);
        lineNBSideBar->setMinimumWidth(55);
        lineNBSideBar->setColumnWidth(0, 55);
      }
      else if (lineCount > 10) {
        lineNBSideBar->setMaximumWidth(45);
        lineNBSideBar->setMinimumWidth(45);
        lineNBSideBar->setColumnWidth(0, 45);
      }
      else {
        lineNBSideBar->setMaximumWidth(35);
        lineNBSideBar->setMinimumWidth(35);
        lineNBSideBar->setColumnWidth(0, 35);
      }

      for (int j =1; j < lineCount; j++) {
          lineNBSideBar->setRowCount(j+1);
          lineNBSideBar->setRowHeight (j, 20 );
          lastSBItem = new SideBar(2, lastSBItem, lineNBSideBar);
          lineNBSideBar->setCellWidget ( j, 0,lastSBItem); //TODO flags do not work, send a Qt bugs (feature request) to check when widget inherit QTableWidgetItem to follow flags
          lastSBItem->setFlags(Qt::NoItemFlags);
      }
   }
 }

  void ScriptEditor::executeNextCommand() {
    int i = countLine(txtScriptEditor->toPlainText().toAscii());
    if ((currentLine < lineNumber) && (sbCurrentLine->debugState == false)) {
      if (sbCurrentLine->previousSBItem != NULL) 
        sbCurrentLine->previousSBItem->btnDebug->setIcon(*sbCurrentLine->icnEmpty);
        
      evalCommand();
      currentLine++;
    }
    if (currentLine == i) {
      setDebuggerMode(false);
    }
  }

  void ScriptEditor::setDebuggerMode(bool value) {
    isDebugging = value;
    txtScriptEditor->setReadOnly(value);
    btnDbgNextLine->setDisabled(!value);
    btnDbgSkipLine->setDisabled(!value);
    btnDgbNextBP->setDisabled(!value);
    btnStopDebug->setDisabled(!value);
    btnDebug->setDisabled(value);
    btnPaste->setDisabled(value);
    btnCopy->setDisabled(value);
    btnCut->setDisabled(value);
    btnComment->setDisabled(value);
    btnUncomment->setDisabled(value);
  }
  
  #include <iostream>
  bool ScriptEditor::evalCondition(QString line) {
    line = line.mid(line.indexOf("[")+1, (line.count() - (line.indexOf("[")+1)));
    line = line.left(line.indexOf("]")).trimmed();
    std::string result = Shell::getResult("/home/lepagee/test2.sh \"" + line.toStdString() + "\"");
    printf("\n \n \n This is the result: %s \n \n \n",result.c_str());
    
    return !(bool) QString::fromStdString(result).toInt();
  }

  bool ScriptEditor::loopUntilCondition() {
    currentLine++;
    while ((commandArray[currentLine].trimmed().left(2).toLower() != "fi") && (commandArray[currentLine].trimmed().left(4).toLower() != "elif") && (commandArray[currentLine].trimmed().left(4).toLower() != "else")) {
      currentLine++;
      /*sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      sbCurrentLine = sbCurrentLine->nextSBItem;*/
    }
    return false;
  }
  
  bool ScriptEditor::ifStatement() {
    inCondition++;
    if (evalCondition(commandArray[currentLine])) {
      currentLine++;
      sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      sbCurrentLine = sbCurrentLine->nextSBItem;
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
  
  bool ScriptEditor::whileLoop() {
    
  }
  
  bool ScriptEditor::forLoop() {
    
  }
  
  bool ScriptEditor::untilLoop() {
    
  }
  
  bool ScriptEditor::elseStatement() {
    currentLine++;
    sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
    sbCurrentLine = sbCurrentLine->nextSBItem;
    evalCommand();
  }
  
  bool ScriptEditor::elifStatement() {
    if (evalCondition(commandArray[currentLine])) {
          currentLine++;
          sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
          sbCurrentLine = sbCurrentLine->nextSBItem;
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
  
  bool ScriptEditor::fiStatement() {
    inCondition--;
    currentLine++;
    sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
    sbCurrentLine = sbCurrentLine->nextSBItem;
    sendCommand(commandArray[currentLine].toStdString().c_str()); //TODO test if this is a condition
  }
  
  bool ScriptEditor::evalCommand() {
    if (commandArray[currentLine].trimmed().left(2).toLower() == "if") {                            
      ifStatement();
    }
    else if (commandArray[currentLine].trimmed().left(5).toLower() == "while") {                            
      evalCondition(commandArray[currentLine]);
    }
    else if (commandArray[currentLine].trimmed().left(4).toLower() == "elif") {                            
      elifStatement();
    }
    else if (commandArray[currentLine].trimmed().left(4).toLower() == "else") {            
      printf("i am here");
      elseStatement();
    }
    else if (commandArray[currentLine].trimmed().left(5).toLower() == "until") {                            
      evalCondition(commandArray[currentLine]);
    }
    else if (commandArray[currentLine].trimmed().left(3).toLower() == "for") {                            
      evalCondition(commandArray[currentLine]);
    }
    else if (commandArray[currentLine].trimmed().left(2).toLower() == "fi") {                            
      fiStatement();
    }
    else {
      sbCurrentLine->btnDebug->setIcon(*sbCurrentLine->icnArrow);
      sendCommand(commandArray[currentLine].toStdString().c_str());
      sbCurrentLine = sbCurrentLine->nextSBItem;
    }
  }