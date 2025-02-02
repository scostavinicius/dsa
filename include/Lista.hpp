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

  /**
   * @brief Remove o primeiro elemento da lista
   *
   * @throw `std::out_of_range` se a lista estiver vazia
   */
  void pop_front();

  /**
   * @brief Remove o último elemento da lista
   *
   * @throw `std::out_of_range` se a lista estiver vazia
   */
  void pop_back();

  /**
   * @brief Adiciona um novo elemento no início da lista
   *
   * @param dado Novo dado que será adicionado na lista
   */
  void push_front(Type dado);

  /**
   * @brief Adiciona um novo elemento no final da lista
   *
   * @param dado Novo dado que será adicionado na lista
   */
  void push_back(Type dado);

  /**
   * @brief Adiciona um novo elemento em uma dada posição da lista
   *
   * @param posicao Índice da lista onde será adicionado um novo elemento
   * @param dado Novo dado que será adicionado na lista
   *
   * @throw `std::out_of_range` se a posição for maior que o tamanho da lista
   */
  void insert(size_t posicao, Type dado);

  /**
   * @brief Remove um elemento em uma dada posição da lista
   *
   * @param posicao Índice da lista que será removido
   *
   * @throw `std::out_of_range` se a posição for maior ou igual ao tamanho da
   * lista
   */
  void remove(size_t posicao);

  /**
   * @brief Limpa (reseta) completamente a lista
   *
   */
  void clear();

  /**
   * @brief Inverte todos elementos da lista
   *
   */
  void reverse();

  /**
   * @brief Imprime todos elementos da lista
   *
   */
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
  clear();
}

template <typename Type>
void Lista<Type>::pop_front() {
  if (!primeiro) {
    throw std::out_of_range("A lista está vazia!");
  }

  // Mover a posse do nó atual para um ponteiro temporário
  std::unique_ptr<Node<Type>> temp = std::move(primeiro);

  // Atualizar o ponteiro "primeiro" para apontar para o próximo nó
  primeiro = std::move(temp->getProximo());

  // Se a lista ficou vazia após a remoção, atualizar "ultimo"
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
  Node<Type>* penultimo = primeiro.get();
  while (penultimo->getProximo().get()->getProximo().get()) {
    penultimo = penultimo->getProximo().get();
  }

  // Remover o último nó
  penultimo->getProximo().reset();
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
    temp->setProximo(primeiro);
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
    ultimo->setProximo(temp);
    ultimo = ultimo->getProximo().get();
  }

  ++tamanho;
}

template <typename Type>
void Lista<Type>::insert(size_t posicao, Type dado) {
  if (posicao < 0 || posicao > tamanho) {
    throw std::out_of_range("Posicao invalida (maior que o tamanho da lista)");
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
  Node<Type>* temp = primeiro.get();
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->getProximo().get();
  }

  // O nó temp agora deve apontar para o novo nó e o novo nó deve apontar para o
  // proximo de temp
  std::unique_ptr<Node<Type>> novo = std::make_unique<Node<Type>>(dado);
  novo->setProximo(temp->getProximo());
  temp->setProximo(novo);

  ++tamanho;
}

template <typename Type>
void Lista<Type>::remove(size_t posicao) {
  if (posicao >= tamanho) {
    throw std::out_of_range("Posicao invalida (maior ou igual ao tamanho da lista)");
  }

  // Se a posição for 0, apenas faz o pop_front
  if (posicao == 0) {
    pop_front();
    return;
  }

  // Percorre até o nó anterior ao que será removido
  Node<Type>* temp = primeiro.get();
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->getProximo().get();
  }

  // O nó que será removido
  std::unique_ptr<Node<Type>> toDelete = std::move(temp->getProximo());

  // Corrige o ponteiro do nó anterior para apontar ao próximo do nó removido
  temp->setProximo(toDelete->getProximo());

  --tamanho;
}

template <typename Type>
void Lista<Type>::clear() {
  // Como usamos unique_ptr, basta resetar o ponteiro "primeiro".
  // Depois que "primeiro" é resetado, todos os nós são automaticamente
  // deletados
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
    posterior = std::move(atual->getProximo());
    atual->setProximo(anterior);
    anterior = std::move(atual);
    atual = std::move(posterior);
  }

  primeiro = std::move(anterior);

  // Colocar o último no lugar certo
  ultimo = primeiro.get();
  while (ultimo && ultimo->getProximo()) {
    ultimo = ultimo->getProximo().get();
  }
}

template <typename Type>
void Lista<Type>::print() {
  Node<Type>* temp = primeiro.get();

  if (temp == nullptr) {
    std::cout << "A lista esta vazia!" << std::endl;
    return;
  }

  // Percorre e imprime os elementos da lista
  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo().get();
  }

  std::cout << std::endl;
}

#endif