// Znajdowanie wyj�cia z labiryntu
// Data: 25.08.2013
// (C)2013 mgr Jerzy Wa�aszek
//--------------------------------

#include <iostream>
#include <string>
//zmiana
using namespace std;

const int MAXINT = -2147483647;

// Typy dla kolejki

struct slistEl
{
  slistEl * next;
  int v;
};

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
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu queue
//---------------------

// Konstruktor - tworzy pust� list�
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa list� z pami�ci
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

// Zwraca pocz�tek kolejki.
// Warto�� specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->v;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int v)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->v = v;
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

// Zmienne globalne
//-----------------

int wst,kst;                  // Wsp�rz�dne startowe - wiersz, kolumna
int wwy,kwy;                  // Wsp�rz�dne wyj�cia  - wiersz, kolumna
int n = 10;                   // Liczba wierszy
string * L = new string [n];  // Labirynt

// Odczytuje labirynt
// Wyszukuje wierzcho�ki
// startowy i wyj�ciowy
//----------------------
void czytajL()
{
  string s, * T;
  int i,j;

  i = 0;                  // Licznik wierszy
  do
  {
    cin >> s;             // Czytamy wiersz z wej�cia
    if(s != "*")          // Je�li nie jest to wiersz ko�cowy, to
    {
      if(n < i+1)         // ustawiamy rozmiar tablicy
      {
        T = new string [i + 10];
        for(j = 0; j < n; j++) T[j] = L[j];
        delete [] L;
        L = T;
        n = i + 10;
      }
      L[i++] = s;         // odczytany wiersz umieszczamy w tablicy M
    }
  } while(s != "*");

  n = i;                  // Liczba wierszy w L

  wst = kst = wwy = kwy = -1; // Wsp�rz�dne startu oraz wyj�cia

  for(i = 0; i < n; i++)  // Szukamy S i W
    for(j = 0; j < (int)L[i].length(); j++)
      if(L[i][j] == 'S')
      {
        wst = i; kst = j;   // S znalezione
      }
      else if(L[i][j] == 'W')
      {
        wwy = i; kwy = j;   // W znalezione
        L[i][j] = '.';
      }
}

// Procedura szukania wyj�cia
//---------------------------
void SzukajW()
{
  queue Q;
  int w,k;                   // Wiersz, kolumna bie��cego wierzcho�ka
  int i,j;

  Q.push(wst);               // W kolejce umieszczamy wierzcho�ek startowy
  Q.push(kst);

  while(!Q.empty())
  {
    w = Q.front(); Q.pop();  // Pobieramy z kolejki wiersz
    k = Q.front(); Q.pop();  // i kolumn� bie��cego wierzcho�ka

    // Sprawdzamy, czy osi�gn�li�my wyj�cie

    if((w == wwy) && (k == kwy)) break;

    // Przegl�damy s�siad�w bie��cego wierzcho�ka

    for(i = -1; i <= 1; i++)
      for(j = -1; j <= 1; j++)
        if((i != j) && (!i || !j))
        {
          if(L[w+i][k+j] == '.')
          {
            // W kom�rce s�siada zapisujemy, sk�d przyszli�my do niej

            if(     i == -1) L[w+i][k+j] = 'd';  // z do�u
            else if(i ==  1) L[w+i][k+j] = 'g';  // z g�ry
            else if(j == -1) L[w+i][k+j] = 'p';  // z prawej
            else             L[w+i][k+j] = 'l';  // z lewej

            Q.push(w+i);       // S�siad zostaje umieszczony w kolejce
            Q.push(k+j);
          }
        }
  }
}

// Procedura wypisuje labirynt z ewentualn� �cie�k�
// Zast�puje znaki kierunk�w znakiem -.
//-------------------------------------------------
void PiszL()
{
  int i,j;
  char c;

  // Najpierw sprawdzamy, czy �cie�ka zosta�a znaleziona
  // Je�li tak, to zast�pujemy j� znakami +

  if(L[wwy][kwy] != '.')
  {
    i = wwy; j = kwy;

    while((i != wst) || (j != kst))
    {
      c = L[i][j];
      L[i][j] = '+';
      switch(c)
      {
        case 'd' : i++; break;
        case 'g' : i--; break;
        case 'p' : j++; break;
        case 'l' : j--; break;
      }
    }
  }

  L[wwy][kwy] = 'W'; // Odtwarzamy znak wyj�cia

  // Teraz usuwamy znaki kierunku i wypisujemy labirynt

  for(i = 0; i < n; i++)
  {
    for(j = 0; j < (int)L[i].length(); j++)
      switch(L[i][j])
      {
        case 'g': ;
        case 'd': ;
        case 'p': ;
        case 'l': L[i][j] = ' ';
      }
    cout << L[i] << endl;
  }
  cout << endl;
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  czytajL();    // Wczytujemy labirynt

  if((wst == -1) || (kst == -1) || (wwy == -1) || (kwy == -1))
    cout << "BRAK DEFINICJI S LUB W !!!\n";
  else
  {
    SzukajW(); // Szukamy wyj�cia
    PiszL();   // Wy�wietlamy wyniki poszukiwa�
  }
  return 0;
} 