#include "Creature.h"
using namespace std;

int Creature::vulnerMatch(std::string weapon)
{
    for(int i=0;i<vulnerability.size();i++){
        if(weapon==vulnerability[i])
            return 1;
    }
    return 0;
}

void Creature::kill()
{
    status="dead";
    cout<<"You kill the "<<name<<" successfully, congratulations!"<<endl;
}

std::string Creature::triggerInvoked(Inventory* pInv,int *pInvoked)
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

        tritype=triggers.triggerset[i].type;
        if(tritype!="permanent" && tritype!="single" && tritype!="")
            continue;

        triconobj=triggers.triggerset[i].condition.object;
        Item* pitem=pInv->getItemPointer(triconobj);
        if(triconobj!="" && !pitem )
            continue;

        triconsts=triggers.triggerset[i].condition.status;
        if(triconsts!=""){
            if(pitem && pitem->getStatus()!=triconsts)
                continue;
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
        if(tritype=="single" )
            triggers.triggerset[i].type="done";
        *pInvoked=1;
        return triact;
    }
    *pInvoked=0;
    return string("");
}

std::string Creature::attackInvoke(Inventory pInv)
{
    Item* pitem=pInv.getItemPointer(atk.condition.object);
    if(pitem && atk.condition.status==pitem->getStatus()){
        cout<<atk.prints<<endl;
        return atk.action;
    }
    if(atk.condition.status==status){
        cout<<atk.prints<<endl;
        return atk.action;
    }
    cout<<"no effect"<<endl;
    return string("");
}

int Creature::haveVul(std::string vul)
{
    for(int i=0;i<vulnerability.size();i++){
        if(vulnerability[i]==vul)
            return 1;
    }
    return 0;
}
