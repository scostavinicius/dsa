#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>

template <typename Type>
struct Node {
  Type valor;

  /**
   * @brief Aponta para o próximo nó
   *
   */
  Node* proximo;

  Node(Type valor) : valor(valor), proximo(nullptr) {}
};

/**
 * @brief Lista ligada simples
 *
 * @tparam Type
 *
 * @
 */
template <typename Type>
class Lista {
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

  /**
   * @brief Ponteiro para o primeiro nó da lista
   *
   */
  Node<Type>* primeiro;

  /**
   * @brief Ponteiro para o último nó da lista
   *
   */
  Node* ultimo;

  /**
   * @brief Número de elementos na lista
   *
   */
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
  if (outraLista.primeiro == nullptr) {
    return;
  }

  // Criação do primeiro no da lista cópia
  primeiro = new Node(outraLista.primeiro->valor);

  // Nós para percorrer as listas
  Node* atualCopia = primeiro;
  Node* atualOrig = outraLista.primeiro->proximo;

  while (atualOrig != nullptr) {
    atualCopia->proximo = new Node<Type>(atualOrig->valor);
    atualCopia = atualCopia->proximo;
    atualOrig = atualOrig->proximo;
  }

  ultimo = atualCopia;
  tamanho = outraLista.tamanho;
}

template <typename Type>
Lista<Type>::~Lista() {
  clear();
}

template <typename Type>
void Lista<Type>::pop_front() {
  if (tamanho == 0) {
    throw std::out_of_range("A lista esta vazia!");
  }

  Node* aux = primeiro;
  primeiro = primeiro->proximo;
  delete aux;

  --tamanho;

  if (tamanho == 0) {
    ultimo = nullptr;
  }
}

template <typename Type>
void Lista<Type>::pop_back() {
  if (tamanho == 0) {
    throw std::out_of_range("A lista esta vazia!");
  }

  if (tamanho == 1) {
    delete primeiro;
    primeiro = nullptr;
    ultimo = nullptr;
  } else {
    // Percorrer a lista para encontrar o penúltimo nó
    Node* penultimo = primeiro;
    while (penultimo->proximo != ultimo) {
      penultimo = penultimo->proximo;
    }

    // Remover o último nó
    delete ultimo;
    penultimo->proximo = nullptr;
    ultimo = penultimo;
  }

  --tamanho;
}

template <typename Type>
void Lista<Type>::push_front(Type dado) {
  // Criar um novo nó
  Node* novo = new Node<Type>(dado);

  // Se a lista estiver vazia
  if (tamanho == 0) {
    primeiro = novo;
    ultimo = novo;
  } else {
    // Inserir o novo nó na frente da lista
    novo->proximo = primeiro;
    primeiro = novo;
  }

  ++tamanho;
}

template <typename Type>
void Lista<Type>::push_back(Type dado) {
  // Cria um novo nó
  Node* novo = new Node(dado);

  // Se a lista estiver vazia
  if (tamanho == 0) {
    primeiro = novo;
    ultimo = novo;
  } else {
    // Inserir o novo nó no final da lista
    ultimo->proximo = novo;
    ultimo = ultimo->proximo;
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
  Node* temp = primeiro;
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->proximo;
  }

  // Cria um novo nó
  Node* novo = new Node(dado);

  // O novo nó deve ficar entre o nó temp e o nó depois de temp
  novo->proximo = temp->proximo;
  temp->proximo = novo;

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
  Node* temp = primeiro;
  for (size_t i = 0; i < posicao - 1; ++i) {
    temp = temp->proximo;
  }

  // O nó que será removido
  Node* deletar = temp->proximo;

  // Corrige o ponteiro do nó anterior para apontar ao nó após o nó removido
  temp->proximo = deletar->proximo;

  // Se o nó removido era o último, atualiza o ponteiro 'ultimo'
  if (deletar == ultimo) {
    ultimo = temp;
  }

  delete deletar;

  --tamanho;
}

template <typename Type>
void Lista<Type>::clear() {
  Node* atual = primeiro;

  while (atual != nullptr) {
    Node* posterior = atual->proximo;
    delete atual;
    atual = posterior;
  }

  primeiro = nullptr;
  ultimo = nullptr;
  tamanho = 0;
}

template <typename Type>
void Lista<Type>::reverse() {
  // Criação dos nós anterior, atual e posterior, nós auxiliares para inverter a
  // lista
  Node* anterior = nullptr;
  Node* atual = primeiro;
  Node* posterior = nullptr;

  // Percorre a lista e inverte os ponteiros
  while (atual) {
    posterior = atual->proximo;
    atual->proximo = anterior;
    anterior = atual;
    atual = posterior;
  }

  // Atualiza o primeiro
  primeiro = anterior;

  // Atualiza o último
  ultimo = primeiro;
  while (ultimo && ultimo->proximo) {
    ultimo = ultimo->proximo;
  }
}

template <typename Type>
void Lista<Type>::print() {
  Node* temp = primeiro;

  if (!temp) {
    std::cout << "A lista esta vazia!" << std::endl;
    return;
  }

  // Percorre e imprime os elementos da lista
  while (temp) {
    std::cout << temp->valor << " ";
    temp = temp->proximo;
  }

  std::cout << std::endl;
}

#endif