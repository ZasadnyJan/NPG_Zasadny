// Graf krawêdziowy
// Data   : 22.04.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream> asdasdasdasd

using namespace std;

// Definicja elementu listy s¹siedztwa

struct slistEl
{
  slistEl * next;                 // Nastêpny element listy;
  int v;                          // Wierzcho³ek docelowy
  int i;                          // Numer krawêdzi
};

int main()
{
  int n,m;                        // Liczba wierzcho³ków, liczba krawêdzi
  slistEl **G,**GE;               // Grafy
  int i,u,v,ei;
  slistEl *p,*r,*s;

  cin >> n >> m;                  // Czytamy rozmiary grafu

  G = new slistEl * [n];          // Tworzymy zerowy graf G
  for(i = 0; i < n; i++) G[i] = NULL;

  GE = new slistEl * [m];         // Tworzymy zerowy graf GE
  for(i = 0; i < m; i++) GE[i] = NULL;

  // Odczytujemy definicje krawêdzi grafu G

  for(i = 0; i < m; i++)
  {
    cin >> v >> u >> ei;          // Czytamy wierzcho³ki i numer krawêdzi
    p = new slistEl;              // Tworzymy rekord listy
    p->v = u;                     // Wype³niamy go danymi
    p->i = ei;
    p->next = G[v];               // Element do³¹czamy do listy s¹siedztwa wierzcho³ka v
    G[v] = p;

    p = new slistEl;              // To samo dla krawêdzi odwrotnej
    p->v = v;
    p->i = ei;
    p->next = G[u];
    G[u] = p;
  }

  // Tworzymy graf krawêdziowy

  for(v = 0; v < n; v++)          // Przechodzimy przez kolejne wierzcho³ki grafu
    for(p = G[v]; p; p = p->next) // Przechodzimy przez listê s¹siadów wierzcho³ka v
      for(r = G[p->v]; r; r = r->next) // Przechodzimy przez listê s¹siadów s¹siada v
        if(r->v != v)
        {
          s = new slistEl;        // Tworzymy nowy element listy
          s->v = r->i;            // Wierzcho³kiem docelowym bêdzie krawêdŸ wychodz¹ca
          s->next = GE[p->i];     // Wierzcho³kiem startowym bêdzie krawêdŸ wchodz¹ca
          GE[p->i] = s;           // Dodajemy krawêdŸ do grafu krawêdziowego
        }

  // Wyœwietlamy wyniki

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
