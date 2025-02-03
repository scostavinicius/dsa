#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>
#include <stdexcept>

#include "Node.hpp"

template <typename Type>
class Fila {
 private:
  std::unique_ptr<Node<Type>> inicio;
  Node<Type>* fim;
  size_t tamanho;

 public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {};
  Fila(const Fila<Type>& outraFila);
  // Destrutor (implementado mais abaixo)
  ~Fila();

  /**
   * @brief Adiciona um novo elemento na fila
   *
   * @param dado Novo dado que será adicionado na fila
   */
  void push(Type dado);

  /**
   * @brief Remove o primeiro elemento da fila
   *
   * @throw `std::out_of_range` se a fila estiver vazia
   */
  void pop();

  /**
   * @brief Retorna o primeiro elemento da fila
   *
   * @return Type
   *
   * @throw `std::out_of_range` se a fila estiver vazia
   */
  Type front();

  /**
   * @brief Retorna se a fila está ou não vazia
   *
   * @return true se a fila estiver vazia
   * @return false se a fila não estiver vazia
   */
  bool isEmpty() const;

  /**
   * @brief Retorna o tamanho da fila
   *
   * @return size_t
   */
  size_t size();

  /**
   * @brief Limpa (reseta) completamente a fila
   *
   */
  void clear();

  /**
   * @brief Imprime todos elementos da fila
   *
   */
  void print();
};

template <typename Type>
Fila<Type>::Fila(const Fila<Type>& outraFila) : Fila() {
  Node<Type>* atualOrig = outraFila.inicio.get();
  while (atualOrig != nullptr) {
    push(atualOrig->getDado());
    atualOrig = atualOrig->getProximo().get();
  }
}

template <typename Type>
Fila<Type>::~Fila() {
  clear();
}

template <typename Type>
void Fila<Type>::push(Type dado) {
  std::unique_ptr<Node<Type>> novo = std::make_unique<Node<Type>>(dado);
  if (isEmpty()) {
    inicio = std::move(novo);
    fim = inicio.get();
  } else {
    fim->setProximo(novo);
    fim = fim->getProximo().get();
  }
  ++tamanho;
}

template <typename Type>
void Fila<Type>::pop() {
  if (isEmpty()) {
    throw std::out_of_range("A fila está vazia");
  }

  // Mover a posse do nó atual para um ponteiro temporário
  std::unique_ptr<Node<Type>> temp = std::move(inicio);

  // Atualizar o ponteiro "inicio" para apontar para o próximo nó
  inicio = std::move(temp->getProximo());

  // Se a lista ficou vazia após a remoção, atualizar "fim"
  if (!inicio) {
    fim = nullptr;
  }

  --tamanho;
}

template <typename Type>
Type Fila<Type>::front() {
  if (isEmpty()) {
    throw std::out_of_range("A pilha está vazia");
  }

  return inicio->getDado();
}

template <typename Type>
bool Fila<Type>::isEmpty() const {
  return inicio == nullptr;
}

template <typename Type>
size_t Fila<Type>::size() {
  return tamanho;
}

template <typename Type>
void Fila<Type>::clear() {
  inicio.reset();
  fim = nullptr;
  tamanho = 0;
}

template <typename Type>
void Fila<Type>::print() {
  if (isEmpty()) {
    std::cout << "Fila vazia!" << std::endl;
    return;
  }

  Node<Type>* temp = inicio.get();
  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo().get();
  }
  std::cout << std::endl;
}

#endif