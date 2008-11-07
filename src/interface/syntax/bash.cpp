#include "bash.h"
#include <QColor>

  BashSyntaxHighlighter::BashSyntaxHighlighter(QTextEdit* parent, QStringList commandList) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    
    //keywordFormat.setFontWeight(QFont::Bold);
    
    commandKeyword.setForeground(QColor("#A25100"));
    foreach (QString pattern, commandList) {
        rule.pattern = QRegExp(pattern + "\\ ");
        rule.format = commandKeyword;
        highlightingRules.append(rule);
    }
    
    keywordFormat.setForeground(Qt::darkRed);
    QStringList keywordPatterns;
    keywordPatterns << "if " << "then" << "elif " << "else" << "fi" << "while " << "do" << "done" << "until " << "for " << "\\&" << "\\|" << "\\ \\+\\ " << "\\\\" << "\\ /\\ " << "\\ \\*\\ " << "\\ \\-\\ " << ":" << ";" << "<" << ">" << "\\[" << "\\]" << "\\$\\[" << "\\{" << "\\}" << "\\$\\{" << "!" << "=";
    foreach (QString pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    
    variables.setForeground(QColor("#0D370F"));
    rule.pattern = QRegExp("[a-zA-Z][a-zA-Z0-9]*=");
    rule.format = variables;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\$[a-zA-Z][a-zA-Z0-9]*");
    rule.format = variables;
    highlightingRules.append(rule);
    
    path.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("/[A-Za-z0-9.\\-_/]*\\ ");
    rule.format = path;
    highlightingRules.append(rule);
    
    optionsFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\ \\-[a-zA-Z0-9]*\\ ");
    rule.format = optionsFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\ \\-\\-[a-zA-Z0-9]*\\ ");
    rule.format = optionsFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::gray);
    singleLineCommentFormat.setFontItalic(true);
    rule.pattern = QRegExp("#[a-zA-Z0-9,.\\;\\:\\-_\\ ]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
  }
  
  void BashSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (HighlightingRule rule, highlightingRules) {
      QRegExp expression(rule.pattern);
      int index = text.indexOf(expression);
      while (index >= 0) {
          int length = expression.matchedLength();
          setFormat(index, length, rule.format);
          index = text.indexOf(expression, index + length);
      }
    }

    setCurrentBlockState(0);
  }
