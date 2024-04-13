
#include "Komorki.h"

#define Odleglosc 15
#define Szybkosc  1

typedef ULONG Obsluga( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom );

typedef Obsluga *Tablica[ T_Zlicz ];

extern Tablica tablica;

void Przeskanuj( Plansza *plansza );
