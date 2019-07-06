#include <sys/time.h>
#include <stddef.h>
#include <sys/resource.h>
#include <unistd.h>
#include "timer.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void cpu_timer_start1(struct timespec *tstart_cpu)
{
   clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}
double cpu_timer_stop1(struct timespec tstart_cpu)
{
   struct timespec tstop_cpu, tresult;
   clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_nsec*1.0e-9;

   return(result);
}

#ifdef __MACH__
void cpu_timer_start2(struct timespec *tstart_cpu)
{
   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   (*tstart_cpu).tv_sec = mts.tv_sec;
   (*tstart_cpu).tv_nsec = mts.tv_nsec;
}

double cpu_timer_stop2(struct timespec  tstart_cpu)
{
   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   struct timespec tstop_cpu, tresult;
   tstop_cpu.tv_sec = mts.tv_sec;
   tstop_cpu.tv_nsec = mts.tv_nsec;
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_nsec*1.0e-9;

   return(result);
}
#endif

void cpu_timer_start3(struct timespec *tstart_cpu)
{
   clock_gettime(CLOCK_REALTIME, tstart_cpu);
}
double cpu_timer_stop3(struct timespec tstart_cpu)
{
   struct timespec tstop_cpu, tresult;
   clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_nsec*1.0e-9;

   return(result);
}

void cpu_timer_start4(struct timeval *tstart_cpu)
{
   gettimeofday(tstart_cpu, NULL);
}

double cpu_timer_stop4(struct timeval tstart_cpu)
{
   struct timeval tstop_cpu, tresult;
   gettimeofday(&tstop_cpu, NULL);
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_usec = tstop_cpu.tv_usec - tstart_cpu.tv_usec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_usec*1.0e-6;

   return(result);
}

void cpu_timer_start5(struct timeval *tstart_cpu)
{
   struct rusage usage;
   getrusage(RUSAGE_SELF, &usage);
   (*tstart_cpu) = usage.ru_utime;
}

double cpu_timer_stop5(struct timeval tstart_cpu)
{
   struct timeval tstop_cpu, tresult;
   struct rusage usage;
   getrusage(RUSAGE_SELF, &usage);
   tstop_cpu = usage.ru_utime;
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_usec = tstop_cpu.tv_usec - tstart_cpu.tv_usec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_usec*1.0e-6;

   return(result);
}

