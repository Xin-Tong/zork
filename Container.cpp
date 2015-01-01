#include "Container.h"
using namespace std;

string Container::triggerInvoked(string comm,int *pInvoked)
{
    string tricommand;
    string tritype;
    string triconobj;
    string triconsts;
    string triconhas;
    string triconown;
    string triprints;
    string triact;

    for(int i=0;i<triggers.size();i++){
        tricommand=triggers.triggerset[i].command;
        if(tricommand!="" && tricommand!=comm)
            continue;

        tritype=triggers.triggerset[i].type;
        if(tritype!="permanent" && tritype!="single" && tritype!="")
            continue;

        triconobj=triggers.triggerset[i].condition.object;
        Item* pitem=getItemPointer(triconobj);
        //Container* pContainer=getContainerPointer(triconobj);
        if(triconobj!="" && !pitem)
            continue;

        triconsts=triggers.triggerset[i].condition.status;
        if(triconsts!=""){
            if(pitem && pitem->getStatus()!=triconsts)
                continue;
//            else if(pContainer && pContainer->getStatus()!=triconsts)
//                continue;
        }
        triconhas=triggers.triggerset[i].condition.has;
        triconown=triggers.triggerset[i].condition.owner;
        if(triconhas=="yes" && (triconown==""||triconobj==""))
            continue;
        if(triconhas=="yes" && triconown!=name)
            continue;
        triprints=triggers.triggerset[i].prints;
        cout<<triprints<<endl;
        triact=triggers.triggerset[i].action;
        *pInvoked=1;
        return triact;
    }
    *pInvoked=0;
    return string("");
}

Item* Container::getItemPointer(std::string itemname)
{
    for(int i=0;i<ItemPointers.size();i++){
        if(ItemPointers[i]->getName()==itemname)
            return ItemPointers[i];
    }
    return NULL;
}
