#ifndef LIST_H
#define LIST_H
#include "Node.h"
using namespace myNode;


namespace myList {
template <typename T> class List
{
public:
    List();
    List(const List<T> &other);
    ~List();
    void append(const T &value);
    void append(const List<T> &value);
    const T &at(int i) const;
    void clear();
    bool contains(const T &value) const;
    int count(const T &value) const;
    int count() const;
    bool endsWith(const T &value) const;
    T &first();
    const T &first() const;
    int indexOf(const T &value, int from = 0) const;
    void insert(int i, const T &value);
    bool isEmpty() const;
    T &last();
    const T &last() const;
    int	lastIndexOf(const T &value, int from = -1 ) const;
    int	length() const;
    List<T> mid(int pos, int length = -1) const;
    void move(int from, int to);
    void prepend(const T &value);
    int	removeAll(const T &value);
    void removeAt(int i);
    void removeFirst();
    void removeLast();
    bool removeOne(const T &value);
    void replace(int i, const T &value);
    int	size()const;
    bool startsWith(const T &value) const;
    void swap(List<T> &other);
    void swap(int i, int j);
    T takeAt(int i);
    T takeFirst();
    T takeLast();
    int toVector(T *&vector) const;
    T value(int i) const;
    T value(int i, const T &defaultValue) const;
    bool operator != (const List<T> &other) const;
    List<T> operator + (const List<T> &other) const;
    List<T> &operator += (const List<T> &other);
    List<T> &operator += (const T &value);
    List<T> &operator << (const List<T> &other);
    List<T> &operator << (const T &value);
    bool operator == (const List<T> &other) const;
    T &operator[] (int i);
    const T &operator[] (int i) const;

    //Static members
    static List<T> fromPtrVector(const T * const vector, int size);

protected:
    Node<T> *atNode(int index) const;
    Node<T> *First;
};

#include "List.cpp"
}
#endif // LISTA_H
