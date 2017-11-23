// Graf kraw�dziowy
// Data   : 22.04.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream> asdasdasdasd

using namespace std;

// Definicja elementu listy s�siedztwa

struct slistEl
{
  slistEl * next;                 // Nast�pny element listy;
  int v;                          // Wierzcho�ek docelowy
  int i;                          // Numer kraw�dzi
};

int main()
{
  int n,m;                        // Liczba wierzcho�k�w, liczba kraw�dzi
  slistEl **G,**GE;               // Grafy
  int i,u,v,ei;
  slistEl *p,*r,*s;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  for(i = 0; i < n; i++) G[i] = NULL;

  GE = new slistEl * [m];         // Tworzymy zerowy graf GE
  for(i = 0; i < m; i++) GE[i] = NULL;

  // Odczytujemy definicje kraw�dzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u >> ei;          // Czytamy wierzcho�ki i numer kraw�dzi
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype�niamy go danymi
    p->i = ei;
    p->next = G[v];               // Element do��czamy do listy s�siedztwa wierzcho�ka v
    G[v] = p;

    p = new slistEl;              // To samo dla kraw�dzi odwrotnej
    p->v = v;
    p->i = ei;
    p->next = G[u];
    G[u] = p;
  }

  // Tworzymy graf kraw�dziowy

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho�ki grafu
    for(p = G[v]; p; p = p->next) // Przechodzimy przez list� s�siad�w wierzcho�ka v
      for(r = G[p->v]; r; r = r->next) // Przechodzimy przez list� s�siad�w s�siada v
        if(r->v != v)
        {
          s = new slistEl;        // Tworzymy nowy element listy
          s->v = r->i;            // Wierzcho�kiem docelowym b�dzie kraw�d� wychodz�ca
          s->next = GE[p->i];     // Wierzcho�kiem startowym b�dzie kraw�d� wchodz�ca
          GE[p->i] = s;           // Dodajemy kraw�d� do grafu kraw�dziowego
        }

  // Wy�wietlamy wyniki

  cout << endl;

  for(i = 0; i < m; i++)
  {
    cout << i << ": ";
    for(p = GE[i];p;p = p->next) cout << p->v << " ";
    cout << endl;
  }

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

  for(i = 0; i < m; i++)
  {
    p = GE[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] GE;

  return 0;
}
