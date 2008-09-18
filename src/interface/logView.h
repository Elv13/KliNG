/**     @file logView.h

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

        logView.cpp header file

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#ifndef UI_LOGVIEW_H
#define UI_LOGVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <kcombobox.h>
#include <kpushbutton.h>
#include <kseparator.h>
#include <kdialog.h>

class LogView : public KDialog
{
  Q_OBJECT
public:
    LogView(QWidget* parent);  
    ~LogView();
    void retranslateUi();
    
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlControl;
    KComboBox *cbbLog;
    QSlider *sldLenght;
    KSeparator *kseparator;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *rtfViewer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    KPushButton *btnClose;
  

//private slots:

};

/*class LogView : KDialog
{
  Q_OBJECT
public:
    LogView(QWidget* parent);  
    ~LogView();
    void retranslateUi();

    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlControl;
    KComboBox *cbbLog;
    QSlider *sldLenght;
    KSeparator *kseparator;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *rtfViewer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    KPushButton *btnClose;
};*/

#endif
