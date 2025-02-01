#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>

#include "Node.hpp"
template <typename Type>
class Lista {
 private:
  std::unique_ptr<Node<Type>> primeiro;
  Node<Type> *ultimo;
  size_t tamanho;

 public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Lista() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {};
  Lista(const Lista<Type> &outraLista);
  // Destrutor (implementado mais abaixo)
  ~Lista();

  void pop_front();
  void pop_back();
  void push_front(Type dado);
  void push_back(Type dado);
  void insert(size_t posicao, Type dado);
  void remove(size_t posicao);
  void clear();
  void reverse();
  void print();
};

template <typename Type>
Lista<Type>::Lista(const Lista<Type> &outraLista) : Lista() {
  Node<Type> *temp = outraLista.primeiro;

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
    throw std::out_of_range("A lista esta vazia!");
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
    throw std::out_of_range("A lista esta vazia!");
  }

  // Se há apenas um nó, limpar toda a lista
  if (tamanho == 1) {
    primeiro.reset();
    ultimo = nullptr;
    tamanho = 0;
    return;
  }

  // Percorrer a lista para encontrar o penúltimo nó
  Node<Type> *penultimo = primeiro.get();
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
  // Cria um novo nó
  std::unique_ptr<Node<Type>> temp = std::make_unique<Node<Type>>(dado);

  // Se a lista estiver vazia
  if (tamanho == 0) {
    primeiro = std::move(temp);
    ultimo = primeiro.get();
  } else {
    // Inserir o novo nó no final da lista
    ultimo->proximo = std::move(temp);
    ultimo = ultimo->proximo.get();
  }

  ++tamanho;
}

template <typename Type>
void Lista<Type>::insert(size_t posicao, Type dado) {
  if (posicao < 0 || posicao > tamanho) {
    throw std::out_of_range(
        "Posicao invalida (menor que 0 ou maior que o tamanho da lista)");
  }

  // Se a posição for 0, apenas faz o push_front
  if (posicao == 0) {
    push_front(dado);
    return;
  }

  // Se a posição for igual ao tamanho da lista, apenas faz o push_back
  if (posicao == tamanho) {
    push_back(dado);
    return;
  }

  // Percorre até o nó anterior à posição desejada
  Node<Type> *temp = primeiro.get();
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->getProximo();
  }

  // O nó temp agora deve apontar para o novo nó e o novo nó deve apontar para o
  // proximo de temp
  std::unique_ptr<Node<Type>> novo = std::make_unique<Node<Type>>(dado);
  novo->setProximo(std::move(temp->proximo));
  temp->setProximo(std::move(novo));

  ++tamanho;
}

template <typename Type>
void Lista<Type>::remove(size_t posicao) {
  if (posicao >= tamanho) {
    throw std::out_of_range(
        "Posicao invalida (maior ou igual ao tamanho da lista)");
  }

  // Se a posição for 0, apenas faz o pop_front
  if (posicao == 0) {
    pop_front();
    return;
  }

  // Percorre até o nó anterior ao que será removido
  Node<Type> *temp = primeiro.get();
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->getProximo();
  }

  // O nó que será removido
  std::unique_ptr<Node<Type>> toDelete = std::move(temp->proximo);

  // Corrige o ponteiro do nó anterior para apontar ao próximo do nó removido
  temp->proximo = std::move(toDelete->proximo);

  --tamanho;
}

template <typename Type>
void Lista<Type>::clear() {
  primeiro.reset();
  tamanho = 0;
}

template <typename Type>
void Lista<Type>::reverse() {
  // Criação dos nós anterior, atual e posterior, nós auxiliares para reverter a
  // lista
  std::unique_ptr<Node<Type>> anterior = nullptr;
  std::unique_ptr<Node<Type>> atual = std::move(primeiro);
  std::unique_ptr<Node<Type>> posterior = nullptr;

  // Percorre a lista e inverte os ponteiros
  while (atual) {
    posterior = std::move(atual->proximo);
    atual->proximo = std::move(anterior);
    anterior = std::move(atual);
    atual = std::move(posterior);
  }

  primeiro = std::move(anterior);
  ultimo = primeiro.get();

  while (ultimo && ultimo->proximo) {
    ultimo = ultimo->proximo.get();
  }
}

template <typename Type>
void Lista<Type>::print() {
  Node<Type> *temp = lista.getPrimeiro();

  if (temp == nullptr) {
    std::cout << "A lista está vazia!" << std::endl;
    return;
  }

  // Percorre e imprime os elementos da lista
  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo();
  }

  std::cout << std::endl;
}

#endif