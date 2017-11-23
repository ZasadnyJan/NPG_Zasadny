// Kwadrat grafu
// Data: 25.01.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  int n,m,i,j,k,v1,v2;
  char ** A, ** AK;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A  = new char * [n];   // Tworzymy tablice wskaŸników
  AK = new char * [n];

  for(i = 0; i < n; i++)
  {
    A[i]  = new char [n]; // Tworzymy wiersze
    AK[i] = new char [n];
  }

  // Macierz wype³niamy zerami

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) A[i][j] = 0;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    A[v1][v2] = 1;      // KrawêdŸ v1->v2 obecna
  }

  cout << endl;

  // Obliczamy kwadrat grafu w macierzy AK

  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++) AK[i][j] = A[i][j];
    for(j = 0; j < n; j++)
      if((i != j) && A[i][j])
        for(k = 0; k < n; k++)
          if(A[j][k]) AK[i][k] = 1;
  }

  // Wypisujemy zawartoœæ macierzy s¹siedztwa AK

  cout << "   ";
  for(i = 0; i < n; i++) cout << setw(3) << i;
  cout << endl << endl;
  for(i = 0; i < n; i++)
  {
    cout << setw(3) << i;
    for(j = 0; j < n; j++) cout << setw(3) << (int) AK[i][j];
    cout << endl;
  }

  // Usuwamy macierze

  for(i = 0; i < n; i++)
  {
    delete [] A[i];
    delete [] AK[i];
  }
  delete [] A;
  delete [] AK;

  cout << endl;

  return 0;
} 