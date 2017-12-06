// Problem komiwojażera
// Data: 22.03.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

// Zmienne globalne

int n,m,v0,d,dh,sptr,shptr;
bool **A;                         // Macierz sąsiedztwa
int **W;                          // Macierz wag krawędzi
int *S,*Sh;                       // Stosy w tablicy
bool *visited;                    // Tablica odwiedzin

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag krawędzi
// v - wierzchołek bieżący
//----------------------------------------------------
void TSP(int v)
{
  int u;

  Sh[shptr++] = v;                // zapamiętujemy na stosie bieżący wierzchołek

  if(shptr < n)                   // jeśli brak ścieżki Hamiltona, to jej szukamy
  {
    visited[v] = true;            // Oznaczamy bieżący wierzchołek jako odwiedzony
    for(u = 0; u < n; u++)        // Przeglądamy sąsiadów wierzchołka v
      if(A[v][u] && !visited[u])  // Szukamy nieodwiedzonego jeszcze sąsiada
      {
        dh += W[v][u];            // Dodajemy wagę krawędzi v-u do sumy
        TSP(u);                   // Rekurencyjnie wywołujemy szukanie cyklu Hamiltona
        dh -= W[v][u];            // Usuwamy wagę krawędzi z sumy
      }
    visited[v] = false;           // Zwalniamy bieżący wierzchołek
  }
  else if(A[v0][v])               // Jeśli znaleziona ścieżka jest cyklem Hamiltona
  {
    dh += W[v][v0];               // to sprawdzamy, czy ma najmniejszą sumę wag
    if(dh < d)                    // Jeśli tak,
    {
      d = dh;                     // To zapamiętujemy tę sumę
      for(u = 0; u < shptr; u++)  // oraz kopiujemy stos Sh do S
        S[u] = Sh[u];
      sptr = shptr;
    }
    dh -= W[v][v0];               // Usuwamy wagę krawędzi v-v0 z sumy
  }
  shptr--;                        // Usuwamy bieżący wierzchołek ze ścieżki
}

//**********************
//*** Program główny ***
//**********************

int main()
{
  int i,j,x,y,z;

  cin >> n >> m;                  // Czytamy liczbę wierzchołków i krawędzi

  // Tworzymy struktury dynamiczne i inicjujemy je

  S       = new int [n];
  Sh      = new int [n];
  visited = new bool [n];
  A       = new bool * [n];
  W       = new int * [n];
  for(i = 0; i < n; i++)
  {
    A[i] = new bool [n];
    W[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      A[i][j] = false;
      W[i][j] = 0;
    }
    visited[i] = false;
  }
  sptr = shptr = 0;

  // Odczytujemy dane wejściowe

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> z;
    A[x][y] = A[y][x] = true;     // Krawędź x-y
    W[x][y] = W[y][x] = z;        // Waga krawędzi x-y
  }

  cout << endl;

  // Rozpoczynamy algorytm

  d  = MAXINT;
  dh = v0 = 0;
  TSP(v0);
  if(sptr)
  {
    for(i = 0; i < sptr; i++) cout << S[i] << " ";
    cout << v0 << endl;
    cout << "d = " << d << endl;
  }
  else cout << "NO HAMILTONIAN CYCLE" << endl;

  cout << endl;

  // Usuwamy tablice dynamiczne

  delete [] S;
  delete [] Sh;
  delete [] visited;

  for(i = 0; i < n; i++)
  {
    delete [] A[i];
    delete [] W[i];
  }

  delete [] A;
  delete [] W;

  return 0;
} 
