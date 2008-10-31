/**     @file cronparser.cpp

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

        Layer between Kling and the crontab interface

        @author Emmanuel Lepage Vallée
        @date 14 May 2008
        @version 0.0.9
*/

#include "cronparser.h"

#include "interface/newCronJob.h"
#include <KLocalizedString>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Shell.h"

using namespace std;

/**
  CronParser constructor

  @param[in] parent The parent widget (nothing)
*/
  string CronParser::makeReadable(string command) {
    //This function is not completed, when it will be it will return a string lloking like "Every friday at 10:00, Everymonth, Everyday at 3, Jan 25 at 6:00 and other string like that. DO NOT delete that actual useless code.
    int minute, hours, month, dow, dom;
    int i=0;
    size_t iteration =0;
    QString minute_str, hours_str, month_str, dow_str, dom_str;
    char tmp[5][2];
    bool UseMinuteAlternative, UseHoursAlternative, UseMonthAlternative, UseDowAlternative, UseDomAlternative = {false};

    sscanf(command.c_str(),"%s %s %s %s %s",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4]);

    minute_str = tmp[0];
    minute_str=minute_str.left(2);
    hours_str = tmp[1];
    hours_str=hours_str.left(2);
    month_str = tmp[3];
    month_str=month_str.left(2);
    dow_str = tmp[4];
    dow_str=dow_str.left(2);
    dom_str = tmp[2];
    dom_str=dom_str.left(2);

    while (i < 5) {
      iteration = command.find(" ", iteration+1);
      i++;
    }
    command = command.substr(0, iteration);

    while (command.find("*") != -1) command = command.replace(command.find("*"), 1, "99");
    sscanf(command.c_str(),"%d %d %d %d %d",&minute,&hours,&dom,&month,&dow);


    QString dayOfTheWeek[7] = {i18n("Mon"), i18n("Tue"), i18n("Wed"), i18n("Thu"), i18n("Fri"), i18n("Sat"), i18n("Sun")};
    QString monthOfTheYears[12] = {i18n("Jan"), i18n("Feb"), i18n("Mar"), i18n("Apr"), i18n("May"), i18n("Jun"), i18n("Jul"), i18n("Aug"), i18n("Sep"), i18n("Oct"), i18n("Nov"), i18n("Dec")};

    if (minute_str == "*")
      minute_str.clear();

    if (hours_str == "*")
    {
      //hours_str = Every;
    }

    if (dom_str == "*")
      dom_str = i18n("Everyday");

    if (month_str != "*")
      month_str = monthOfTheYears[month-1];
    else
      month_str = i18n("Everymonth");

    if (dow_str != "*")
      dow_str = dayOfTheWeek[dow-1];
    else
      dow_str = "";

    QString output = month_str + " " + dom_str + " " + dow_str + i18n(" at ") + hours_str + ":" + minute_str;
    return output.toStdString();
  }

/**
  ThreadExec constructor

  @param[in] parent The parent widget (nothing)
  @return a semi parser string
  @todo check if it is still used
*/
  QString CronParser::display(char* parsedJob[3]) {
    QString month;

    if (strcmp(parsedJob[3], "1") ==0)
      month= i18n("Jan");
    else if (strcmp(parsedJob[3], "2") ==0)
      month= i18n("Feb");
    else if (strcmp(parsedJob[3], "3") ==0)
      month= i18n("Mar");
    else if (strcmp(parsedJob[3], "4") ==0)
      month= i18n("Apr");
    else if (strcmp(parsedJob[3], "5") ==0)
      month= i18n("May");
    else if (strcmp(parsedJob[3], "6") ==0)
      month= i18n("Jun");
    else if (strcmp(parsedJob[3], "7") ==0)
      month= i18n("Jul");
    else if (strcmp(parsedJob[3], "8") ==0)
      month= i18n("Aug");
    else if (strcmp(parsedJob[3], "9") ==0)
      month= i18n("Sep");
    else if (strcmp(parsedJob[3], "10") ==0)
      month= i18n("Oct");
    else if (strcmp(parsedJob[3], "11") ==0)
      month= i18n("Nov");
    else if (strcmp(parsedJob[3],"12") ==0)
      month= i18n("Dec");
    else
      month= i18n("*(all)");


    QString toReturn = parsedJob[0];
    toReturn += " ";
    toReturn += parsedJob[1];
    toReturn += " ";
    toReturn += parsedJob[2];
    toReturn += " ";
    toReturn += parsedJob[3];
    toReturn += " ";
    toReturn += parsedJob[4];
    toReturn += " ";
    toReturn += parsedJob[5];

    return toReturn;
  }

