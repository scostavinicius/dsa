#ifndef NODE_HPP
#define NODE_HPP

template <typename Type>
class Node {
 private:
  Type dado;
  Node<Type>* proximo;

 public:
  Node() : proximo(nullptr) {};
  Node(Type dado) : dado(dado), proximo(nullptr) {};
  Node(Type dado, Node<Type>* proximo) : dado(dado), proximo(proximo) {};

  Type getDado() { return dado; };
  Node<Type>* getProximo() { return proximo; };
  void setDado(Type _dado) { dado = _dado; };
  void setProximo(Node<Type>* prox) { proximo = prox; };
};

#endif