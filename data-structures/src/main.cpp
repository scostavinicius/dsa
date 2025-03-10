#include <iostream>
#include <memory>

// #include "Fila.hpp"
#include "Lista.hpp"
// #include "Pilha.hpp"

void testarLista() {
  Lista<int> lista;

  std::cout << "Testando Lista: " << std::endl;

  // Testando push_back
  std::cout << "Adicionando elementos: 1, 2, 3" << std::endl;
  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(3);

  // Testando print
  std::cout << "Conteudo da lista: ";
  lista.print();

  // Testando push_front
  std::cout << "Adicionando elementos no inicio: 10, 20, 30" << std::endl;
  lista.push_front(10);
  lista.push_front(20);
  lista.push_front(30);

  std::cout << "Conteudo da lista: ";
  lista.print();

  // Testando o construtor de cópia após modificações
  Lista<int> listaCopia2 = lista;
  std::cout << "Conteudo da lista copiada apos modificacoes: ";
  listaCopia2.print();

  try {
    // Testando pop
    std::cout << "Removendo elemento do inicio e do final" << std::endl;
    lista.pop_front();
    lista.pop_back();
    std::cout << "Conteudo da lista: ";
    lista.print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Testando insert
  std::cout << "Adicionando elementos 1000 no indice 2 e 2000 no indice 3" << std::endl;
  lista.insert(2, 1000);
  lista.insert(3, 2000);

  std::cout << "Conteudo da lista: ";
  lista.print();

  try {
    // Testando remove
    std::cout << "Removendo elementos no indice 2 e no indice 1" << std::endl;
    lista.remove(2);
    lista.remove(1);
    std::cout << "Conteudo da lista: ";
    lista.print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Testando reverse
  std::cout << "Invertendo a lista..." << std::endl;
  lista.reverse();

  std::cout << "Conteudo da lista: ";
  lista.print();

  // Testando o clear
  std::cout << "Limpando a lista..." << std::endl;
  lista.clear();
  std::cout << "Conteudo da lista: ";
  lista.print();

  std::cout << std::endl;
}

// void testarPilha() {
//   Pilha<int> pilha;

//   std::cout << "Testando pilha: " << std::endl;

//   // Testando push
//   std::cout << "Empilhando elementos: 10, 20, 30" << std::endl;
//   pilha.push(10);
//   pilha.push(20);
//   pilha.push(30);

//   // Testando print
//   std::cout << "Conteudo da pilha: ";
//   pilha.print();

//   Pilha<int> pilhaCopia = pilha;
//   std::cout << "Conteudo da pilha copiada: ";
//   pilhaCopia.print();

//   try {
//     // Testando top
//     std::cout << "Topo da pilha: " << pilha.top() << std::endl;
//   } catch (const std::exception& e) {
//     std::cerr << e.what() << '\n';
//   }

//   try {
//     // Testando pop
//     std::cout << "Desempilhando elemento..." << std::endl;
//     pilha.pop();
//     std::cout << "Conteudo da pilha apos pop: ";
//     pilha.print();
//   } catch (const std::exception& e) {
//     std::cerr << e.what() << '\n';
//   }

//   // Testando tamanho
//   std::cout << "Tamanho da pilha: " << pilha.size() << std::endl;

//   // Testando clear
//   std::cout << "Limpando a pilha..." << std::endl;
//   pilha.clear();
//   std::cout << "Conteudo da pilha: ";
//   pilha.print();
//   std::cout << "A pilha esta vazia? " << (pilha.isEmpty() ? "Sim" : "Nao") << std::endl;

//   std::cout << std::endl;
// }

// void testarFila() {
//   Fila<int> fila;

//   std::cout << "Testando fila: " << std::endl;

//   // Testando push
//   std::cout << "Enfileirando elementos: 10, 20, 30" << std::endl;
//   fila.push(10);
//   fila.push(20);
//   fila.push(30);

//   // Testando print
//   std::cout << "Conteudo da fila: ";
//   fila.print();

//   Fila<int> filaCopia = fila;
//   std::cout << "Conteudo da fila copiada: ";
//   filaCopia.print();

//   try {
//     // Testando front
//     std::cout << "Frente da fila: " << fila.front() << std::endl;
//   } catch (const std::exception& e) {
//     std::cerr << e.what() << '\n';
//   }

//   try {
//     std::cout << "Desenfileirando elemento..." << std::endl;
//     fila.pop();
//     std::cout << "Conteudo da fila: ";
//     fila.print();
//   } catch (const std::exception& e) {
//     std::cerr << e.what() << '\n';
//   }

//   // Testando tamanho
//   std::cout << "Tamanho da fila: " << fila.size() << std::endl;

//   // Testando clear
//   std::cout << "Limpando a fila..." << std::endl;
//   fila.clear();
//   std::cout << "Conteudo da fila: ";
//   fila.print();
//   std::cout << "A fila esta vazia? " << (fila.isEmpty() ? "Sim" : "Nao") << std::endl;

//   std::cout << std::endl;
// }

int main() {
  testarLista();
  // testarPilha();
  // testarFila();

  return 0;
}
