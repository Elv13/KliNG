/**     @file thread.cpp

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
	___________________

        Heritage from QThread implementing multitask to Kling

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "thread.h"

#include <iostream>
#include <cstdlib>
#include <QString>
#include "Shell.h"

using namespace std;

/**
  ThreadExec constructor

  @param[in] parent The parent widget (nothing)
*/
  ThreadExec::ThreadExec(QObject* parent, std::string aScript) : QThread(parent) {
    script = aScript;
  }

/**
  Virtual function executed on creation of the thread

  @param[in] parent The parent widget (nothing)
*/
  void ThreadExec::run() {
    int pos0A =0;
    int posLast0A=-1;
    int i = 0;
    int advencement;

    for (int j = 0; j <= script.size(); j++) //Count the script line
          if ((script[j] == 0x0A) && (script[j+1] != 0x0A)) 
            i++;
            
    if (script[script.size()-1] != 0x0A)
      i++;
      
    advencement = 100 / i;
    i=0;

    while (pos0A < script.size()) {
      while ((script[pos0A] != 0x0A) && (pos0A < script.size())) pos0A++;
      int pos0Aclone = pos0A+1;
      while ((script[pos0Aclone] != 0x0A) && (pos0Aclone < script.size())) pos0Aclone++;
      emit currentLine(QString::fromStdString(script.substr(posLast0A+1, (pos0A-posLast0A-1))));
      emit nextLine(QString::fromStdString(script.substr(pos0A+1, (pos0Aclone-pos0A-1))));
      system(script.substr(posLast0A+1, (pos0A-posLast0A-1)).c_str());
      i += advencement;
      emit progress(i);
      posLast0A=pos0A;
      pos0A++;
    }
    emit isOver();
  }
