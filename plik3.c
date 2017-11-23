// Stopie� grafu nieskierowanego
// Data   : 26.04.2014
// (C)2014 mgr Jerzy Wa�aszek
//------------------------------

#include <iostream>

using namespace std;

// Definicja elementu listy s�siedztwa

struct slistEl
{
  slistEl * next ;                // Nast�pny element listy
  int v;                          // Wierzcho�ek docelowy
};

int main()
{
  int n,m;                        // Liczba wierzcho�k�w, liczba kraw�dzi
  slistEl **G;                    // Graf
  int dg,dv,i,v,u;
  slistEl *p,*r;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  for(i = 0; i < n; i++) G[i] = NULL;

  // Odczytujemy definicje kraw�dzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Czytamy wierzcho�ki
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype�niamy go danymi
    p->next = G[v];               // Rekord do��czamy do listy s�siedztwa wierzcho�ka v
    G[v] = p;

    if(v != u)                    // To samo dla kraw�dzi odwrotnej o ile nie jest to p�tla
    {
      p = new slistEl;
      p->v = v;
      p->next = G[u];
      G[u] = p;
    }
  }

  // Wyznaczamy stopie� grafu

  dg = 0;

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho�ki grafu
  {
    dv = 0;                       // Zerujemy stopie� wierzcho�ka
    for(p = G[v]; p; p = p->next) // Przegl�damy s�siad�w wierzcho�ka v
      if(p->v == v) dv += 2;      // P�tle zliczamy za 2
      else          dv++;         // Zwyk�� kraw�d� zliczamy za 1
    if(dv > dg) dg = dv;          // Je�li stopie� jest wi�kszy od dg, to uaktualniamy
  }

  // Wy�wietlamy wynik

  cout << endl << dg << endl << endl;

  // Usuwamy dynamiczne struktury

  for(i = 0; i < n; i++)
  {
    p = G[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] G;

  return 0;
} 