/** 	@file main.cpp

This file is part of the Kling project
Copyright (C) 2008 Emmanuel Lepage Vallee <elv1313@gmail.com>

This software is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 or 3 of the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

  File used to check if kling is configured and create the 
  mainwindow
  @author Emmanuel Lepage Vallée
  @date 14 May 2008
  @version 0.0.9
*/


#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <QFile>
#include <KStandardDirs>
#include <KUrl>

#include "mainwindow.h"
//#include "src/Shell.h"
#include "src/interface/setup.h"
#include "src/configSkeleton.h"

  int main (int argc, char *argv[]) {
    KAboutData aboutData( "kling", "kling",
    ki18n("Kling"), "0.0.9",
    ki18n("A complete environemnt to develop, manage and execute Unix scripts"),
    KAboutData::License_GPL,
    ki18n("Copyright (c) 2008 Emmanuel Lepage Vallee") );
    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options; 
    options.add("+[file]", ki18n("Document to open")); 
    KCmdLineArgs::addCmdLineOptions(options); 
    KApplication app;
    KlingConfigSkeleton* klingConfigSkeleton = new  KlingConfigSkeleton();
    klingConfigSkeleton->readConfig();
    
    if (klingConfigSkeleton->isConfigured == false) {
      klingConfigSkeleton->isConfigured = true;
      klingConfigSkeleton->writeConfig();
      Setup* setup = new Setup();
      setup->show();
    }
    else {
      MainWindow* window = new MainWindow(0, klingConfigSkeleton);
      window->show();
    }

    /*KCmdLineArgs *args = KCmdLineArgs::parsedArgs(); //PASDEMOI
    if(args->count())
    {
    window->openFile(args->url(0).url()); 
    }*/
    return app.exec();
  }
