// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList(){
    // header = nullptr;
    // trailer = nullptr;
    header.next = &trailer;
    trailer.prev = &header;  
  }// default constructor
  DLList(const DLList<T>& dll) {
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode<T> *node = dll.header.next;

    while(node != &dll.trailer){
        insert_last(node->obj);
        node = node->next;
    }
  }
  // copy constructor
  DLList(DLList<T>&& dll){
    if(!dll.is_empty()){
        this->header.next = dll.header.next; //header points to dll's header
        this->trailer.prev = dll.trailer.prev; //trailer point to dll's trailer

        dll.header.next->prev = &this->header; //node past header's prev points to header
        this->trailer.prev->next = &this->trailer; //node before trialer points to trailer

        dll.header.next = &dll.trailer; //reset moved dll
        dll.trailer.prev = &dll.header;
    }else{
        header = 0;
        trailer = 0;
        header.next = &trailer;
        trailer.prev = &header;
    }
  } // move constructor
  ~DLList(){
    DLListNode<T> *prev_node,*node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
        }
    header.next = &trailer;
    trailer.prev = &header;
  } // destructor
  DLList<T>& operator=(const DLList<T>& dll){
    if (this != &dll){
        if (!is_empty()){
            DLListNode<T> *prev_node, *node = header.next;
            while (node != &trailer){
                prev_node = node;
                node = node->next;
                delete prev_node;
            }
        }
        header.next = &trailer;
        trailer.prev = &header;


        DLListNode<T> *n = dll.header.next;

        if(n == &dll.trailer){
            header.next = &trailer;
            trailer.prev = &header;
            return *this;
        }

        while(n != &dll.trailer){
            this->insert_last(n->obj);
            n = n->next;
        }
    }

    return *this;
  } // copy assignment operator
  DLList<T>& operator=(DLList<T>&& dll){
    if (this != &dll && !dll.is_empty()){
        if (!is_empty()){
            DLListNode<T> *prev_node, *node = header.next;

            while(node != &trailer){
                prev_node = node;
                node = node->next;
                delete prev_node;
            }
        }
        header.next = &trailer;
        trailer.prev = &header;
        this->header.next = dll.header.next; //header points to dll's header
        this->trailer.prev = dll.trailer.prev; //trailer point to dll's trailer

        dll.header.next->prev = &this->header; //node past header's prev points to header
        this->trailer.prev->next = &this->trailer; //node before trialer points to trailer
        cout << header.next->obj << endl;

    }
    dll.header.next = &dll.trailer; //reset moved dll
    dll.trailer.prev = &dll.header;
    return *this;
  } // move assignment operator
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const{
    if(is_empty()){  throw invalid_argument("Empty Doubly Linked List.");}
    return header.next->obj;
  } // return the first object
  T last() const{
    if(is_empty()) { throw invalid_argument("Empty Doubly Linked List.");}
    return trailer.prev->obj; 
  } // return the last object
  void insert_first(T obj){
      DLListNode<T> *n = new DLListNode<T>(obj, &header, header.next);

      header.next->prev = n;
      header.next = n;
  } // insert to the first node
  T remove_first(){
      if(is_empty()){
          throw invalid_argument("Empty Doubly Linked List.");
      }

      DLListNode<T> *node = header.next;

      node->next->prev = &header;
      header.next = node->next;
      T obj = node->obj;
      delete node;
      return obj;
  } // remove the first node
  void insert_last(T obj){
    DLListNode<T> *node = new DLListNode<T>(obj, trailer.prev, &trailer);
    trailer.prev->next = node;
    trailer.prev = node;
    node->next = &trailer;
  } // insert to the last node
  T remove_last(){
    if(is_empty()){
        throw invalid_argument("Empty Doubly Linked List.");
    }

    DLListNode<T> *n = trailer.prev;
    n->prev->next = &trailer;
    trailer.prev = n->prev;
    T obj = n->obj;
    delete n;
    return obj;
  } // remove the last node
  void insert_after(DLListNode<T> &p, T obj){
    if(is_empty()) throw invalid_argument("List is empty");

    DLListNode<T> *node = new DLListNode<T>(obj, &p, p.next);
    p.next->prev = node;
    p.next = node;
  }
  void insert_before(DLListNode<T> &p, T obj){
      if(is_empty()) throw invalid_argument("List is empty");

      DLListNode<T> *node = new DLListNode<T>(obj, p.prev, &p);
      p.prev->next = node;
      p.prev = node;
  }
  T remove_after(DLListNode<T> &p){
    if(&p == trailer.prev) throw invalid_argument("Node not found.");
    if(is_empty()) throw invalid_argument("List is empty.");

    T obj = p.next->obj;
    DLListNode<T> *node = header.next;

    while(node != &p && node->next != nullptr) node = node->next;

    if(node->next != nullptr) node = node->next;
    else throw invalid_argument("Node not found.");

    if(node->prev == nullptr) header.next->next = node->next;
    else node->prev->next = node->next;

    if(node->next == nullptr) trailer.prev = node->prev;
    else node->next->prev = node->prev;

    return obj;
  }
  T remove_before(DLListNode<T> &p){
    if(&p == &header) throw invalid_argument("Node not found.");
    if(is_empty()) throw invalid_argument("List is empty.");
    T obj = p.prev->obj;

    DLListNode<T> *node = header.next;

    while(node->next != &p && node->next != nullptr) node = node->next;

    if(node->next == nullptr) throw invalid_argument("Node not found.");

    if(node->prev == nullptr) header.next->next = node->next;
    else node->prev->next = node->next;

    if(node->next == nullptr) trailer.prev = node->prev;
    else node->next->prev = node->prev;


    return obj;
  }
};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll){
   if(!dll.is_empty()){
        DLListNode<T> *n = dll.first_node();
        while(n != dll.after_last_node()){
            out << n->obj << ", ";
            n = n->next;
        }
    }else{
        out << "List is empty";
    }
    return out;
}


#endif
