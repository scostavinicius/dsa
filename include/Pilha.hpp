#ifndef PILHA_HPP
#define PILHA_HPP

#include <iostream>
#include <stdexcept>

#include "Node.hpp"

template <typename Type>
class Pilha {
 private:
  Node<Type>* topo;
  size_t tamanho;

 public:
  // Construtores (o construtor cópia é implementado mais abaixo)
  Pilha() : topo(nullptr), tamanho(0) {};
  Pilha(const Pilha<Type>& outraPilha);
  // Destrutor (implementado mais abaixo)
  ~Pilha();

  /**
   * @brief Remove o último elemento da pilha
   *
   */
  void pop();

  /**
   * @brief Adiciona um elemento no final da pilha
   *
   * @param dado
   */
  void push(Type dado);

  /**
   * @brief Retorna o último elemento da pilha
   *
   * O último elemento da pilha é o próximo a ser removido
   *
   * @return Type
   */
  Type top();

  /**
   * @brief Retorna o tamanho da pilha
   *
   * @return size_t
   */
  size_t size();

  /**
   * @brief Retorna se a pilha está ou não vazia
   *
   * @return true se a pilha estiver vazia
   * @return false se a pilha não estiver vazia
   */
  bool isEmpty();

  /**
   * @brief Limpa (reseta) completamente a pilha
   *
   */
  void clear();

  /**
   * @brief Imprime todos elementos da pilha
   *
   */
  void print();
};

template <typename Type>
Pilha<Type>::Pilha(const Pilha<Type>& outraPilha) : Pilha() {
  Node<Type>* temp = outraPilha.topo;

  while (temp != nullptr) {
    push(temp->getDado());
    temp = temp->getProximo();
  }
}

template <typename Type>
Pilha<Type>::~Pilha() {
  while (!isEmpty()) {
    pop();
  }
}

template <typename Type>
bool Pilha<Type>::isEmpty() {
  return topo == nullptr;
}

template <typename Type>
void Pilha<Type>::pop() {
  if (isEmpty()) {
    std::cerr << "Erro: Pilha vazia" << std::endl;
    return;
  }

  Node<Type>* temp = topo;
  topo = topo->getProximo();
  delete temp;
  tamanho--;
}

template <typename Type>
void Pilha<Type>::push(Type dado) {
  Node<Type>* temp = new Node<Type>(dado);
  temp->setProximo(topo);
  topo = temp;
  tamanho++;
}

template <typename Type>
Type Pilha<Type>::top() {
  if (isEmpty()) {
    throw std::runtime_error("Erro: Pilha vazia");
  }

  return topo->getDado();
}

template <typename Type>
size_t Pilha<Type>::size() {
  return tamanho;
}

template <typename Type>
void Pilha<Type>::clear() {
  while (!isEmpty()) {
    pop();
  }
}

template <typename Type>
void Pilha<Type>::print() {
  Node<Type>* temp = topo;

  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo();
  }
}

#endif