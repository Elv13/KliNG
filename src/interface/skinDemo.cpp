#include "skinDemo.h"
#include <QColor>
#include <QBrush>
#include <QPalette>

SkinDemo::SkinDemo(QWidget* parent, QString background, QString textColor, int textSize, QString font, bool bold, QString pathColor, QString cmdColor) : QLabel(parent) {
  QString strBold;
  strBold = bold?";font-weight:bold":"";
  
  QPalette aPalette;
  this->setStyleSheet("background-color:"+background+";color:"+textColor+";font-size:"+QString::number(textSize)+";font-family"+font+";border-radius:5px;border-color:"+aPalette.light().color().name()+";border-width:3px;border-style:solid"+strBold);
  setText("<b><font color=\""+pathColor+"\">path</font> <font color=\""+cmdColor+"\">(cmd):</font></b> text");
}