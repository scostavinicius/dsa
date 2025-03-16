#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <iostream>

/**
 * @brief Árvore binária de busca
 *
 * @tparam Type
 */
template <typename Type>
class BinTree {
 private:
  struct Node {
    Type valor;
    Node* left;
    Node* right;

    Node(Type valor) : valor(valor), left(nullptr), right(nullptr) {}
  };

  Node* raiz;

 public:
  BinTree() : raiz(nullptr) {}
  BinTree(const BinTree<Type>& outraArvore);
  ~BinTree();

  /**
   * @brief Insere um valor na árvore binária de busca.
   *
   * O valor é inserido de maneira recursiva na árvore. Caso o valor seja menor que o valor do nó
   * atual, ele é adicionado à subárvore esquerda. Caso contrário, ele é adicionado à subárvore
   * direita.
   *
   * Esse método chama o método recursivo `insert(Node* node, Type valor)` para realizar a
   * inserção no nó apropriado.
   *
   * @param valor O valor a ser inserido na árvore.
   */
  void insert(Type valor);

  /**
   * @brief Percorre a árvore em pré-ordem (pre-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido raiz -> esquerda -> direita e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `preOrder(Node* node)` para realizar o percurso.
   */
  void preOrder();

  /**
   * @brief Percorre a árvore em ordem (in-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido esquerda -> raiz -> direita e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `inOrder(Node* node)` para realizar o percurso.
   */
  void inOrder();

  /**
   * @brief Percorre a árvore em pós-ordem (post-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido esquerda -> direita -> raiz e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `postOrder(Node* node)` para realizar o percurso.
   */
  void postOrder();

  /**
   * @brief Verifica se um valor específico está presente na árvore.
   *
   * O método utiliza a lógica de implementação da árvore binária de busca para procurar pelo valor.
   *
   * Esse método chama o método recursivo `search(Node* node, Type valor)` para realizar a
   * busca.
   *
   * @param valor O valor a ser buscado na árvore
   */
  bool search(Type valor) const;

  // size_t height() const;

  size_t countNodes() const;

 private:
  /**
   * @brief Função auxiliar utilizada pelo Construtor cópia.
   *
   * Essa função é utilizada para copiar recursivamente os valores dos nós de uma árvore binária
   *
   * @param arvore Árvore destino da cópia
   * @param node Nó atual da árvore que está sendo copiada
   */
  void auxCopia(BinTree<Type>& arvore, const Node* node);

  /**
   * @brief Função auxiliar utilizada pelo Destrutor.
   *
   * Essa função é utilizada para destruir recursivamente os valores dos nós de uma árvore binária
   *
   * @param node Nó atual da árvore que está sendo destruida
   */
  void auxDestrutor(Node* node);

  /**
   * @brief Insere um valor em um nó da árvore de forma recursiva.
   *
   * Esse método compara o valor a ser inserido com o valor do nó atual e decide se o valor deve ser
   * inserido na subárvore esquerda ou direita.
   *
   * @param node O nó atual da árvore onde a inserção será realizada.
   * @param valor O valor a ser inserido no nó.
   * @return Retorna o nó atual, que pode ter sido modificado durante a inserção.
   */
  Node* insert(Node* node, Type valor);

  /**
   * @brief Realiza um percurso recursivo pré-ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando o nó raiz, a subárvore esquerda,
   * e a subárvore direita, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void preOrder(Node* node);

  /**
   * @brief Realiza um percurso recursivo em ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando a subárvore esquerda, o nó raiz
   * e a subárvore direita, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void inOrder(Node* node);

  /**
   * @brief Realiza um percurso recursivo em ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando a subárvore esquerda, a subárvore
   * direita e o nó raiz, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void postOrder(Node* node);

  /**
   * @brief Verifica se um valor específico está presente na árvore.
   *
   * @param node Nó atual que está sendo verificado para busca.
   * @param valor Valor que está sendo buscado.
   */
  bool search(Node* node, Type valor) const;

  // size_t height(Node* node) const;

  size_t countNodes(Node* node) const;

  // TODO: remoção(remove)
  // TODO: altura da árvore(height)
  // TODO:contagem de nós (countNodes)
  // TODO: verificação de balanceamento (isBalanced)
};

template <typename Type>
BinTree<Type>::BinTree(const BinTree<Type>& outraArvore) : BinTree() {
  if (outraArvore.raiz != nullptr) {
    insert(outraArvore.raiz->valor);

    // Copia recursivamente os demais nós (subárvores esquerda e direita)
    auxCopia(*this, outraArvore.raiz->left);
    auxCopia(*this, outraArvore.raiz->right);
  }
}

template <typename Type>
void BinTree<Type>::auxCopia(BinTree<Type>& arvore, const typename BinTree<Type>::Node* node) {
  if (node != nullptr) {
    arvore.insert(node->valor);
    auxCopia(arvore, node->left);
    auxCopia(arvore, node->right);
  }
}

template <typename Type>
BinTree<Type>::~BinTree() {
  auxDestrutor(raiz);
}

template <typename Type>
void BinTree<Type>::auxDestrutor(typename BinTree<Type>::Node* node) {
  if (node != nullptr) {
    auxDestrutor(node->left);
    auxDestrutor(node->right);
  }

  delete node;
}

template <typename Type>
void BinTree<Type>::insert(Type valor) {
  raiz = insert(raiz, valor);
}

template <typename Type>
typename BinTree<Type>::Node* BinTree<Type>::insert(typename BinTree<Type>::Node* node,
                                                    Type valor) {
  if (node == nullptr) {
    return new Node(valor);
  }

  if (valor < node->valor) {
    node->left = insert(node->left, valor);
  } else {
    node->right = insert(node->right, valor);
  }

  return node;
}

template <typename Type>
void BinTree<Type>::preOrder() {
  preOrder(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::preOrder(typename BinTree<Type>::Node* node) {
  if (node == nullptr) return;

  std::cout << node->valor << " ";
  preOrder(node->left);
  preOrder(node->right);
}

template <typename Type>
void BinTree<Type>::inOrder() {
  inOrder(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::inOrder(typename BinTree<Type>::Node* node) {
  if (node == nullptr) return;

  inOrder(node->left);
  std::cout << node->valor << " ";
  inOrder(node->right);
}

template <typename Type>
void BinTree<Type>::postOrder() {
  postOrder(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::postOrder(typename BinTree<Type>::Node* node) {
  if (node == nullptr) return;

  postOrder(node->left);
  postOrder(node->right);
  std::cout << node->valor << " ";
}

template <typename Type>
bool BinTree<Type>::search(Type valor) const {
  return search(raiz, valor);
}

template <typename Type>
bool BinTree<Type>::search(typename BinTree<Type>::Node* node, Type valor) const {
  if (node == nullptr) return false;

  if (node->valor == valor) return true;

  if (valor < node->valor) {
    return search(node->left, valor);
  } else {
    return search(node->right, valor);
  }
}

template <typename Type>
size_t BinTree<Type>::countNodes() const {
  return countNodes(raiz);
}

template <typename Type>
size_t BinTree<Type>::countNodes(typename BinTree<Type>::Node* node) const {
  if (node == nullptr) return 0;

  return 1 + countNodes(node->left) + countNodes(node->right);
}

#endif