/***************************************************************
 * Criação: Jonlenes Silva de Castro/Aluno do 3º período de
 *          ciência da computação.
 * Data de inicio: 07/01/2015
 * Data de conclusão total: 11/01/2014
 * Propósito: Implatação dos métodos que compoem uma lista.
 * ************************************************************/

#ifndef LIST_CPP
#define LIST_CPP
//#define No Node<T>
#define Template template <typename T>
#include "List.h"
using namespace std;
using namespace myList;


Template List<T>::List()
{
    First = NULL;
}

Template List<T>::List(const List<T> &other)
{
    First = NULL;
    *this << other;
}

Template List<T>::~List()
{
    Node<T> *no;
    while(First){
        no = First;
        First = First->GetNext();
        delete no;
    }
    delete First;
}

Template void List<T>::append(const T &value)
{
    /****************************************
 *Adiciona o valor no final da lista
 ***************************************/

    Node<T> *no = new Node<T>;
    no->SetValue(value);

    if(isEmpty())
        First = no;
    else
    {
        Node<T> *Aux = First;
        while(Aux->GetNext()) {
            Aux = Aux->GetNext();
        }
        Aux->SetNext(no);
    }
}

Template void List<T>::append(const List<T> &value )
{
    /****************************************
 *Adiciona a lista passada ao final da
 *lista atual
 ***************************************/

    *this += value;
}

Template T const &List<T>::at(int index) const
{
    /****************************************
 *Retorna o elemento de posção index na lista.
 ***************************************/

    if(index < 0 || index >= size())
        throw string("at - index fora do intervalo" + index);
    int i = 0;
    Node<T> *Aux = First;
    while(i < index) {
        Aux = Aux->GetNext();
        i++;
    }
    return (*Aux).GetValue();
}

Template Node<T> *List<T>::atNode(int index) const
{
    /*****************************************
 * Retorna o Node da posção index na lista.
 * Esse método é protected e será utilizado
 * apenas internamente.
 ***************************************/

    if(index < 0 || index >= size())
        throw string("atNode - index fora do intervalo");
    int i = 0;
    Node<T> *Aux = First;
    while(i < index) {
        Aux = Aux->GetNext();
        i++;
    }
    return Aux;
}

Template void List<T>::clear()
{
    /****************************************
 *Limpa a lista
 ***************************************/
    *this = List<T>();
}

Template bool List<T>::contains(const T &value) const
{
    /****************************************
 *Verifica se o valor passado existe na
 * lista
 * Obs.: Se for uma lista de objetos é
 * necessário que o mesmo tenho uma
 * sobrecarga de operator != (Tipo Objeto)
 ***************************************/

    Node<T> *Aux = First;
    while (Aux && Aux->GetValue() != value) {
        Aux = Aux->GetNext();
    }
    if(!Aux)
        return false;
    return true;
}

Template int List<T>::count(const T &value) const
{
    /****************************************
 *Retorna a quantidade de vezes que o va_
 * lue apareçe na lista.
 ***************************************/

    Node<T> *Aux = First;
    int count = 0;
    while (Aux) {
        if(Aux->GetValue() == value){
            count++;
        }
        Aux = Aux->GetNext();
    }
    return count;
}

Template int List<T>::count() const
{
    /****************************************
 *Retorna a qtde de itens na lista
 ***************************************/

    return size();
}

Template bool List<T>::endsWith(const T &value) const
{
    /****************************************
 * Verifica se o ultimo elemento da lista
 * possui valor value.
 * Obs.: Se for uma lista de objetos é
 * necessário que a mesma possua uma
 * sobrecarga de operator ==(type class)
 * *************************************/

    return (at(size() - 1) == value);
}

Template T &List<T>::first()
{
    /****************************************
 * Retona uma referencia do primeiro ele_
 * mento da lista.
 * *************************************/

    if(isEmpty())
        throw string("first - Lista vazia!");

    return (First->GetValue());
}

Template const T &List<T>::first() const
{
    /****************************************
 * Retona uma referencia constante do
 * primeiro elemento da lista.
 * *************************************/

    if(isEmpty())
        throw string("first - Lista vazia!");
    return First->GetValue();
}

Template int List<T>::indexOf(const T &value, int from) const
{
    /*****************************************
 * Retorna o index da primeira ocorrencia
 * de value na lista, começando a parti de
 * from. Retorna -1 se o item não for
 * encontrado.
 * **************************************/

    if(from < 0)
        from = max(from + size(), 0);
    if(from < size()){
        Node<T> *Aux = atNode(from);
        int index = from;
        while (Aux) {
            if(Aux->GetValue() == value)
                return index;
            Aux = Aux->GetNext();
            index++;
        }
    }
    return -1;
}

