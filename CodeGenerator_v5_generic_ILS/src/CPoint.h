//
// Created by Bertrand LE GAL on 06/02/2016.
//

#ifndef MAIN_CPOINT_H
#define MAIN_CPOINT_H

class CPoint{
private:
    int posX;
    int posY;
    int value;
    int pos_msg;

public:
    CPoint(int x, int y, int msg)
    {
        posX    = x;
        posY    = y;
        value   = 1;
        pos_msg = msg;
    }

    CPoint(int x, int y, int v, int msg)
    {
        posX    = x;
        posY    = y;
        value   = v;
        pos_msg = msg;
    }

    int x( ) const
    {
        return posX;
    }

    void x( int newX )
    {
        posX = newX;
    }

    int y( ) const
    {
        return posX;
    }

    void y( int newY )
    {
        posY = newY;
    }

    int v( ) const
    {
        return value;
    }

    void v( int newV )
    {
        value = newV;
    }

    int msg( ) const
    {
        return pos_msg;
    }

    void msg( int nmsg )
    {
        pos_msg = nmsg;
    }

    //
    // UTILISE POUR REORDONNER LES COLONNES DANS LA MATRICE
    //
    bool operator<( const CPoint& val ) const {
        return posX < val.posX;
    }
};

class Xgreater
{
public:
    bool operator()( const CPoint* lx, const CPoint* rx ) const {
        return lx->x() < rx->x();
    }
};

#endif //MAIN_CPOINT_H
