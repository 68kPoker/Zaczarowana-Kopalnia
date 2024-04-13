
#include <stdio.h>

#include <clib/graphics_protos.h>

#include "Obiekty.h"

#define MIN(a, b) ( (a) < (b) ? (a) : (b) )
#define MAX(a, b) ( (a) > (b) ? (a) : (b) )

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
    const UBYTE podloga = klatki[ T_Pusta ];
    BOOL tlo = FALSE;
    WORD dx, dy, xMin, yMin, xMax, yMax, ox, oy;
    BYTE odlegloscX, odlegloscY;

    if( kom->ten.grafika != kom->poprz.grafika || kom->ten.odleglosc != kom->poprz.odleglosc )
    {
        /* printf("(%2d/%2d): Odswiezam (%2d, %2d) -> (%2d, %2d)\n", x, y, kom->poprz.grafika, kom->poprz.odleglosc, kom->ten.grafika, kom->ten.odleglosc); */

        if( kom->obiekt.typ == T_Pusta || kom->obiekt.typ == T_Ziemia || kom->obiekt.typ == T_Sciana )
        {
            /* BltBitMap(plansza->gfx, klatki[ kom->obiekty.typ ] << 4, 0, plansza->rp->BitMap, x << 4, y << 4, 16, 16, 0xc0, 0xff, NULL); */
            printf( "bac (%2d/%2d) -> (%2d/%2d) [%2d/%2d]\n", kom->ten.grafika << 4, 0, x << 4, y << 4, 16, 16 );
        }
        else
        {
            dx = -przes[ kom->kier ].dx;
            dy = -przes[ kom->kier ].dy;

            odlegloscX = kom->ten.odleglosc * dx;
            odlegloscY = kom->ten.odleglosc * dy;

            xMin = MAX( 0, odlegloscX );
            yMin = MAX( 0, odlegloscY );
            xMax = MIN( 15, odlegloscX + 15 );
            yMax = MIN( 15, odlegloscY + 15 );

            ox = xMin - odlegloscX;
            oy = yMin - odlegloscY;

            /* BltBitMap(plansza->gfx, podloga << 4, 0, plansza->rp->BitMap, x << 4, y << 4, 16, 16, 0xc0, 0xff, NULL); */
            tlo = TRUE;
            if( xMin <= xMax && yMin <= yMax )
            {
                printf( "ent (%2d/%2d) -> (%2d/%2d) [%2d/%2d]\n", ( kom->ten.grafika << 4 ) + ox, oy, ( x << 4 ) + xMin, ( y << 4 ) + yMin, xMax - xMin + 1, yMax - yMin + 1 );
                /* BltMaskBitMapRastPort( plansza->gfx, ( kom->ten.grafika << 4 ) + ox, oy, plansza->rp, ( x << 4 ) + xMin, ( y << 4 ) + yMin, xMax - xMin + 1, yMax - yMin + 1, ABC | ABNC | ANBC, plansza->mask ); */
            }
        }
        kom->poprz = kom->ten;
    }

    for( i = 0; i < 4; i++ )
    {
        graf = kom->sasiedzi + i;
        poprz = kom->poprzSasiedzi + i;

        if( graf->grafika != poprz->grafika || graf->odleglosc != poprz->odleglosc )
        {
            /*
            if( graf->odleglosc < 16 )
                printf( "(%2d/%2d): %-9s (%2d, %2d) -> (%2d, %2d)\n", x, y, nazwy[ i ], poprz->grafika, poprz->odleglosc, graf->grafika, graf->odleglosc );
            else
                printf( "(%2d/%2d): %-9s (%2d, %2d) -> (Czyszcze)\n", x, y, nazwy[ i ], poprz->grafika, poprz->odleglosc );
            */
            dx = przes[ kom->kier ].dx;
            dy = przes[ kom->kier ].dy;

            odlegloscX = graf->odleglosc * dx;
            odlegloscY = graf->odleglosc * dy;

            xMin = MAX( 0, odlegloscX );
            yMin = MAX( 0, odlegloscY );
            xMax = MIN( 15, odlegloscX + 15 );
            yMax = MIN( 15, odlegloscY + 15 );

            ox = xMin - odlegloscX;
            oy = yMin - odlegloscY;

            if( !tlo )
            {
                /* BltBitMap(plansza->gfx, podloga << 4, 0, plansza->rp->BitMap, x << 4, y << 4, 16, 16, 0xc0, 0xff, NULL); */
                tlo = TRUE;
            }
            if( xMin <= xMax && yMin <= yMax )
            {
                printf( "lea (%2d/%2d) -> (%2d/%2d) [%2d/%2d]\n", ( graf->grafika << 4 ) + ox, oy, ( x << 4 ) + xMin, ( y << 4 ) + yMin, xMax - xMin + 1, yMax - yMin + 1 );
                /* BltMaskBitMapRastPort(plansza->gfx, ( graf->grafika << 4 ) + ox, oy, plansza->rp, ( x << 4 ) + xMin, ( y << 4 ) + yMin, xMax - xMin + 1, yMax - yMin + 1, ABC | ABNC | ANBC, plansza->mask); */
            }

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
