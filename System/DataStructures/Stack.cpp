/***************************************************************
 * Criação: Jonlenes Silva de Castro/Aluno do 3º período de
 *          ciência da computação.
 * Data de inicio: 18/01/2015
 * Data de conclusão total: --/--/----
 * Detalhes:
 * Propósito: Implatação dos métodos que compoem uma pilha.
 * ************************************************************/

#ifndef PILHA_CPP
#define PILHA_CPP
#include "Stack.h"

template <class T> Stack<T>::Stack()
{
    Top = NULL;
}

template <class T> Stack<T>::~Stack()
{
    Node<T> *no;
    while(Top){
        no = Top;
        Top = Top->GetPrevious();
        delete no;
    }
    delete Top;
}

template <class T> bool Stack<T>::isEmpty() const
/**************************************
 * Retorna true se a Pilha estiver vazia.
 * ***********************************/
{
    return (!Top);
}

template <class T> void Stack<T>::clear()
/**************************************
 * Limpa apilha.
 * ***********************************/
{
    *this = Stack<T>();
}

template <class T> void Stack<T>::push(const T &Value)
/**************************************
 * Adiciona elementos a pilha.
 * ***********************************/
{
    Node<T> *no = new Node<T>;
    no->SetValue(Value);

    no->SetPrevious(Top);
    Top = no;
}

template <class T> void Stack<T>::pop()
/**************************************
 * Remove elementos da pilha.
 * ***********************************/
{
    if(isEmpty())
        throw string("pilha vazia.");

    Node<T> *no = Top;
    Top = Top->GetPrevious();
    delete no;
}

template <class T> T &Stack<T>::top()
/**************************************
 * Retorna a refêrencia do topo.
 * ***********************************/
{
    if(isEmpty())
        throw string("pilha vazia.");

   return Top->GetValue();
}

template <class T> const T &Stack<T>::top() const
/**************************************
 * Retorna uma refêrencia constante do
 * topo.
 * ***********************************/
{
    if(isEmpty())
        throw string("top - pilha vazia.");

   return Top->GetValue();
}

template <class T> int Stack<T>::size()
/**************************************
 * Retorna o tamanho da pilha.
 * ***********************************/
{
    int count = 0;
    for(Node<T> *no = Top; no; no = no->GetPrevious())
        count++;
    return count;
}

template <class T> void Stack<T>::swap(Stack<T> &other)
/**************************************
 * Troca a pilha atul com a other.
 * ***********************************/
{
    Node<T> *NoAux = other.Top;
    other.Top = Top;
    Top = NoAux;
}

template <class T> void Stack<T>::reverse()
/**************************************
 * Inverte a pilha atual
 * ***********************************/
{
    Stack<T> *stackAux = new Stack<T>;

    while(!isEmpty()) {
        stackAux->push(top());
        pop();
    }
    swap(*stackAux);
    delete stackAux;
}

template <class T> Stack<T> &Stack<T>::operator += (const T &Value)
/**************************************
 * Adiciona o Value a pilha.
 * ***********************************/
{
    push(Value);
    return *this;
}

template <class T> Stack<T> &Stack<T>::operator << (const T &Value)
/**************************************
 * Adiciona o Value a pilha.
 * ***********************************/
{
    push(Value);
    return *this;
}

template <class T> bool Stack<T>::operator == (Stack<T> &other)
/**************************************
 * Retorna true se as pilhas forem iguais.
 * ***********************************/
{
    if(size() != other.size())
        return false;
    T *Stack1;
    toPtrVector(Stack1);
    T *Stack2;
    other.toPtrVector(Stack2);
    for(int i = 0; i < size(); i++) {
        if(Stack1[i] != Stack2[i])
            return false;
    }
    return true;
}

template <class T> int Stack<T>::toPtrVector(T *&Vector)
/**************************************
 * Retorna o endereço de um vetor com
 * todos os elementos da pilha por
 * referencia e o tamanho do mesmo por
 * return.
 * ***********************************/
{
    int cou = count();
    int i = cou - 1;
    if(i < 0){ Vector = NULL; return -1; }
    Vector = new T[ cou ];
    for(Node<T> *NoI = Top; NoI; NoI = NoI->GetPrevious(), i--)
        Vector[i] = NoI->GetValue();
    return cou;
}

/*static*/ template <class T> Stack<T> Stack<T>::fromPtrVector(const T *const vector, int size)
/**************************************
 * Retorna uma pilha com os elementos
 * contidos no vetor.
 * ***********************************/
{
    Stack<T> StackAux;
    for(int i = 0; i < size; i++)
        StackAux.push(vector[i]);
    return StackAux;
}

#endif
