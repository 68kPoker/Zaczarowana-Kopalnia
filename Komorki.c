
#include <stdio.h>
#include <stdlib.h>

#include "Komorki.h"

void PoliczDystrybucje( NowaPlansza *np )
{
    UBYTE typ;

    for( typ = 1; typ < T_Zlicz; typ++ )
    {
        np->dystrybucja[ typ ] += np->dystrybucja[ typ - 1 ];
    }
}

void ZainicjujPole( Plansza *plansza, NowaPlansza *np, Komorka *kom, UBYTE x, UBYTE y )
{
    UBYTE typ, los;

    if( x == 0 || y == 0 || x == P_Szer - 1 || y == P_Wys - 1 )
    {
        kom->obiekt.typ = T_Sciana;
        return;
    }

    los = rand() & 0xff;

    for( typ = 0; typ < T_Zlicz; typ++ )
    {
        if( los < np->dystrybucja[ typ ] )
        {
            kom->obiekt.typ = typ;
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
        plansza->komorki[ oper->gora ][ oper->lewo ].obiekt = oper->obiekt;
        break;
    }
}

void UtworzPlansze( Plansza *plansza, NowaPlansza *np )
{
    UBYTE x, y, op;

    PoliczDystrybucje( np );

    for( y = 0; y < P_Wys; y++ )
    {
        for( x = 0; x < P_Szer; x++ )
        {
            ZainicjujPole( plansza, np, plansza->komorki[ y ] + x, x, y );
        }
    }

    srand( np->ziarno );

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
}

int main( void )
{
    static NowaPlansza np;
    Plansza p;

    np.dystrybucja[ T_Glaz ] = 0x10;
    np.dystrybucja[ T_Diament ] = 0x18;
    np.dystrybucja[ T_Pusta ] = 0x18;
    np.dystrybucja[ T_Ziemia ] = 0xc0;
    np.ziarno = 100;

    np.operacje[ 0 ].lewo = 1;
    np.operacje[ 0 ].gora = 1;
    np.operacje[ 0 ].obiekt.typ = T_Bohater;
    np.operacje[ 0 ].typ = O_Wstaw;
    np.zlicz = 1;

    UtworzPlansze( &p, &np );
    WypiszPlansze( &p );
    return( 0 );
}

/** EOF **/