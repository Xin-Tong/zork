#ifndef _ROOM_H_
#define _ROOM_H_

#include <iostream>
#include <vector>
#include <string>
#include "Container.h"
#include "Items.h"
#include "Creature.h"
#include "triggerset.h"

class Room{
private:
    std::string name;
    std::string description;
    std::string type;
    struct{
        Room* nRoom;        //北方房间
        Room* eRoom;        //东方房间
        Room* sRoom;        //南方房间
        Room* wRoom;        //西方房间
        std::string nRoomName;  //北方房间描述
        std::string eRoomName;  //东方房间描述。。。
        std::string sRoomName;
        std::string wRoomName;
    }border;

    std::vector<Item*> itemPointers;
    std::vector<Container*> containerPointers;
    std::vector<Creature*> creaturePointers;


    Triggerset triggers;

public:
    Room();
    Room(std::string nm,std::string dscrip,
         std::string nRn,std::string eRn,
         std::string sRn,std::string wRn);
    void setNRoomName(std::string nrname){border.nRoomName=nrname;}
    void setERoomName(std::string ername){border.eRoomName=ername;}
    void setSRoomName(std::string srname){border.sRoomName=srname;}
    void setWRoomName(std::string wrname){border.wRoomName=wrname;}

    void setNRoom(Room* room){border.nRoom=room;}
    void setERoom(Room* room){border.eRoom=room;}
    void setSRoom(Room* room){border.sRoom=room;}
    void setWRoom(Room* room){border.wRoom=room;}

    std::string getRoomName() {return name;}

    std::string getERoomName(){return border.eRoomName;}
    std::string getSRoomName(){return border.sRoomName;}
    std::string getNRoomName(){return border.nRoomName;}
    std::string getWRoomName(){return border.wRoomName;}

    Room* getERoom(){return border.eRoom;}
    Room* getSRoom(){return border.sRoom;}
    Room* getNRoom(){return border.nRoom;}
    Room* getWRoom(){return border.wRoom;}

    void setType(std::string tp){type=tp;}
    std::string getType(){return type;}

    void AddItemPointer(Item *p){itemPointers.push_back(p);}
    void AddContainerPointer(Container *p){containerPointers.push_back(p);}
    void AddCreaturePointer(Creature *p){creaturePointers.push_back(p);}

    int itemSize(){return itemPointers.size();}
    int containerSize(){return containerPointers.size();}
    int creatureSize(){return creaturePointers.size();}

    Item* getItemPointer(int i){return itemPointers[i];}
    Container* getContainerPointer(int i){return containerPointers[i];}
    Creature* getCreaturePointer(int i){return creaturePointers[i];}

    Item* getItemPointer(std::string itemname);
    Container* getContainerPointer(std::string containername);
    Creature* getCreaturePointer(std::string creaturename);

    void eraseItem(int i){
        std::vector<Item*>::iterator iter=itemPointers.begin();
        itemPointers.erase(iter+i);
    }

    void eraseItem(std::string itemname);
    void eraseCreature(std::string creaturename);

    int searchItem(std::string itemname);
    int searchContainer(std::string containername);


    void print();

    void MyPrint();
    Creature* triggerCheck();
    void addtrigger(Trigger newtrigger){triggers.addtrigger(newtrigger);}

    std::string triggerInvoked(std::string comm,int *pInvoked);
    std::string triggerInvoked(std::string comm,int *pInvoked,Inventory inv);
};

#endif
