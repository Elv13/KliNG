/**     @file manParser.cpp

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

        Index, download, read, parse and extract informations from manpage

        @author Emmanuel Lepage Vall�e
        @date 14 May 2008
        @version 0.0.9
*/
#define CHUNK 16384

#include "manParser.h"

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <stack>
#include <string>
#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace std;

/**
  ManParser constructor

  @param[in] parent The parent widget (nothing)
*/
  string ManParser::parseLine(string line) {
    char ifBOpen = false;
    char ifIOpen = false;
    char ifUOpen = false;
    char ifFontOpen = false;
    char ifSpecialLine = false;
    stack<string> tagStack;

    if (line.substr(0,2) == ".\\") 
      line = "";

    while (line.find(".BI") != -1) {
        line.replace(line.find(".BI"), 3, "<b><i>");
        ifBOpen =true;
        ifIOpen = true;
        ifSpecialLine == true;
    }
    
    while (line.find(".RS") != -1)
      line.replace(line.find(".RS"), 3, ".............");
      
    while (line.find(".I") != -1) {
        line.replace(line.find(".I"), 2, "<u><i>");
        ifUOpen = true;
        ifIOpen = true;
        ifSpecialLine == true;
    }
    
    while (line.find(".br") != -1) {
        line.replace(line.find(".br"), 3, "<b><font type=roman>");
        ifBOpen = true;
        ifFontOpen = true;
        ifSpecialLine == true;
    }
    
    while (line.find(".B") != -1) {
        line.replace(line.find(".B"), 2, "<b>");
        ifBOpen = true;
        ifSpecialLine == true;
    }
    
    while (line.find(".IR") != -1) {
        line.replace(line.find(".IR"), 3, "<i><font type=roman>");
        ifIOpen = true;
        ifFontOpen = true;
        ifSpecialLine == true;
    }

    if (ifBOpen == true) {
        line += "</b>";
        ifBOpen = false;
    }
    
    if (ifIOpen == true) {
         line += "</i>";
         ifIOpen = false;
    }
    
    if (ifUOpen == true) {
         line += "</u>";
         ifUOpen = false;
    }
    
    if (ifFontOpen == true) {
         line += "</font>";
         ifFontOpen = false;
    }
    
    if (ifSpecialLine == true) {
         line += "</br>";
         ifSpecialLine = false;
    }

    int j = 0;
    while (j != line.size()) {
      if ((line[j] == 0x5C) && (line[j+1] == 0x2D))
	line = line.replace(j,1, "");
      else
        j++;
    }

    while (line.find("\\fB") != -1) {
      line.replace(line.find("\\"), 3, "<b>");
      tagStack.push("</b>");
      ifBOpen++;
     }
     
     while (line.find("\\fI") != -1) {
      line.replace(line.find("\\"), 3, "<i>");
      tagStack.push("</i>");
      ifIOpen++;
     }
     
     while (line.find("\\fR") != -1) {
      line.replace(line.find("\\"), 3, "<font type=roman>");
      tagStack.push("</font>");
      ifFontOpen++;
     }
     
     while ((line.find("\\fP") != -1) && (tagStack.size() > 0)) {
        //Dirty hack to ensure that even if the manpage is not corect, it will not cause the rest to be damaged
      if(tagStack.top() == "</b>") ifBOpen--;
      else if(tagStack.top() == "</i>") ifIOpen--;
      else if(tagStack.top() == "</font>") ifFontOpen--;
      line.replace(line.find("\\"), 3, tagStack.top());
      tagStack.pop();
     }

     while(ifBOpen > 0) {
        line += "</b>";
        ifBOpen--;
     }
     
     while(ifIOpen > 0) {
        line += "</i>";
        ifIOpen--;
     }
     
     while(ifFontOpen > 0) {
        line += "</font>";
        ifFontOpen--;
     }

     return line;
  }

  string ManParser::parseManPage(string name) {
    string line;
    string path = "/tmp/man/" + name;
    ifstream toRead(path.c_str());
    string anOption;
    string optionName;

    string manPage;
    bool inContent = false;
    bool ifInDescription = false;
    bool ifInOptions = false;
    bool ifInUsage = false;
    bool ifLastLineIsATP = false;
    bool isFLOfOption = true;
    manPage = "<body style=\"background-color:#ADBE14;\"";

    while (! toRead.eof() ) {
      getline (toRead,line);
      if (line.find(".SH") != -1) {
          if (line.find("NAME") != -1) inContent = true;
            ifLastLineIsATP = false;

          if (line.size() > 5) 
            if ( inContent)
              manPage += "<br><br><h2>" +  line.replace(0, (line.find(".SH") +3), "") + "</h2>";

          if ((line.find("Description") != -1) || (line.find("description") != -1) || (line.find("DESCRIPTION") != -1)) {
            ifInDescription =  true;
            ifInOptions = false;
            ifInUsage = false;
          }
          
          else if (((line.find("Usage") != -1) || (line.find("usage") != -1) || (line.find("USAGE") != -1)) || ((line.find("Examples") != -1) || (line.find("examples") != -1) || (line.find("EXAMPLES") != -1))) {
            ifInDescription =  false;
            ifInOptions = false;
            ifInUsage = true;
          }
          else if ((line.find("Options") != -1) || (line.find("options") != -1) || (line.find("OPTIONS") != -1)) {
            ifInDescription =  false;
            ifInOptions = true;
            ifInUsage = false;
          }
          else {
            ifInDescription =  false;
            ifInOptions = false;
            ifInUsage = false;
          }
      }
      else if (line == ".TP") {
        ifLastLineIsATP = true;
        manPage +=  "<br><br>";

        if ( ((ifInDescription == true) || ( ifInOptions == true) || ( ifInUsage == true)) && (anOption != "")) {
          //TODO code for adding options/usage/description in db
          /*if (ifInDescription == true)
          {
            QSqlQuery query;
            QString aQuery = manPage.c_str();
            query.exec("insert into TMAN_PAGE (CONTENT) values ('" + aQuery + "')");
          }*/
          if (ifInOptions == true) {
            QSqlQuery query;
            QString manPName = name.substr(0, name.find_last_of(".")).c_str();
            QString aCommandOption = anOption.c_str();
            QString anOptionName = optionName.c_str();
            QString aQuery = "insert into TOPTION (COMMAND,OPT_DES,OPT_NAME) values ('" + manPName;
            aQuery += "','" + aCommandOption;
            aQuery += "','" +anOptionName;
            
            aQuery += "')";
            query.exec(aQuery);
          }
          else if(ifInUsage == true) {
            QSqlQuery query;
            QString manPName = name.substr(0, name.find_last_of(".")).c_str();
            QString aCommandOption = anOption.c_str();
            QString anOptionName = optionName.c_str();
            QString aQuery = "insert into TUSAGE (COMMAND,USAGE,USAGE_DES) values ('" + manPName;
            aQuery += "','" + anOptionName;
            aQuery += "','" + aCommandOption;
            aQuery += "')";
            query.exec(aQuery);
          }
          isFLOfOption = true;
          anOption.clear();
        }
      }
      else {
        if ( inContent == true) {
          if (ifInDescription == true) {
            string parsedLine = parseLine(line);
            manPage += parsedLine;
            
            if (isFLOfOption == true) {
              optionName = parsedLine;
              isFLOfOption = false;
            }
            else 
              anOption += parsedLine;
          }
          else if ( ifInOptions == true) {
            string parsedLine = parseLine(line);
            manPage += parsedLine;
            if (isFLOfOption == true) {
              optionName = parsedLine;
              isFLOfOption = false;
            }
            else
              anOption += parsedLine;
          }
          else if ( ifInUsage == true) {
            string parsedLine = parseLine(line);
            manPage += parsedLine;
            if (isFLOfOption == true) {
              optionName = parsedLine;
              isFLOfOption = false;
            }
            else 
              anOption += parsedLine;
          }
          else
            manPage += parseLine(line);
        }
        ifLastLineIsATP = false;
      }
    }
    toRead.close();
    return manPage;
  }

