#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

template <typename Type>
class Node {
 private:
  Type dado;
  std::unique_ptr<Node<Type>> proximo;

 public:
  Node() : proximo(nullptr) {};
  Node(Type dado) : dado(dado), proximo(nullptr) {};
  Node(Type dado, std::unique_ptr<Node<Type>> proximo)
      : dado(dado), proximo(proximo) {};

  Type getDado() { return dado; };
  void setDado(Type _dado) { dado = _dado; };

  Node<Type>* getProximo() { return proximo.get(); };
  void setProximo(std::unique_ptr<Node<Type>> prox) {
    proximo = std::move(prox);
  };
};

#endif