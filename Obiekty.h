
#include <exec/types.h>

#include "Komorki.h"

#define Szybkosc  2
#define Odleglosc (16 - Szybkosc)

typedef struct Przesuniecie
{
    BYTE dx, dy;
} Przesuniecie;

extern UBYTE klatki[ T_Zlicz ];
extern Przesuniecie przes[];

typedef ULONG Obsluga( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom );

typedef Obsluga *Tablica[ T_Zlicz ];

extern Tablica tablica;

void Przeskanuj( Plansza *plansza );

void NarysujPlansze( Plansza *plansza );
