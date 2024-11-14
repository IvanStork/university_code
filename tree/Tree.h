// Fig. 19.22: Tree.h
// Template Tree class definition.
#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>

// Tree class-template definition
template <typename NODETYPE> class Tree
{
  public:
    // constructor
    Tree() : rootPtr(nullptr) { /* empty body */}

    // insert node in Tree
    void insertNode(const NODETYPE &value)
    {
        insertNodeHelper(&rootPtr, value);
    } // end function insertNode

    // begin preorder traversal of Tree
    void preOrderTraversal() const
    {
        preOrderHelper(rootPtr);
    } // end function preOrderTraversal

    // begin inorder traversal of Tree
    void inOrderTraversal() const
    {
        inOrderHelper(rootPtr);
    } // end function inOrderTraversal

    // begin postorder traversal of Tree
    void postOrderTraversal() const
    {
        postOrderHelper(rootPtr);
    } // end function postOrderTraversal

    TreeNode<NODETYPE>* search(int value) {//following the other functions in this file as examples, a global "substep" has been made to link it to main
        
        return searchHelper(rootPtr, value);//because of this subfunction, rootptr can be used in the searchfunction while not defining it in main
       
   }
    void display() {//following the other functions in this file as examples, a global "substep" has been made to link it to main
        outputTree(rootPtr, 0);//because of this subfunction, rootptr can be used in the printfunction while not defining it in main
    }
    
  private:
    TreeNode<NODETYPE> *rootPtr;

    // utility function called by insertNode; receives a pointer
    // to a pointer so that the function can modify pointer's value
    void insertNodeHelper(TreeNode<NODETYPE> **ptr, const NODETYPE &value)
    {
        // subtree is empty; create new TreeNode containing value
        if (*ptr == nullptr)
            *ptr = new TreeNode<NODETYPE>(value);
        else // subtree is not empty
        {
            // data to insert is less than data in current node
            if (value < (*ptr)->data)
                insertNodeHelper(&((*ptr)->leftPtr), value);
            else {
                // data to insert is greater than data in current node
                if (value > (*ptr)->data)
                    insertNodeHelper(&((*ptr)->rightPtr), value);
                else // duplicate data value ignored
                    std::cout << value << " dup" << std::endl;
            } // end else
        }     // end else
    }         // end function insertNodeHelper

    // utility function to perform preorder traversal of Tree
    void preOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr) {
            std::cout << ptr->data << ' '; // process node
            preOrderHelper(ptr->leftPtr);  // traverse left subtree
            preOrderHelper(ptr->rightPtr); // traverse right subtree
        }                                  // end if
    }                                      // end function preOrderHelper

    // utility function to perform inorder traversal of Tree
    void inOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr) {
            inOrderHelper(ptr->leftPtr);   // traverse left subtree
            std::cout << ptr->data << ' '; // process node
            inOrderHelper(ptr->rightPtr);  // traverse right subtree
        }                                  // end if
    }                                      // end function inOrderHelper

    // utility function to perform postorder traversal of Tree
    void postOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr) {
            postOrderHelper(ptr->leftPtr);  // traverse left subtree
            postOrderHelper(ptr->rightPtr); // traverse right subtree
            std::cout << ptr->data << ' ';  // process node
        }                                   // end if
    }                                       // end function postOrderHelper

    TreeNode<NODETYPE>* searchHelper(TreeNode<NODETYPE> *ptr, int value) {//traversing binary tree to find given value
        
        if (ptr != nullptr) {//while the pointer is not out of the range of the tree
            
            std::cout << "searching...\n";
            std::cout << ptr->data << std::endl;//print value of data of pointer for visual reference
            if (ptr->data == value) {//if the value has been found
                std::cout << "the value has been found\n";
                return ptr;
                
            }
            else {//traverse the binary tree, picking which way to go each time
                if (ptr->data > value) {//if we are too high in the list, move down
                    searchHelper(ptr->leftPtr, value);//recursive 
                }
                else {//else move up
                    searchHelper(ptr->rightPtr, value);
                }
            }
        }
        
        else {//if the pointers reach the end of the tree without locating the value
            std::cout << "value not found\n";
            return nullptr;
        }
    }
    void outputTree(TreeNode<NODETYPE>* ptr, int line) {//function to print the tree
        if (ptr != nullptr) {//if the pointer in still inside the tree
            outputTree(ptr->rightPtr, line + 1);//make sure to print the highest number on top, with spacing
            for (int i = 0; i < line; i++) {//print spacing the further the node is from the treetop
                std::cout << "\t";//print a tab (other option would be "            ")
            }
             std::cout << ptr->data << std::endl;//print the data
             outputTree(ptr->leftPtr, line + 1);//move to lower number on the left of the node
            
        
        }
    }
};                                          // end class Tree

#endif

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
