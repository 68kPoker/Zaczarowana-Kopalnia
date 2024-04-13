
#include <stdio.h>

#include "Obiekty.h"

void NarysujPole( Plansza *plansza, UBYTE x, UBYTE y )
{
    Komorka *kom = plansza->komorki[ y ] + x;
    Grafika *graf, *poprz;
    UBYTE i;
    STRPTR nazwy[ 4 ] =
    {
        "Lewo",
        "Gora",
        "Prawo",
        "Dol"
    };

    if( kom->ten.grafika != kom->poprz.grafika || kom->ten.odleglosc != kom->poprz.odleglosc )
    {
        printf( "(%2d/%2d): Odswiezam (%2d, %2d) -> (%2d, %2d)\n", x, y, kom->poprz.grafika, kom->poprz.odleglosc, kom->ten.grafika, kom->ten.odleglosc );
        kom->poprz = kom->ten;
    }

    for( i = 0; i < 4; i++ )
    {
        graf = kom->sasiedzi + i;
        poprz = kom->poprzSasiedzi + i;

        if( graf->grafika != poprz->grafika || graf->odleglosc != poprz->odleglosc )
        {
            if( graf->odleglosc < 16 )
                printf( "(%2d/%2d): %-9s (%2d, %2d) -> (%2d, %2d)\n", x, y, nazwy[ i ], poprz->grafika, poprz->odleglosc, graf->grafika, graf->odleglosc );
            else
                printf( "(%2d/%2d): %-9s (%2d, %2d) -> (Czyszcze)\n", x, y, nazwy[ i ], poprz->grafika, poprz->odleglosc );
            *poprz = *graf;
        }
    }
    
}

void NarysujPlansze( Plansza *plansza )
{
    UBYTE x, y;

    printf( "Plansza:\n" );

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            NarysujPole( plansza, x, y );
        }
    }
    putchar( '\n' );
}
