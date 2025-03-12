#ifndef PILHA_HPP
#define PILHA_HPP

#include <iostream>
#include <stdexcept>

template <typename Type>
class Pilha {
 private:
  struct Node {
    Type valor;

    /**
     * @brief Aponta para o próximo nó
     *
     */
    Node* proximo;

    Node(Type valor) : valor(valor), proximo(nullptr) {}
  };

  Node* topo;
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
   * @throw `std::out_of_range` se a pilha estiver vazia
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
   *
   * @throw `std::out_of_range` se a pilha estiver vazia
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
  bool isEmpty() const;

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
Pilha<Type>::Pilha(const Pilha<Type>& outraPilha) : topo(nullptr), tamanho(0) {
  if (!outraPilha.isEmpty()) {
    // Pegar o ponteiro para o primeiro nó da pilha original
    Node<Type>* atualOrig = outraPilha.topo.get();

    // Criar o primeiro nó da nova pilha
    topo = std::make_unique<Node<Type>>(atualOrig->getDado());
    Node<Type>* atualCopia = topo.get();
    ++tamanho;

    // Copiar o restante dos nós
    while (atualOrig->getProximo() != nullptr) {
      atualOrig = atualOrig->getProximo().get();
      // Cria o novo nó com o dado do nó atual da pilha original
      std::unique_ptr<Node<Type>> temp = std::make_unique<Node<Type>>(atualOrig->getDado());

      // Conecta o novo nó ao final da cópia
      atualCopia->setProximo(temp);

      // Atualiza o ponteiro para o último nó copiado
      atualCopia = atualCopia->getProximo().get();
      ++tamanho;
    }
  }
}

template <typename Type>
Pilha<Type>::~Pilha() {
  clear();
}

template <typename Type>
bool Pilha<Type>::isEmpty() const {
  return topo == nullptr;
}

template <typename Type>
void Pilha<Type>::pop() {
  if (isEmpty()) {
    throw std::out_of_range("A pilha está vazia");
  }
  topo = std::move(topo->getProximo());
  --tamanho;
}

template <typename Type>
void Pilha<Type>::push(Type dado) {
  // Cria um novo nó
  std::unique_ptr<Node<Type>> temp = std::make_unique<Node<Type>>(dado);

  // O topo se torna o próximo do novo nó
  temp->setProximo(topo);

  // O novo nó se torna o topo
  topo = std::move(temp);
  ++tamanho;
}

template <typename Type>
Type Pilha<Type>::top() {
  if (isEmpty()) {
    throw std::out_of_range("A pilha está vazia");
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
  if (isEmpty()) {
    std::cout << "Pilha vazia!" << std::endl;
    return;
  }

  Node<Type>* temp = topo.get();
  while (temp != nullptr) {
    std::cout << temp->getDado() << " ";
    temp = temp->getProximo().get();
  }
  std::cout << std::endl;
}

#endif