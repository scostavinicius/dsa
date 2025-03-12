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
Pilha<Type>::Pilha(const Pilha<Type>& outraPilha) : Pilha() {
  if (!outraPilha.isEmpty()) {
    // Pegar o ponteiro para o primeiro nó da pilha original
    Node* atualOrig = outraPilha.topo;

    // Criar o primeiro nó da nova pilha
    topo = new Node(atualOrig->valor);
    Node* atualCopia = topo;
    ++tamanho;

    // Copiar o restante dos nós
    while (atualOrig->proximo != nullptr) {
      atualOrig = atualOrig->proximo;
      // Cria o novo nó com o dado do nó atual da pilha original
      Node* temp = new Node(atualOrig->dado);

      // Conecta o novo nó ao final da cópia
      atualCopia->proximo = temp;

      // Atualiza o ponteiro para o último nó copiado
      atualCopia = atualCopia->proximo;
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

  // Cria um nó temporário apontando para o topo
  Node* temp = topo;

  // Atualiza o topo para o próximo nó
  topo = topo->proximo;

  // Desaloca o nó temporário
  delete temp;

  --tamanho;
}

template <typename Type>
void Pilha<Type>::push(Type dado) {
  // Cria um novo nó
  Node* novo = new Node(dado);

  // O topo se torna o próximo do novo nó
  novo->proximo = topo;

  // O novo nó se torna o topo
  topo = novo;
  ++tamanho;
}

template <typename Type>
Type Pilha<Type>::top() {
  if (isEmpty()) {
    throw std::out_of_range("A pilha está vazia");
  }

  return topo->valor;
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

  Node* temp = topo;
  while (temp != nullptr) {
    std::cout << temp->valor << " ";
    temp = temp->proximo;
  }
  std::cout << std::endl;
}

#endif