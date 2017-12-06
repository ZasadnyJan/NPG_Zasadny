// Badanie, czy graf zawiera cykl lub ścieżkę Eulera
// Data: 4.01.2014
// (C)2013 mgr Jerzy Wałaszek
//--------------------------------------------------

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

// Funkcja bada graf pod kątem posiadania cyklu lub ścieżki Eulera
// n    - liczba wierzchołków w grafie
// graf - tablica list sąsiedztwa
// Wynik:
// 0 - graf nie zawiera ścieżki lub cyklu Eulera
// 1 - graf zawiera ścieżkę Eulera
// 2 - graf zawiera cykl Eulera
//-----------------------------------------------------------------
int isEulerian(int n, slistEl ** graf)
{
  int no,nc,i,v,u;
  stack S;
  bool * visited;
  slistEl *p;

  for(i = 0; i < n && !graf[i]; i++); // Szukamy pierwszego wierzchołka z sąsiadami

  if(i == n) return 1;        // Graf nie ma krawędzi

  visited = new bool [n];     // Tworzymy dynamicznie tablicę odwiedzin
  for(v = 0; v < n; v++)      // Wypełniamy ją wartościami false
    visited[v] = false;

  no = 0;                     // Zerujemy licznik wierzchołków o stopniu nieparzystym

  S.push(i);                  // Wierzchołek startowy na stos
  visited[i] = true;          // oznaczamy go jako odwiedzony

  // Uruchamiamy przejście DFS, aby wyznaczyć spójną składową zawierającą
  // wierzchołek startowy oraz policzyć stopnie wierzchołków i wyznaczyć
  // liczbę wierzchołków o stopniach nieparzystych

  while(!S.empty())
  {
    v = S.top();              // Pobieramy do v wierzchołek ze stosu
    S.pop();                  // Pobrany wierzchołek usuwamy ze stosu

    nc = 0;                   // Licznik sąsiadów na zero

    for(p = graf[v]; p; p = p->next) // Przeglądamy sąsiadów wierzchołka v
    {
      nc++;                   // Zwiększamy licznik sąsiadów
      u = p->v;
      if(!visited[u])         // Szukamy nieodwiedzonych sąsiadów
      {
        visited[u] = true;    // Zaznaczamy ich jako odwiedzonych
        S.push(u);            // i umieszczamy na stosie
      }
    }

    if(nc % 2 == 1) no++;     // Nieparzysta liczba sąsiadów?
  }

  for(v = i + 1; v < n; v++)  // Przeglądamy pozostałe wierzchołki grafu
    if(!visited[v] && graf[v])
    {
      delete [] visited;      // Usuwamy tablicę odwiedzin
      return 0;               // graf nie jest spójny
    }

  delete [] visited;          // Usuwamy tablicę odwiedzin

  if(!no) return 2;           // Graf zawiera cykl Eulera

  if(no == 2) return 1;       // Graf zawiera ścieżkę Eulera

  return 0;                   // Graf nie posiada ścieżki lub cyklu Eulera
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

  // Tablicę wypełniamy pustymi listami

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

  switch(isEulerian(n,A))
  {
    case 0: cout << "NOT AN EULERIAN GRAPH\n";
            break;
    case 1: cout << "SEMI-EULERIAN GRAPH\n";
            break;
    case 2: cout << "EULERIAN GRAPH\n";
            break;
  }

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