/**
  Parse all system man page 
*/
  void ManParser::parseAllManPage() {
    system("mkdir /tmp/man");
    chdir("/tmp/man/");
    struct dirent **namelist;
    int n;
    char manDir[] ="/usr/share/man/";
    n = scandir(manDir, &namelist, 0, alphasort);
    std::string manName;
    string folderName;
    if (n < 0)
      perror("scandir");
    else
      while(n--) {
        folderName = namelist[n]->d_name;
        if ((strcmp(namelist[n]->d_name, ".") != 0) && (strcmp(namelist[n]->d_name, "..") != 0) && ( folderName.find("scandir") == -1)) {
            std::string folderPath = manDir;
            folderPath += namelist[n]->d_name;
            printf("%s\n", namelist[n]->d_name);
            struct dirent **namelist2;
            int n2;
            n2 = scandir(folderPath.c_str(), &namelist2, 0, alphasort);
            if (n2 < 0)
                perror("scandir");
            else {
              while(n2--) {
                manName = namelist2[n2]->d_name;
                if (((strcmp(namelist2[n2]->d_name, ".") != 0) && (strcmp(namelist2[n2]->d_name, "..") != 0)) && (manName.find("man") == -1) && ( manName.find("scandir") == -1)) {
                  string command;
                  string name = namelist2[n2]->d_name;
                  command = "cp ";
                  command += manDir;
                  command += namelist[n]->d_name;
                  command += "/";
                  command += namelist2[n2]->d_name;
                  command += " /tmp/man";
                  system(command.c_str());
                  command.clear();


                  if (manName.find(".bz2") != -1) {
                    command =  "bunzip2 -d /tmp/man/";
                    command += namelist2[n2]->d_name;
                    name = name.substr(0, name.find(".bz2"));
                    system(command.c_str());
                  }
                  else if (manName.find(".gz") != -1) {
                    name = name.substr(0, name.find(".gz"));
                    //unGz(name);
		    command =  "gunzip /tmp/man/";
                    command += namelist2[n2]->d_name;
                    name = name.substr(0, name.find(".gz"));
                    system(command.c_str());
                  }
                  
                  QSqlQuery query;
                  QString aQuery = name.substr(0, name.find_last_of(".")).c_str();
                  aQuery += "','/usr/share/man/";
                  aQuery += namelist[n]->d_name;
                  aQuery += "/";
                  aQuery += namelist2[n2]->d_name;
                  query.exec("insert into TMAN_PAGE (TITLE,PATH) values ('" + aQuery + "')");
                  parseManPage(name);
                  name = "rm -f /tmp/man/*"; //Cheaper, but some page like sed fail if it is not like that.

                  printf("|______________>  %s\n", namelist2[n2]->d_name);
                  system(name.c_str());
              }
            }
          }
        }
      }
  }

  int ManParser::unGz(string name) {
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
    //char[] source = QString(QString("/tmp/man/")+namelist2[n2]->d_name).toStdString().c_str();
    FILE * pFile;         
    FILE* dest;
    pFile = fopen ( QString(QString("/tmp/man/")+QString::fromStdString(name)+".gz").toStdString().c_str(), "r");
    dest = fopen ((QString(QString("/tmp/man/") + QString::fromStdString(name))).toStdString().c_str(),"w");
    
    if (pFile == NULL) 
      perror ("Error opening file");
    else {

      strm.zalloc = Z_NULL;
      strm.zfree = Z_NULL;
      strm.opaque = Z_NULL;
      strm.avail_in = 0;
      strm.next_in = Z_NULL;
      ret = inflateInit(&strm);
      if (ret != Z_OK)
        return ret;
      
      /* decompress until deflate stream ends or end of file */
      do {
        strm.avail_in = fread(in, 1, CHUNK, pFile);
        if (ferror(pFile)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;
        /* run inflate() on input until output buffer not full */
        do {
          strm.avail_out = CHUNK;
          strm.next_out = out;
          ret = inflate(&strm, Z_NO_FLUSH);
          assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
          switch (ret) {
          case Z_NEED_DICT:
              ret = Z_DATA_ERROR;     /* and fall through */
          case Z_DATA_ERROR:
          case Z_MEM_ERROR:
              (void)inflateEnd(&strm);
              return ret;
          }
          have = CHUNK - strm.avail_out;
          if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
              (void)inflateEnd(&strm);
              return Z_ERRNO;
          }
        } while (strm.avail_out == 0);
      /* done when inflate() says it's done */
      } while (ret != Z_STREAM_END);
      (void)inflateEnd(&strm);
      return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
    }
    fclose (pFile);
    return 0;
  }