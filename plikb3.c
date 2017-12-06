// Wyszukiwanie cykli w grafie nieskierowanym
// Data: 22.12.2013
// (C)2013 mgr Jerzy Wałaszek
//-------------------------------------------

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

// Funkcja rekurencyjna wyszukująca cykl
//--------------------------------------
bool DFSfindCycle(slistEl ** graf, int v, int w, stack & S, bool * visited)
{
  int u;
  slistEl * p;

  visited[w] = true;             // Oznaczamy wierzchołek jako odwiedzony
  p = graf[w];                   // Rozpoczynamy przeglądanie sąsiadów
  while(p)
  {
    u = p->v;                    // u - numer wierzchołka będącego sąsiadem
    if(u != S.top())             // Pomijamy wierzchołek, z którego przyszliśmy
    {
      S.push(w);                 // Na stos wierzchołek bieżący
      if(u == v) return true;    // Cykl znaleziony, kończymy
      if(!visited[u] && DFSfindCycle(graf,v,u,S,visited)) return true;
      S.pop();
    }
    p = p->next;
  }
  return false;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
  int n,m,i,j,u,v1,v2;
  slistEl * p,* r,** A;
  bool * visited;
  stack S;

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

  cout << endl;

  visited = new bool [n];          // Tworzymy tablicę odwiedzin

  for(i = 0; i < n; i++)           // Przechodzimy przez kolejne wierzchołki grafu
  {
    for(j = 0; j < n; j++)         // Zerujemy tablicę odwiedzin
      visited[j] = false;

    S.push(-1);                    // Na stos znacznik początku ścieżki

    cout << i;                     // Wypisujemy wierzchołek startowy cyklu

    if(!DFSfindCycle(A,i,i,S,visited)) // Szukamy cyklu
    {
      S.pop();                     // Usuwamy ze stosu początek ścieżki
      cout << " - no cycle\n";   // Komunikat
    }
    else
      while(!S.empty())            // Wypisujemy cykl, jesli istnieje
      {
        u = S.top(); S.pop();      // Pobieramy ze stosu numer wierzcjołka
        if(u > -1) cout << " " << u; // i wypisujemy go
        else       cout << endl;
      }
  }

  // Usuwamy dynamiczne struktury danych

  delete [] visited;

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