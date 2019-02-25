#ifndef FILA_CPP
#define FILA_CPP

#include "Queue.h"
#include <stack>

template <class T> Queue<T>::Queue()
{
    First = NULL;
    Top = NULL;
}

template <class T> Queue<T>::~Queue()
{
    Node<T> *aux;
    while(First){
        aux = First;
        First = First->GetNext();
        delete aux;
    }
    delete First;
}

template <class T> bool Queue<T>::isEmpty()
{
    return (!First);
}

template <class T> void Queue<T>::clear()
{
    *this = Queue<T>();
}

template <class T> void Queue<T>::enqueue(const T &value)
{
    Node<T> *no = new Node<T>;
    no->SetValue(value);

    if(isEmpty()) First = no; else Top->SetNext(no);
    Top = no;
}

template <class T> void Queue<T>::dequene()
{
    if(isEmpty())
        throw string("dequene - fila vazia");
    Node<T> *no = First;
    First = First->GetNext();
    if(isEmpty())
        Top = NULL;
    delete no;
}

template <class T> T &Queue<T>::head()
{
    if(isEmpty())
        throw string("head - fila vazia");
    return First->GetValue();
}

template <class T> const T &Queue<T>::head() const
{
    if(isEmpty())
        throw string("head - fila vazia");
    return First->GetValue();
}


template <class T> int Queue<T>::size()
{
    int count = 0;
    for(Node<T> *NoAux = First; NoAux; NoAux = NoAux->GetNext())
        count++;
    return count;
}

template <class T> const T &Queue<T>::at(int index)
{
    if(index < 0 || index >= size())
        throw string("at - index fora do intervalo válido.");
    Node<T> *NoAux = First;
    for(int i = 0; (i != index && NoAux); i++)
        NoAux = NoAux->GetNext();
    return NoAux->GetValue();
}
template <class T> void Queue<T>::swap(Queue<T> &other)
{
    Node<T> *NoAuxFister = other.First;
    Node<T> *NoAuxTop = other.Top;
    other.Top = Top;
    other.First = First;
    First = NoAuxFister;
    Top = NoAuxTop;
}

template <class T> void Queue<T>::reverse()
{
    stack<T> *stackAux = new stack<T>;

    while(!isEmpty()) {
        stackAux->push(head());
        dequene();
    }
    while (!stackAux->empty()) {
        enqueue(stackAux->top());
        stackAux->pop();
    }
    delete stackAux;
}

template <class T> Queue<T> &Queue<T>::operator += (const T &Value)
{
    enqueue(Value);
    return *this;
}

template <class T> Queue<T> &Queue<T>::operator << (const T &Value)
{
    enqueue(Value);
    return *this;
}

template <class T> bool Queue<T>::operator == (Queue<T> &other)
{
    if(count() != other.count())
        return false;
    Node<T> *NoThis = First;
    Node<T> *NoOther = other.First;

    while (NoThis) {
        if(NoThis->GetValue() != NoOther->GetValue())
            return false;
        NoThis = NoThis->GetNext();
        NoOther = NoOther->GetNext();
    }
    return true;
}

template <class T> int Queue<T>::toPtrVector(T *&Vector)
{
    int i = 0;
    int coun = count();
    Node<T> *NoAux = First;
    if(coun == 0) { Vector = NULL; return 0; }
    Vector = new T[coun];

    while (NoAux) {
        Vector[i] = NoAux->GetValue();
        NoAux = NoAux->GetNext();
        i++;
    }
    return coun;
}

/*Static*/ template <class T> Queue<T> Queue<T>::fromPtrVector(const T *const vector, int size)
{
    Queue<T> QueueAux;
    for(int i = 0; i < size; i++)
        QueueAux.enqueue(vector[i]);
    return QueueAux;
}

#endif
