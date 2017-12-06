// Drzewo rozpinaj�ce w g��b
// Data: 22.09.2013
// (C)2013 mgr Jerzy Wa�aszek
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

slistEl ** graf; // Tablica list s�siedztwa grafu
slistEl ** T;    // Tablica list s�siedztwa drzewa rozpinaj�cego
bool * visited;  // Tablica odwiedzin

// Rekurencyjna funkcja tworzenia drzewa rozpinaj�cego w g��b
// v - numer wierzcho�ka startowego
// reszta zmiennych globalna
//-------------------------------------------------------------
void DFSTree(int v)
{
  slistEl *p, *r;
  int u;

  visited[v] = true;         // Oznaczamy wierzcho�ek jako odwiedzony
  for(p = graf[v]; p; p = p->next) // Przegl�damy s�siad�w
  {
    u = p->v;                // u - numer s�siada
    if(!visited[u])          // Interesuj� nas tylko nieodwiedzeni s�siedzi
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
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int n,m,i,v1,v2;
  slistEl *p, *r;

  cin >> n >> m;             // Czytamy liczb� wierzcho�k�w i kraw�dzi
  graf = new slistEl * [n];  // Tworzymy tablic� list s�siedztwa grafu
  T    = new slistEl * [n];  // Tworzymy tablic� list s�siedztwa drzewa rozpinaj�cego
  visited = new bool [n];    // Tworzymy tablic� odwiedzin

  // Tablice wype�niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    graf[i] = T[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;         // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;         // Tworzymy nowy element
    p->v     = v2;           // Numerujemy go jako v2
    p->next  = graf[v1];     // Dodajemy go na pocz�tek listy A[v1]
    graf[v1] = p;
    p = new slistEl;         // Teraz kraw�d� w odwrotn� stron�
    p->v     = v1;
    p->next  = graf[v2];
    graf[v2] = p;
  }

  // Tworzymy drzewo rozpinaj�ce w g��b

  cin >> v1;                 // Czytamy wierzcho�ek startowy

  DFSTree(v1);

  // Wy�wietlamy tablic� list s�siedztwa drzewa rozpinaj�cego

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