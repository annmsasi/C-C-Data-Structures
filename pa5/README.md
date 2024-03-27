/****************************************************************************************
Ann Sasi
pa5
CruzID asasi
README.md

*****************************************************************************************/

This repository contains the implementation of a List ADT implemented in C++ that is traveresed bidirectionally by 2 node objects. List is a double ended queue with a vertical cursor standing between elements. In addition, there is a client file utilizing the List structure to create a shuffle algorithm within the client file that outputs how many shuffles are required to shuffle a deck back to its original state. The project is structured as follows:

List.h: Header file for a C++ program that implements a linked List ADT. It contains constructors and destructors, as well as getters and setters.

List.c: The implementation of the getters, setters, constructors, and destructors mentioned above. It is implementing a linked list designed to be navigated with two node pointers that index the space between two values in the list.

Shuffle.cpp: A client file designed to take in input as a card deck, shuffle it, then output the number of shuffles required to set the deck back to its original state.

ListTest.c: A file containing function calls to methods in List.c to test each method's functionality.

Makefile: A makefile for easy compilation of the project. It defines rules for building the executable files from the source code

README.md: Simply a description of everything mentioned above.