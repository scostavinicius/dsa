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

  // Operações da Fila
  void push(Type dado);
  void pop();
  void front();
  void back();
  bool isEmpty();
  size_t size();
  void clear();
  void reverse();
  void print();
};

#endif