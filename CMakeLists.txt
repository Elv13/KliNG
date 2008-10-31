      project(kling)

      find_package(KDE4 REQUIRED)
      include_directories( ${KDE4_INCLUDES}${QT_INCLUDE_DIR}/QtWebKit )

      set(kling_SRCS
        main.cpp
        mainwindow.cpp
        src/interface/scriptBrowser.cpp
        src/interface/sheduledTask.cpp
        src/interface/history.cpp
        src/interface/debug.cpp
        src/interface/commandList.cpp
        src/interface/man.cpp
        src/interface/setup.cpp
        src/Shell.cpp
        src/manParser.cpp
        src/thread.cpp
        src/interface/sideBar.cpp
        src/cronparser.cpp
        src/interface/newCronJob.cpp
        src/interface/scriptMonitor.cpp
        src/interface/addScript.cpp
        src/interface/term.cpp
        src/interface/completer.cpp
        src/interface/fileBrowser.cpp
        src/interface/logView.cpp
        src/interface/config.cpp
        src/configSkeleton.h
        src/interface/outputViewer.cpp
        src/interface/debugTerm.cpp
        src/interface/scriptEditor.cpp
        src/interface/executionMonitor.cpp
        src/interface/advancedScriptManager.cpp
        src/interface/miniClasses.cpp
        src/interface/webBrowser.cpp
        src/interface/defaultScreen.cpp
      )

      kde4_add_executable(kling ${kling_SRCS})

      target_link_libraries(kling ${KDE4_KDEUI_LIBS}
      ${KDE4_KIO_LIBS} ${QT_QTSQL_LIBRARY} ${QT_WEBKIT_LIBRARY}${QT_LIBRARIES} QtWebKit)

      install(TARGETS kling DESTINATION ${BIN_INSTALL_DIR})
      install( FILES klingui.rc
		     pixmap/22x22/comment.png
                     kling.db
                     
      DESTINATION ${DATA_INSTALL_DIR}/kling )
      
            install( FILES 
                     pixmap/22x22/arrow.png
                     pixmap/22x22/arrowBP.png
                     pixmap/22x22/bp.png
                     pixmap/22x22/clock.png
                     pixmap/22x22/comment.png
                     pixmap/22x22/gearA.png
                     pixmap/22x22/gearI.png
                     pixmap/22x22/kill.png
                     pixmap/22x22/nextline.png
                     pixmap/22x22/run.png
                     pixmap/22x22/skipline.png
                     pixmap/22x22/uncomment.png
                     pixmap/22x22/pause.png
                     pixmap/22x22/eye.png
                     
      DESTINATION ${DATA_INSTALL_DIR}/kling/pixmap/22x22 )

            install( FILES 
                     pixmap/22x22/oxygen/arrow-right.png
                     pixmap/22x22/oxygen/document-print.png
                     pixmap/22x22/oxygen/document-save.png
                     pixmap/22x22/oxygen/edit-copy.png
                     pixmap/22x22/oxygen/edit-cut.png
                     pixmap/22x22/oxygen/edit-paste.png
                     pixmap/22x22/oxygen/edit-redo.png
                     pixmap/22x22/oxygen/edit-undo.png
                     pixmap/22x22/oxygen/go-next.png
                     pixmap/22x22/oxygen/go-previous.png
                     pixmap/22x22/oxygen/rating.png
                     pixmap/22x22/oxygen/view-refresh.png
                     pixmap/22x22/oxygen/window-close.png
                     pixmap/22x22/oxygen/window-new.png
                     pixmap/22x22/oxygen/window-suppressed.png
                     

                     
      DESTINATION ${DATA_INSTALL_DIR}/kling/outpt_dump )
      
        install( FILES 
                     pixmap/22x22/oxygen/arrow-right.png

                     
      DESTINATION ${DATA_INSTALL_DIR}/kling/outpt_dump )