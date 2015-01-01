#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <iostream>

class Item{
private:
    std::string name;
    std::string description;
    std::string writing;
    std::string status;
    int trigger;
    struct{
        std::string prints;
        std::string action;
    }turnon;
public:
    Item():name(""),description(""),writing(""),
        status(""),trigger(0){}
    Item(std::string nm,std::string descrpt,std::string wr)
        :name(nm),description(descrpt),writing(wr),
        status(""),trigger(0){}
    std::string getName(){return name;}
    std::string getDescription(){return description;}
    std::string getWriting(){return writing;}

    void setStatus(std::string sts){status=sts;}
    std::string getStatus(){return status;}

    void setTurnonprint(std::string prt){turnon.prints=prt;}
    std::string getTurnonprint(){return turnon.prints;}

    void setTurnonaction(std::string act){turnon.action=act;}
    std::string getTurnonaction(){return turnon.action;}
};


#endif
