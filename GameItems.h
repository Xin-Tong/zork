#ifndef _GAMEITEMS_H_
#define _GAMEITEMS_H_

#include "Room.h"
#include "Items.h"
#include "Container.h"
#include "Inventory.h"
#include "Creature.h"
#include <string>
#include <vector>

class GameItems{
private:
    std::vector<Room> Rooms;
    std::vector<Container> Containers;
    std::vector<Item> Items;
    std::vector<Creature> Creatures;
public:
    GameItems(){}
    void insertRoom(Room rm);
    void InitiateItems(std::string roomXML="",std::string containerXML="",
        std::string creatureXML="",std::string itemXML="",std::string triggerXML="");
    void establishLinks();
    void run();

    Item* getItemPointer(std::string itemname);
    Container* getContainerPointer(std::string containername);
    Creature* getCreaturePointer(std::string creaturename);

//    void InitiateItems(const char *roomXML="");
};

#endif
