#ifndef FILA_H
#define FILA_H
#include "Node.h"
using namespace myNode;

template<class T> class Queue
{
public:
    Queue();
    ~Queue();
    bool isEmpty();
    void clear();
    int count(){ return size(); }
    void enqueue(const T &value);
    void dequene();
    T &head();
    const T &head() const;
    int size();
    const T &at(int index);
    void swap(Queue<T> &other);
    void reverse();
    Queue<T>&operator += (const T &Value);
    Queue<T> &operator << (const T &Value);
    bool operator == (Queue<T> &other);
    int toPtrVector(T *&Vector);

    //Static members
    static Queue<T> fromPtrVector(const T *const vector, int size);

private:
    Node<T> *First, *Top;

};
#include "Queue.cpp"
#endif // FILA_H
