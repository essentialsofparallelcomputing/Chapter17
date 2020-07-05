#if !defined(TIMER1) && !defined(TIMER2) && !defined(TIMER3) && !defined(TIMER4) && !defined(TIMER5)
#define TIMER1
#endif

#if defined(TIMER1) || defined(TIMER2) || defined(TIMER3)
#define TIMERSTRUCT timespec
#elif defined(TIMER4) || defined(TIMER5)
#define TIMERSTRUCT timeval
#endif

#if defined(TIMER1)
#define CPU_TIMER_START cpu_timer_start1
#define CPU_TIMER_STOP  cpu_timer_stop1
#elif defined(TIMER2)
#define CPU_TIMER_START cpu_timer_start2
#define CPU_TIMER_STOP  cpu_timer_stop2
#elif defined(TIMER3)
#define CPU_TIMER_START cpu_timer_start3
#define CPU_TIMER_STOP  cpu_timer_stop3
#elif defined(TIMER4)
#define CPU_TIMER_START cpu_timer_start4
#define CPU_TIMER_STOP  cpu_timer_stop4
#elif defined(TIMER5)
#define CPU_TIMER_START cpu_timer_start4
#define CPU_TIMER_STOP  cpu_timer_stop4
#endif
#ifndef _TIMER_H
#define _TIMER_H
#include <time.h>

void cpu_timer_start1(struct timespec *tstart_cpu);
double cpu_timer_stop1(struct timespec tstart_cpu);

void cpu_timer_start2(struct timespec *tstart_cpu);
double cpu_timer_stop2(struct timespec tstart_cpu);

void cpu_timer_start3(struct timespec *tstart_cpu);
double cpu_timer_stop3(struct timespec tstart_cpu);

void cpu_timer_start4(struct timeval *tstart_cpu);
double cpu_timer_stop4(struct timeval tstart_cpu);

void cpu_timer_start5(struct timeval *tstart_cpu);
double cpu_timer_stop5(struct timeval tstart_cpu);
#endif
