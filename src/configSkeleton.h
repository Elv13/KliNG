#ifndef DEF_TERM2
#define DEF_TERM2

 #include <kconfigskeleton.h>

 class KlingConfigSkeleton : public KConfigSkeleton
 {
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

       setCurrentGroup("Monitor");
       addItemBool("enableMonitor", enableMonitor, true);
       addItemBool("showScriptBrowserMonitor", showScriptBrowserMonitor, true);
       addItemBool("showScheduledTaskMonitor", showScheduledTaskMonitor, true);
       addItemBool("showCommandListMonitor", showCommandListMonitor, false);
       addItemBool("showHistoryMonitor", showHistoryMonitor, false);
       addItemBool("showManPageMonitor", showManPageMonitor, false);
       addItemBool("showDebugMonitor", showDebugMonitor, false);

       setCurrentGroup("Editor");
       addItemBool("enableEditor", enableEditor, true);
       addItemBool("showScriptBrowserEditor", showScriptBrowserEditor, true);
       addItemBool("showScheduledTaskEditor", showScheduledTaskEditor, true);
       addItemBool("showCommandListEditor", showCommandListEditor, true);
       addItemBool("showHistoryEditor", showHistoryEditor, false);
       addItemBool("showManPageEditor", showManPageEditor, true);
       addItemBool("showDebugEditor", showDebugEditor, true);

       setCurrentGroup("WebBrowser");
       addItemBool("enableWebBrowser", enableWebBrowser, true);
       addItemBool("showScriptBrowserWebBrowser", showScriptBrowserWebBrowser, false);
       addItemBool("showScheduledTaskrWebBrowser", showScheduledTaskrWebBrowser, false);
       addItemBool("showCommandListrWebBrowser", showCommandListrWebBrowser, false);
       addItemBool("showHistoryrWebBrowser", showHistoryrWebBrowser, false);
       addItemBool("showManPagerWebBrowser", showManPagerWebBrowser, true);
       addItemBool("showDebugWebBrowser", showDebugWebBrowser, false);
       
       setCurrentGroup("Logginf");
       addItemInt("ammountToKeep", ammountToKeep,20);
       addItemInt("maxOutputSize", maxOutputSize,15);

       setCurrentGroup("Logginf");
       addItemInt("ammountToKeep", ammountToKeep,20);
       addItemInt("maxOutputSize", maxOutputSize,15);


     }

    bool isConfigured;
    bool enableTerminal;
    bool enableMonitor;
    bool enableEditor;
    bool enableWebBrowser;
    bool showScriptBrowserTerminal;
    bool showScheduledTaskTerminal;
    bool showCommandListTerminal;
    bool showHistoryTerminal;
    bool showManPageTerminal;
    bool enableUIDefault;
    bool fmShowHidden;
    bool enableCompleter;
    bool showScriptBrowserMonitor;
    bool showScheduledTaskMonitor;
    bool showCommandListMonitor;
    bool showHistoryMonitor;
    bool showManPageMonitor;
    bool showScriptBrowserEditor;
    bool showScheduledTaskEditor;
    bool showCommandListEditor;
    bool showHistoryEditor;
    bool showManPageEditor;
    bool showScriptBrowserWebBrowser;
    bool showScheduledTaskrWebBrowser;
    bool showCommandListrWebBrowser;
    bool showHistoryrWebBrowser;
    bool showManPagerWebBrowser;
    bool showDebugTerminal;
    bool showDebugMonitor;
    bool showDebugEditor;
    bool showDebugWebBrowser;
    int ammountToKeep;
    int maxOutputSize;
 };
#endif

