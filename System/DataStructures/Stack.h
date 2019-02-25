#ifndef PILHA_H
#define PILHA_H
#include "Node.h"
#include<iostream>
using namespace std;
using namespace myNode;

template<class T> class Stack
{
public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void clear();
    int count(){ return size(); }
    void push(const T &Value);
    void pop();
    T &top();
    const T &top() const;
    int size();
    void swap(Stack<T> &other);
    void reverse();
    Stack<T> &operator += (const T &Value);
    Stack<T> &operator << (const T &Value);
    bool operator == (Stack<T> &other);
    int toPtrVector(T *&Vector);

    //Static members
    static Stack<T> fromPtrVector(const T *const vector, int size);

private:
    Node<T> *Top;
};
#include "Stack.cpp"
#endif // PILHA_H
