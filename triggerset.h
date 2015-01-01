#ifndef _TRIGGERSET_H_
#define _TRIGGERSET_H_

#include <vector>
#include <string>
#include <iostream>

class Trigger{
public:
    std::string command;
    std::string type;
    struct{
        std::string object;
        std::string status;
        std::string has;
        std::string owner;
    }condition;
    std::string prints;
    std::string action;
public:
    Trigger(){}
    Trigger(std::string cmmd,std::string tp,std::string obj,std::string sts,
            std::string hs,std::string onr,std::string prnt,std::string act):
            command(cmmd),type(tp),prints(prnt),action(act) {
        condition.object=obj;
        condition.status=sts;
        condition.has=hs;
        condition.owner=onr;
    }
};

class Triggerset{
public:
    std::vector <Trigger> triggerset;
public:
    Triggerset(){}
    void addtrigger(Trigger newtrigger){ triggerset.push_back(newtrigger);}
    int size(){return triggerset.size();}
};

#endif
