// Wyszukiwanie cyklu Eulera
// Data: 19.03.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

// Zmienne globalne

int n,m,sptr;
int ** A;                       // Macierz sąsiedztwa
int * S;                        // Stos w tablicy

// Procedura wyszukuje cykl Eulera
// We:
// v - wierzchołek startowy
//--------------------------------
void DFSEuler(int v)
{
  int i;

  for(i = 0; i < n; i++)          // Przeglądamy sąsiadów
    while(A[v][i])
    {
      A[v][i]--;                  // Usuwamy krawędź
      A[i][v]--;
      DFSEuler(i);                // Rekurencja
    }
  S[sptr++] = v;                  // Wierzchołek v umieszczamy na stosie
}

// **********************
// *** Program główny ***
// **********************

int main()
{
  int i,j,v1,v2;

  cin >> n >> m;                // Czytamy liczbę wierzchołków i krawędzi

  A = new int * [n];            // Tworzymy tablicę wskaźników
  S = new int [m + 1];          // Tworzymy stos
  sptr = 0;

  for(i = 0; i < n; i++)
    A[i] = new int [n];         // Tworzymy wiersze macierzy sąsiedztwa

  // Macierz wypełniamy zerami

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) A[i][j] = 0;

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // wierzchołki końcowe krawędzi
    A[v1][v2]++;        // Krawędź v1->v2 obecna
    A[v2][v1]++;        // Krawędź v2->v1 obecna
  }

  cout << endl;

  // Wyznaczamy cykl Eulera

  DFSEuler(0);

  // Wypisujemy zawartość stosu

  cout << "EULERIAN CYCLE : ";

  for(i = 0; i < sptr; i++) cout << S[i] << " ";
  cout << endl;

  // Usuwamy tablice dynamiczne

  for(i = 0; i < n; i++) delete [] A[i];

  delete [] A;
  delete [] S;

  return 0;
} 