Template void List<T>::insert(int index, const T &value)
{
    /******************************************
 * Insere o elemento value na posição index
 * ***************************************/

    if(index < 0 || index > size())
        throw string("insert - index de inserceção inválido.");
    int count = 0;

    Node<T> *NoAux = First, *NoPrev = NULL, *NoNew = new Node<T>;
    NoNew->SetValue(value);

    while (NoAux && count < index) {
        NoPrev = NoAux;
        NoAux = NoAux->GetNext();
        count++;
    }
    if (NoPrev) NoPrev->SetNext(NoNew); else First = NoNew;
    NoNew->SetNext(NoAux);
}

Template bool List<T>::isEmpty() const
{
    /****************************************
 *Retorna verdadeiro caso a lista esteja
 * vazia
 ***************************************/

    return (!First);
}

Template T &List<T>::last()
{
    /****************************************
 * Retona uma referencia do ultimo eleme_
 * mento da lista.
 * *************************************/

    if(isEmpty())
        throw string("last - Lista vazia!");

    return atNode(size() - 1)->GetValue();
}

Template const T &List<T>::last() const
{
    /****************************************
 * Retona uma referencia constante do
 * ultimo elemento da lista.
 * *************************************/

    if(isEmpty())
        throw string("last - Lista vazia!");
    return at(size() - 1);

}

Template int List<T>::length() const
{
    /****************************************
 *Retorna a qtde de itens na lista
 ***************************************/

    return count();
}

Template List<T> List<T>::mid(int pos, int length) const
{
    /****************************************
 * Retorna uma lista cujos elementos são
 * copiados a partir dessa lista, iniciando
 * na posição pos. Se o comprimento for
 * -1, todos os elementos de pos são
 * copiados; caso contrário comprimento
 * j   (ou todos os elementos
 * remanescentes, se houver menos do que
 * comprimento elementos) são copiados
 * *************************************/

    if(pos < 0 || pos >= size())
        throw string("mid - posição fora do intervalo.");

    List<T> ListAux;
    Node<T> *NoAux = atNode(pos);

    if(length == -1)
        length = size();
    length += pos;
    while (NoAux && pos < length) {
        ListAux.append(NoAux->GetValue());
        NoAux = NoAux->GetNext();
        pos++;
    }
    return ListAux;
}

Template void List<T>::move(int from, int to)
{
    /***************************************
 * Move o item da posição from para a
 * posição to.
 * ************************************/

    try{
        insert(to, takeAt(from));
    }catch(...){
        throw string("move - posição fora do intervalo.");
    }
}

Template void List<T>::prepend(const T &value)
{
    /***************************************
 * Insere o elemento no First da lista
 * ************************************/

    insert(0, value);
}

Template int List<T>::removeAll(const T &value)
{
    /***************************************
 * Remover todas as ocorrencias de value
 * da lista e retorna a qtde de
 * ocorrencias.
 * Obs.: Esse método pode facilmente ser
 * refeito de forma mais otimizada.
 * ************************************/

    int index = indexOf(value);
    int  count = 0;
    while(index != -1) {
        removeAt(index);
        count++;
        index = indexOf(value);
    }
    return count;
}

Template void List<T>::removeAt(int index)
{
    /*************************************
 * Remove o elemento de index index na
 * lista.
 * **********************************/

    if(index < 0 || index >= size())
        throw string("removeAt - index fora do intervalo.");
    int count = 0;
    Node<T> *NoAux = First, *NoAnt = NULL;
    while(count < index) {
        NoAnt = NoAux;
        NoAux = NoAux->GetNext();
        count++;
    }
    if(NoAnt)
        NoAnt->SetNext(NoAux->GetNext());
    else
        First = NoAux->GetNext();

    delete NoAux;
}

Template void List<T>::removeFirst()
{
    /*************************************
 * Remove o primeiro elemento da lista.
 * **********************************/

    try{
        removeAt(0);
    }catch(...){
        throw string("removeFirst - lista vazia.");
    }
}

Template void List<T>::removeLast()
{
    /*************************************
 * Remove o ultimo elemento da lista.
 * **********************************/

    try{
        removeAt(size() - 1);
    }catch(...){
        throw string("removeLast - lista vazia.");
    }
}

Template bool List<T>::removeOne(const T &value)
{
    /******************************************
 * Remove a primeira ocorrencia de value na
 * lista.
 * ***************************************/

    int index = indexOf(value);
    if(index != -1) {
        removeAt(index);
        return true;
    }
    return false;
}

Template void List<T>::replace(int index, const T &value)
{
    /******************************************
 * Substitui o elemento da posição index
 * por value.
 * ***************************************/
    try{
        Node<T> *NoAux = atNode(index);
        NoAux->SetValue(value);
    }catch(...){
        throw string("replace - index fora do intervalo.");
    }
}

Template int List<T>::size()const
{
    /*****************************************
 * Retorna o tamanho da lista.
 * **************************************/

    int count = 0;
    Node<T> *Aux = First;
    while(Aux){
        count++;
        Aux = Aux->GetNext();
    }
    return count;
}

