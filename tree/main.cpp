//==============================================================
// Filename :main
// Authors :Ivan Ooijevaar & Marlin Sliman
// Version :1
// License :
// Description :Binary tree constructor/traverser
//==============================================================
#include <iostream>
#include <string>
#include<array>
#include "Tree.h"

std::array<int, 10> first = { 4, 3, 7, 1, 11, 8, 6, 9, 2 };//predefine array to be used
 int value;
int main()
{
    Tree<int> random;//initialize tree
    for (int i = 0; i < first.size(); i++) {//fill tree with array items
        random.insertNode(first[i]);
        }
    std::cout << "What number are you looking for?\n";
    std::cin >> value;//ask for value to search in tree
    random.search(value);//use search function in tree.h
    random.display();//show the binary tree
    return 0;
}




