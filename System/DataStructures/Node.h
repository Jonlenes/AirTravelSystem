#ifndef NODE_H
#define NODE_H

#include<iostream>
using namespace std;

namespace myNode {
template <typename T>
class Node
{
public:
    Node ();
    Node (T Value);
    ~Node ();

    T &GetValue();
    void SetValue(T);
    //void operator = (Node<T>*);

    Node<T> *GetNext();
    void SetNext(Node<T> *);

    Node<T> *GetPrevious();
    void SetPrevious(Node<T> *);

private:
    T Value;
    Node<T> *Prev;
    Node<T> *Next;
};

#include "Node.cpp"
}
#endif // NODE_H
