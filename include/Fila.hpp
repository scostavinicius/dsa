#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>
#include <stdexcept>

#include "Node.hpp"

template <typename Type>
class Fila {
 private:
  Node<Type>* inicio;
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
   */
  void pop();

  /**
   * @brief Retorna o primeiro elemento da fila
   *
   * @return Type
   */
  Type front();

  /**
   * @brief Retorna se a fila está ou não vazia
   *
   * @return true se a fila estiver vazia
   * @return false se a fila não estiver vazia
   */
  bool isEmpty();

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

#endif