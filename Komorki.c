
#include <stdio.h>
#include <stdlib.h>

#include "Obiekty.h"

void PoliczDystrybucje( NowaPlansza *np )
{
    UBYTE typ;

    for( typ = 1; typ < T_Zlicz; typ++ )
    {
        np->dystrybucja[ typ ] += np->dystrybucja[ typ - 1 ];
    }
}

void UstawPole( Komorka *kom, TypObiektu typ )
{
    kom->obiekt.typ = typ;
    kom->ten.grafika = klatki[ typ ];
}

void ZainicjujPole( Plansza *plansza, NowaPlansza *np, Komorka *kom, UBYTE x, UBYTE y )
{
    UBYTE typ, los;

    if( x == 0 || y == 0 || x == P_Szer - 1 || y == P_Wys - 1 )
    {
        UstawPole( kom, T_Sciana );
        return;
    }

    los = rand() & 0xff;

    for( typ = 0; typ < T_Zlicz; typ++ )
    {
        if( los < np->dystrybucja[ typ ] )
        {
            UstawPole( kom, typ );            
            return;
        }
    }
}

void WykonajOperacje( Plansza *plansza, NowaPlansza *np, UBYTE op )
{
    Operacja *oper = np->operacje + op;

    switch( oper->typ )
    {
    case O_Wstaw:
        UstawPole( plansza->komorki[ oper->gora ] + oper->lewo, oper->obiekt.typ );
        /* plansza->komorki[oper->gora][oper->lewo].obiekt = oper->obiekt; */
        break;
    }
}

void UtworzPlansze( Plansza *plansza, NowaPlansza *np )
{
    UBYTE x, y, op;

    PoliczDystrybucje( np );

    srand( np->ziarno );

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            ZainicjujPole( plansza, np, plansza->komorki[ y ] + x, x, y );
        }
    }

    for( op = 0; op < np->zlicz; op++ )
    {
        WykonajOperacje( plansza, np, op );
    }
}

void WypiszPlansze( Plansza *plansza ) 
{
    UBYTE x, y;
    BYTE znaki[ T_Zlicz ] =
    {
        '.', ' ', '#', 'O', '$', 'R'
    };

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            putchar( znaki[ plansza->komorki[ y ][ x ].obiekt.typ ] );
        }
        putchar( '\n' );
    }
    putchar( '\n' );

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            UBYTE od = plansza->komorki[ y ][ x ].ten.odleglosc;
            if( od == 0 )
                putchar( '.' );
            else
                printf( "%x", od );
        }
        putchar( '\n' );
    }
    putchar( '\n' );
}

int main( void )
{
    static NowaPlansza np;
    static Plansza p;
    UBYTE i;

    np.dystrybucja[ T_Glaz ] = 0x20;
    np.dystrybucja[ T_Diament ] = 0x18;
    np.dystrybucja[ T_Pusta ] = 0x48;
    np.dystrybucja[ T_Ziemia ] = 0x80;
    np.ziarno = 200;

    np.operacje[ 0 ].lewo = 1;
    np.operacje[ 0 ].gora = 1;
    np.operacje[ 0 ].obiekt.typ = T_Bohater;
    np.operacje[ 0 ].typ = O_Wstaw;
    np.zlicz = 1;

    UtworzPlansze(&p, &np);
    /* WypiszPlansze(&p); */
    
    for( i = 0; i < 16; i++ )
    {
        Przeskanuj( &p );

        NarysujPlansze( &p );
    }
    
    return( 0 );
}

/** EOF **/
