#ifndef TIMER_H__
#define TIMER_H__

#include "TVasik.h"

#define TIMER_INT       int
#define DEFAULT_TIMERS  1024

class timer : public TPlugin {
public:
	// construct & destruct
	timer();
	~timer();
	// plugin func's
	void        init(int numTimers = DEFAULT_TIMERS);
	void        quit(void);
	// other wrapping func's
	// ...
    int         createTimer(void);
    int         start(int timerId);
    TIMER_INT   getMs(int timerId);
    TIMER_INT   getMu(int timerId);
    // base timing function
    TIMER_INT   getTicks(void); // in microseconds
private:
	// plugin var's
	// ...
    TIMER_INT*  starttime;
    int         timerCounter;
};

#endif
