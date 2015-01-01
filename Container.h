#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <iostream>
#include <string>
#include <vector>
#include "Items.h"
#include "triggerset.h"

class Container{
private:
    std::string name;
    std::string description;
    std::string writing;
    std::vector<Item*> ItemPointers;
    std::string status;
    std::string accept;

    Triggerset triggers;

public:
    Container():name(""),description(""),writing(""){}
    Container(std::string nm,std::string dsc,std::string wr)
        :name(nm),description(dsc),writing(wr){}
    void AddItemPointer(Item *p){ItemPointers.push_back(p);}
    std::string getName(){return name;}
    std::string getDescription(){return description;}

    void eraseItem(int i){
        std::vector<Item*>::iterator iter=ItemPointers.begin();
        ItemPointers.erase(iter+i);
    }

    int itemSize(){return ItemPointers.size();}
    Item* getItemPointer(int i){return ItemPointers[i];}

    void setStatus(std::string sts){status=sts;}
    std::string getStatus(){return status;}

    void setAccept(std::string acc){accept=acc;}
    std::string getAccept(){return accept;}

    Item* getItemPointer(std::string itemname);

    void addtrigger(Trigger newtrigger){triggers.addtrigger(newtrigger);}

    std::string triggerInvoked(std::string comm,int *pInvoked);

};

#endif
