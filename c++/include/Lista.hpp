#ifndef LISTA_HPP
#define LISTA_HPP

#include "Node.hpp"
#include <iostream>

template<typename Type>
class Lista
{
private:
  Node<Type>* primeiro;
  Node<Type>* ultimo;
  size_t tamanho;

public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Lista()
    : primeiro(nullptr)
    , ultimo(nullptr)
    , tamanho(0) {};
  Lista(const Lista<Type>& outraLista);
  // Destrutor (implementado mais abaixo)
  ~Lista();

  void pop_front();
  void pop_back();
  void push_front(Type dado);
  void push_back(Type dado);
  void insert(int posicao, Type dado);
  void remove(int posicao);
  void clear();
  void reverse();
  void print();
};

template<typename Type>
Lista<Type>::Lista(const Lista<Type>& outraLista)
  : Lista()
{
  Node<Type>* temp = outraLista.primeiro;

  while (temp != nullptr) {
    push_back(temp->getDado());
    temp = temp->getProximo();
  }
}

template<typename Type>
Lista<Type>::~Lista()
{
  Node<Type>* temp = lista.getPrimeiro();
  Node<Type>* temp2 = lista.getPrimeiro();

  while (temp != nullptr) {
    temp2 = temp->getProximo();
    delete temp;
    temp = temp2;
  }

  lista.setPrimeiro(nullptr);
  lista.setUltimo(nullptr);
  lista.setTamanho(0);
}

template<typename Type>
void
Lista<Type>::pop_front()
{
  if (lista.getTamanho() == 0) {
    std::cout << "Lista vazia" << std::endl;
    return;
  }

  Node<Type>* temp = lista.getPrimeiro();
  lista.setPrimeiro(lista.getPrimeiro()->getProximo());
  delete temp;

  lista.setTamanho(lista.getTamanho() - 1);
}

template<typename Type>
void
Lista<Type>::pop_back()
{
  if (lista.getTamanho() == 0) {
    std::cout << "Lista vazia" << std::endl;
    return;
  }

  Node<Type>* temp = lista.getUltimo();
  Node<Type>* temp2 = lista.getPrimeiro();

  while (temp2->getProximo() != temp) {
    temp2 = temp2->getProximo();
  }

  temp2->setProximo(nullptr);
  delete temp;

  lista.setUltimo(temp2);
}

template<typename Type>
void
Lista<Type>::push_front(Type dado)
{
  Node<Type>* temp = new Node<Type>(dado);

  if (lista.getTamanho() == 0) {
    lista.setPrimeiro(temp);
    lista.setUltimo(temp);
    lista.setTamanho(1);
    return;
  }

  temp->setProximo(lista.getPrimeiro());
  lista.setPrimeiro(temp);

  lista.setTamanho(lista.getTamanho() + 1);
}

template<typename Type>
void
Lista<Type>::push_back(Type dado)
{
  Node<Type>* temp = new Node<Type>(dado);

  if (lista.getTamanho() == 0) {
    lista.setPrimeiro(temp);
    lista.setUltimo(temp);
    lista.setTamanho(lista.getTamanho() + 1);
  }

  lista.getUltimo()->setProximo(temp);
  lista.setUltimo(temp);
  lista.setTamanho(lista.getTamanho() + 1);
}

template<typename Type>
void
Lista<Type>::insert(int posicao, Type dado)
{
  if (posicao < 0 || posicao > lista.getTamanho()) {
    std::cout << "Posicao invalida" << std::endl;
  }

  if (posicao == 0) {
    lista.push_front(lista, dado);
    return;
  }

  if (posicao == lista.getTamanho()) {
    lista.push_back(lista, dado);
  }

  Node<Type>* temp = lista.getPrimeiro();
  Node<Type>* temp2 = new Node<Type>(dado);

  for (int i = 0; i < posicao; ++i) {
    temp = temp->getProximo();
  }

  temp2->setProximo(temp->getProximo());
  temp->setProximo(temp2);

  lista.setTamanho(lista.getTamanho() + 1);
}

template<typename Type>
void
Lista<Type>::remove(int posicao)
{
  if (posicao < 0 || posicao >= lista.getTamanho()) {
    std::cout << "Posicao invalida" << std::endl;
    return;
  }

  if (posicao == 0) {
    lista.pop_front(lista);
    return;
  }

  if (posicao == lista.getTamanho() - 1) {
    lista.pop_back(lista);
    return;
  }

  Node<Type>* temp = lista.getPrimeiro();
  Node<Type>* temp2 = lista.getPrimeiro();

  for (int i = 0; i < posicao; ++i) {
    temp = temp->getProximo();
  }

  for (int i = 0; i < posicao - 1; ++i) {
    temp2 = temp2->getProximo();
  }

  temp2->setProximo(temp->getProximo());
  delete temp;

  lista.setTamanho(lista.getTamanho() - 1);
}

template<typename Type>
void
Lista<Type>::clear()
{
  ~Lista();
}

template<typename Type>
void
Lista<Type>::reverse()
{
  Node<Type>* anterior = nullptr;
  Node<Type>* atual = lista.getPrimeiro();
  Node<Type>* proximo = nullptr;

  while (atual != nullptr) {
    proximo = atual->getProximo();
    atual->setProximo(anterior);
    anterior = atual;
    atual = proximo;
  }

  lista.setPrimeiro(anterior);
}

template<typename Type>
void
Lista<Type>::print()
{
  Node<Type>* temp = lista.getPrimeiro();

  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo();
  }

  std::cout << std::endl;
}

#endif