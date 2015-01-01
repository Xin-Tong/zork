#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "Items.h"
#include <iostream>
#include <vector>

class Inventory{
private:
    std::vector<Item*> ItemPointers;
public:
    void print();
    void InsertItem(Item * pItem);

    int itemSize(){return ItemPointers.size();}
    Item* getItemPointer(int i){return ItemPointers[i];}
    void eraseItem(int i){
        std::vector<Item*>::iterator iter=ItemPointers.begin();
        ItemPointers.erase(iter+i);
    }
    int haveItem(std::string itemname);
    Item* getItemPointer(std::string itemname);
};

#endif
