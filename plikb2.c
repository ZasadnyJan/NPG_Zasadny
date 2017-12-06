// Badanie cykliczności spójnego grafu nieskierowanego
// Data: 10.12.2013
// (C)2013 mgr Jerzy Wałaszek
//----------------------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowująca stos

  public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
  S = NULL;
}

// Destruktor - zwalnia tablicę dynamiczną
//----------------------------------------
stack::~stack()
{
  while(S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
  if(S)
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Funkcja bada cykliczność grafu
//-------------------------------
bool isCyclic(int n, slistEl ** G)
{
  stack S;                      // Stos
  bool * visited;               // Tablica odwiedzin
  slistEl * p;                  // Wskaźnik elementu listy
  int w,v,z,i;                  // Zmienne pomocnicze

  visited = new bool[n];        // Tworzymy tablicę odwiedzin

  for(i = 0; i < n; i++) visited[i] = false;  // i zerujemy ją

  S.push(0); S.push(-1);        // Na stos wierzchołek startowy i -1
  visited[0] = true;            // Oznaczamy wierzchołek jako odwiedzony
  while(!S.empty())             // W pętli przechodzimy graf za pomocą DFS
  {
    w = S.top(); S.pop();       // Pobieramy ze stosu wierzchołek z którego przyszliśmy
    v = S.top(); S.pop();       // oraz wierzchołek bieżący
    for(p = G[v]; p; p = p->next) // Przeglądamy jego listę sąsiadów
    {
      z = p->v;                 // Numer sąsiada
      if(!visited[z])
      {
        S.push(z); S.push(v);   // Sąsiada nieodwiedzonego umieszczamy na stosie
        visited[z] = true;      // Oznaczamy go jako odwiedzonego
      }
      else if(z != w)           // Jeśli sąsiad jest odwiedzony i nie jest wierzchołkiem
      {                         // z którego przyszliśmy, to odkryliśmy cykl
        delete [] visited;      // Usuwamy zmienne pomocnicze
        return true;            // Kończymy z wynikiem true
      }
    }
  }
  delete [] visited;            // W grafie nie ma cykli.
  return false;                 // Kończymy z wynikiem false
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczbę wierzchołków i krawędzi

  A = new slistEl * [n]; // Tworzymy tablicę list sąsiedztwa

  // Tablice wypełniamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na początek listy A[v1]
    A[v1] = p;
    p = new slistEl;    // Krawędź w drugą stronę, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  if(isCyclic(n,A)) cout << "CYCLIC GRAPH";
  else              cout << "ACYCLIC GRAPH";

  cout << endl;

  // Usuwamy tablicę list sąsiedztwa

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] A;

  return 0;
} 