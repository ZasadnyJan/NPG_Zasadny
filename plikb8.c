// Algorytm Bellmana-Forda
// Data   : 13.04.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // Największa liczba całkowita

// Typy danych
struct slistEl
{
  slistEl * next;
  int v,w;
};

// Zmienne globalne
int m,n;                          // Liczba krawędzi i wierzchołków w grafie
slistEl ** A;                     // Tablica dynamiczna list sąsiedztwa
long long * d;                    // Tablica kosztów dojścia
int * p;                          // Tablica poprzedników

// Funkcja wyznacza najkrótsze ścieżki
// v - wierzchołek startowy
// Wyjście:
// true  - wyniki w d i p
// false - graf zawiera ujemny cykl
//------------------------------------
bool BF(int v)
{
  int i,x;
  bool test;
  slistEl * pv;

  d[v] = 0;                       // Zerujemy koszt dojścia do v
  for(i = 1; i < n; i++)          // Pętla relaksacji
  {
    test = true;                  // Oznacza, że algorytm nie wprowadził zmian do d i p
    for(x = 0; x < n; x++)        // Przechodzimy przez kolejne wierzchołki grafu
      for(pv = A[x]; pv; pv = pv->next) // Przeglądamy listę sąsiadów wierzchołka x
        if(d[pv->v] > d[x] + pv->w) // Sprawdzamy warunek relaksacji
        {
          test = false;           // Jest zmiana w d i p
          d[pv->v] = d[x] + pv->w; // Relaksujemy krawędź z x do jego sąsiada
          p[pv->v] = x;           // Poprzednikiem sąsiada będzie x
        }
    if(test) return true;         // Jeśli nie było zmian, to kończymy
  }

  // Sprawdzamy istnienie ujemnego cyklu

  for(x = 0; x < n; x++)
    for(pv = A[x];pv;pv = pv->next)
      if(d[pv->v] > d[x] + pv->w) return false; // ujemny cykl!!

  return true;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
  int i,v,x,y,w,sptr,*S;
  slistEl *rv,*pv;

  cin >> v >> n >> m;             // Wierzchołek startowy, liczba wierzchołków i krawędzi

  A = new slistEl * [n];          // Tworzymy tablicę list sąsiedztwa
  d = new long long [n];          // Tworzymy tablicę kosztów dojścia
  p = new int [n];                // Tworzymy tablice poprzedników
  for(i = 0; i < n; i++)          // Inicjujemy struktury danych
  {
    d[i] = MAXINT;
    p[i] = -1;
    A[i] = NULL;
  }

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Czytamy wierzchołki krawędzi oraz jej wagę
    pv = new slistEl;             // Tworzymy element listy
    pv->v = y;                    // Inicjujemy go
    pv->w = w;
    pv->next = A[x];              // Dodajemy go na początek listy sąsiadów wierzchołka x
    A[x] = pv;
  }

  cout << endl;

  // Wyznaczamy najkrótsze ścieżki algorytmem Bellmana-Forda

  if(BF(v))
  {
    S = new int [n];              // Tworzymy prosty stos
    sptr = 0;

    for(i = 0; i < n; i++)
    {
      cout << i << ": ";
      for(x = i;x != -1;x = p[x]) // Wierzchołki ścieżki umieszczamy na stosie
        S[sptr++] = x;            // w kolejności od ostatniego do pierwszego

      while(sptr)                 // Wierzchołki ze stosu drukujemy
        cout << S[--sptr] << " "; // w kolejności od pierwszego do ostatniego

      cout << "$" << d[i] << endl; // Na końcu wyświetlamy koszt
    }
    delete [] S;                  // Usuwamy stos
  }
  else cout << "Negative Cycle found!" << endl;

  // Usuwamy struktury dynamiczne

  for(i = 0; i < n; i++)
  {
    pv = A[i];
    while(pv)
    {
      rv = pv;
      pv = pv->next;
      delete rv;
    }
  }

  delete [] A;
  delete [] d;
  delete [] p;

  return 0;
} 