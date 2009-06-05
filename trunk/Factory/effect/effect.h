#ifndef EFFECT_H__
#define EFFECT_H__

#include "TVasik.h"

class effect : public TPlugin
{
public:
	// construct & destruct
	effect();
	~effect();
	// plugin func's
	void 		init(void);
    void 		quit(void);
	int	 		render(void);
    int	 		render(double* data);
    int 		print(void);
private:
	// plugin var's
};

#endif
