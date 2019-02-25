#ifndef NODE_CPP
#define NODE_CPP
//#define node Node<T>
//#define Template template <typename T>
#include "Node.h"
#include <iostream>
using namespace std;
using namespace myNode;

template <typename T> Node<T>::Node()
{
    Prev = Next = 0;
}

template <typename T> Node<T>::Node(T Value)
{
    this->Value = Value;
    Prev = Next = 0;
}

template <typename T> Node<T>::~Node()
{

}

template <typename T> T &Node<T>::GetValue()
{
    return this->Value;
}

template <typename T> void Node<T>::SetValue(T Value)
{
    this->Value = Value;
}

/*template <typename T> void Node<T>::operator =(T Value)
{
    SetValue(Value);
}*/

template <typename T> Node<T> *Node<T>::GetNext()
{
    return this->Next;
}

template <typename T> void Node<T>::SetNext(Node<T> *node)
{
    this->Next = node;
}

template <typename T> Node<T> *Node<T>::GetPrevious()
{
    return this->Prev;
}

template <typename T> void Node<T>::SetPrevious(Node<T> *node)
{
    this->Prev = node;
}

#endif
