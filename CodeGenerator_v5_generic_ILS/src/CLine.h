//
// Created by Bertrand LE GAL on 06/02/2016.
//

#ifndef MAIN_CLINE_H
#define MAIN_CLINE_H

#include <vector>
#include <map>
#include <algorithm>
#include "CPoint.h"

class CLine{
private:
    int vMin;
    int vMax;
    std::vector<CPoint*> *list;
    std::map<int, CPoint*>   fast;

public:

    CLine( )
    {
        list = new std::vector<CPoint*>();
        //fast = new std::map<int, int>();
        vMin = 0;
        vMax = 0;
    }

    ~CLine( )
    {
        delete list;
    }

    void addElement(int x, int y, int msg)
    {
        addElement(x, y, 1, msg);
    }

    void addElement(int x, int y, int v, int msg) {
        CPoint* p = new CPoint(x, y, v, msg);
        list->push_back( p );
        //std::sort(list->begin(), list->end(), Xgreater());
        sort(list->begin(), list->end(), Xgreater());
        fast[x] = p;
    }

    int test_value( int x )
    {
        return (fast.count( x ) == 0) ? 0 : 1;
    }

    CPoint* getCPoint( int x )
    {
        return (fast.count( x ) == 0) ? NULL : fast[x];
    }

    int deg( ) const
    {
        return list->size();
    }

    int max( ) const
    {
        return list->at( list->size() - 1 )->x( );
    }

    void dump()
    {
        std::cout << "CN [" << list->size() << "] : ";
        for(int p=0; p<list->size(); p++)
        {
            std::cout << list->at(p)->x() << "  ";
        }
        std::cout << std::endl;
    }

    std::vector<CPoint*>* elements( )
    {
        return list;
    }

    //
    // UTILISE POUR REORDONNER LES COLONNES DANS LA MATRICE
    //
    bool operator<( const CLine& val ) const {
        return deg() < val.deg();
    }

};

class Ygreater
{
public:
    bool operator()( const CLine* lx, const CLine* rx ) const {
        return lx->deg() > rx->deg();
    }
};

#endif //MAIN_CLINE_H
