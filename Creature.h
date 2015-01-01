#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <iostream>
#include <vector>
#include <string>
#include "triggerset.h"
#include "Inventory.h"
#include "Items.h"

#define STAT_ALIVE 1

class Attack{
public:
    struct{
        std::string object;
        std::string status;
    }condition;
    std::string prints;
    std::string action;
public:
    Attack(){}
};

class Creature{
private:
    std::string name;
    std::string description;
    std::vector<std::string> vulnerability;
    std::string direction;
    std::string status;
    Triggerset triggers;

    Attack atk;


public:
    Creature(){}
    Creature(std::string nm,std::string des):
        name(nm),description(des){}
    Creature(std::string nm,std::string des,std::string dir, std::string sts):
        name(nm),description(des),direction(dir),status(sts){}
    void addVul(std::string vul){
        vulnerability.push_back(vul);
    }

    std::string getName(){return name;}
    std::string getStatus(){return status;}
    std::string getDirection(){return direction;}

    void setStatus(std::string sts){status=sts;}
    int vulnerMatch(std::string weapon);

    void addtrigger(Trigger newtrigger){triggers.addtrigger(newtrigger);}

    void kill();

    std::string triggerInvoked(Inventory* pInv,int *pInvoked);

    void setAttack(std::string obj,std::string sts,
           std::string prnt,std::string act)
    {
        atk.condition.object=obj;
        atk.condition.status=sts;
        atk.action=act;
        atk.prints=prnt;
    }

    std::string attackInvoke(Inventory pInv);

    int haveVul(std::string vul);
};

#endif
