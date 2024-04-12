
#include "Komorki.h"

#define Rozmiar  16
#define Szybkosc 2

typedef ULONG Obsluga( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom );

typedef Obsluga *Tablica[ T_Zlicz ];

extern Tablica tablica;

void Przeskanuj( Plansza *plansza );
