#include "GameItems.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <sstream>

//using namespace std;
using namespace rapidxml;

void GameItems::insertRoom(Room rm)
{
    Rooms.push_back(rm);
}

void GameItems::InitiateItems(std::string roomXML,std::string containerXML,
        std::string creatureXML,std::string itemXML,std::string triggerXML)
//void GameItems::InitiateItems(const char *roomXML)
{
    if(!roomXML.empty()){
        const char *a=roomXML.c_str();
        file<> fdoc(a);
//        std::cout<<fdoc.data()<<std::endl;

        xml_document<> doc;
        doc.parse<0>(fdoc.data());

        xml_node<>* map=doc.first_node();

        //record all the items
        xml_node<>* item=map->first_node("item");
        while(item){
            std::string namestr("");
            std::string writingstr("");
            std::string descriptionstr("");
            std::string statusstr("");

            xml_node<>* name=item->first_node("name");
            if(name) namestr=name->value();
            xml_node<>* writing=item->first_node("writing");
            if(writing) writingstr=writing->value();
            xml_node<>* description=item->first_node("description");
            if(description) descriptionstr=description->value();

            Item newitem(namestr,descriptionstr,writingstr);

            xml_node<>* status=item->first_node("status");
            if(status) {
                statusstr=status->value();
                newitem.setStatus(statusstr);
            }

            xml_node<>* turnon=item->first_node("turnon");
            if(turnon) {
                newitem.setTurnonprint(turnon->first_node("print")->value());
                newitem.setTurnonaction(turnon->first_node("action")->value());
            }

            Items.push_back(newitem);

            item=item->next_sibling("item");
        }

        xml_node<>* creature=map->first_node("creature");
        while(creature){
            std::string namestr("");
            std::string descriptionstr("");
            std::string directionstr("");
            std::string statusstr("");


            xml_node<>* name=creature->first_node("name");
            if(name) namestr=name->value();
            xml_node<>* description=creature->first_node("description");
            if(description) descriptionstr=description->value();
            xml_node<>* direction=creature->first_node("direction");
            if(direction) directionstr=direction->value();
            xml_node<>* status=creature->first_node("status");
            if(status) statusstr=status->value();

            Creature newCreature(namestr,descriptionstr,directionstr,statusstr);

            Creatures.push_back(newCreature);

            xml_node<>* vulner=creature->first_node("vulnerability");
            while(vulner){
                std::string vul=vulner->value();
                Creatures[Creatures.size()-1].addVul(vul);
                vulner=vulner->next_sibling("vulnerability");
            }


            xml_node<>* attack=creature->first_node("attack");
            while(attack){
                std::string conObjstr;
                std::string conStsstr;
                std::string printsstr;
                std::string actionstr;

                if(attack->first_node("condition")){
                    if(attack->first_node("condition")->first_node("object"))
                        conObjstr=attack->first_node("condition")
                            ->first_node("object")->value();

                    if(attack->first_node("condition")->first_node("status"))
                        conStsstr=attack->first_node("condition")
                            ->first_node("status")->value();
                }

                xml_node<>* print=attack->first_node("print");
                while(print){
                    printsstr=printsstr+"\n"+print->value();
                    print=print->next_sibling("print");
                }

                xml_node<>* action=attack->first_node("action");
                while(action){
                    actionstr=actionstr+" "+action->value();
                    action=action->next_sibling("action");
                }
                Creatures[Creatures.size()-1].setAttack(conObjstr,conStsstr,
                    printsstr,actionstr);
                attack=attack->next_sibling("attack");
            }

            xml_node<>* trigger=creature->first_node("trigger");
            while(trigger){
                std::string commandstr;
                std::string typestr;
                std::string conObjstr;
                std::string conStsstr;
                std::string conHasstr;
                std::string conOwnstr;
                std::string printsstr;
                std::string actionstr;

                if(trigger->first_node("command"))
                    commandstr=trigger->first_node("command")->value();
                if(trigger->first_node("type"))
                    typestr=trigger->first_node("type")->value();
                if(trigger->first_node("condition")){
                    if(trigger->first_node("condition")->first_node("object"))
                        conObjstr=trigger->first_node("condition")->first_node("object")->value();
                    if(trigger->first_node("condition")->first_node("status"))
                        conStsstr=trigger->first_node("condition")->first_node("status")->value();
                    if(trigger->first_node("condition")->first_node("has"))
                        conHasstr=trigger->first_node("condition")->first_node("has")->value();
                    if(trigger->first_node("condition")->first_node("owner"))
                        conOwnstr=trigger->first_node("condition")->first_node("owner")->value();
                }

                xml_node<>* print=trigger->first_node("print");
                while(print){
                    printsstr=printsstr+"\n"+print->value();
                    print=print->next_sibling("print");
                }

                xml_node<>* action=trigger->first_node("action");
                while(action){
                    actionstr=actionstr+" "+action->value();
                    action=action->next_sibling("action");
                }

                Trigger newtri(commandstr,typestr,conObjstr,conStsstr,conHasstr,
                    conOwnstr,printsstr,actionstr);
                Creatures[Creatures.size()-1].addtrigger(newtri);
                trigger=trigger->next_sibling("trigger");
            }//end of while(trigger)


            creature=creature->next_sibling("creature");
        }

        xml_node<>* container=map->first_node("container");
        while(container){
            std::string namestr("");
            std::string writingstr("");
            std::string descriptionstr("");
            std::string statusstr("");
            std::string acceptstr("");

            xml_node<>* name=container->first_node("name");
            if(name) namestr=name->value();
            xml_node<>* writing=container->first_node("writing");
            if(writing) writingstr=writing->value();
            xml_node<>* description=container->first_node("description");
            if(description) descriptionstr=description->value();

            Container newContainer(namestr,descriptionstr,writingstr);

            xml_node<>* status=container->first_node("status");
            if(status) {
                statusstr=status->value();
                newContainer.setStatus(statusstr);
            }

            xml_node<>* accept=container->first_node("accept");
            if(accept){
                acceptstr=accept->value();
                newContainer.setAccept(acceptstr);
            }
            Containers.push_back(newContainer);


            xml_node<>* trigger=container->first_node("trigger");
            while(trigger){
                std::string commandstr;
                std::string typestr;
                std::string conObjstr;
                std::string conStsstr;
                std::string conHasstr;
                std::string conOwnstr;
                std::string printsstr;
                std::string actionstr;

                if(trigger->first_node("command"))
                    commandstr=trigger->first_node("command")->value();
                if(trigger->first_node("type"))
                    typestr=trigger->first_node("type")->value();
                if(trigger->first_node("condition")){
                    if(trigger->first_node("condition")->first_node("object"))
                        conObjstr=trigger->first_node("condition")->first_node("object")->value();
                    if(trigger->first_node("condition")->first_node("status"))
                        conStsstr=trigger->first_node("condition")->first_node("status")->value();
                    if(trigger->first_node("condition")->first_node("has"))
                        conHasstr=trigger->first_node("condition")->first_node("has")->value();
                    if(trigger->first_node("condition")->first_node("owner"))
                        conOwnstr=trigger->first_node("condition")->first_node("owner")->value();
                }

                xml_node<>* print=trigger->first_node("print");
                while(print){
                    printsstr=printsstr+"\n"+print->value();
                    print=print->next_sibling("print");
                }

                xml_node<>* action=trigger->first_node("action");
                while(action){
                    actionstr=actionstr+" "+action->value();
                    action=action->next_sibling("action");
                }

                Trigger newtri(commandstr,typestr,conObjstr,conStsstr,conHasstr,
                    conOwnstr,printsstr,actionstr);
                Containers[Containers.size()-1].addtrigger(newtri);
                trigger=trigger->next_sibling("trigger");
            }//end of while(trigger)

            xml_node<>* contents=container->first_node("item");
            while(contents){
                std::string itemName=contents->value();
                for(int i=0;i<Items.size();i++){
                    if(itemName.compare(Items[i].getName())==0)
                        Containers[Containers.size()-1].AddItemPointer(&Items[i]);
                }
                contents=contents->next_sibling("item");
            }

            container=container->next_sibling("container");
        }

        xml_node<>* room=map->first_node("room");
        //record all the room
        while(room){
            std::string namestr("");
            std::string descriptionstr("");
            std::string typestr;

            xml_node<>* roomName=room->first_node("name");
            if(roomName) namestr=roomName->value();

//            std::cout<<roomName->value()<<std::endl;
            xml_node<>* roomDes=room->first_node("description");
            if(roomDes) descriptionstr=roomDes->value();

            Room newroom(namestr,descriptionstr,"","","","");

            xml_node<>* roomType=room->first_node("type");
            if(roomType) typestr=roomType->value();
            newroom.setType(typestr);

            xml_node<>* roomborder=room->first_node("border");

            while(roomborder){
                xml_node<>* direction=roomborder->first_node("direction");
                xml_node<>* name=roomborder->first_node("name");
                if(std::string(direction->value()).compare("north")==0)
                    newroom.setNRoomName(name->value());
                else if(std::string(direction->value()).compare("east")==0)
                    newroom.setERoomName(name->value());
                else if(std::string(direction->value()).compare("south")==0)
                    newroom.setSRoomName(name->value());
                else
                    newroom.setWRoomName(name->value());

                roomborder=roomborder->next_sibling("border");
            }
            insertRoom(newroom);

            xml_node<>* contents=room->first_node("item");
            while(contents){
                std::string itemName=contents->value();
                for(int i=0;i<Items.size();i++){
                    if(itemName.compare(Items[i].getName())==0)
                        Rooms[Rooms.size()-1].AddItemPointer(&Items[i]);
                }
                contents=contents->next_sibling("item");
            }

            xml_node<>* container=room->first_node("container");
            while(container){
                std::string containerName=container->value();
                for(int i=0;i<Containers.size();i++){
                    if(containerName.compare(Containers[i].getName())==0)
                        Rooms[Rooms.size()-1].AddContainerPointer(&Containers[i]);
                }
                container=container->next_sibling("container");
            }

            xml_node<>* creature=room->first_node("creature");
            while(creature){
                std::string creatureName=creature->value();
                for(int i=0;i<Creatures.size();i++){
                    if(creatureName.compare(Creatures[i].getName())==0)
                        Rooms[Rooms.size()-1].AddCreaturePointer(&Creatures[i]);
                }
                creature=creature->next_sibling("creature");
            }

            xml_node<>* trigger=room->first_node("trigger");
            while(trigger){
                std::string commandstr;
                std::string typestr;
                std::string conObjstr;
                std::string conStsstr;
                std::string conHasstr;
                std::string conOwnstr;
                std::string printsstr;
                std::string actionstr;

                if(trigger->first_node("command"))
                    commandstr=trigger->first_node("command")->value();
                if(trigger->first_node("type"))
                    typestr=trigger->first_node("type")->value();
                if(trigger->first_node("condition")){
                    if(trigger->first_node("condition")->first_node("object"))
                        conObjstr=trigger->first_node("condition")->first_node("object")->value();
                    if(trigger->first_node("condition")->first_node("status"))
                        conStsstr=trigger->first_node("condition")->first_node("status")->value();
                    if(trigger->first_node("condition")->first_node("has"))
                        conHasstr=trigger->first_node("condition")->first_node("has")->value();
                    if(trigger->first_node("condition")->first_node("owner"))
                        conOwnstr=trigger->first_node("condition")->first_node("owner")->value();
                }

                xml_node<>* print=trigger->first_node("print");
                while(print){
                    printsstr=printsstr+"\n"+print->value();
                    print=print->next_sibling("print");
                }


                xml_node<>* action=trigger->first_node("action");
                while(action){
                    actionstr=actionstr+" "+action->value();
                    action=action->next_sibling("action");
                }

                Trigger newtri(commandstr,typestr,conObjstr,conStsstr,conHasstr,
                        conOwnstr,printsstr,actionstr);
                Rooms[Rooms.size()-1].addtrigger(newtri);

                trigger=trigger->next_sibling("trigger");
            }

            room=room->next_sibling("room");
        }
    }//room establishment completed
    if(!containerXML.empty()){
        ;
    }
    if(!creatureXML.empty()){
        ;
    }
    if(!itemXML.empty()){
        ;
    }
    if(!triggerXML.empty()){
        ;
    }

    return;
}

