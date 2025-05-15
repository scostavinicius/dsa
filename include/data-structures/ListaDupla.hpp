#ifndef LISTA_DUPLA.HPP
#define LISTA_DUPLA .HPP

/**
 * @brief Lista duplamente ligada
 *
 * @tparam Type
 */
template <typename Type>
class ListaDupla {
 private:
  struct Node {
    Type dado;

    /**
     * @brief Aponta para o nó anterior
     *
     */
    Node* anterior;

    /**
     * @brief Aponta para o próximo nó
     *
     */
    Node* proximo;

    Node(Type dado) : dado(dado), anterior(nullptr), proximo(nullptr) {}
  };

  /**
   * @brief Ponteiro para o primeiro nó da lista
   *
   */
  Node* primeiro;

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
  ListaDupla() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {};
  ListaDupla(const ListaLigada2<Type>& outraLista);
  ~ListaDupla();

  void pop_front();

  void pop_back();

  void push_front(Type dado);

  void push_back(Type dado);

  void insert(Type dado, size_t posicao);

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

#endif