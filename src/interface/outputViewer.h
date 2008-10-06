#include <KDialog>
#include <KTextBrowser>

  class OutputViewer : public KDialog {
    Q_OBJECT
    
    public:
      OutputViewer(QWidget* parent, uint id);
      
    private:
      KTextBrowser* centralTextBrowser;
      uint id;
      
    private slots:
      void setKeep(bool value);
  };
  