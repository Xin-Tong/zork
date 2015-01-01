#include "Room.h"

using namespace std;

Room::Room()
{
    name="";
    description="";

    border.nRoom=NULL;
    border.eRoom=NULL;
    border.sRoom=NULL;
    border.wRoom=NULL;
    border.nRoomName="";
    border.eRoomName="";
    border.sRoomName="";
    border.wRoomName="";
}

Room::Room(string nm,string dscrip,
         string nRn,string eRn,string sRn,string wRn)
    :name(nm),description(dscrip)
{
    border.nRoomName=nRn;
    border.eRoomName=eRn,
    border.sRoomName=sRn;
    border.wRoomName=wRn;
    border.nRoom=NULL;
    border.eRoom=NULL;
    border.sRoom=NULL;
    border.wRoom=NULL;
}

int Room::searchItem(std::string itemname)
{
    for(int i=0;i<itemPointers.size();i++){
        if(itemPointers[i]->getName()==itemname)
            return 1;
    }
    return 0;
}
int Room::searchContainer(std::string containername)
{
    for(int i=0;i<containerPointers.size();i++){
        if(containerPointers[i]->getName()==containername)
            return 1;
    }
    return 0;
}

Item* Room::getItemPointer(std::string itemname)
{
    for(int i=0;i<itemPointers.size();i++){
        if(itemPointers[i]->getName()==itemname)
            return itemPointers[i];
    }
    return NULL;
}
Container* Room::getContainerPointer(std::string containername)
{
    for(int i=0;i<containerPointers.size();i++){
        if(containerPointers[i]->getName()==containername)
            return containerPointers[i];
    }
    return NULL;
}
Creature* Room::getCreaturePointer(std::string creaturename)
{
    for(int i=0;i<creaturePointers.size();i++){
        if(creaturePointers[i]->getName()==creaturename)
            return creaturePointers[i];
    }
    return NULL;
}

void Room::eraseItem(std::string itemname)
{
    vector<Item*>::iterator iter=itemPointers.begin();
    for(int i=0;i<itemPointers.size();i++){
        if(itemPointers[i]->getName()==itemname){
            itemPointers.erase(iter+i);
            return;
        }
    }
}

void Room::eraseCreature(std::string creaturename)
{
    vector<Creature*>::iterator iter=creaturePointers.begin();
    for(int i=0;i<creaturePointers.size();i++){
        if(creaturePointers[i]->getName()==creaturename){
            creaturePointers.erase(iter+i);
            return;
        }
    }
}



void Room::print()
{
    cout<<"This is "<<name<<endl;
    cout<<""<<description<<endl;
}

void Room::MyPrint()
{
    cout<<"the name of the room is: "<<name<<endl;
    cout<<"the description is: "<<description<<endl;

    cout<<"the north room is: "<<border.nRoomName<<endl;
    cout<<"the east room is: "<<border.eRoomName<<endl;
    cout<<"the south roome is: "<<border.sRoomName<<endl;
    cout<<"the west room is: "<<border.wRoomName<<endl;
}

Creature* Room::triggerCheck()
{
    if(!creaturePointers.size())
        return NULL;
    for(int i=0;i<creaturePointers.size();i++){
        if(creaturePointers[i]->getStatus()=="alive")
            return creaturePointers[i];
    }
    return NULL;
}

string Room::triggerInvoked(string comm,int *pInvoked)
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
        if(tricommand!=""&&tricommand!=comm)
            continue;

        tritype=triggers.triggerset[i].type;
        if(tritype!="permanent" && tritype!="single" && tritype!="")
            continue;

        triconobj=triggers.triggerset[i].condition.object;
        Item* pitem=getItemPointer(triconobj);
        Container* pContainer=getContainerPointer(triconobj);
        if(triconobj!="" && !pitem && !pContainer)
            continue;

        triconsts=triggers.triggerset[i].condition.status;
        if(triconsts!=""){
            if(pitem && pitem->getStatus()!=triconsts)
                continue;
            else if(pContainer && pContainer->getStatus()!=triconsts)
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
        *pInvoked=1;
        return triact;
    }
    *pInvoked=0;
    return string("");
}

string Room::triggerInvoked(string comm,int *pInvoked,Inventory inv)
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
        if(tricommand!=""&&tricommand!=comm)
            continue;

        tritype=triggers.triggerset[i].type;
        if(tritype!="permanent" && tritype!="single" && tritype!="")
            continue;

        triconobj=triggers.triggerset[i].condition.object;
        triconhas=triggers.triggerset[i].condition.has;

        Item* pitem=getItemPointer(triconobj);
        Container* pContainer=getContainerPointer(triconobj);
        if(triconobj!="" && !pitem && !pContainer && triconhas=="yes")
            continue;

        triconsts=triggers.triggerset[i].condition.status;
        if(triconsts!=""){
            if(pitem && pitem->getStatus()!=triconsts)
                continue;
            else if(pContainer && pContainer->getStatus()!=triconsts)
                continue;
        }
        triconown=triggers.triggerset[i].condition.owner;
        if(triconhas=="yes" && (triconown==""||triconobj==""))
            continue;
        if(triconhas=="yes" && triconown!=name)
            continue;
        if(triconhas=="no"){
            if(triconown=="inventory"){
                Item* pitem=inv.getItemPointer(triconobj);
                if(pitem)
                    continue;
            }
        }
        triprints=triggers.triggerset[i].prints;
        cout<<triprints<<endl;
        triact=triggers.triggerset[i].action;
        *pInvoked=1;
        return triact;
    }
    *pInvoked=0;
    return string("");
}
