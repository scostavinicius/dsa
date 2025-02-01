#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>

#include "Node.hpp"

template <typename Type>
class Lista {
 private:
  std::unique_ptr<Node<Type>> primeiro;
  Node<Type>* ultimo;
  size_t tamanho;

 public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Lista() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {};
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

template <typename Type>
Lista<Type>::Lista(const Lista<Type>& outraLista) : Lista() {
  Node<Type>* temp = outraLista.primeiro;

  while (temp != nullptr) {
    push_back(temp->getDado());
    temp = temp->getProximo();
  }
}

template <typename Type>
Lista<Type>::~Lista() {
  // Como usamos unique_ptr, basta resetar o ponteiro "primeiro".
  // Depois que "primeiro" é resetado, todos os nós são automaticamente
  // deletados
  primeiro.reset();
  tamanho = 0;
}

template <typename Type>
void Lista<Type>::pop_front() {
  if (tamanho == 0) {
    throw std::out_of_range("A lista está vazia!");
  }

  // Mover o ponteiro para o próximo nó.
  // Quando "temp" sair de escopo, o antigo nó "primeiro" será automaticamente
  // deletado
  std::unique_ptr<Node<Type>> temp = std::move(primeiro);
  primeiro = std::move(temp->proximo);

  // Se a lista ficou vazia após a remoção, atualizar 'ultimo'
  if (!primeiro) {
    ultimo = nullptr;
  }

  --tamanho;
}

template <typename Type>
void Lista<Type>::pop_back() {
  if (tamanho == 0) {
    throw std::out_of_range("A lista está vazia!");
  }

  // Se há apenas um nó, limpar toda a lista
  if (tamanho == 1) {
    primeiro.reset();
    ultimo = nullptr;
    tamanho = 0;
    return;
  }

  // Percorrer a lista para encontrar o penúltimo nó
  Node<Type>* penultimo = primeiro.get();
  while (penultimo->proximo->proximo) {
    penultimo = penultimo->proximo.get();
  }

  // Remover o último nó
  penultimo->proximo.reset();
  ultimo = penultimo;
  --tamanho;
}

template <typename Type>
void Lista<Type>::push_front(Type dado) {
  // Criar um novo nó
  std::unique_ptr<Node<Type>> temp = std::make_unique<Node<Type>>(dado);

  // Se a lista estiver vazia
  if (tamanho == 0) {
    primeiro = std::move(temp);
    ultimo = primeiro.get();
  } else {
    // Inserir o novo nó na frente da lista
    temp->proximo = std::move(primeiro);
    primeiro = std::move(temp);
  }

  ++tamanho;
}

template <typename Type>
void Lista<Type>::push_back(Type dado) {
  Node<Type>* temp = new Node<Type>(dado);

  if (lista.getTamanho() == 0) {
    lista.setPrimeiro(temp);
    lista.setUltimo(temp);
    lista.setTamanho(lista.getTamanho() + 1);
    return;
  }

  lista.getUltimo()->setProximo(temp);
  lista.setUltimo(temp);
  lista.setTamanho(lista.getTamanho() + 1);
}

template <typename Type>
void Lista<Type>::insert(int posicao, Type dado) {
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

template <typename Type>
void Lista<Type>::remove(int posicao) {
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

template <typename Type>
void Lista<Type>::clear() {
  ~Lista();
}

template <typename Type>
void Lista<Type>::reverse() {
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

template <typename Type>
void Lista<Type>::print() {
  Node<Type>* temp = lista.getPrimeiro();

  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo();
  }

  std::cout << std::endl;
}

#endif