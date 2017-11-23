// Wyznaczanie silnie spójnych sk³adowych
// Data: 18.01.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj¹ca stos

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

// Destruktor - zwalnia tablicê dynamiczn¹
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

// Funkcja bada, czy istnieje œcie¿ka od u do v
// u    - wierzcho³ek startowy œcie¿ki
// v    - wierzcho³ek koñcowy œcie¿ki
// n    - liczba wierzcho³ków w grafie
// graf - tablica list s¹siedztwa
// Wynik:
// true - istnieje œcie¿ka od u do v
// false- nie istnieje œcie¿ka od u do v
//----------------------------------------------
bool DFSback(int u, int v, int n, slistEl ** graf)
{
  int i,x,y;
  stack S;
  bool * visited;
  slistEl * p;

  visited = new bool [n];        // Tworzymy tablicê odwiedzin
  for(i = 0; i < n; i++)         // i wype³niamy j¹ wartoœciami false
    visited[i] = false;

  S.push(u);                     // Wierzcho³ek startowy na stos
  visited[u] = true;             // Oznaczamy go jako odwiedzonego

  while(!S.empty())              // Uruchamiamy przejœcie DFS
  {
    x = S.top();                 // Pobieramy wierzcho³ek ze stosu
    S.pop();                     // Pobrany wierzcho³ek usuwamy ze stosu

    for(p = graf[x]; p; p = p->next) // Przegl¹damy s¹siadów
    {
      y = p->v;                  // Numer s¹siada do y
      if(y == v)                 // Jeœli s¹siadem jest wierzcho³ek v,
      {                          // to œcie¿ka znaleziona
        delete [] visited;       // Usuwamy tablicê visited
        return true;             // Koñczymy z wynikiem true
      }
      if(!visited[y])
      {
        S.push(y);               // Nieodwiedzonego s¹siada umieszczamy na stosie
        visited[y] = true;       // i oznaczamy jako odwiedzonego
      }
    }
  }

  delete [] visited;             // Usuwamy tablicê visited
  return false;                  // i koñczymy z wynikiem false
}

// Procedura przechodzi przez graf od wierzcho³ka startowego v
// i umieszcza w tablicy C informacjê o przynale¿noœci wierzcho³ków
// do okreœlonej silnie spójnej sk³adowej.
// v    - wierzcho³ek startowy
// n    - liczba wierzcho³ków w grafie
// graf - tablica list s¹siedztwa
// cn   - numer silnie spójnej sk³adowej
// C    - tablica numerów silnie spójnych sk³adowych dla wierzcho³ków
// Wynik:
// Ustawia tablicê C
//--------------------------------------------------------------------
void DFSscc(int v, int n, slistEl ** graf, int cn, int * C)
{
  int i,u,w;
  stack S;
  bool * visited;
  slistEl * p;

  visited = new bool [n];
  for(i = 0; i < n; i++) visited[i] = false;

  S.push(v);                     // Wierzcho³ek startowy na stos
  visited[v] = true;             // Oznaczamy go jako odwiedzonego
  C[v] = cn;                     // Ustawiamy dla v numer sk³adowej

  while(!S.empty())              // Przejœcie DFS
  {
    u = S.top();                 // Odczytujemy wierzcho³ek ze stosu
    S.pop();                     // Usuwamy ze stosu odczytany wierzcho³ek

    if((u != v) && DFSback(u,v,n,graf)) C[u] = cn;

    for(p = graf[u]; p; p = p->next) // Przegl¹damy s¹siadów wierzcho³ka u
    {
      w = p->v;
      if(!visited[w])
      {
        S.push(w);               // Nieodwiedzonego s¹siada umieszczamy na stosie
        visited[w] = true;       // i oznaczamy jako odwiedzonego
      }
    }
  }

  delete [] visited;
}

// **********************
// *** Program g³ówny ***
// **********************

int main()
{
  int n,m;                   // Liczba wierzcho³ków i krawêdzi
  slistEl ** graf;           // Tablica list s¹siedztwa
  int * C;                   // Tablica z numerami spójnych sk³adowych
  int i,v,u,cn;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczbê wierzcho³ków i krawêdzi

  graf = new slistEl * [n];  // Tworzymy tablice dynamiczne
  C = new int [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    C[i] = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz¹tek listy graf[v]
    graf[v] = p;
  }

  // Wyznaczamy silnie spójne sk³adowe

  cn = 0;                    // Inicjujemy licznik sk³adowych

  for(v = 0; v <= n - 1; v++) // Przegl¹damy kolejne wierzcho³ki grafu
    if(!C[v]) DFSscc(v,n,graf,++cn,C); // Wyznaczamy silnie spójn¹ sk³adow¹


  // Wyœwietlamy silnie spójne sk³adowe

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