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

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9
*/

#include "cronparser.h"

#include "interface/newCronJob.h"
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
    string minute_str, hours_str, month_str, dow_str, dom_str;
    char tmp[5][2];
    bool UseMinuteAlternative, UseHoursAlternative, UseMonthAlternative, UseDowAlternative, UseDomAlternative = {false};

    sscanf(command.c_str(),"%s %s %s %s %s",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4]);

    minute_str = tmp[0];
    minute_str=minute_str.substr(0,2);
    hours_str = tmp[1];
    hours_str=hours_str.substr(0,2);
    month_str = tmp[3];
    month_str=month_str.substr(0,2);
    dow_str = tmp[4];
    dow_str=dow_str.substr(0,2);
    dom_str = tmp[2];
    dom_str=dom_str.substr(0,2);

    cout << minute_str<<"hours: "<<hours_str<<"DOM:"<<dom_str <<endl;
    while (i < 5) {
      iteration = command.find(" ", iteration+1);
      i++;
    }
    command = command.substr(0, iteration);
    cout << command << endl;

    while (command.find("*") != -1) command = command.replace(command.find("*"), 1, "99");
    sscanf(command.c_str(),"%d %d %d %d %d",&minute,&hours,&dom,&month,&dow);


    string dayOfTheWeek[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    string monthOfTheYears[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (minute_str == "*")
      minute_str.clear();

    if (hours_str == "*")
    {
      //hours_str = Every;
    }

    if (dom_str == "*")
      dom_str = "Everyday";

    if (month_str != "*")
      month_str = monthOfTheYears[month-1];
    else
      month_str = "Everymonth";

    if (dow_str != "*")
      dow_str = dayOfTheWeek[dow-1];
    else
      dow_str = "";

    string output = month_str + " " + dom_str + " " + dow_str + " at " + hours_str + ":" + minute_str;
    cout << "THIS IS THE OUTPUT: " << output << endl;
    return output;
  }

/**
  ThreadExec constructor

  @param[in] parent The parent widget (nothing)
  @return a semi parser string
  @todo check if it is still used
*/
  string CronParser::display(char* parsedJob[3]) {
    string month;

    if (strcmp(parsedJob[3], "1") ==0)
      month= "Jan";
    else if (strcmp(parsedJob[3], "2") ==0)
      month= "Feb";
    else if (strcmp(parsedJob[3], "3") ==0)
      month= "Mar";
    else if (strcmp(parsedJob[3], "4") ==0)
      month= "Apr";
    else if (strcmp(parsedJob[3], "5") ==0)
      month= "May";
    else if (strcmp(parsedJob[3], "6") ==0)
      month= "Jun";
    else if (strcmp(parsedJob[3], "7") ==0)
      month= "Jul";
    else if (strcmp(parsedJob[3], "8") ==0)
      month= "Aug";
    else if (strcmp(parsedJob[3], "9") ==0)
      month= "Sep";
    else if (strcmp(parsedJob[3], "10") ==0)
      month= "Oct";
    else if (strcmp(parsedJob[3], "11") ==0)
      month= "Nov";
    else if (strcmp(parsedJob[3],"12") ==0)
      month= "Dec";
    else
      month= "*(all)";

    cout << month << " " << parsedJob[2] << ", " << parsedJob[1] << ":" << parsedJob[0] << "    Command --> " << parsedJob[5];

    string toReturn = parsedJob[0];
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
            newCronFile.push_back(display(parsedJob));
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
    
    cout << "Job:  "<< aNewCronJob ;
    newCronFile.push_back(aNewCronJob);
    ofstream toWrite("/tmp/newCronFile.cron");
    for (int l =0; l < newCronFile.size(); l++) {
        toWrite << newCronFile[l].substr(0, newCronFile[l].size() -1)  << endl;
        cout << newCronFile[l].substr(0, newCronFile[l].size() -1) << endl;
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
