// Algorytm Dijkstry z wyszukiwaniem liniowym
// Data: 15.03.2014
// (C)2014 mgr Jerzy Wałaszek
//-------------------------------------------

#include <iostream>

using namespace std;

// Typy danych

struct slistEl
{
  slistEl * next;
  int v,w;                        // numer węzła docelowego i waga krawędzi
};

const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
  int i,j,m,n,v,u,w,x,y,sptr,*d,*p,*S;
  bool *QS;                       // Zbiory Q i S
  slistEl **graf;                 // Tablica list sąsiedztwa
  slistEl *pw,*rw;

  cin >> v >> n >> m;             // Węzeł startowy, liczba wierzchołków i krawędzi

  // Tworzymy tablice dynamiczne

  d = new int [n];                // Tablica kosztów dojścia
  p = new int [n];                // Tablica poprzedników
  QS = new bool [n];              // Zbiory Q i S
  graf = new slistEl * [n];       // Tablica list sąsiedztwa
  S = new int [n];                // Stos
  sptr = 0;                       // Wskaźnik stosu

  // Inicjujemy tablice dynamiczne

  for(i = 0; i < n; i++)
  {
    d[i] = MAXINT;
    p[i] = -1;
    QS[i] = false;
    graf[i] = NULL;
  }

  // Odczytujemy dane wejściowe

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Odczytujemy krawędź z wagą
    pw = new slistEl;             // Tworzymy element listy sąsiedztwa
    pw->v = y;                    // Wierzchołek docelowy krawędzi
    pw->w = w;                    // Waga krawędzi
    pw->next = graf[x];
    graf[x] = pw;                 // Element dołączamy do listy
  }

  cout << endl;

  d[v] = 0;                       // Koszt dojścia v jest zerowy

  // Wyznaczamy ścieżki

  for(i = 0; i < n; i++)
  {
    // Szukamy wierzchołka w Q o najmniejszym koszcie d

    for(j = 0; QS[j]; j++);
    for(u = j++; j < n; j++)
      if(!QS[j] && (d[j] < d[u])) u = j;

    // Znaleziony wierzchołek przenosimy do S

    QS[u] = true;

    // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q

    for(pw = graf[u]; pw; pw = pw->next)
      if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
      {
        d[pw->v] = d[u] + pw->w;
        p[pw->v] = u;
      }
  }

  // Gotowe, wyświetlamy wyniki

  for(i = 0; i < n; i++)
  {
    cout << i << ": ";

    // Ścieżkę przechodzimy od końca ku początkowi,
    // Zapisując na stosie kolejne wierzchołki

    for(j = i; j > -1; j = p[j]) S[sptr++] = j;

    // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

    while(sptr) cout << S[--sptr] << " ";

    // Na końcu ścieżki wypisujemy jej koszt

    cout << "$" << d[i] << endl;
  }

  // Usuwamy tablice dynamiczne

  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

  for(i = 0; i < n; i++)
  {
    pw = graf[i];
    while(pw)
    {
      rw = pw;
      pw = pw->next;
      delete rw;
    }
  }

  delete [] graf;

  return 0;
} 