Template bool List<T>::startsWith(const T &value) const
{
    /*********************************************
 * Retorna true se a lista não for vazia e o
 * seu primeiro elemento seja igual a value.
 * ******************************************/

    return (!isEmpty() && First->GetValue() == value);
}

Template void List<T>::swap(List<T> &other)
{
    /**********************************************
 * Troca esta lista pela other.
 * *******************************************/

    Node<T> *NoAux = other.First;
    other.First = First;
    First = NoAux;
}

Template void List<T>::swap(int i, int j)
{
    /**********************************************
 * Troca o elemento da posição i com o elemento
 * com o elemento da posição j.
 * *******************************************/

    if(i < 0 || i >= size()
            || j < 0 || j >= size())
        throw string("swap - posição fora do intervalo.");
    T valuePosI = value(i);
    T valuePosJ = value(j);
    replace(i, valuePosJ);
    replace(j, valuePosI);
}

Template T List<T>::takeAt(int index)
{
    /**********************************************
 * Remove e retorna o elemento na posição index.
 * *******************************************/

    if(index < 0 || index >= size())
        throw string("takeAt - index fora do intervalo.");
    T Value = at(index);
    removeAt(index);
    return Value;
}

Template T List<T>::takeFirst()
{
    /**********************************************
 * Remove e retorna o primeiro elemento.
 * *******************************************/

    try{
        T Value = at(0);
        removeAt(0);
        return Value;
    }catch(...) {
        throw string("takeFirst - lista vazia.");
    }
}

Template T List<T>::takeLast()
{
    /**********************************************
 * Remove e retorna o ultimo elemento.
 * *******************************************/

    try{
        T Value = at(size() - 1);
        removeAt(size() - 1);
        return Value;
    }catch(...) {
        throw string("takeLast - lista vazia.");
    }
}

Template int List<T>::toVector(T *&Vect) const
{
    /*******************************************
 * Retorna o endereço de um vetor com todos
 * os elementos da lista por referencia e o
 * tamanho do mesmo por return.
 * ****************************************/

    Vect = new T[size()];
    for(int i = 0; i < size(); i++)
    {
        Vect[i] = at(i);
    }
    return size();
}

Template T List<T>::value(int index) const
{
    /*****************************************
 * Retorna o value na posição index
 * **************************************/

    try{
        return at(index);
    }catch(...) {
        throw string("value - index fora do intervalo.");
    }
}

Template T List<T>::value(int index, const T &defaultValue) const
{
    /*****************************************
 * Retorna o value na posição index. Se o
 * index está fora do intervalo, então ele
 * retorna defaultValue.
 * **************************************/

    try{
        return at(index);
    }catch(...) {
        return defaultValue;
    }
}

Template bool List<T>::operator != (const List<T> &other) const
{
    /*****************************************
 * Retorna true se as mesmas possuim tamanhos ou
 * elemento diferentes.
 * **************************************/

    return (!(*this == other));
}

Template List<T> List<T>::operator + (const List<T> &other) const
{
    /*****************************************
 * Retorna a soma das duas listas
 * **************************************/

    List<T> ListAux;
    ListAux += *this;
    ListAux += other;
    return ListAux;
}

Template List<T> &List<T>::operator += (const List<T> &other)
{
    /*****************************************
 * Adiciona os elementos de other ao final
 * desta lista.
 * **************************************/

    if(!other.isEmpty())
    {
        for(int i = 0; i < other.size(); i++)
            append(other.value(i));
    }
    return *this;
}

Template List<T> &List<T>::operator += (const T &value)
{
    /*****************************************
 * Adiciona value ao final da lista.
 * **************************************/

    append(value);
    return *this;
}

Template List<T> &List<T>::operator << (const List<T> &other)
{
    /*****************************************
 * Adiciona a lista other ao final desta
 * lista.
 * **************************************/

    *this += other;
    return *this;
}

Template List<T> &List<T>::operator << (const T &value)
{
    /*****************************************
 * Adiciona value ao final da lista.
 * **************************************/

    append(value);
    return *this;
}

Template bool List<T>::operator == (const List<T> &other) const
{
    /*****************************************
 * Verifica se ao duas lista são iguais.
 * **************************************/

    if(size() != other.size())
        return false;
    for(int i = 0; i < size(); i++) {
        if(at(i) != other.at(i))
            return false;
    }
    return true;
}

Template T &List<T>::operator[] (int index)
{
    /*****************************************
 * Retorna o valor na posição index.
 * **************************************/

    return ((T &) at(index));
}

Template const T &List<T>::operator [](int index) const
{
    /*****************************************
 * Retorna o valor na posição index.
 * **************************************/

    return (at(index));
}

/*static*/Template List<T> List<T>::fromPtrVector(const T *const vector, int size)
{
    List<T> ListAux;
    for(int i = 0; i < size; i++)
        ListAux.append(vector[i]);
    return ListAux;
}
#endif
