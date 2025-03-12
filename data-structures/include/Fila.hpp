#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>
#include <stdexcept>

template <typename Type>
class Fila {
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

  Node* inicio;
  Node* fim;
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
  // Cria um novo nó para o início da outra fila
  Node* atualOrig = outraFila.inicio;

  // Percorre a outra fila adicionando cópias de seus elementos na fila cópia
  while (atualOrig != nullptr) {
    push(atualOrig->valor);
    atualOrig = atualOrig->proximo;
  }
}

template <typename Type>
Fila<Type>::~Fila() {
  clear();
}

template <typename Type>
void Fila<Type>::push(Type dado) {
  // Cria um novo nó
  Node* novo = new Node(dado);

  if (isEmpty()) {  // Se a fila estiver vazia
    inicio = novo;  // O início e o fim se tornam o novo nó
    fim = inicio;
  } else {                // Se não estiver vazia
    fim->proximo = novo;  // Adiciona o novo nó no final
    fim = fim->proximo;   // O nó final se torna o novo nó
  }

  ++tamanho;
}

template <typename Type>
void Fila<Type>::pop() {
  if (isEmpty()) {
    throw std::out_of_range("A fila está vazia");
  }

  // Mover a posse do nó atual para um ponteiro temporário
  Node* temp = inicio;

  // Atualizar o ponteiro "inicio" para apontar para o próximo nó
  inicio = temp->proximo;

  // Desaloca o nó temporário
  delete temp;

  --tamanho;

  // Se a lista ficou vazia após a remoção, atualizar "fim"
  if (isEmpty()) {
    fim = nullptr;
  }
}

template <typename Type>
Type Fila<Type>::front() {
  if (isEmpty()) {
    throw std::out_of_range("A pilha está vazia");
  }

  return inicio->valor;
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
  while (!isEmpty()) {
    pop();
  }
}

template <typename Type>
void Fila<Type>::print() {
  if (isEmpty()) {
    std::cout << "Fila vazia!" << std::endl;
    return;
  }

  Node* temp = inicio;
  while (temp != nullptr) {
    std::cout << temp->valor << " ";
    temp = temp->proximo;
  }
  std::cout << std::endl;
}

#endif