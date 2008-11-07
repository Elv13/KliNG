#include <QSyntaxHighlighter>
#include <QStringList>


  class BashSyntaxHighlighter : public QSyntaxHighlighter {
    public:
      BashSyntaxHighlighter(QTextEdit* parent, QStringList commandList);
      void highlightBlock(const QString &text);
        
    private:
      struct HighlightingRule {
          QRegExp pattern;
          QTextCharFormat format;
      };
      QVector<HighlightingRule> highlightingRules;

      QRegExp commentStartExpression;
      QRegExp commentEndExpression;

      QTextCharFormat keywordFormat;
      QTextCharFormat commandKeyword;
      QTextCharFormat operatorKeyword;
      QTextCharFormat variables;
      QTextCharFormat path;
      QTextCharFormat optionsFormat;
      QTextCharFormat singleLineCommentFormat;
      QTextCharFormat multiLineCommentFormat;
      QTextCharFormat quotationFormat;
      QTextCharFormat functionFormat;
  };