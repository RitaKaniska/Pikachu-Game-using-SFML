#pragma once
#include <iostream>
#include "Random.h"
#include "Button.h"
using namespace std;

struct node {
    Button key;
    node* next;
    node* prev;
};

struct list {
    node* head;
    node* tail;
};

inline node* createNode(Button data) {
    node* p = new node;
    p->key = data;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

list createList(node*); //Create a new list
void addHead(list&, Button);    //Add data at the first position of the list
void addTail(list&, Button);    //Add data at the last position of the list
void removeHead(list&);         //Remove the first data
void removeTail(list&);         //Remove the last data
void removePos(list&, int);     //Remove data at the position
void addPos(list&, int, Button);//Add data the position 
int countElements(list);        //Count the number of list