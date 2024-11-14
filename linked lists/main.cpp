//==============================================================
// Filename :main
// Authors :Ivan Ooijevaar & Marlin Sliman
// Version :
// License :
// Description :code to add lists together
//==============================================================

#include "List.h"
#include <iostream>
#include <string>

std::string in1 = "singlylinkedlist";
std::string in2 = "abcdefg";
std::string in3 = "hijklmnop";
std::string in4 = "qrstuvw";
void fillList(std::string &, List<char> &);//initialize fillList function

int main()
{
    List<char> list1;//initialize lists
    List<char> list2;
    List<char> list3;
    List<char> list4;

    fillList(in1, list1);//fill the lists
    fillList(in2, list2);
    fillList(in3, list3);
    fillList(in4, list4);
    list1.print();//print lists 1 and 2 (as for exercises)
    list2.print();
    list2.concatenate(list3);//add list 3 to list 2
    list2.concatenate(list4);//add list 4 to list 2
    list2.print();   
    return 0;
}

//fill chosen list
void fillList(std::string &input, List<char> &list) {
    for (int i = 0; i < input.length(); i++) {
        list.insertAtBack(input[i]);
    }
}
