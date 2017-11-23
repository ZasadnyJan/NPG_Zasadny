// Znajdowanie spójnych sk³adowych
// Data: 27.08.2013
// (C)2013 mgr Jerzy Wa³aszek
//--------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj¹ca stos

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

// Destruktor - zwalnia tablicê dynamiczn¹
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
// *** Program g³ówny ***
// **********************

int main()
{
  int n,m;                   // Liczba wierzcho³ków i krawêdzi
  slistEl ** A;              // Tablica list s¹siedztwa
  int * C;                   // Tablica z numerami spójnych sk³adowych
  stack S;                   // Stos
  int cn,i,j,v,u;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n];     // Tworzymy tablice dynamiczne
  C = new int [n];

  // Tablicê A wype³niamy pustymi listami, a tablicê C wype³niamy zerami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    C[i] = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = A[v];          // Dodajemy go na pocz¹tek listy A[v]
    A[v] = p;
    p = new slistEl;         // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

  cn = 0;                    // Zerujemy licznik spójnych sk³adowych

  for(i = 0; i < n; i++)
    if(!C[i])                // Szukamy nieodwiedzonego jeszcze wierzcho³ka
    {
      cn++;                  // Zwiêkszamy licznik sk³adowych
      S.push(i);             // Na stosie umieszczamy numer bie¿¹cego wierzcho³ka
      C[i] = cn;             // i oznaczamy go jako odwiedzonego i ponumerowanego
      while(!S.empty())      // Przechodzimy graf algorytmem DFS
      {
        v = S.top();         // Pobieramy wierzcho³ek
        S.pop();             // Usuwamy go ze stosu

        // Przegl¹damy s¹siadów wierzcho³ka v

        for(p = A[v]; p; p = p->next)
        {
          u = p->v;          // Numer s¹siada do u
          if(!C[u])
          {
            S.push(u);       // Na stos id¹ s¹siedzi nieodwiedzeni
            C[u] = cn;       // i ponumerowani
          }
        }
      }
    }

  for(i = 1; i <= cn; i++)
  {
    cout << "SCC : " << i << " : "; // Numer spójnej sk³adowej
    for(j = 0; j < n; j++)
      if(C[j] == i) cout << setw(2) << j << " "; // Wierzcho³ki tej sk³adowej
    cout << endl;
  }

  cout << endl;

  // Usuwamy tablicê list s¹siedztwa

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
  delete [] C;

  return 0;
} 