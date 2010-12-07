#ifndef SESSION_LOADER
#define SESSION_LOADER
#include <KDialog>
#include <QListWidget>
#include "termSession.h"

class SessionLoader : public KDialog {
  Q_OBJECT
  public:
    SessionLoader(QWidget* parent, TermSession* aTermSession);
  private:
    QListWidget* lstSession;
    TermSession* aTermSession;
  private slots:
    void loadSession();
};
#endif