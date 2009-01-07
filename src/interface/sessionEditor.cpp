#include "sessionEditor.h"
#include <QSizePolicy>
#include <QVector>
#include <QInputDialog>


  SessionEditor::SessionEditor(QWidget* parent, Session* aSession) : KDialog(parent) {
    currentItem = NULL;
    setCaption( "Add new job" );
    setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Apply);
    
    QSizePolicy sizePolicy1(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QSizePolicy sizePolicy2(QSizePolicy::Expanding,QSizePolicy::Minimum);
   
    this->aSession = aSession;
    
    QWidget* centralWidget = new QWidget();
    setMainWidget(centralWidget);
    centralWidget->setGeometry(QRect(206, 24, 550, 450));
    
    QGridLayout* gridSession = new QGridLayout();
    centralWidget->setLayout(gridSession);
    
    lstSessionList = new QListWidget();
    //lstSessionList->setSizePolicy(sizePolicy1);
    gridSession->addWidget(lstSessionList,0,0,2,2);
    
    grbSshField = new QGroupBox();
    grbSshField->setSizePolicy(sizePolicy1);
    grbSshField->setTitle("SSH options");
    grbSshField->setHidden(true);
    gridSession->addWidget(grbSshField,5,0,1,3);
    
    QGridLayout* gridSsh = new QGridLayout();
    grbSshField->setLayout(gridSsh);
    
    lblIcon = new QLabel();
    lblIcon->setSizePolicy(sizePolicy1);
    lblIcon->setText("Icon:");
    gridSession->addWidget(lblIcon,2,0,1,1);
    
    lblName = new QLabel();
    lblName->setSizePolicy(sizePolicy1);
    lblName->setText("Name:");
    gridSession->addWidget(lblName,3,0,1,1);
    
    lblType = new QLabel();
    lblType->setSizePolicy(sizePolicy1);
    lblType->setText("Type:");
    gridSession->addWidget(lblType,4,0,1,1);
    
    lblConnectionMethod = new QLabel();
    lblConnectionMethod->setText("Method:");
    gridSsh->addWidget(lblConnectionMethod,5,0,1,1);
    
    lblInputMethod = new QLabel("Input method:");
    lblInputMethod->setSizePolicy(sizePolicy1);
    gridSession->addWidget(lblInputMethod,6,0,1,1);
    
    lblPublicKey = new QLabel();
    lblPublicKey->setText("Public key:");
    gridSsh->addWidget(lblPublicKey,2,0,1,1);
    
    lblUsername = new QLabel();
    lblUsername->setText("Username:");
    gridSsh->addWidget(lblUsername,0,0,1,1);
    
    lblPassword = new QLabel();
    lblPassword->setText("Password:");
    gridSsh->addWidget(lblPassword,1,0,1,1);
    
    lblDefaultPath = new QLabel();
    lblDefaultPath->setSizePolicy(sizePolicy1);
    lblDefaultPath->setText("Default path:");
    gridSession->addWidget(lblDefaultPath,7,0,1,1);
    
    lblDefaultCommand = new QLabel("Default command");
    lblDefaultCommand->setSizePolicy(sizePolicy1);
    gridSession->addWidget(lblDefaultCommand,8,0,1,1);
    
    
    btnAddSession = new QPushButton();
    btnAddSession->setText("Add");
    gridSession->addWidget(btnAddSession,0,2,1,1);
    
    btnRemSession = new QPushButton();
    btnRemSession->setText("Remove");
    gridSession->addWidget(btnRemSession,1,2,1,1);
    
    QWidget* wdgIcon = new QWidget();
    QGridLayout* aLayout = new QGridLayout(wdgIcon);
    aLayout->setContentsMargins(0,0,0,0);
    btnIcon = new QPushButton();
    btnIcon->setSizePolicy(sizePolicy2);
    btnIcon->setMinimumSize(30,30);
    btnIcon->setMaximumSize(30,30);
    aLayout->addWidget(btnIcon,0,0);
    aLayout->addItem(new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum),0,1);
    btnIcon->setDisabled(true);
    gridSession->addWidget(wdgIcon,2,1,1,1);
    
    txtSessionName = new QLineEdit();
    txtSessionName->setSizePolicy(sizePolicy2);
    txtSessionName->setDisabled(true);
    gridSession->addWidget(txtSessionName,3,1,1,2);
    
    cbbSessionType = new QComboBox();
    cbbSessionType->setSizePolicy(sizePolicy2);
    cbbSessionType->addItem("Local");
    cbbSessionType->addItem("SSHv1");
    cbbSessionType->addItem("SSHv2");
    cbbSessionType->addItem("Telnet");
    cbbSessionType->setDisabled(true);
    gridSession->addWidget(cbbSessionType,4,1,1,2);
    
    inputMethod = new QComboBox();
    inputMethod->addItem("Standard");
    inputMethod->addItem("Python");
    inputMethod->addItem("Pash");
    inputMethod->addItem("Bash");
    inputMethod->setSizePolicy(sizePolicy2);
    inputMethod->setDisabled(true);
    gridSession->addWidget(inputMethod,6,1,1,2);
    
    cbbConnectionMethod = new QComboBox();
    cbbConnectionMethod->setSizePolicy(sizePolicy2);
    gridSsh->addWidget(cbbConnectionMethod,5,1,1,2);
    
    txtPublicKey = new QLineEdit();
    txtPublicKey->setSizePolicy(sizePolicy2);
    gridSsh->addWidget(txtPublicKey,2,1,1,1);
    
    txtUsername = new QLineEdit();
    txtUsername->setSizePolicy(sizePolicy2);
    gridSsh->addWidget(txtUsername,0,1,1,1);
    
    txtPassword = new QLineEdit();
    txtPassword->setSizePolicy(sizePolicy2);
    gridSsh->addWidget(txtPassword,1,1,1,1);
    
    txtDefaultPath = new QLineEdit();
    txtDefaultPath->setSizePolicy(sizePolicy2);
    txtDefaultPath->setDisabled(true);
    gridSession->addWidget(txtDefaultPath,7,1,1,2);
    
    txtDefaultCommand = new QLineEdit();
    txtDefaultCommand->setSizePolicy(sizePolicy2);
    txtDefaultCommand->setDisabled(true);
    gridSession->addWidget(txtDefaultCommand,8,1,1,2);
    
    /*txtDefaultPath = new QLineEdit();
    txtDefaultPath->setSizePolicy(sizePolicy2);*/
    gridSession->addItem(new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Expanding),9,1,1,2);
    
    QObject::connect(lstSessionList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*, QListWidgetItem*)));
    connect( this, SIGNAL( okClicked() ), this, SLOT( apply() ) );
    connect( btnAddSession, SIGNAL( clicked() ), this, SLOT( addItem() ) );
    connect( txtSessionName, SIGNAL( textChanged(QString) ), this, SLOT( updateCurrentName(QString) ) );
    
    if (aSession != 0) {
      itemList = aSession->getItem();
      if (itemList.count() != 0) {
	for (int i =0; i < itemList.count(); i++) {
	  lstSessionList->addItem(itemList[i].name);
	}
      }
      itemList = aSession->getItem();
    }
    
    if (lstSessionList->count() != 0) {
      lstSessionList->setCurrentRow(0);
    }
  }
  
  void SessionEditor::itemChanged(QListWidgetItem* item1, QListWidgetItem* item2) {
    btnIcon->setEnabled(true);
    txtSessionName->setEnabled(true); 
    cbbSessionType->setEnabled(true); 
    inputMethod->setEnabled(true); 
    txtDefaultPath->setEnabled(true); 
    txtDefaultCommand->setEnabled(true);
    
    if (currentItem != NULL ) {
      //currentListItem->setText(currentItem->name);
      currentItem->name = txtSessionName->text();
      currentItem->path = txtDefaultPath->text();
      currentItem->command = txtDefaultCommand->text();
      currentItem->type = cbbSessionType->currentIndex();
      currentItem->input = inputMethod->currentIndex();
    }
    //currentListItem = lstSessionList->currentItem();
    sessionItem* aSessionItem = NULL;
    
    if (itemList.count() != 0) {
      for (int i =0; i < itemList.count(); i++) {
	if (itemList[i].name == lstSessionList->currentItem()->text())
	  aSessionItem = &(itemList[i]);
      }
    }
    
    if (aSessionItem != NULL ) {
      txtSessionName->setText(aSessionItem->name);
      txtDefaultPath->setText(aSessionItem->path);
      txtDefaultCommand->setText(aSessionItem->command);
      cbbSessionType->setCurrentIndex(aSessionItem->type);
      inputMethod->setCurrentIndex(aSessionItem->input);
      currentItem = aSessionItem;
    }
    else
      currentItem = NULL;

  }
  
  void SessionEditor::apply() {
    if (currentItem != NULL ) {
      //currentListItem->setText(currentItem->name);
      currentItem->name = txtSessionName->text();
      currentItem->path = txtDefaultPath->text();
      currentItem->command = txtDefaultCommand->text();
      currentItem->type = cbbSessionType->currentIndex();
      currentItem->input = inputMethod->currentIndex();
    }
    aSession->setItem(this->itemList);
  }
  
  void SessionEditor::updateCurrentName(QString text) {
    lstSessionList->currentItem()->setText(text);
  }
  
  void SessionEditor::addItem() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add a tab", "Add a new tab to this session", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      itemChanged(0, 0);
      lstSessionList->addItem(text);
      sessionItem* aSessionItem2 = new sessionItem;
      aSessionItem2->name = text;
      itemList.push_back(*aSessionItem2);
      currentItem = aSessionItem2;
    }
  }