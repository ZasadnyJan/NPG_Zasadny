// Drzewo rozpinaj¹ce w g³¹b
// Data: 22.09.2013
// (C)2013 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;
//zmiana
// Typ listy jednokierunkowej

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

slistEl ** graf; // Tablica list s¹siedztwa grafu
slistEl ** T;    // Tablica list s¹siedztwa drzewa rozpinaj¹cego
bool * visited;  // Tablica odwiedzin

// Rekurencyjna funkcja tworzenia drzewa rozpinaj¹cego w g³¹b
// v - numer wierzcho³ka startowego
// reszta zmiennych globalna
//-------------------------------------------------------------
void DFSTree(int v)
{
  slistEl *p, *r;
  int u;

  visited[v] = true;         // Oznaczamy wierzcho³ek jako odwiedzony
  for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów
  {
    u = p->v;                // u - numer s¹siada
    if(!visited[u])          // Interesuj¹ nas tylko nieodwiedzeni s¹siedzi
    {
      r = new slistEl;       // Dodajemy u do listy T[v]
      r->v = u;
      r->next = T[v];
      T[v] = r;
      DFSTree(u);            // Rekurencyjnie tworzymy drzewo
    }
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int n,m,i,v1,v2;
  slistEl *p, *r;

  cin >> n >> m;             // Czytamy liczbê wierzcho³ków i krawêdzi
  graf = new slistEl * [n];  // Tworzymy tablicê list s¹siedztwa grafu
  T    = new slistEl * [n];  // Tworzymy tablicê list s¹siedztwa drzewa rozpinaj¹cego
  visited = new bool [n];    // Tworzymy tablicê odwiedzin

  // Tablice wype³niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    graf[i] = T[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;         // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;         // Tworzymy nowy element
    p->v     = v2;           // Numerujemy go jako v2
    p->next  = graf[v1];     // Dodajemy go na pocz¹tek listy A[v1]
    graf[v1] = p;
    p = new slistEl;         // Teraz krawêdŸ w odwrotn¹ stronê
    p->v     = v1;
    p->next  = graf[v2];
    graf[v2] = p;
  }

  // Tworzymy drzewo rozpinaj¹ce w g³¹b

  cin >> v1;                 // Czytamy wierzcho³ek startowy

  DFSTree(v1);

  // Wyœwietlamy tablicê list s¹siedztwa drzewa rozpinaj¹cego

  cout << endl;

  for(i = 0; i < n; i++)
  {
    cout << setw(2) << i << " :";
    for(p = T[i]; p; p = p->next) cout << setw(3) << p->v;
    cout << endl;
  }

  // Usuwamy dynamiczne struktury danych

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }

    p = T[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] graf;
  delete [] T;
  delete [] visited;

  cout << endl;

  return 0;
} 