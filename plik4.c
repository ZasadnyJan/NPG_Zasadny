// DFS - szukanie �cie�ki
// Data: 24.07.2013
// (C)2013 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>
#include <iomanip>

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

// Zmienne globalne
//-----------------
int n;                   // Liczba wierzcho�k�w
slistEl ** A;            // Macierz s�siedztwa

// Procedura szukania �cie�ki
// vs - numer wierzcho�ka startowego
// vk - numer wierzcho�ka ko�cowego
//----------------------------------
void DFS_Path(int vs, int vk)
{
  stack S;
  bool * visited, found;
  int  * P,v,u,i;
  slistEl * pv;

  visited = new bool[n];   // Tworzymy tablice odwiedzin
  for(i = 0; i < n; i++)   // Tablic� visited zerujemy
    visited[i] = false;

  P = new int[n];          // Tworzymy tablic� �cie�ki

  P[vs] = -1;

  S.push(vs);              // Na stosie umieszczamy wierzcho�ek startowy

  visited[vs] = true;      // Wierzcho�ek startowy oznaczamy jako odwiedzony

  found = false;

  while(!S.empty())
  {
    v = S.top();           // Pobieramy ze stosu wierzcho�ek v
    S.pop();

    if(v == vk)            // Sprawdzamy, czy osi�gn�li�my wierzcho�ek ko�cowy
    {
      found = true;        // Zaznaczamy sukces
      break;               // Przerywamy p�tl�
    }

    // Przegl�damy s�siad�w wierzcho�ka v

    for(pv = A[v]; pv; pv = pv->next)
    {
      u = pv->v;
      if(!visited[u])
      {
        P[u] = v;        // W P zapisujemy fragment �cie�ki
        S.push(u);       // S�siad zostaje umieszczony na stosie
        visited[u] = true; // i oznaczony jako odwiedzony
      }
    }
  }

  if(!found) cout << "BRAK"; // �cie�ka nie zosta�a znaleziona
  else
    while(v > -1)
    {
      cout << setw(3) << v;  // Wypisujemy wierzcho�ki �cie�ki
      v = P[v];    // Cofamy si� do poprzedniego wierzcho�ka �cie�ki
    }

  delete [] P;
  delete [] visited;
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;               // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];       // Tworzymy tablic� list s�siedztwa

  // Tablic� wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
  }

  // Odczytujemy wierzcho�ek startowy i ko�cowy �cie�ki

  cin >> v1 >> v2;

  cout << endl;

  DFS_Path(v1,v2);      // Szukamy �cie�ki

  // Usuwamy tablic� list s�siedztwa

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