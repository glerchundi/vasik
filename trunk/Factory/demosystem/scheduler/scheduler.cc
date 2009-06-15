#include "scheduler.h"

scheduler::scheduler() {
    this->nlayers   = -1;
}

scheduler::~scheduler() {
}

void
scheduler::init(int nlayers) {
    this->nlayers   = nlayers;
    this->layers    = new TList<FuncKey*>[nlayers];
}

void
scheduler::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
scheduler::quit(void) {
}

int
scheduler::addfx(int layer, int t1, int t2, char *plugin, char *func, param *vars) {
    FuncKey *key = new FuncKey();

    key->plugin = new char[strlen(plugin)+1];
    key->func   = new char[strlen(func)+1];

    key->exec   = false;
    key->t1     = t1;
    key->t2     = t2;
    snprintf(key->plugin, strlen(plugin)+1, "%s", plugin);
    snprintf(key->func, strlen(func)+1, "%s", func);
    key->vars   = vars;

    if(layer < 0) {
        this->oneshot.add(NULL, key);
    }
    else if(layer < this->nlayers) {
        this->layers[layer].add(NULL, key);
    }
    else {
        // error
    }
    return 0;
}

int
scheduler::play(int delayMs) {
    param *ret;
    bool isFinished;
    int i,j,mysize,currentMs;

    ret = execute("timer","createTimer",NULL);
    p[0]._int = ret->_int;
    execute("timer","start",p);

    do {
        ret         = execute("timer","getMs",p);
        currentMs   = ret->_int;
        
        // one shot functions
        mysize = this->oneshot.size();
        for(i = 0 ; i < this->oneshot.size() ; i++) {
            FuncKey *key = this->oneshot.get(i);
            
            if(!key->exec && (currentMs >= key->t1 || key->t1 == -1)) {
                key->exec = true;
                this->execute   (
                                key->plugin,
                                key->func,
                                key->vars
                                );
            }
        }

        // layered and continious functions
        for(i = 0 ; i < this->nlayers ; i++) {
            mysize = this->layers[i].size();
            for(j = 0 ; j < mysize ; j++) {
                FuncKey *key = this->layers[i].get(j);
                if(currentMs >= key->t1 && (currentMs <= key->t2 || key->t2 == -1)) {
                    this->execute   ( 
                                    key->plugin,
                                    key->func,
                                    key->vars
                                    );
                }
            }
        }
        execute("window","swapbuffers",NULL);

        ret         = execute("window","isfinished",NULL);
        isFinished  = ret->_bool;
    } while (!isFinished);
    return 0;
}
