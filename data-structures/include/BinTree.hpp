#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <iostream>

template <typename Type>
struct Node {
  Type valor;
  Node<Type>* left;
  Node<Type>* right;

  Node(Type valor) : valor(valor), left(nullptr), right(nullptr) {}
};

template <typename Type>
class BinTree {
 private:
  Node<Type>* raiz;

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
   * Esse método chama o método recursivo `inserir(Node<Type>* node, Type valor)` para realizar a
   * inserção no nó apropriado.
   *
   * @param valor O valor a ser inserido na árvore.
   */
  void inserir(Type valor);

  /**
   * @brief Percorre a árvore em pré-ordem (pre-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido raiz -> esquerda -> direita e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `preOrdem(Node<Type>* node)` para realizar o percurso.
   */
  void preOrdem();

  /**
   * @brief Percorre a árvore em ordem (in-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido esquerda -> raiz -> direita e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `emOrdem(Node<Type>* node)` para realizar o percurso.
   */
  void emOrdem();

  /**
   * @brief Percorre a árvore em pós-ordem (post-order) e imprime os valores.
   *
   * O método percorre a árvore no sentido esquerda -> direita -> raiz e imprime os valores
   * encontrados.
   *
   * Esse método chama o método recursivo `posOrdem(Node<Type>* node)` para realizar o percurso.
   */
  void posOrdem();

 private:
  /**
   * @brief Função auxiliar utilizada pelo Construtor cópia
   *
   * Essa função é utilizada para copiar recursivamente os valores dos nós de uma árvore binária
   *
   * @param arvore Árvore destino da cópia
   * @param node Nó atual da árvore que está sendo copiada
   */
  void auxCopia(BinTree<Type>& arvore, const Node<Type>* node);

  /**
   * @brief Insere um valor em um nó da árvore de forma recursiva.
   *
   * Esse método recursivo é chamado pela função pública `inserir`. Ele compara o valor a ser
   * inserido com o valor do nó atual e decide se o valor deve ser inserido na subárvore esquerda ou
   * direita.
   *
   * @param node O nó atual da árvore onde a inserção será realizada.
   * @param valor O valor a ser inserido no nó.
   * @return Retorna o nó atual, que pode ter sido modificado durante a inserção.
   */
  Node<Type>* inserir(Node<Type>* node, Type valor);

  /**
   * @brief Realiza um percurso recursivo pré-ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando o nó raiz, a subárvore esquerda,
   * e a subárvore direita, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void preOrdem(Node<Type>* node);

  /**
   * @brief Realiza um percurso recursivo em ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando a subárvore esquerda, o nó raiz
   * e a subárvore direita, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void emOrdem(Node<Type>* node);

  /**
   * @brief Realiza um percurso recursivo em ordem na árvore e imprime os valores.
   *
   * Esse método percorre a árvore recursivamente, visitando a subárvore esquerda, a subárvore
   * direita e o nó raiz, imprimindo os valores no caminho.
   *
   * @param node O nó atual da árvore que está sendo percorrido.
   */
  void posOrdem(Node<Type>* node);
};

template <typename Type>
void BinTree<Type>::auxCopia(BinTree<Type>& arvore, const Node<Type>* node) {
  if (node != nullptr) {
    arvore.inserir(node->valor);
    auxCopia(arvore, node->left);
    auxCopia(arvore, node->right);
  }
}

template <typename Type>
BinTree<Type>::BinTree(const BinTree<Type>& outraArvore) : BinTree() {
  if (outraArvore.raiz != nullptr) {
    inserir(outraArvore.raiz->valor);

    // Copia recursivamente os demais nós (subárvores esquerda e direita)
    auxCopia(*this, outraArvore.raiz->left);
    auxCopia(*this, outraArvore.raiz->right);
  }
}

template <typename Type>
void BinTree<Type>::inserir(Type valor) {
  raiz = inserir(raiz, valor);
}

template <typename Type>
Node<Type>* BinTree<Type>::inserir(Node<Type>* node, Type valor) {
  if (node == nullptr) {
    return new Node<Type>(valor);
  }

  if (valor < node->valor) {
    node->left = inserir(node->left, valor);
  } else {
    node->right = inserir(node->right, valor);
  }

  return node;
}

template <typename Type>
void BinTree<Type>::preOrdem() {
  preOrdem(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::preOrdem(Node<Type>* node) {
  if (node == nullptr) return;

  std::cout << node->valor << " ";
  preOrdem(node->left);
  preOrdem(node->right);
}

template <typename Type>
void BinTree<Type>::emOrdem() {
  emOrdem(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::emOrdem(Node<Type>* node) {
  if (node == nullptr) return;

  emOrdem(node->left);
  std::cout << node->valor << " ";
  emOrdem(node->right);
}

template <typename Type>
void BinTree<Type>::posOrdem() {
  posOrdem(raiz);
  std::cout << std::endl;
}

template <typename Type>
void BinTree<Type>::posOrdem(Node<Type>* node) {
  if (node == nullptr) return;

  posOrdem(node->left);
  posOrdem(node->right);
  std::cout << node->valor << " ";
}

#endif