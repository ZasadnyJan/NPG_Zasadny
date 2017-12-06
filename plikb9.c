// Algorytm Floyda-Warshalla
// Data   : 20.04.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // "plus nieskończoność"

int main()
{
  int ** d;                       // Macierz minimalnych kosztów dojścia
  int i,j,k,n,m,x,y,w;

  cin >> n >> m;                  // Czytamy liczbę wierzchołków oraz krawędzi

  d = new int * [n];              // Tworzymy dynamiczną macierz d
  for(i = 0; i < n; i++)
  {
    d[i] = new int [n];           // Tworzymy wiersz macierzy
    for(j = 0; j < n; j++)
      d[i][j] = MAXINT;           // Wiersz wypełniamy największą liczbą dodatnią
    d[i][i] = 0;                  // Jednakże na przekątnej wpisujemy 0
  }

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Czytamy definicję krawędzi
    d[x][y] = w;                  // Wagę krawędzi umieszczamy w macierzy d
  }

  // Algorytm Floyda-Warshalla

  for(k = 0; k < n; k++)
    for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
      {
        if((d[i][k] == MAXINT) || (d[k][j] == MAXINT)) continue;
        w = d[i][k] + d[k][j];
        if(d[i][j] > w) d[i][j] = w;
      }

  // Wyświetlamy wyniki

  cout << endl;

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
    {
      cout << "d[" << i << "," << j << "] = ";
      if(d[i][j] == MAXINT) cout << "NO PATH";
      else                  cout << d[i][j];
      cout << endl;
    }

  // Usuwamy macierz dynamiczną

  for(i = 0; i < n; i++) delete [] d[i];
  delete [] d;

  return 0;
} 