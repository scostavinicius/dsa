#include <iostream>
#include <memory>

#include "Fila.hpp"
#include "Lista.hpp"
#include "Pilha.hpp"

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

  // Testando pop
  std::cout << "Removendo elemento do inicio e do final" << std::endl;
  lista.pop_front();
  lista.pop_back();

  std::cout << "Conteudo da lista: ";
  lista.print();

  // Testando insert
  std::cout << "Adicionando elementos 1000 no indice 2 e 2000 no indice 3" << std::endl;
  lista.insert(2, 1000);
  lista.insert(3, 2000);

  std::cout << "Conteudo da lista: ";
  lista.print();

  // Testando remove
  std::cout << "Removendo elementos no indice 2 e no indice 1" << std::endl;
  lista.remove(2);
  lista.remove(1);

  std::cout << "Conteudo da lista: ";
  lista.print();

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

void testarPilha() {
  Pilha<int> pilha;

  std::cout << "Testando pilha: " << std::endl;

  // Testando push
  std::cout << "Empilhando elementos: 10, 20, 30" << std::endl;
  pilha.push(10);
  pilha.push(20);
  pilha.push(30);

  // Testando print
  std::cout << "Conteudo da pilha: ";
  pilha.print();

  // Testando top
  std::cout << "Topo da pilha: " << pilha.top() << std::endl;

  // Testando pop
  std::cout << "Desempilhando elemento..." << std::endl;
  pilha.pop();

  // Testando print novamente
  std::cout << "Conteudo da pilha apos pop: ";
  pilha.print();

  // Testando tamanho
  std::cout << "Tamanho da pilha: " << pilha.size() << std::endl;

  // Testando clear
  std::cout << "Limpando a pilha..." << std::endl;
  pilha.clear();
  std::cout << "Conteudo da pilha: ";
  pilha.print();
  std::cout << "A pilha esta vazia? " << (pilha.isEmpty() ? "Sim" : "Nao") << std::endl;

  std::cout << std::endl;
}

void testarFila() {}

int main() {
  testarLista();
  testarPilha();

  return 0;
}
