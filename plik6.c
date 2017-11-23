// Badanie sp�jno�ci grafu
// Data: 6.01.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj�ca stos

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

// Destruktor - zwalnia tablic� dynamiczn�
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

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int n,m;        // Liczba wierzcho�k�w i kraw�dzi
  slistEl ** A;   // Tablica list s�siedztwa grafu
  bool * visited; // Tablica odwiedzin
  stack S;        // Stos
  int i,v,u,vc;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];     // Tworzymy tablice dynamiczne
  visited = new bool [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje kraw�dzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = A[v];          // Dodajemy go na pocz�tek listy A[v]
    A[v] = p;
    p = new slistEl;         // To samo dla kraw�dzi w drug� stron�
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

  // Badamy sp�jno�� grafu

  vc = 0;                    // Zerujemy licznik wierzcho�k�w

  S.push(0);                 // Wierzcho�ek startowy na stos
  visited[0] = true;         // Oznaczamy go jako odwiedzony

  while(!S.empty())          // Wykonujemy przej�cie DFS
  {
    v = S.top();             // Pobieramy wierzcho�ek ze stosu
    S.pop();                 // Pobrany wierzcho�ek usuwamy ze stosu
    vc++;                    // Zwi�kszamy licznik wierzcho�k�w
    for(p = A[v]; p; p = p->next) // Przegl�damy s�siad�w
    {
      u = p->v;
      if(!visited[u])        // Szukamy wierzcho�k�w nieodwiedzonych
      {
        visited[u] = true;   // Oznaczamy wierzcho�ek jako odwiedzony
        S.push(u);           // i umieszczamy go na stosie
      }
    }
  }

  // Wy�wietlamy wyniki

  cout << endl;

  if(vc == n) cout << "CONNECTED GRAPH"; else cout << "DISCONNECTED GRAPH";

  cout << endl;

  // Usuwamy tablice dynamiczne

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
  delete [] visited;

  return 0;
} 