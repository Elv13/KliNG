/**     @file term.h

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

        term.cpp header

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9
*/
#ifndef DEF_TERM
#define DEF_TERM

#include "../Shell.h"
#include "kcombobox.h"
#include "klineedit.h"
#include "kpushbutton.h"
#include <QtGui/QTextEdit>
#include <kicon.h>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QFrame>
#include <QSplitter>
#include <QCheckBox>
#include "completer.h"
#include "history.h"
#include "fileBrowser.h"

QT_BEGIN_NAMESPACE

class Term : public QWidget
{
      Q_OBJECT

  public:
    Term(History* aDockHistory, QWidget* parent, QStringList* commandStringList, QStringList* historyStringList);
    ~Term();

    QVBoxLayout *verticalLayout_6;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    KPushButton *kpushbutton_4;
    QLabel *label;
    QLineEdit *klineedit_3; //TODO when KDE bug #162071 will be fixed (reported by me) use KLineEdit instead of QLineEdit
    KPushButton *kpushbutton_5;
    QLabel* cmdStatus;
    QPixmap* pxmCmdInactive;
    QTextEdit *rtfCmdOutput;
    QHBoxLayout *hlCommand;
    KLineEdit *txtCommand;
    KComboBox *cbbOutModifier;
    KPushButton *kpushbutton_3;
    QHBoxLayout *hlCkbLayout;
    QCheckBox* ckbShowGUI;
    QCheckBox* ckbShowHiddenFile;
    QSplitter* completerSplitter;
    History* dockHistory;
    Completer* completer;
    FileBrowser* fileBrowser;

private:
  ShellThread* aThread;

private slots:
  void sendCommand();
  void searchCmdOutput();
  void updateCmdOutput(QString line);
  void resetCmdInputLine();
  void clearCmdOutput();
  void killPros();
  void resizeCompleter();
  void cmdInfoChanged(QString);
  void showFileBrowser(QString path, bool setPath);
  void addToHistory(QString line);
  void updateDate(QString date, double key);
  
signals:
  void cmdInfo(QString, int);

};

#endif