/**
    Read the user cron job
    @return a string vector that contian all jobs

*/
  vector<string> CronParser::parseUserJob() {
    char* parsedJob[6];
    vector<string> newCronFile;
    int currentLine =0;
    string tmp;
    int counter =0;
    int start =0;

    FILE *JOB = popen("crontab -l", "r" );
    char buffer[3000];
    if ( JOB != NULL ) {
      while ( fgets( buffer, sizeof buffer, JOB ) != NULL ) {
        string line = buffer;
        int i =0;
        int j =0;
        //sscanf(buffer,"%s %s %s %s %s %s %s",minute,hours,month,day,user,command); //Would be better, but fail in most case.
        if (buffer[0] != 0x23) {
          while (j < line.size()) {
            while (buffer[j] == 0x20) 
              j++;
            start = j;
            while (buffer[j] != 0x20) 
              j++;
            if (i ==5)
              while (buffer[j] != 0x00) 
                j++;

            parsedJob[i] = new char[j - start +1 ]; //FR pas delete, elles vont mourir avec l'application et c'est bien comme sa
            strcpy(parsedJob[i], line.substr(start, (j - start)).c_str());
            i++;
          }
        }

        if (buffer[0] != '#') {
            newCronFile.push_back(display(parsedJob).toStdString());
            currentLine++;
        }
      }
      pclose( JOB );
    }
    return newCronFile;
  }


/**
  Add a job to the user job file

  @param[in] parent GUI
*/
  void CronParser::addJob(NewCronJob* gui) {
    vector<string> newCronFile = parseUserJob();
    
    string aNewCronJob;
    string tmpStr;
    string month[12] = {"1","2","3","4","5","6","7","8","9","10","11","12" };
    string dow[7] = {"1","2","3","4","5","6","7"};

    if (gui->chkMinute->checkState() == Qt::Checked)
	aNewCronJob = gui->txtMinute->text().toStdString();
    else
      aNewCronJob = "*";
    
    aNewCronJob += " ";
    
    if (gui->chkHours->checkState()  == Qt::Checked) {
      tmpStr = gui->txtHours->text().toStdString();
      aNewCronJob +=tmpStr;
    }
    else
      aNewCronJob += "*";
    
    aNewCronJob += " ";
    
    if (gui->chkDom->checkState()  == Qt::Checked) {
	tmpStr = gui->txtDom->text().toStdString();
	aNewCronJob += tmpStr;
    }
    else
      aNewCronJob += "*";
    
    aNewCronJob += " ";
    
    if (gui->chkMonth->checkState() == Qt::Checked) {
      tmpStr = month[(gui->cbbMonth->currentIndex ())];
      aNewCronJob += tmpStr;
    }
    else
      aNewCronJob += "*";
    
    aNewCronJob += " ";
    
    if (gui->chkDow->checkState() == Qt::Checked) {
	tmpStr = dow[(gui->cbbDow->currentIndex ())];
	aNewCronJob += tmpStr;
    }
    else
      aNewCronJob += "*";
    
    aNewCronJob += " ";
    
    if (gui->rbScript->isChecked() == true) {
      string scriptPath = (Shell::getResult("echo $HOME").substr(0, Shell::getResult("echo $HOME").size()-1)) + "/.kling/script/" + gui->tblScript->item(gui->tblScript->currentRow(),0)->text().toStdString() + ".sh ";
      aNewCronJob += scriptPath;
    }
    else
      aNewCronJob += gui->txtCommand->text().toStdString();
    
    newCronFile.push_back(aNewCronJob);
    ofstream toWrite("/tmp/newCronFile.cron");
    for (int l =0; l < newCronFile.size(); l++) {
        toWrite << newCronFile[l].substr(0, newCronFile[l].size() -1)  << endl;
    }
    toWrite.close();
    system("crontab /tmp/newCronFile.cron");
    system("rm /tmp/newCronFile.cron");
  }


/**
  Remove date to keep only the command

  @return the job command
*/
  string CronParser::getCommand(string line) {
    size_t iteration =0;
    int i = 0;
    while (i < 5) {
      iteration = line.find(" ", iteration+1);
      i++;
    }
    return line.substr(iteration, line.size() - iteration);
  }
