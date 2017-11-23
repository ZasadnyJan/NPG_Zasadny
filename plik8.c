// Wyznaczanie silnie sp�jnych sk�adowych
// Data: 18.01.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj�ca stos

  public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
  S = NULL;
}

// Destruktor - zwalnia tablic� dynamiczn�
//----------------------------------------
stack::~stack()
{
  while(S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
  if(S)
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Funkcja bada, czy istnieje �cie�ka od u do v
// u    - wierzcho�ek startowy �cie�ki
// v    - wierzcho�ek ko�cowy �cie�ki
// n    - liczba wierzcho�k�w w grafie
// graf - tablica list s�siedztwa
// Wynik:
// true - istnieje �cie�ka od u do v
// false- nie istnieje �cie�ka od u do v
//----------------------------------------------
bool DFSback(int u, int v, int n, slistEl ** graf)
{
  int i,x,y;
  stack S;
  bool * visited;
  slistEl * p;

  visited = new bool [n];        // Tworzymy tablic� odwiedzin
  for(i = 0; i < n; i++)         // i wype�niamy j� warto�ciami false
    visited[i] = false;

  S.push(u);                     // Wierzcho�ek startowy na stos
  visited[u] = true;             // Oznaczamy go jako odwiedzonego

  while(!S.empty())              // Uruchamiamy przej�cie DFS
  {
    x = S.top();                 // Pobieramy wierzcho�ek ze stosu
    S.pop();                     // Pobrany wierzcho�ek usuwamy ze stosu

    for(p = graf[x]; p; p = p->next) // Przegl�damy s�siad�w
    {
      y = p->v;                  // Numer s�siada do y
      if(y == v)                 // Je�li s�siadem jest wierzcho�ek v,
      {                          // to �cie�ka znaleziona
        delete [] visited;       // Usuwamy tablic� visited
        return true;             // Ko�czymy z wynikiem true
      }
      if(!visited[y])
      {
        S.push(y);               // Nieodwiedzonego s�siada umieszczamy na stosie
        visited[y] = true;       // i oznaczamy jako odwiedzonego
      }
    }
  }

  delete [] visited;             // Usuwamy tablic� visited
  return false;                  // i ko�czymy z wynikiem false
}

// Procedura przechodzi przez graf od wierzcho�ka startowego v
// i umieszcza w tablicy C informacj� o przynale�no�ci wierzcho�k�w
// do okre�lonej silnie sp�jnej sk�adowej.
// v    - wierzcho�ek startowy
// n    - liczba wierzcho�k�w w grafie
// graf - tablica list s�siedztwa
// cn   - numer silnie sp�jnej sk�adowej
// C    - tablica numer�w silnie sp�jnych sk�adowych dla wierzcho�k�w
// Wynik:
// Ustawia tablic� C
//--------------------------------------------------------------------
void DFSscc(int v, int n, slistEl ** graf, int cn, int * C)
{
  int i,u,w;
  stack S;
  bool * visited;
  slistEl * p;

  visited = new bool [n];
  for(i = 0; i < n; i++) visited[i] = false;

  S.push(v);                     // Wierzcho�ek startowy na stos
  visited[v] = true;             // Oznaczamy go jako odwiedzonego
  C[v] = cn;                     // Ustawiamy dla v numer sk�adowej

  while(!S.empty())              // Przej�cie DFS
  {
    u = S.top();                 // Odczytujemy wierzcho�ek ze stosu
    S.pop();                     // Usuwamy ze stosu odczytany wierzcho�ek

    if((u != v) && DFSback(u,v,n,graf)) C[u] = cn;

    for(p = graf[u]; p; p = p->next) // Przegl�damy s�siad�w wierzcho�ka u
    {
      w = p->v;
      if(!visited[w])
      {
        S.push(w);               // Nieodwiedzonego s�siada umieszczamy na stosie
        visited[w] = true;       // i oznaczamy jako odwiedzonego
      }
    }
  }

  delete [] visited;
}

// **********************
// *** Program g��wny ***
// **********************

int main()
{
  int n,m;                   // Liczba wierzcho�k�w i kraw�dzi
  slistEl ** graf;           // Tablica list s�siedztwa
  int * C;                   // Tablica z numerami sp�jnych sk�adowych
  int i,v,u,cn;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  graf = new slistEl * [n];  // Tworzymy tablice dynamiczne
  C = new int [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    C[i] = 0;
  }

  // Odczytujemy kolejne definicje kraw�dzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz�tek listy graf[v]
    graf[v] = p;
  }

  // Wyznaczamy silnie sp�jne sk�adowe

  cn = 0;                    // Inicjujemy licznik sk�adowych

  for(v = 0; v <= n - 1; v++) // Przegl�damy kolejne wierzcho�ki grafu
    if(!C[v]) DFSscc(v,n,graf,++cn,C); // Wyznaczamy silnie sp�jn� sk�adow�


  // Wy�wietlamy silnie sp�jne sk�adowe

  cout << endl;

  for(i = 1; i <= cn; i++)
  {
    cout << "SCC" << setw(3) << i << " :";
    for(v = 0; v < n; v++) if(C[v] == i) cout << setw(3) << v;
    cout << endl;
  }

  cout << endl;

  // Usuwamy tablice dynamiczne

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] graf;
  delete [] C;

  return 0;
} 