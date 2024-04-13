
#include "Komorki.h"

#define Szybkosc  2
#define Odleglosc (16 - Szybkosc)

typedef ULONG Obsluga( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom );

typedef Obsluga *Tablica[ T_Zlicz ];

extern Tablica tablica;

void Przeskanuj( Plansza *plansza );

void NarysujPlansze( Plansza *plansza );
