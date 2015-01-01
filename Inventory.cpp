#include "Inventory.h"

using namespace std;

void Inventory::print(){
    int itemNum=ItemPointers.size();
    if(!itemNum)
        cout<<"Inventory: empty"<<endl;
    else{
        cout<<"Inventory: "<<endl;
        for(int i=0;i<itemNum;i++)
            cout<<ItemPointers[i]->getName()<<endl;
    }
}

void Inventory::InsertItem(Item * pItem)
{
    ItemPointers.push_back(pItem);
}

int Inventory::haveItem(std::string itemname)
{
    for(int i=0;i<ItemPointers.size();i++)
    {
        if(ItemPointers[i]->getName()==(itemname))
            return 1;
    }
    return 0;
}

Item* Inventory::getItemPointer(std::string itemname)
{
    for(int i=0;i<ItemPointers.size();i++)
    {
        if(ItemPointers[i]->getName()==(itemname))
            return ItemPointers[i];
    }
    return NULL;
}

