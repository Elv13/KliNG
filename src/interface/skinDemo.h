#ifndef SKIN_DEMO
#define SKIN_DEMO
#include <QLabel>
#include <QString>

class SkinDemo : public QLabel {
  Q_OBJECT
  public:
    SkinDemo(QWidget* parent, QString background, QString textColor, int textSize, QString font, bool bold, QString pathColor, QString cmdColor);
};
#endif