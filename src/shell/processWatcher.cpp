#include "processWatcher.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <linux/types.h>
#include <asm/param.h>




  ProcessWatcher::ProcessWatcher(QObject* parent, int pid) {
    this->pid = pid;
  }
  
  void ProcessWatcher::run() {
    Process aProcess;
    sleep(1);
    forever {
      int file = open (QString("/proc/"+QString::number(pid)+"/stat").toStdString().c_str(), O_RDONLY, 0);
      char buffer2[10000];
      read(file, buffer2, 9999);
    
      sscanf (buffer2, "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu"
      "%ld %ld %ld %ld %*ld %ld %lu %lu %ld %lu %lu %lu %lu %lu"
      "%lu %lu %lu %lu %lu %lu %lu %lu %d %d",
      &aProcess.pid, aProcess.comm, &aProcess.state, &aProcess.ppid,
      &aProcess.pgrd, &aProcess.session, &aProcess.tty_nr, &aProcess.tpgid,
      &aProcess.flags, &aProcess.minflt, &aProcess.cminflt, &aProcess.majflt,
      &aProcess.cmajflt, &aProcess.utime, &aProcess.stime, &aProcess.cutime,
      &aProcess.cstime, &aProcess.priority, &aProcess.nice, &aProcess.itrealvalue,
      &aProcess.starttime, &aProcess.vsize, &aProcess.rss, &aProcess.rlim,
      &aProcess.startcode, &aProcess.endcode, &aProcess.startstack, &aProcess.kstkesp,
      &aProcess.kstkeip, &aProcess.signal, &aProcess.blocked, &aProcess.sigignore,
      &aProcess.sigcatch, &aProcess.wcham, &aProcess.nswap, &aProcess.cnswap,
      &aProcess.exit_signal, &aProcess.processor) ;
      
      int procUptime = open("/proc/uptime", O_RDONLY);
      char buffer[256];
      int limit = read(procUptime, buffer, 255);
      
      if (limit<=0) {
                perror("Unable to read uptime");
                return;
      }
      
      buffer[limit] = '\0';
      buffer[255] = '\0';


      close(procUptime);

      int uptime_secs = atol(buffer);
      
      int time_now = time(0);
      
      float total_time = (aProcess.utime + aProcess.stime);
      
      float seconds = ((uptime_secs * (long)HZ) - aProcess.starttime) / HZ;
      float pcpu = seconds ? (total_time * 10.0f * 100.0f / (float)HZ) / seconds : 0; 
      if (pcpu > 999) pcpu = 999;

      emit ressource(pcpu/10,0);
      
      sleep(5);
    }
  }
  