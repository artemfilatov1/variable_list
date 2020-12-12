
#ifndef list_hpp
#define list_hpp

#include <stdio.h>
#include "variantA.hpp"

using namespace std;

struct elem{
    elem* next;
    elem* prev;
    variant data;
    elem(variant d): next(0), prev(0), data(d){}
};

class list{
    elem * head;
    elem * last;
    int size;
public:
    list();
    ~list();
    
    variant & operator[](const int number);
    void pushBack(const variant& data);
    void delBack();
    void pushFront(const variant& data);
    void delFront();
    void insert(int idx, const variant& data);
    void del(int idx);
    void clearList();
    int getSize(){return size;}
    void cpyList(const list& l);
    void showList();
};

//-------------------------------------------------------------------------

list::list(){
    head = nullptr;
    last = nullptr;
    size = 0;
}

list::~list(){
    for (elem * i = head; i != 0;){
        elem* tmp = i;
        i = i->next;
        delete tmp;
    }
}

void list::pushBack(const variant& data){
    elem * e = new elem(data);
    if (head == nullptr){
        head = e;
        head->prev = nullptr;
    } else {
        last->next = e;
        e->prev = last;
    }
    last = e;
    last->next = nullptr;
    e->data = data;
    size++;
}

void list::delBack(){
    if (head == nullptr) return;
    last = last->prev;
    delete last->next;
    last->next = nullptr;
    size--;
}

void list::pushFront(const variant& data){
    elem * e = new elem(data);
    if (head == nullptr){
        head = e;
        head->prev = nullptr;
    } else {
        e->next = head;
        head = e;
        size++;
    }
    e->data = data;
    size++;
}

void list::delFront(){
    if (head == nullptr) return;
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    size--;
}

void list::showList(){
    for (elem * i = head; i != 0; i = i->next){
        t type = i->data.getType();
        switch (type) {
            case String: cout << (char*)i->data << " "; break;
            case Double: cout << (double)i->data << " "; break;
            case Int: cout << (int)i->data << " "; break;
            case Bool: cout << (bool)i->data << " "; break;
            case Char: cout << (char)i->data << " "; break;
        }
    }
    cout << endl;
}

void list::del(int idx){
    if(idx >= size || idx < 0) return;
    if(idx == size-1){
        delBack();
        return;
    }
    if(idx == 0){
        delFront();
        return;
    }

    int cnt = 0;
    for (elem * i = head; i != 0; i = i->next){
        if (cnt == idx){
            i->prev->next = i->next;
            delete i;
            size--;
            break;
        }
        cnt++;
    }
}

void list::insert(int idx, const variant& data){
    if(idx >= size || idx < 0) return;
    if(idx == size-1){
        pushBack(data);
        return;
    }
    if(idx == 0){
        pushFront(data);
        return;
    }

    int cnt = 0;
    for (elem * i = head; i != 0; i = i->next){
        if (cnt == idx){
            elem * e = new elem(data);
            e->data = data;
            i->prev->next = e;
            e->next = i;
            size++;
            break;
        }
        cnt++;
    }
}

variant & list::operator[](const int number){
    int cnt = 0;
        for (elem* i = head; i != 0; i = i->next){
            if (number == cnt){
                return i->data;
            }
            cnt++;
        }
    throw "error: double & list::operator[](const int number)";
}

void list::clearList(){
    if (head == nullptr) return;
    for(elem* i = head; i != 0; i = i->next){
        delete i;
        size--;
    }
    head = nullptr;
    last = nullptr;
}

void list::cpyList(const list& l){
    if (l.head == head){
        return;
    }
    for(elem* i = l.head; i != 0; i = i->next){
        pushBack(i->data);
    }
}

#endif /* list_hpp */