void GameItems::establishLinks()
{
    int i,j;
    for(i=0;i!=Rooms.size();i++){
        for(j=0;j!=Rooms.size();j++){
            std::string roomname=Rooms[j].getRoomName();
            if(roomname.compare(Rooms[i].getNRoomName())==0)
                Rooms[i].setNRoom(&(Rooms[j]));
            else if(roomname.compare(Rooms[i].getERoomName())==0)
                Rooms[i].setERoom(&(Rooms[j]));
            else if(roomname.compare(Rooms[i].getSRoomName())==0)
                Rooms[i].setSRoom(&(Rooms[j]));
            else if(roomname.compare(Rooms[i].getWRoomName())==0)
                Rooms[i].setWRoom(&(Rooms[j]));
        }
    }
}

void GameItems::run()
{
    char inputchar;
    std::string inputCom1;
    std::string inputCom2;
    std::string inputCom3;
    std::string inputCom4;
    Room* curRoom=&Rooms[0];
    Container *curContainer;
    Room* nextRoom=NULL;
    Inventory inv;
    int direcCom=0;
    int noGate=0;
    curRoom->print();
    while(1){
//        do{inputchar=std::cin.get();}while(inputchar=='\n');
//        Creature* pCre=curRoom->triggerCheck();
        // check trigger
//        if(pCre){
//            std::cin>>inputCom1;
//            if(inputCom1=="attack"){
//                std::cin>>inputCom2;
//                std::cin>>inputCom3;
//                std::cin>>inputCom4;
//                if(inputCom2!=pCre->getName()){
//                    std::cout<<"This creature is a "<<pCre->getName()<<std::endl;
//                    continue;
//                }
//                if(inputCom3!="with"){
//                    std::cout<<"Illegal command"<<std::endl;
//                    continue;
//                }
//                if(!inv.haveItem(inputCom4)){
//                    std::cout<<"No such item in your inventory."<<std::endl;
//                    continue;
//                }
//                if(!pCre->vulnerMatch(inputCom4)){
//                    std::cout<<"This has no effect on the "<<pCre->getName()<<std::endl;
//                    continue;
//                }
//
//                pCre->kill();
//
//                continue;
//            }
//            if(inputCom1==pCre->getDirection()){
//                std::cout<<"A "<<pCre->getName()<<
//                    " is facing you, and you must kill it to go that way."<<std::endl;
//                continue;
//            }
//        }
        std::string action;
        int invoked=0;

        for(int i=0;i<curRoom->creatureSize();i++){
            action=curRoom->getCreaturePointer(i)->triggerInvoked(&inv,&invoked);
            if(invoked){
                break;
            }
        }

        // if no creatures are invoked
        if(!invoked) {

        std::cin>>inputCom1;
        if(inputCom1=="q" || inputCom1=="Q"){
            std::cout<<"Quit!"<<std::endl;
            break;
        }


        if(inputCom1=="e" || inputCom1=="E"){
            direcCom=1;
            action=curRoom->triggerInvoked(inputCom1,&invoked);
            if(invoked){
                direcCom=0;
                invoked=0;
            }

            else if(curRoom->getERoom()){
                nextRoom=curRoom->getERoom();
                std::cout<<"You are facing "<<nextRoom->getRoomName()<<std::endl;
            }
            else
                noGate=1;
        }
        else if (inputCom1=="s" || inputCom1=="S"){
            direcCom=1;
            action=curRoom->triggerInvoked(inputCom1,&invoked);
            if(invoked){
                direcCom=0;
                invoked=0;
            }

            else if(curRoom->getSRoom()){
                nextRoom=curRoom->getSRoom();
                std::cout<<"You are facing "<<nextRoom->getRoomName()<<std::endl;
            }
            else
                noGate=1;
        }
        else if(inputCom1=="w" || inputCom1=="W"){
            direcCom=1;
            action=curRoom->triggerInvoked(inputCom1,&invoked);
            if(invoked){
                direcCom=0;
                invoked=0;
            }

            else if(curRoom->getWRoom()){
                nextRoom=curRoom->getWRoom();
                std::cout<<"You are facing "<<nextRoom->getRoomName()<<std::endl;
            }
            else
                noGate=1;
        }
        else if(inputCom1=="n" || inputCom1=="N"){
            direcCom=1;
            action=curRoom->triggerInvoked(inputCom1,&invoked);
            if(invoked){
                direcCom=0;
                invoked=0;
            }

            else if(curRoom->getNRoom()){
                nextRoom=curRoom->getNRoom();
                std::cout<<"You are facing "<<nextRoom->getRoomName()<<std::endl;
            }
            else
                noGate=1;
        }

        //other commands

        //command look
        else if(inputCom1=="look"||inputCom1=="LOOK"){
            int itemNum=curRoom->itemSize();
            if(itemNum){
                std::cout<<"the items you can see here are: ";
                for(int i=0;i<itemNum;i++)
                    std::cout<<curRoom->getItemPointer(i)->getName()<<", ";
            }
            std::cout<<std::endl;
            int containerNum=curRoom->containerSize();
            if(containerNum){
                std::cout<<"the containers you can see here are: ";
                for(int i=0;i<containerNum;i++)
                    std::cout<<curRoom->getContainerPointer(i)->getName()<<", ";
            }
            std::cout<<std::endl;
            int creatureNum=curRoom->creatureSize();
            if(creatureNum){
                std::cout<<"the creatures you can see here are: ";
                for(int i=0;i<creatureNum;i++)
                    std::cout<<curRoom->getCreaturePointer(i)->getStatus()<<" "<<
                        curRoom->getCreaturePointer(i)->getName()<<", ";
            }
            std::cout<<std::endl;
            if(!itemNum && !containerNum && !creatureNum)
                std::cout<<"nothing can be seen in this room"<<std::endl;
        }

        //command i(inventory)
        else if(inputCom1=="i" || inputCom1=="I"||
                inputCom1=="inventory"|| inputCom1=="INVENTORY"){
            inv.print();
        }

        //command take item
        else if(inputCom1=="take"||inputCom1=="TAKE"){
            std::cin>>inputCom2;
            int itemNum=curRoom->itemSize();
            int i;
            for(i=0;i<itemNum;i++){
                if(inputCom2.compare(curRoom->getItemPointer(i)->getName())==0){
                    inv.InsertItem(curRoom->getItemPointer(i));
                    curRoom->eraseItem(i);
                    std::cout<<"item taken"<<std::endl;
                    break;
                }
            }
            if(i==itemNum)
                std::cout<<"no such item in this room"<<std::endl;
        }

        //command drop
        else if(inputCom1=="drop"||inputCom1=="DROP"){
            std::cin>>inputCom2;
            int itemNum=inv.itemSize();
            int i;
            for(i=0;i<itemNum;i++){
                if(inputCom2.compare(inv.getItemPointer(i)->getName())==0){
                    curRoom->AddItemPointer(inv.getItemPointer(i));
                    inv.eraseItem(i);
                    std::cout<<"item dropped"<<std::endl;
                    break;
                }
            }
            if(i==itemNum)
                std::cout<<"no such item in your inventory"<<std::endl;
        }

        //command open
        else if(inputCom1=="open"||inputCom1=="OPEN"){
            std::cin>>inputCom2;
            int containerNum=curRoom->containerSize();
            int i;
            action=curRoom->triggerInvoked(inputCom1+" "+inputCom2,&invoked,inv);
            if(invoked);
            else if(inputCom2=="exit"){
                if(curRoom->getType()=="exit"){
                    std::cout<<"Congratualations! You've got the final success"<<std::endl;
                    return;
                }
            }
            else if(containerNum>0 ){
                for(i=0;i<containerNum;i++){
                    if(inputCom2.compare(curRoom->getContainerPointer(i)->getName())==0){
                        curContainer=curRoom->getContainerPointer(i);
                        if(curContainer->getDescription()!="")
                            std::cout<<curContainer->getDescription()<<std::endl;

                        int itemNum=curContainer->itemSize();
                        if(itemNum==0)
                            std::cout<<"The "<<curContainer->getName()<<" is empty."<<std::endl;
                        else {
                            std::cout<<"The "<<curContainer->getName()<<" contains: ";
                            for(int j=0;j<itemNum;j++){
                                std::cout<<curContainer->getItemPointer(j)->getName()<<", ";
                            }
                            std::cout<<std::endl;
                        }
                        break;
                    }
                }//end of container search
                if(i==containerNum)
                    std::cout<<"No such container."<<std::endl;
                else{
                    while(1){
                        std::cout<<"Do you wanna leave(input \"leave\" to leave), take anything,"
                            <<" or put anything into the container? "<<std::endl;
                        std::cin>>inputCom1;
                        if(inputCom1=="take"||inputCom1=="TAKE"){
                            std::cin>>inputCom2;

                            int itemNum=curContainer->itemSize();
                            if(itemNum==0)
                                std::cout<<"The container is empty."<<std::endl;
                            else {
                                int j;
                                for(j=0;j<itemNum;j++){
                                    if(inputCom2.compare(curContainer->getItemPointer(j)
                                        ->getName())==0){
                                        inv.InsertItem(curContainer->getItemPointer(j));
                                        curContainer->eraseItem(j);
                                        std::cout<<"The item is taken successfully"<<std::endl;
                                        break;
                                    }
                                }
                                if(j==itemNum)
                                    std::cout<<"No such item here"<<std::endl;
                            }
                        }
                        else if(inputCom1=="put"||inputCom1=="PUT"){
                            std::cin>>inputCom2;
                            std::cin>>inputCom3;
                            std::cin>>inputCom4;
                            int itemNum=inv.itemSize();
                            if(!itemNum)
                                std::cout<<"your inventory is empty"<<std::endl;
                            else if (curContainer->getAccept()!="" && curContainer->getAccept()!=inputCom2)
                                std::cout<<"This item cannot be accepted"<<std::endl;
                            else if (inputCom3!="in")
                                std::cout<<"invalid command"<<std::endl;
                            else if (inputCom4!=curContainer->getName())
                                std::cout<<"This container is a "<<curContainer->getName()<<"."<<std::endl;
                            else{
                                int j;
                                for(j=0;j<itemNum;j++){
                                    if(inputCom2.compare(inv.getItemPointer(j)
                                        ->getName())==0){
                                        curContainer->AddItemPointer(inv.getItemPointer(j));
                                        inv.eraseItem(j);
                                        std::cout<<"Item added to "<<curContainer->getName()<<std::endl;

                                        action=curContainer->triggerInvoked(inputCom1+" "+inputCom2+" "
                                            +inputCom3+" "+inputCom4,&invoked);
                                        invoked=0;

                                        //deal with actions here
                                        std::istringstream iss(action);
                                        std::string act1;
                                        std::string act2;
                                        std::string act3;
                                        std::string act4;

                                        iss>>act1;
                                        if(act1=="Update"){
                                            iss>>act2;          //name of the item
                                            iss>>act3;
                                            iss>>act4;          //new state
                                            Item* pitem=curContainer->getItemPointer(act2);
                                            if(pitem)
                                                pitem->setStatus(act4);
                                            else if(curContainer->getName()==act2)
                                                curContainer->setStatus(act4);
                                        }
//                                        else if(act1=="Add"){
//                                            iss>>act2;
//                                            iss>>act3;
//                                            iss>>act4;
//                                        }
//                                        else if(act1=="Delete"){
//                                            iss>>act2;
//                                        }
//                                        else if(act1=="Game"){
//                                            iss>>act2;
//                                        }

                                        action="";

                                        break;
                                    }
                                }// end of for(j=0;j<itemNum;j++)
                                if(j==itemNum)
                                    std::cout<<"No such item in your inventory."<<std::endl;
                            }
                        }
                        else if(inputCom1!="leave" && inputCom1!="LEAVE"){
                            std::cout<<"illegal input"<<std::endl;
                        }
                        else
                        {std::cout<<"Left the container."<<std::endl; break;}
                    }
                }
            }
            else
                std::cout<<"No container."<<std::endl;
        }

        //command read
        else if(inputCom1=="read"||inputCom1=="READ"){
            std::cin>>inputCom2;
            int itemNum=inv.itemSize();
            if(!itemNum)
                std::cout<<"Your inventory is empty"<<std::endl;
            else{
                int j;
                for(j=0;j<itemNum;j++){
                    if(inputCom2.compare(inv.getItemPointer(j)->getName())==0){
                        std::string descriptionstr
                            =inv.getItemPointer(j)->getWriting();
                        if(descriptionstr!="")
                            std::cout<<descriptionstr<<std::endl;
                        else
                            std::cout<<"Nothing to be read on the item."<<std::endl;
                        break;
                    }
                }
                if(j==itemNum)
                    std::cout<<"No such item in your inventory."<<std::endl;
            }
        }

        else if(inputCom1=="attack"){
            std::cin>>inputCom2;
            std::cin>>inputCom3;
            std::cin>>inputCom4;
            Creature *pcreature=curRoom->getCreaturePointer(inputCom2);
            if(!pcreature){
                std::cout<<"No "<<inputCom2<<" here"<<std::endl;
            }
            else if(inputCom3!="with"){
                std::cout<<"Illegal command"<<std::endl;
            }
            else if(!inv.haveItem(inputCom4)){
                std::cout<<"No "<<inputCom4<<" in your inventory."<<std::endl;
            }
            else if(!pcreature->haveVul(inputCom4)){
                std::cout<<inputCom4<<" is not the vulnerability of "<<inputCom2<<std::endl;
            }
            {
                action=pcreature->attackInvoke(inv);
            }
        }

        //command quit
        else if(inputCom1=="q" || inputCom1=="Q"){
            std::cout<<"Quit"<<std::endl;
            break;
        }

        else if(inputCom1=="turn"){
            std::cin>>inputCom2;
            std::cin>>inputCom3;
            if(inputCom2!="on")
                std::cout<<"invalid command"<<std::endl;
            else {
                Item* pitem=inv.getItemPointer(inputCom3);
                if(pitem){
                    std::cout<<pitem->getTurnonprint()<<std::endl;
                    action=pitem->getTurnonaction();
                }
                else
                    std::cout<<"you do not have a "<<inputCom3
                        <<" in your inventory"<<std::endl;
            }
        }

        //wrong input
        else{
            std::cout<<"No such command, try again"<<std::endl;
        }

        if(direcCom){
            direcCom=0;
            if(noGate){
                noGate=0;
                std::cout<<"You can not get out from this direction."<<std::endl;
                continue;
            }
            else{
                std::cout<<"Do you wanna enter the adjacent room(y/n)?"<<std::endl;
                std::cin>>inputCom1;
                if(inputCom1=="Y" || inputCom1=="y"){
                    curRoom=nextRoom;
                    curRoom->print();
                    continue;
                }
            }
        }//ends of if(direcCom)

        }//end of if(!invoked) also end of ordinary input

        //deal with actions here
        std::istringstream iss(action);
        std::string act1;
        std::string act2;
        std::string act3;
        std::string act4;

        while(iss){
            iss>>act1;
            if(act1=="Update"){
                iss>>act2;          //name of the item
                iss>>act3;
                iss>>act4;          //new state
                Item* pitem=curRoom->getItemPointer(act2);
                if(!pitem)
                    pitem=inv.getItemPointer(act2);
                Container* pcontainer=getContainerPointer(act2);
                Creature* pcreature=getCreaturePointer(act2);
                if(pitem)
                    pitem->setStatus(act4);
                else if(pcontainer)
                    pcontainer->setStatus(act4);
                else if(pcreature)
                    pcreature->setStatus(act4);
            }
            else if(act1=="Add"){
                iss>>act2;
                iss>>act3;
                iss>>act4;
                Room* proom=NULL;
                Item* pitem=NULL;
                for(int i=0;i<Rooms.size();i++){
                    if(Rooms[i].getRoomName()==act4){
                        proom=&Rooms[i];
                        break;
                    }
                }
                for(int i=0;i<Items.size();i++){
                    if(Items[i].getName()==act2){
                        pitem=&Items[i];
                        break;
                    }
                }
                if(proom && pitem)
                    proom->AddItemPointer(pitem);
            }
            else if(act1=="Delete"){
                iss>>act2;
                curRoom->eraseCreature(act2);
            }
            else if(act1=="Game"){
                iss>>act2;
                std::cout<<"";
            }
        }//while(iss)

    }//while(1) ends
}

Item* GameItems::getItemPointer(std::string itemname)
{
    for(int i=0;i<Items.size();i++){
        if(Items[i].getName()==itemname)
            return &Items[i];
    }
    return NULL;
}
Container* GameItems::getContainerPointer(std::string containername)
{
    for(int i=0;i<Containers.size();i++){
        if(Containers[i].getName()==containername)
            return &Containers[i];
    }
    return NULL;
}
Creature* GameItems::getCreaturePointer(std::string creaturename)
{
    for(int i=0;i<Creatures.size();i++){
        if(Creatures[i].getName()==creaturename)
            return &Creatures[i];
    }
    return NULL;
}
