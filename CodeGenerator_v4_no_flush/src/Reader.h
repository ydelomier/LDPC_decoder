//
// Created by Bertrand LE GAL on 08/02/2016.
//

#ifndef MAIN_READER_H
#define MAIN_READER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "CMatrix.h"

using namespace std;

class Reader{
public:

    static CMatrix* aListReader(string filename)
    {
        ifstream myfile ( filename );
        int tempvalue = 0;
        string str;
        if (myfile.is_open())
        {
            int N, M, dvMax, dcMax;

            //
            // ON RECUPERE LA DIMENSION DE LA MATRICE
            //
            getline(myfile, str);
            istringstream line_1(str);
            line_1 >> N;
            line_1 >> M;

            CMatrix *m = new CMatrix( N, M );

            std::cout << "Nombre de VNs = " << N << endl;
            std::cout << "Nombre de CNs = " << M << endl;

            //
            // ON RECUPERE LES DEGRES MAX DES VNs/CNs
            //
            getline(myfile, str);
            istringstream line_2(str);
            line_2 >> dvMax;
            line_2 >> dcMax;

            getline(myfile, str); // LES DEGRES DE VNs
            getline(myfile, str); // LES DEGRES DE CNs

            //
            // ON SAUTE LES LIGNES DECRIVANT LES NOEUDS Vns
            //
            for(int i=0; i<N; i++)
            {
                getline(myfile, str);
            }

            for(int y=0; y<M; y++)
            {
                getline(myfile, str);
                istringstream is(str);
                while( is >> tempvalue )
                {
                    m->addElement(tempvalue - 1, y, 0); // offset du a matlab
                }
            }
            m->UpdateStructure( );

            if (myfile.is_open())
                myfile.close();

            return m;
        }
        return NULL;
    }


    static CMatrix* aList2Reader(string filename)
    {
        ifstream myfile ( filename );
        int tempvalue = 0;
        string str;
        if (myfile.is_open())
        {
            int N, M, GF, dvMax, dcMax;

            //
            // ON RECUPERE LA DIMENSION DE LA MATRICE
            //
            getline(myfile, str);
            istringstream line_1(str);
            line_1 >> N;
            line_1 >> M;
            line_1 >> GF;

            CMatrix *m = new CMatrix( N, M );

            std::cout << "Nombre de VNs = " <<  N << endl;
            std::cout << "Nombre de CNs = " <<  M << endl;
            std::cout << "Nombre de GF  = " << GF << endl;

            //
            // ON RECUPERE LES DEGRES MAX DES VNs/CNs
            //
            getline(myfile, str);

            getline(myfile, str); // LES DEGRES DE VNs
            getline(myfile, str); // LES DEGRES DE CNs

            getline(myfile, str);

            //
            // ON SAUTE LES LIGNES DECRIVANT LES NOEUDS Vns
            //
            for(int y=0; y<M; y++)
            {
                getline(myfile, str);
                std::cout << "Processing [\n" << str << "\n]" << endl;
                istringstream is(str);
                while( is >> tempvalue )
                {
                    int multF; is >> multF;
                    printf(" > %d %d\n", tempvalue, multF);
                    m->addElement(tempvalue - 1, y, multF, 0); // offset du a matlab
                }
            }
            m->UpdateStructure( );

            if (myfile.is_open())
                myfile.close();

            return m;
        }
        return NULL;
    }

    static CMatrix* BinaryReader(string filename)
    {
        ifstream myfile ( filename );
        int tempvalue = 0;
        string str;
        if (myfile.is_open())
        {
            //
            // ON RECUPERE LA DIMENSION DE LA MATRICE
            //
            CMatrix *m = new CMatrix( );

            //
            // ON SAUTE LES LIGNES DECRIVANT LES NOEUDS Vns
            //
            int y = 0;
            while(myfile.eof() == false)
            {
                getline(myfile, str);
                std::cout << "Processing [\n" << str << "\n]" << endl;
                istringstream is(str);

                int counter = 0;
                while( is >> tempvalue )
                {
                    //int multF; is >> multF;
                    //printf(" > %d %d\n", tempvalue, multF);
                    if( tempvalue == 1 ){
                        m->addElement(counter, y, 0, 0); // offset du a matlab
                    }
                    counter += 1;
                }
                y += 1;
            }

            std::cout << "Nombre de VNs = " << m->width()      << endl;
            std::cout << "Nombre de CNs = " << m->height()     << endl;
            std::cout << "Nombre de GF  = " << m->GF()         << endl;
            std::cout << "Nombre de MSG = " << m->NbMessages() << endl;

            m->UpdateStructure( );

            if (myfile.is_open())
                myfile.close();

            return m;
        }
        return NULL;
    }

    static CMatrix* BinaryQcReader(string filename)
    {
        ifstream myfile ( filename );
        int tempvalue = 0;
        string str;
        if (myfile.is_open())
        {
            //
            // ON RECUPERE LA DIMENSION DE LA MATRICE
            //
            CMatrix *m = new CMatrix( );

            int N, offset;

            //
            // ON RECUPERE LA DIMENSION DE LA MATRICE
            //
            getline(myfile, str);
            istringstream line_1(str);
            line_1 >> N;

            getline(myfile, str);
            istringstream line_2(str);
            line_2 >> offset;

            std::cout << "Nombre de bits = " << N << endl;
            std::cout << "Shift offset   = " << offset << endl;

            //
            // ON SAUTE LES LIGNES DECRIVANT LES NOEUDS Vns
            //
            int y = 0;
            while(myfile.eof() == false)
            {
                getline(myfile, str);
                //std::cout << "Processing [\n" << str << "\n]" << endl;
                istringstream is(str);

                int x = 0;
                while( is >> tempvalue )
                {
                    if( (tempvalue-offset) >= 0 ){
                        m->addElement(x, y, (tempvalue-offset), 0);
                        //cout << "Element identified : (" << x << ", " << y << ") => " << (tempvalue-offset) << endl;
                    }
                    x += 1;
                }
                y += 1;
            }

            std::cout << "Nombre de VNs = " << m->width()      << endl;
            std::cout << "Nombre de CNs = " << m->height()     << endl;
            std::cout << "Nombre de GF  = " << m->GF()         << endl;
            std::cout << "Nombre de MSG = " << m->NbMessages() << endl;

            int qc = N / m->width();
            assert ( (N % m->width()) == 0 );
            std::cout << "Valeur de QC  = " << qc << endl;
            m->qc( qc );

            m->UpdateStructure( );

            if (myfile.is_open())
                myfile.close();

            return m;
        }
        return NULL;
    }
};

#endif //MAIN_READER_H
