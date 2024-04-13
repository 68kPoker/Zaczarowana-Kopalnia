
#include "Obiekty.h"

typedef struct Przesuniecie
{
    BYTE dx, dy;
} Przesuniecie;

Przesuniecie przes[] =
{
    { -1,  0 },
    {  0, -1 },
    {  1,  0 },
    {  0,  1 }
};

Kierunek opozycja[] =
{
    K_Prawo,
    K_Dol,
    K_Lewo,
    K_Gora
};

void Przemiesc( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom, Kierunek kier, Komorka *cel )
{
    cel->obiekt = kom->obiekt;
    cel->obiekt.kier = opozycja[ kier ];
    cel->obiekt.odleglosc = Odleglosc;

    kom->obiekt.typ = T_Pusta;

    kom->sasiedzi[ kier ].odleglosc = 0;
    cel->sasiedzi[ opozycja[ kier ] ].odleglosc = Odleglosc;

    if( kier == K_Prawo || kier == K_Dol )
    {
        cel->przeskanowane = TRUE;
    }
}

ULONG Glaz( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom )
{
    Komorka *cel;

    cel = plansza->komorki[ y + 1 ] + x;

    if( cel->obiekt.typ == T_Pusta )
    {
        Przemiesc( plansza, x, y, kom, K_Dol, cel );
        return( 1 );
    }
    else if( cel->obiekt.typ == T_Sciana || cel->obiekt.typ == T_Glaz || cel->obiekt.typ == T_Diament )
    {
        cel = plansza->komorki[ y ] + x - 1;

        if( cel->obiekt.typ == T_Pusta && plansza->komorki[ y + 1 ][ x - 1 ].obiekt.typ == T_Pusta )
        {
            Przemiesc( plansza, x, y, kom, K_Lewo, cel );
            return( 1 );
        }

        cel = plansza->komorki[ y ] + x + 1;

        if( cel->obiekt.typ == T_Pusta && plansza->komorki[ y + 1 ][ x + 1 ].obiekt.typ == T_Pusta )
        {
            Przemiesc( plansza, x, y, kom, K_Prawo, cel );
            return( 1 );
        }
    }

    return( 0 );
}

ULONG Diament( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom )
{
    Komorka *cel;

    cel = plansza->komorki[ y + 1 ] + x;

    if( cel->obiekt.typ == T_Pusta )
    {
        Przemiesc( plansza, x, y, kom, K_Dol, cel );
        return( 1 );
    }
    else if( cel->obiekt.typ == T_Sciana || cel->obiekt.typ == T_Glaz || cel->obiekt.typ == T_Diament )
    {
        cel = plansza->komorki[ y ] + x - 1;

        if( cel->obiekt.typ == T_Pusta && plansza->komorki[ y + 1 ][ x - 1 ].obiekt.typ == T_Pusta )
        {
            Przemiesc( plansza, x, y, kom, K_Lewo, cel );
            return( 1 );
        }

        cel = plansza->komorki[ y ] + x + 1;

        if( cel->obiekt.typ == T_Pusta && plansza->komorki[ y + 1 ][ x + 1 ].obiekt.typ == T_Pusta )
        {
            Przemiesc( plansza, x, y, kom, K_Prawo, cel );
            return( 1 );
        }
    }

    return( 0 );
}

ULONG Bohater( Plansza *plansza, UBYTE x, UBYTE y, Komorka *kom )
{
    return( 0 );
}

void Przeskanuj( Plansza *plansza )
{
    UBYTE x, y;
    Komorka *kom, *cel;
    Kierunek kier;

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            kom = plansza->komorki[ y ] + x;
            kier = kom->obiekt.kier;

            if( !kom->przeskanowane )
            {
                if( kom->obiekt.odleglosc == 0 )
                {
                    Obsluga *obsluga = tablica[ kom->obiekt.typ ];

                    if( obsluga )
                    {
                        obsluga( plansza, x, y, kom );
                    }
                }
                else
                {
                    kom->obiekt.odleglosc -= Szybkosc;
                    kom->sasiedzi[ kier ].odleglosc -= Szybkosc;                    
                    cel = plansza->komorki[ y + przes[ kier ].dy ] + x + przes[ kier ].dx;
                    cel->sasiedzi[ opozycja[ kier ] ].odleglosc += Szybkosc;
                }
            }
            else
            {
                kom->przeskanowane = FALSE;
            }
        }
    }
}

Tablica tablica =
{
    NULL,
    NULL,
    NULL,
    Glaz,
    Diament,
    Bohater
};
