#ifndef PILHA_HPP
#define PILHA_HPP

#include "Node.hpp"
#include <iostream>
#include <stdexcept>

template<typename Type>
class Pilha
{
private:
  Node<Type>* topo;
  size_t tamanho;

public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Pilha()
    : topo(nullptr)
    , tamanho(0) {};
  Pilha(const Pilha<Type>& outraPilha);
  // Destrutor (implementado mais abaixo)
  ~Pilha();

  // Operações da Pilha
  void pop();
  void push(Type dado);
  Type top();
  size_t size();
  bool isEmpty();
  void clear();
  void reverse();
  void print();
};

template<typename Type>
Pilha<Type>::Pilha(const Pilha<Type>& outraPilha)
  : Pilha()
{
  Node<Type>* temp = outraPilha.topo;

  while (temp != nullptr) {
    push(temp->getDado());
    temp = temp->getProximo();
  }
}

template<typename Type>
Pilha<Type>::~Pilha()
{
  while (!isEmpty()) {
    pop();
  }
}

template<typename Type>
bool
Pilha<Type>::isEmpty()
{
  return topo == nullptr;
}

template<typename Type>
void
Pilha<Type>::pop()
{
  if (isEmpty()) {
    std::cerr << "Erro: Pilha vazia" << std::endl;
    return;
  }

  Node<Type>* temp = topo;
  topo = topo->getProximo();
  delete temp;
  tamanho--;
}

template<typename Type>
void
Pilha<Type>::push(Type dado)
{
  Node<Type>* temp = new Node<Type>(dado);
  temp->setProximo(topo);
  topo = temp;
  tamanho++;
}

template<typename Type>
Type
Pilha<Type>::top()
{
  if (isEmpty()) {
    throw std::runtime_error("Erro: Pilha vazia");
  }

  return topo->getDado();
}

template<typename Type>
size_t
Pilha<Type>::size()
{
  return tamanho;
}

template<typename Type>
void
Pilha<Type>::clear()
{
  while (!isEmpty()) {
    pop();
  }
}

template<typename Type>
void
Pilha<Type>::reverse()
{
  Node<Type>* anterior = nullptr;
  Node<Type>* atual = topo;
  Node<Type>* proximo = nullptr;

  while (atual) {
    proximo = atual->getProximo();
    atual->setProximo(anterior);
    anterior = atual;
    atual = proximo;
  }

  topo = anterior;
}

template<typename Type>
void
Pilha<Type>::print()
{
  Node<Type>* temp = topo;

  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo();
  }
}

#endif