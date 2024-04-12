
/* Komorki */

#include <exec/types.h>

#define P_Szer 20
#define P_Wys  16

#define NP_MaxOperacje 16

typedef enum TypObiektu
{
    T_Ziemia,
    T_Pusta,
    T_Sciana,
    T_Glaz,
    T_Diament,
    T_Bohater,
    T_Zlicz
} TypObiektu;

typedef enum Stan
{
    S_Stoi,
    S_Spada
} Stan;

typedef enum Kierunek
{
    K_Lewo,
    K_Gora,
    K_Prawo,
    K_Dol,
    K_Zlicz
} Kierunek;

typedef enum TypOperacji /* Dot. tworzenia planszy */
{
    O_Wstaw,
    O_Linia,
    O_Prostokat
} TypOperacji;

typedef union Tryb
{
    Stan stan;
    Kierunek kierunek;
} Tryb;

typedef struct Sasiad
{
    UBYTE rozmiar;
    UBYTE grafika;
} Sasiad;

typedef struct Obiekt
{
    TypObiektu typ;
    Tryb tryb;
    UBYTE grafika;
    UBYTE klatka;
} Obiekt;

typedef struct Komorka
{
    Obiekt obiekt;    
    Sasiad sasiedzi[ K_Zlicz ];
    BOOL przeskanowane;
} Komorka, Wiersz[ P_Szer ], Macierz[ P_Wys ][ P_Szer ];

typedef struct Plansza
{
    Macierz komorki;
    UBYTE X, Y;
} Plansza;

typedef struct Operacja
{
    TypOperacji typ;
    Obiekt obiekt;
    UBYTE lewo, gora, prawo, dol;
} Operacja;

typedef struct NowaPlansza
{
    ULONG ziarno;
    UWORD dystrybucja[ T_Zlicz ];
    Operacja operacje[ NP_MaxOperacje ];
    UBYTE zlicz;
} NowaPlansza;

void UtworzPlansze( Plansza *plansza, NowaPlansza *np );

/** EOF **/
