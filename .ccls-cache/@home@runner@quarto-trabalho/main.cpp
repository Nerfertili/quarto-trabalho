#include <chrono>
#include <iostream>
#include <random>

using namespace std;

std::mt19937 generator(1);
std::uniform_int_distribution<int> dis(1, 1000001);

class No {
public:
  double v;
  No *prox;

  No(double v) {
    this->v = v;
    this->prox = NULL;
  }

  double getval() { return v; }

  No *getprox() { return prox; }

  void setProx(No *p) { prox = p; }
};

class Lista {
public:
  No *val;
  No *next;

  Lista() {
    val = NULL;
    next = NULL;
  }

  Lista(double v) {
    val = new No(v);
    next = val;
  }

  virtual ~Lista() { delete val; }
  void dell() {

    while (val != NULL) {
      next = val->prox;
      free(val);
      val = next;
    }

    /* deref head_ref to affect the real head back
        in the caller. */
    val = NULL;
  }

  void print() {
    No *c = val;

    while (c) {
      cout << c->getval() << endl;
      c = c->getprox();
    }
    cout << endl;
  }

  double last() {
    No *c = val;
    double tmp;
    while (c) {
      tmp = c->getval();
      c = c->getprox();
    }
    return tmp;
  }

  double get_from_pos(int pos) {
    No *c = val;
    double tmp;
    int index = 0;
    while (c) {
      tmp = c->getval();
      index++;
      if (index == pos)
        break;
      c = c->getprox();
    }
    return tmp;
  }

  bool is_empty() { return (val == NULL); }
  void append(double v) {
    No *novo_no = new No(v);

    if (is_empty()) {
      val = novo_no;
      next = novo_no;
    } else {
      next->setProx(novo_no);
      next = novo_no;
    }
  }
  double size() {
    if (is_empty())
      return 0;

    No *c = val;
    double tam = 0;
    do {
      c = c->getprox();
      tam++;
    } while (c);

    return tam;
  }
  bool exist(double v) {
    No *c = val;

    while (c) {
      if (c->getval() == v)
        return true;
      c = c->getprox();
    }
    return false;
  }
  void pop() {
    if (!is_empty()) {
      if (val->getprox() == NULL)
        val = NULL;
      else if (val->getprox()->getprox() == NULL)
        val->setProx(NULL);
      else {
        No *ant_ant = val;
        No *ant = val->getprox();
        No *corrente = val->getprox()->getprox();

        while (corrente) {
          No *aux = ant;
          ant = corrente;
          ant_ant = aux;
          corrente = corrente->getprox();
        }
        delete ant_ant->getprox();
        ant_ant->setProx(NULL);
        next = ant_ant;
      }
    }
  }
};

int main() {
  Lista lista;
  auto inicio = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 200000; i++) {
    double rand = dis(generator);
    lista.append(rand);
  }
  auto resultado = std::chrono::high_resolution_clock::now() - inicio;
  long long liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
  cout << "tempo passado para popular: " << liliseconds << " milisegundos"
       << endl;

  Lista reserva;
  inicio = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 200000; i++) {
    reserva.append(lista.last());
    lista.pop();
  }
  resultado = std::chrono::high_resolution_clock::now() - inicio;
  liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
  cout << "tempo passado para inverter: " << liliseconds << " milisegundos"
       << endl;

  inicio = std::chrono::high_resolution_clock::now();
  cout << reserva.get_from_pos(100000) << "este e o numero que esta no centro"
       << endl;
  resultado = std::chrono::high_resolution_clock::now() - inicio;
  liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
  cout << "tempo passado para achar o valor do centro: " << liliseconds
       << " milisegundos" << endl;
  inicio = std::chrono::high_resolution_clock::now();
  reserva.dell();
  resultado = std::chrono::high_resolution_clock::now() - inicio;
  liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
  cout << "tempo passado para deletar a lista inteira: " << liliseconds
       << " milisegundos" << endl;
}