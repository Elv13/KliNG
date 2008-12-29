/** Here goes all little class that have no real code and are here only to make things work better**/
#ifndef DEF_MINICLASSES
#define DEF_MINICLASSES
#include <KPushButton>
#include <QCheckBox>
#include <QListWidgetItem>
#include "../session.h"

  class OutputViewerButton : public KPushButton {
    Q_OBJECT
    public:
      OutputViewerButton(QWidget* parent);
      uint id;
  
    private slots:
      void launched();
      
    signals:
      void clicked(uint);
  };
  
  class PlayButton : public KPushButton {
    Q_OBJECT
    public:
      PlayButton(QWidget* parent);
      uint id;
  
    private slots:
      void launched();
      
    signals:
      void clicked(uint);
  };
  
  class EditButton : public KPushButton {
    Q_OBJECT
    public:
      EditButton(QWidget* parent);
      uint id;
  
    private slots:
      void launched();
      
    signals:
      void clicked(uint);
  };
  
  class RemoveButton : public KPushButton {
    Q_OBJECT
    public:
      RemoveButton(QWidget* parent);
      int id;
  
    private slots:
      void launched();
      
    signals:
      void clicked(int);
  };
  
  class AliasCheckBox : public QCheckBox {
    Q_OBJECT
    public:
      AliasCheckBox(QWidget* parent);
      int id;
  
    private slots:
      void launched();
      
    signals:
      void clicked(int);
  };

  class SessionListItem : public QListWidgetItem {
    //Q_OBJECT
    public:
      SessionListItem();
      Session* aSession;
  };
#endif