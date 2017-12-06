// Sortowanie topologiczne
// Data: 13.02.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

// Typy danych

struct slistEl
{
  slistEl *next;
  int v;
};

struct dlistEl
{
  dlistEl *prev,*next;
  int v;
};

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
  int n,m,i,v1,v2,*Vind;
  slistEl *ps,*rs,**graf;
  dlistEl *pd,*rd,*L;
  bool test;

  cin >> n >> m;                // Czytamy liczbę wierzchołków i krawędzi

  // Tworzymy tablice dynamiczne

  graf = new slistEl * [n];
  for(i = 0; i < n; i++) graf[i] = NULL;

  // Odczytujemy definicje krawędzi grafu

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;
    ps = new slistEl;
    ps->v = v2;
    ps->next = graf[v1];
    graf[v1] = ps;
  }

  cout << endl;

  // Wykonujemy sortowanie topologiczne grafu

  Vind = new int [n];           // Tworzymy tablicę stopni wchodzących
  for(i = 0; i < n; i++) Vind[i] = 0; // Zerujemy tablicę Vind[]

  for(i = 0; i < n; i++)        // Przeglądamy graf
    for(ps = graf[i];ps;ps = ps->next) // Przeglądamy sąsiadów każdego wierzchołka
      Vind[ps->v]++;            // Wyznaczamy ich stopnie wchodzące

  L = NULL;
  for(i = n - 1; i >= 0; i--)   // Na liście L umieszczamy od 0 do n - 1
  {
    pd = new dlistEl;
    pd->v = i;
    pd->next = L;
    if(pd->next) pd->next->prev = pd;
    pd->prev = NULL;
    L = pd;
  }

  do
  {
    test = false;               // Oznaczamy brak usunięcia wierzchołka

    pd = L;                     // Przeglądamy listę L
    while(pd)
      if(Vind[pd->v])pd = pd->next; // Wierzchołki o niezerowym stopniu wchodzącym pomijamy
      else
      {
        test = true;            // Będzie usunięcie wierzchołka
        for(ps = graf[pd->v];ps;ps = ps->next) // Przeglądamy listę sąsiadów
          Vind[ps->v]--;        // Modyfikujemy ich stopnie wchodzące

        cout << pd->v << " ";   // Wypisujemy usuwany wierzchołek
        rd = pd;                // Zapamiętujemy adres elementu L
        pd = pd->next;          // Następny wierzchołek na liście lub NULL!

        // Zapamiętany element rd listy L usuwamy z pamięci

        if(rd->next) rd->next->prev = rd->prev;
        if(rd->prev) rd->prev->next = rd->next;
        else L = pd;
        delete rd;
      }
  } while(test);

  cout << endl << endl;

  // Usuwamy zmienne dynamiczne

  delete [] Vind;

  for(i = 0; i < n; i++)
  {
    ps = graf[i];
    while(ps)
    {
      rs = ps;
      ps = ps->next;
      delete rs;
    }
  }
  delete [] graf;

  pd = L;
  while(pd)
  {
    rd = pd;
    pd = pd->next;
    delete rd;
  }

  return 0;
} 