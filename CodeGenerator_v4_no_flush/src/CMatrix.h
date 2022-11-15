//
// Created by Bertrand LE GAL on 06/02/2016.
//

#ifndef MAIN_CMATRIX_H
#define MAIN_CMATRIX_H

#include <assert.h>
#include <fstream>
#include "CLine.h"

class CMatrix{
private:
    int vMin;
    int vMax;
    int QC;
    std::vector<CLine*> *list;

public:
    CMatrix(int dimX, int dimY)
    {
        list = new std::vector<CLine*>();
        vMin = 0;
        vMax = 0;

        for(int y=0; y<dimY; y++)
        {
            list->push_back( new CLine( ) );
        }
    }

    CMatrix( )
    {
        list = new std::vector<CLine*>();
        vMin = 0;
        vMax = 0;
    }

    ~CMatrix( )
    {
        delete list;
    }

    void addElement(int x, int y, int msg)
    {
        while(list->size() <= y)
        {
            list->push_back( new CLine( ) );
        }
        assert( y < list->size() );
        list->at( y )->addElement( x, y, msg );
    }

    void addElement(int x, int y, int gf, int msg)
    {
        while(list->size() <= y)
        {
            list->push_back( new CLine( ) );
        }
        assert( y < list->size() );
        list->at( y )->addElement( x, y, gf, msg );
    }

    int height( )
    {
        return list->size();
    }

    int width( )
    {
        int max = 0;
        for(int y=0; y<list->size(); y++)
        {
            int v = list->at( y )->max( );
            max   = max > v ? max : v;
        }
        return max + 1; // on commence la numerotation a zero
    }

    int NbMessages( )
    {
        int sum = 0;
        for(int y=0; y<list->size(); y++)
        {
            sum += list->at( y )->deg( );
        }
        return sum;
    }

    void dump()
    {
        std::cout << "Matrix loaded from AList file" << std::endl;
        std::cout << "- dimension " << width() << " x " << height() << std::endl;
        std::cout << "- messages  " << NbMessages()  << std::endl;
        int _height = height( );
        for(int y=0; y<_height; y++)
        {
            list->at( y )->dump();
        }
    }

    //
    // On ordonnance les messages en fonction des colonnes CNs
    //
    void UpdateStructure( )
    {
        int cpt = 0;
        int _width = width( );
        for(int x=0; x<_width; x++)
        {
            int _height = height( );
            for(int y=0; y<_height; y++)
            {
                if( test_value( x, y ) != 0 )
                {
                    CPoint* p = list->at( y )->getCPoint( x );
                    p->y  (   y ); // au cas ou on ait precede au tri des colonnes de la matrice
                    p->msg( cpt );
                    cpt += 1;
                }
            }
        }
    }

    void ReOrderCNs( )
    {
        //dump();
        std::sort(list->begin(), list->end(), Ygreater());
        //dump();
    }

    int test_value(int x, int y)
    {
        return list->at( y )->test_value( x );
    }

    std::vector<CPoint*>* elements(int y)
    {
        return list->at( y )->elements();
    }

    CLine* line(int y)
    {
        return list->at( y );
    }

    void WritePPM(char* filename)
    {
        std::ofstream of( filename );
        if( of.is_open() == true )
        {
            of << "P1" << std::endl;
            of << "# Structure d'une matrice LDPC" << std::endl;
            of << width() << " " << height() << std::endl;
            for(int y=0; y<height( ); y++)
            {
                for(int x=0; x<width( ); x++)
                {
                    of << test_value( x, y ) << " ";
                }
                of << std::endl;
            }
            of.close();
        }
    }

    int degCN(int y)
    {
        return list->at( y )->deg();
    }

    int degVN(int x)
    {
        int sum = 0;
        for(int y=0; y<height(); y++)
        {
            sum += test_value(x, y);
        }
        return sum;
    }

    int qc( )
    {
        return QC;
    }

    void qc(int _QC)
    {
        QC = _QC;
    }

    int GF( )
    {
        int max = 0;
        for(int y=0; y<height(); y++)
        {
            std::vector<CPoint*>* liste = list->at(y)->elements();
            for(int q=0; q<liste->size(); q++)
            {
                CPoint* p = liste->at(q);
                max = max > p->v() ? max : p->v();
            }
        }

        int result = 1;
        while (result < max) result <<= 1;
        return result;
    }
};

#endif //MAIN_CMATRIX_H
