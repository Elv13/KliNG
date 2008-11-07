#include "executionMonitor.h"
#include <QSizePolicy>
#include <QGridLayout>
#include <QtGui/QSpacerItem>
#include <QColor>
#include <QBrush>
#include <QPalette>

  ExecutionMonitor::ExecutionMonitor(QWidget* parent) : QWidget(parent) {
    executedScriptNb =0;
    cmdExecutedScriptNb = 0;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setFrameShape(QFrame::StyledPanel);
    scrollArea->setWidgetResizable(true);
    
    display = new QWidget;
    display->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    QPalette aPalette;
    display->setStyleSheet(QString::fromUtf8("background-color:") + aPalette.base().color().name () +";");
    scrollArea->setWidget(display);
    mainLayout->addWidget(scrollArea);
    
    horizontalLayout_4 = new QVBoxLayout(display);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

    QSpacerItem* horizontalSpacer25 = new QSpacerItem(38, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    horizontalLayout_4->addItem(horizontalSpacer25);

    QSpacerItem* horizontalSpacer26 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    horizontalLayout_4->addItem(horizontalSpacer26);
    
    stat = new QWidget;
    stat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    mainLayout->addWidget(stat);
    
    QGridLayout* aGridLayout = new QGridLayout;
    stat->setLayout(aGridLayout);
    
    lblExecuted = new QLabel("Script executed (today): ");
    aGridLayout->addWidget(lblExecuted,0,0);
    
    lblExecutedValue = new QLabel;
    lblExecutedValue->setText(QString::number(executedScriptNb));
    aGridLayout->addWidget(lblExecutedValue,0,1);
    
    aGridLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),0,2);
    
    lblCommandExecuted = new QLabel("Command executed (today): ");
    aGridLayout->addWidget(lblCommandExecuted,1,0);
    
    lblCommandExecutedValue = new QLabel;
    lblCommandExecutedValue->setText(QString::number(cmdExecutedScriptNb));
    aGridLayout->addWidget(lblCommandExecutedValue,1,1);
    
    aGridLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),1,2);
    
    errorToday = new QLabel("Error (today): ");
    aGridLayout->addWidget(errorToday,2,0);
    
    errorTodayValue = new QLabel;
    aGridLayout->addWidget(errorTodayValue,2,1);
    
    aGridLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),2,2);
    
  }
  
  void ExecutionMonitor::launchScript(QString name, QString content) {
    ScriptMonitor* aNewScriptMonitor = new ScriptMonitor(display, name );
    horizontalLayout_4->addWidget(aNewScriptMonitor);
    QObject::connect(aNewScriptMonitor, SIGNAL(newCommand()), this, SLOT(incrCommand()));
    aNewScriptMonitor->launchScript(content);
    lblExecutedValue->setText(QString::number(++executedScriptNb));
  }
  
  void ExecutionMonitor::incrCommand() {
    lblCommandExecutedValue->setText(QString::number(++cmdExecutedScriptNb));
  }
