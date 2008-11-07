/** Here goes all little class that have no real code and are here only to make things work better**/
#include "miniClasses.h"
#include <KIcon>


  OutputViewerButton::OutputViewerButton(QWidget* parent =0) : KPushButton( parent ) {
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(launched()));
  }
      
  void OutputViewerButton::launched() {
    emit clicked(id); 
  }
    
    
  PlayButton::PlayButton(QWidget* parent =0) : KPushButton( parent ) {
    setIcon(KIcon("arrow-right"));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(launched()));
  }
      
  void PlayButton::launched() {
    emit clicked(id); 
  }
  
  EditButton::EditButton(QWidget* parent =0) : KPushButton( parent ) {
    setIcon(KIcon("draw-freehand"));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(launched()));
  }
      
  void EditButton::launched() {
    emit clicked(id); 
  }
  
  RemoveButton::RemoveButton(QWidget* parent =0) : KPushButton( parent ) {
    setIcon(KIcon("list-remove"));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(launched()));
  }
      
  void RemoveButton::launched() {
    emit clicked(id); 
  }