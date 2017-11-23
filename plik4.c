// DFS - szukanie œcie¿ki
// Data: 24.07.2013
// (C)2013 mgr Jerzy Wa³aszek
//---------------------------

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

// Zmienne globalne
//-----------------
int n;                   // Liczba wierzcho³ków
slistEl ** A;            // Macierz s¹siedztwa

// Procedura szukania œcie¿ki
// vs - numer wierzcho³ka startowego
// vk - numer wierzcho³ka koñcowego
//----------------------------------
void DFS_Path(int vs, int vk)
{
  stack S;
  bool * visited, found;
  int  * P,v,u,i;
  slistEl * pv;

  visited = new bool[n];   // Tworzymy tablice odwiedzin
  for(i = 0; i < n; i++)   // Tablicê visited zerujemy
    visited[i] = false;

  P = new int[n];          // Tworzymy tablicê œcie¿ki

  P[vs] = -1;

  S.push(vs);              // Na stosie umieszczamy wierzcho³ek startowy

  visited[vs] = true;      // Wierzcho³ek startowy oznaczamy jako odwiedzony

  found = false;

  while(!S.empty())
  {
    v = S.top();           // Pobieramy ze stosu wierzcho³ek v
    S.pop();

    if(v == vk)            // Sprawdzamy, czy osi¹gnêliœmy wierzcho³ek koñcowy
    {
      found = true;        // Zaznaczamy sukces
      break;               // Przerywamy pêtlê
    }

    // Przegl¹damy s¹siadów wierzcho³ka v

    for(pv = A[v]; pv; pv = pv->next)
    {
      u = pv->v;
      if(!visited[u])
      {
        P[u] = v;        // W P zapisujemy fragment œcie¿ki
        S.push(u);       // S¹siad zostaje umieszczony na stosie
        visited[u] = true; // i oznaczony jako odwiedzony
      }
    }
  }

  if(!found) cout << "BRAK"; // Œcie¿ka nie zosta³a znaleziona
  else
    while(v > -1)
    {
      cout << setw(3) << v;  // Wypisujemy wierzcho³ki œcie¿ki
      v = P[v];    // Cofamy siê do poprzedniego wierzcho³ka œcie¿ki
    }

  delete [] P;
  delete [] visited;
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;               // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n];       // Tworzymy tablicê list s¹siedztwa

  // Tablicê wype³niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz¹tek listy A[v1]
    A[v1] = p;
  }

  // Odczytujemy wierzcho³ek startowy i koñcowy œcie¿ki

  cin >> v1 >> v2;

  cout << endl;

  DFS_Path(v1,v2);      // Szukamy œcie¿ki

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

  cout << endl;

  return 0;
} 