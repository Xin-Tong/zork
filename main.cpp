#include <iostream>

#include "GameItems.h"
#include "Room.h"

using namespace std;

int main()
{

//              " mouth of a cave and decide that in spite of"+
//              " common sense and any sense of self preservation"+
//              " that you're going to go exploring north into it."+
//              " It's a little dark, but luckily there are some"+
//              " torches on the wall","room4","","room5","");
//    room1.print();

    GameItems gameitem;
//    gameitem.insertRoom(room1);

    gameitem.InitiateItems("sampledemo2.xml");       //∂¡»Î∑øº‰
    gameitem.establishLinks();
    gameitem.run();

    return 0;
}
