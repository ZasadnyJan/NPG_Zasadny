// Kojarzenie małżeństw
// Data: 23.12.2013
// (C)2013 mgr Jerzy Wałaszek
//----------------------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i kolejki

struct slistEl
{
  slistEl * next;
  int v;
};

const int MAXINT = -2147483647;

// Definicja typu obiektowego queue
//---------------------------------
class queue
{
  private:
    slistEl * head;
    slistEl * tail;

  public:
    queue();      // konstruktor
    ~queue();     // destruktor
    bool empty(void);
    int  front(void);
    void push(int x);
    void pop(void);
};

//---------------------
// Metody obiektu queue
//---------------------

// Konstruktor - tworzy pustą listę
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa listę z pamięci
//-----------------------------------
queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void)
{
  return !head;
}

// Zwraca początek kolejki.
// Wartość specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->v;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int x)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->v    = x;
  if(tail) tail->next = p;
  else     head = p;
  tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void)
{
  if(head)
  {
    slistEl * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
  int n,m,i,v,x,y, * matching, * augment;
  slistEl * p,* r, ** graf;
  bool * visited, * color;
  queue Q;

  cin >> n >> m;                // Czytamy liczbę wierzchołków i krawędzi

  // Tworzymy zmienne dynamiczne

  color    = new bool[n];       // Kawalerowie (true), panny (false)
  matching = new int[n];        // Skojarzenia
  augment  = new int[n];        // Ścieżka rozszerzająca
  visited  = new bool[n];       // Odwiedziny
  graf     = new slistEl * [n]; // Tworzymy tablicę list sąsiedztwa

  // Tablicę wypełniamy pustymi listami

  for(i = 0; i < n; i++) graf[i] = NULL;

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> x >> y;              // Krawędź panna --- kawaler
    p = new slistEl;            // Tworzymy nowy element
    p->v = y;                   // Numerujemy go jako kawaler
    p->next = graf[x];          // Dodajemy go na początek listy panny
    graf[x] = p;
    p = new slistEl;            // Tworzymy nowy element
    p->v = x;                   // Numerujemy go jako pannę
    p->next = graf[y];          // Dodajemy go na początek listy kawalera
    graf[y] = p;
    color[x] = false;           // Panna
    color[y] = true;            // Kawaler
  }

  cout << endl;

  // Algorytm znajdowania maksymalnego skojarzenia

  for(i = 0; i < n; i++)        // Elementy tablicy matching ustawiamy na -1
    matching[i] = -1;           // Co oznacza brak skojarzenia

  for(v = 0; v < n; v++)        // Przechodzimy przez kolejne wierzchołki
    if((matching[v] == -1) && !color[v])
    {
      for(i = 0; i < n; i++)
        visited[i] = false;     // Zerujemy tablicę odwiedzin

      while(!Q.empty()) Q.pop();// Zerujemy kolejkę

      visited[v] = true;        // Oznaczamy v jako wierzchołek odwiedzony
      augment[v] = -1;          // Poprzednikiem v jest korzeń drzewa rozpinającego
      Q.push(v);                // Umieszczamy v w kolejce

      while(!Q.empty())         // Uruchamiamy BFS
      {
        x = Q.front();          // Pobieramy x z kolejki
        Q.pop();                // Pobrany wierzchołek usuwamy z kolejki

        if(color[x])
        {                       // Kawalerowie
          if(matching[x] == -1)
          {                     // Kawaler wolny
            while(augment[x] > -1)
            {
              if(color[x])
              {                 // Zamieniamy krawędzie skojarzone z nieskojarzonymi
                matching[x] = augment[x];
                matching[augment[x]] = x;
              }
              x = augment[x];   // Cofamy się po ścieżce rozszerzającej
            }
            break;              // Wracamy do pętli głównej
          }
          else
          {                     // Kawaler skojarzony
            augment[matching[x]] = x;
            visited[matching[x]] = true;
            Q.push(matching[x]);// W kolejce umieszczamy skojarzoną pannę
          }
        }
        else
        {                       // Panny
          p = graf[x];          // Przeglądamy kawalerów
          while(p)
          {
            y = p->v;           // Numer kawalera
            if(!visited[y])     // Tylko kawalerowie nieskojarzeni
            {                   // są umieszczani w kolejce
              visited[y] = true;
              augment[y] = x;   // Tworzymy ścieżkę rozszerzającą
              Q.push(y);
            }
            p = p->next;
          }
        }
      }
    }

  // Wyświetlamy skojarzenia panna --- kawaler

  for(i = 0; i < n; i++)
    if(!color[i]) cout << i << " --- " << matching[i] << endl;

  // Usuwamy dynamiczne struktury danych

  delete [] color;
  delete [] matching;
  delete [] augment;
  delete [] visited;

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

  return 0;
} 