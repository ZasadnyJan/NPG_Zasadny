// Wyszukiwanie most�w w grafie nieskierowanym
// Data: 27.12.2013
// (C)2013 mgr Jerzy Wa�aszek
//--------------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa, stosu i listy most�w

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

// Funkcja oblicza liczb� sp�jnych sk�adowych w grafie
// n    - liczba wierzcho�k�w w grafie
// graf - tablica list s�siedztwa
// VU   - tablica dost�pno�ci kraw�dzi grafu
//----------------------------------------------------
int ccn(int n, slistEl ** graf, bool * VU)
{
  int * C,cc,i,v,u;
  stack S;
  slistEl * p;

  C = new int[n];            // Tworzymy tablic� sp�jnych sk�adowych

  for(i = 0; i < n; i++) C[i] = 0; // Zerujemy tablic� sp�jnych sk�adowych

  cc = 0;                    // Zerujemy licznik sp�jnych sk�adowych

  for(i = 0; i < n; i++)
    if(!C[i])                // Szukamy nieodwiedzonego jeszcze wierzcho�ka
    {
      cc++;                  // Zwi�kszamy licznik sk�adowych
      S.push(i);             // Na stosie umieszczamy numer bie��cego w�z�a
      C[i] = cc;             // Wierzcho�ek numerujemy i oznaczamy jako odwiedzony
      while(!S.empty())      // Przechodzimy graf algorytmem DFS
      {
        v = S.top();         // Pobieramy wierzcho�ek
        S.pop();             // Usuwamy go ze stosu
        for(p = graf[v]; p; p = p->next) // Przegl�damy s�siad�w wierzcho�ka v
        {
          u = p->v;
          if((VU[v] || VU[u]) && !C[u])
          {
            S.push(p->v);   // Na stos id� s�siedzi nieodwiedzeni
            C[u] = cc;      // i ponumerowani
          }
        }
      }
    }

  delete [] C;               // Usuwamy tablic� C
  return cc;                 // Zwracamy wynik
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int n,m;                   // Liczba wierzcho�k�w i kraw�dzi
  slistEl ** A;              // Tablica list s�siedztwa
  int nc,i,v,u;
  slistEl * L,* p,* r;
  bool * VU;

  cin >> n >> m;             // Czytamy liczb� wierzcho�k�w i kraw�dzi

  // Tworzymy zmienne dynamiczne

  VU = new bool[n];          // Kraw�dzie aktywne
  A  = new slistEl * [n];    // Tablica list s�siedztwa

  // Tablic� wype�niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    VU[i] = true;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;
    p = new slistEl;
    p->v = u;
    p->next = A[v];
    A[v] = p;
    p = new slistEl;
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

  // Algorytm znajdowania most�w

  L = NULL;                  // Pusta lista most�w

  nc = ccn(n,A,VU);          // Zapami�tujemy liczb� sp�jnych sk�adowych

  for(v = 0; v < n; v++)     // Przechodzimy przez kolejne wierzcho�ki grafu
  {
    p = A[v];                // Przegl�damy list� s�siedztwa wierzcho�ka v
    while(p)
    {
      u = p->v;              // u - numer wierzcho�ka s�siedniego w grafie
      if(u > v)              // Interesuj� nas tylko kraw�dzie w jedn� stron�
      {
        VU[v] = VU[u] = false; // Zaznaczamy kraw�d� v-u jako usuni�t�
        if(ccn(n,A,VU) > nc)
        {
          r = new slistEl;   // Znaleziony most dodajemy do listy L
          r->v = u;
          r->next = L;
          L = r;
          r = new slistEl;
          r->v = v;
          r->next = L;
          L = r;
        }
        VU[v] = VU[u] = true; // Kasujemy zaznaczenie kraw�dzi jako usuni�tej
      }
      p = p->next;
    }
  }

  cout << endl;

  // Wypisujemy znalezione mosty, jednocze�nie usuwaj�c list� L

  v = 0;

  while(L)
  {
    cout << L->v << " ";
    v ^= 1;
    if(!v) cout << endl;
    p = L;
    L = L->next;
    delete [] p;
  }

  // Usuwamy dynamiczne struktury danych

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
  delete [] VU;

  return 0;
} 