#include "Linkedlist.h"

void addHead(list &L, Button data) {
    node* p = createNode(data);
    if (L.head == NULL) {
        L.head = p;
        L.tail = p;
        return;
    }
    else {
        L.head->prev = p;
        p->next = L.head;
        L.head = p;
    }
}

void addTail(list &L, Button data) {
    node* p = createNode(data);
    if (L.head == NULL) {
        L.head = p;
        L.tail = p;
        return;
    }
    else {
        L.tail->next = p;
        p->prev = L.tail;
        L.tail = p;
        L.tail->next = NULL;
    }
}

void removeHead(list &L) {
    if (L.head == NULL) return;
    L.head = L.head->next;
    delete L.head->prev;
    L.head->prev = NULL;
}

void removeTail(list &L) {
    if (L.head == NULL) return;
    L.tail = L.tail->prev;
    L.tail->next = NULL;

}

void removePos(list &L, int pos) {
    if (L.head == NULL) return;
    if (pos == 0) {
        removeHead(L);
        return;
    }
    node* p = L.head;
    for (int i = 0; p != NULL && i < pos; i++) {
        p = p->next;
    }
    if (p->next == NULL){
        p->prev->next = NULL;
        delete p;
        return;
    }
    if (p == NULL || p->next == NULL) return;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}

int countElements(list L){
    int cnt = 0;
    for (node* p = L.head; p != NULL; p = p->next)
        cnt++;
    return cnt;
}

void addPos(list &L, int pos, Button data){
    if (pos == 0){
        addHead(L, data);
        return;
    }
    node* p = L.head;
    for (int i = 0; p != NULL && i < pos; i++)    p = p->next;
    node* pHead = createNode(data);
    pHead->next = p;
    pHead->prev = p->prev;
    p->prev->next = pHead;
    p->prev = p;


}