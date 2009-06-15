#include "timer.h"

WRAPPLUGIN(timer)
WRAPFUNC0(_int,createTimer)
WRAPFUNC1(_int,start,_int)
WRAPFUNC1(_int,getMs,_int)
WRAPFUNC1(_int,getMu,_int)

timer::timer() {
    SHAREPLUGIN(timer);
    SHAREFUNC(createTimer);
    SHAREFUNC(start);
    SHAREFUNC(getMs);
    SHAREFUNC(getMu);

    timerCounter    = 0;
    starttime       = NULL;
    init(DEFAULT_TIMERS);    
}

timer::~timer() {
}

void
timer::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
timer::init(int numTimers) {
    if(starttime != NULL) {
        delete [] starttime;
    }
    starttime   = new int[numTimers];
    timerCounter = 0;
}

void
timer::quit(void) {
}

int
timer::createTimer(void) {
    timerCounter++;
    return timerCounter-1;
}

int
timer::start(int timerId) {
    starttime[timerId] = this->getTicks();
    return 0;
}

TIMER_INT
timer::getMs(int timerId) {
    return (this->getMu(timerId) / 1000.0);
}

TIMER_INT
timer::getMu(int timerId) {
    return (this->getTicks() - starttime[timerId]);
}

/*
#if defined(__MACOSX__)

#include <CoreServices/CoreServices.h>

TIMER_INT
timer::getTicks(void)  {
  unsigned long t[2];  // apple defines it this way 
    Microseconds((UnsignedWide *) &t);
  return t[1];
}
*/

#if  defined(__WIN32__)

TIMER_INT
timer::getTicks(void)
{
    static LARGE_INTEGER timestamp = {0};

    LARGE_INTEGER frequency = {0};
        
    if(frequency.QuadPart == 0) {
        QueryPerformanceFrequency(&frequency);
        frequency.QuadPart /= 1000000;
    }
    
    QueryPerformanceCounter(&timestamp);
    return (TIMER_INT)(timestamp.QuadPart / frequency.QuadPart);
} 
 
#else

#include <sys/time.h>

TIMER_INT
timer::getTicks(void)  {
    struct timeval tp;

    gettimeofday(&tp, NULL);

    return 1000000*(TIMER_INT)tp.tv_sec+(TIMER_INT) tp.tv_usec;
}

#endif
