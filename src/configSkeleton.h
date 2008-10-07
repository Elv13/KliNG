#ifndef DEF_TERM2
#define DEF_TERM2

 #include <kconfigskeleton.h>
#include <QStringList>

  class KlingConfigSkeleton : public KConfigSkeleton {
      public:
        KlingConfigSkeleton() {
        setCurrentGroup("Terminal");
        addItemBool("isConfigured", isConfigured, false);
        
          setCurrentGroup("Terminal");
          addItemBool("enableTerminal", enableTerminal, true);
          addItemBool("showScriptBrowserTerminal", showScriptBrowserTerminal, true);
          addItemBool("showScheduledTaskTerminal", showScheduledTaskTerminal, true);
          addItemBool("showCommandListTerminal", showCommandListTerminal, true);
          addItemBool("showHistoryTerminal", showHistoryTerminal, true);
          addItemBool("showManPageTerminal", showManPageTerminal, true);
          addItemBool("showDebugTerminal", showDebugTerminal, true);
          addItemBool("enableUIDefault", enableUIDefault, true);
          addItemBool("fmShowHidden", fmShowHidden, true);
          addItemBool("enableCompleter", enableCompleter, true);
          addItemInt("scriptBrowserHeightTerminal", scriptBrowserHeightTerminal, -1);
          addItemInt("scheduledTaskHeightTerminal", scheduledTaskHeightTerminal, -1);
          addItemInt("commandListTHeighterminal", commandListTHeighterminal, -1);
          addItemInt("historyHeightTerminal", historyHeightTerminal, -1);
          addItemInt("manPageHeightTerminal", manPageHeightTerminal, -1);
          addItemInt("debugHeightTerminal", debugHeightTerminal, -1);

          setCurrentGroup("Monitor");
          addItemBool("enableMonitor", enableMonitor, true);
          addItemBool("showScriptBrowserMonitor", showScriptBrowserMonitor, true);
          addItemBool("showScheduledTaskMonitor", showScheduledTaskMonitor, true);
          addItemBool("showCommandListMonitor", showCommandListMonitor, false);
          addItemBool("showHistoryMonitor", showHistoryMonitor, false);
          addItemBool("showManPageMonitor", showManPageMonitor, false);
          addItemBool("showDebugMonitor", showDebugMonitor, false);
          addItemInt("scriptBrowserHeightMonitor", scriptBrowserHeightMonitor, -1);
          addItemInt("scheduledTaskHeightMonitor", scheduledTaskHeightMonitor, -1);
          addItemInt("commandListHeightMonitor", commandListHeightMonitor, -1);
          addItemInt("historyHeightMonitor", historyHeightMonitor, -1);
          addItemInt("manPageHeightMonitor", manPageHeightMonitor, -1);
          addItemInt("debugHeightMonitor", debugHeightMonitor, -1);

          setCurrentGroup("Editor");
          addItemBool("enableEditor", enableEditor, true);
          addItemBool("showScriptBrowserEditor", showScriptBrowserEditor, true);
          addItemBool("showScheduledTaskEditor", showScheduledTaskEditor, true);
          addItemBool("showCommandListEditor", showCommandListEditor, true);
          addItemBool("showHistoryEditor", showHistoryEditor, false);
          addItemBool("showManPageEditor", showManPageEditor, true);
          addItemBool("showDebugEditor", showDebugEditor, true);
          addItemInt("scriptBrowserHeightEditor", scriptBrowserHeightEditor, -1);
          addItemInt("scheduledTaskHeightEditor", scheduledTaskHeightEditor, -1);
          addItemInt("commandListHeightEditor", commandListHeightEditor, -1);
          addItemInt("historyHeightEditor", historyHeightEditor, -1);
          addItemInt("manPageHeightEditor", manPageHeightEditor, -1);
          addItemInt("debugHeightEditor", debugHeightEditor, -1);

          setCurrentGroup("WebBrowser");
          addItemBool("enableWebBrowser", enableWebBrowser, true);
          addItemBool("showScriptBrowserWebBrowser", showScriptBrowserWebBrowser, false);
          addItemBool("showScheduledTaskrWebBrowser", showScheduledTaskrWebBrowser, false);
          addItemBool("showCommandListrWebBrowser", showCommandListrWebBrowser, false);
          addItemBool("showHistoryrWebBrowser", showHistoryrWebBrowser, false);
          addItemBool("showManPagerWebBrowser", showManPagerWebBrowser, true);
          addItemBool("showDebugWebBrowser", showDebugWebBrowser, false);
          addItemInt("scriptBrowserHeightWebBrowser", scriptBrowserHeightWebBrowser, -1);
          addItemInt("scheduledTaskHeightWebBrowser", scheduledTaskHeightWebBrowser, -1);
          addItemInt("commandListHeightWebBrowser", commandListHeightWebBrowser, -1);
          addItemInt("historyHeightWebBrowser", historyHeightWebBrowser, -1);
          addItemInt("manPageHeightWebBrowser", manPageHeightWebBrowser, -1);
          addItemInt("debugHeightWebBrowser", debugHeightWebBrowser, -1);
          
          setCurrentGroup("Logginf");
          addItemInt("ammountToKeep", ammountToKeep,20);
          addItemInt("maxOutputSize", maxOutputSize,15);

          setCurrentGroup("Logginf");
          addItemBool("showDebugWebBrowser", showDebugWebBrowser, false);
          
          setCurrentGroup("Logging");
          addItemInt("ammountToKeep", ammountToKeep,20);
          addItemInt("maxOutputSize", maxOutputSize,15);
          addItemBool("keepOutput", keepOutput,true);
          addItemBool("appendToBashHistory", appendToBashHistory, true);
          addItemStringList("logExcludeList", logExcludeList, QStringList() << "ls" << "dir" << "cd" << "pwd");
          addItemStringList("fileToWatch", fileToWatch, QStringList() << "/var/log/messages");
      }

      bool isConfigured;
      bool enableTerminal;
      bool enableMonitor;
      bool enableEditor;
      bool enableWebBrowser;
      
      //Terminal
      bool showScriptBrowserTerminal;
      bool showScheduledTaskTerminal;
      bool showCommandListTerminal;
      bool showHistoryTerminal;
      bool showManPageTerminal;
      bool showDebugTerminal;
      int scriptBrowserHeightTerminal;
      int scheduledTaskHeightTerminal;
      int commandListTHeighterminal;
      int historyHeightTerminal;
      int manPageHeightTerminal;
      int debugHeightTerminal;
      
      bool enableUIDefault;
      bool fmShowHidden;
      bool enableCompleter;
      
      //Monitor
      bool showScriptBrowserMonitor;
      bool showScheduledTaskMonitor;
      bool showCommandListMonitor;
      bool showHistoryMonitor;
      bool showManPageMonitor;
      bool showDebugMonitor;
      int scriptBrowserHeightMonitor;
      int scheduledTaskHeightMonitor;
      int commandListHeightMonitor;
      int historyHeightMonitor;
      int manPageHeightMonitor;
      int debugHeightMonitor;
      
      //Editor
      bool showScriptBrowserEditor;
      bool showScheduledTaskEditor;
      bool showCommandListEditor;
      bool showHistoryEditor;
      bool showManPageEditor;
      bool showDebugEditor;
      int scriptBrowserHeightEditor;
      int scheduledTaskHeightEditor;
      int commandListHeightEditor;
      int historyHeightEditor;
      int manPageHeightEditor;
      int debugHeightEditor;
      
      //Webbrowser
      bool showScriptBrowserWebBrowser;
      bool showScheduledTaskrWebBrowser;
      bool showCommandListrWebBrowser;
      bool showHistoryrWebBrowser;
      bool showManPagerWebBrowser;
      bool showDebugWebBrowser;
      int scriptBrowserHeightWebBrowser;
      int scheduledTaskHeightWebBrowser;
      int commandListHeightWebBrowser;
      int historyHeightWebBrowser;
      int manPageHeightWebBrowser;
      int debugHeightWebBrowser;
      
      //Logging
      int ammountToKeep;
      int maxOutputSize;
      QStringList logExcludeList;
      QStringList fileToWatch;
      bool keepOutput;
      bool appendToBashHistory;
  };
#endif

