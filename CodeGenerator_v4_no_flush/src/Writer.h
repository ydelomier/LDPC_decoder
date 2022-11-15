//
// Created by Bertrand LE GAL on 08/02/2016.
//

#ifndef MAIN_WRITER_H
#define MAIN_WRITER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "math.h"

#include "CMatrix.h"

using namespace std;

class Writer{
public:

    static void WriteFloodingSchedule(CMatrix* m, const char* filename)
    {
        std::ofstream of(filename);
        of << "#ifndef GEN_PAR_CPP_H" << std::endl;
        of << "#define GEN_PAR_CPP_H" << std::endl;
        of << std::endl;

        std::vector<int>   vDegVN, vDegCN;
        std::map<int, int> lDegVN, lDegCN;

        for(int x=0; x<m->width(); x++)
        {
            int deg = m->degVN( x );
            vDegVN.push_back( deg );
            lDegVN[deg] += 1;
        }

        for(int y=0; y<m->height(); y++)
        {
            int deg = m->degCN( y );
            vDegCN.push_back( deg );
            lDegCN[deg] += 1;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> dCNs;
        for(auto imap: lDegCN)
            dCNs.push_back(imap.first);
        std::sort(dCNs.begin(), dCNs.end());

        std::string stateCN = (dCNs.size()==1) ? "true" : "false";
        of << "#define SINGLE_DEG_CHK_NODES " << stateCN << std::endl;
        for(int q=0; q<dCNs.size(); q++)
        {
            of << "#define NB_DEG_CHK_NODES " << (q+1)         <<                       std::endl;
            of << "#define DEG_"    << (q+1) << "_CHK_NODES  " << dCNs.at(q)         << std::endl;
            of << "#define NB_DEG_" << (q+1) << "_CNODES  "    << lDegCN[dCNs.at(q)] << std::endl;
        }
        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> dVNs;
        for(auto imap: lDegVN)
            dVNs.push_back(imap.first);
        std::sort(dVNs.begin(), dVNs.end());

        std::string stateVN = (dVNs.size()==1) ? "true" : "false";
        of << "#define SINGLE_DEG_VAR_NODES " << stateVN << std::endl;
        for(int q=0; q<dVNs.size(); q++)
        {
            of << "#define NB_DEG_VAR_NODES "                  << (q+1)              << std::endl;
            of << "#define DEG_"    << (q+1) << "_VAR_NODES  " << dVNs.at(q)         << std::endl;
            of << "#define NB_DEG_" << (q+1) << "_VNODES  "    << lDegVN[dVNs.at(q)] << std::endl;
        }
        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned char nbVariableParParite[" <<  m->height() <<  "] = {";
        for(int q=0; q<m->height(); q++)
        {
            if( q%32 == 0 ) of << std::endl << "  ";
            if( (q+1) != m->height() )
                of << vDegCN.at( q ) << ", ";
            else
                of << vDegCN.at( q );
        }
        of <<  std::endl << "};" << std::endl << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned char nbPariteParVariable[" <<  m->width()<<  "] = {";
        for(int q=0; q<m->width(); q++)
        {
            if( q%32 == 0 ) of << std::endl << "  ";
            if( q+1 != m->width() )
                of << vDegVN.at( q ) << ", ";
            else
                of << vDegVN.at( q );
        }
        of <<  std::endl << "};" << std::endl << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned short transpose[" <<  m->NbMessages() <<  "] = {" << std::endl;
        for(int y=0; y<m->height(); y++)
        {
            of <<  "  /* CN " << y << " */ ";

            std::vector<CPoint*>* liste = m->line(y)->elements();
            for(int q=0; q<liste->size(); q++)
            {
                CPoint* p = liste->at(q);
                of << p->msg() << ", ";
            }
            of <<  std::endl;
        }
        of.seekp(-3, std::ios_base::cur);
        of <<  std::endl;
        of <<  "};" << std::endl << std::endl;
        of <<  std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        cout << "value of GF = " << m->GF() << endl;
        if( m->GF() > 2 ) {
            of << "//" << std::endl;
            of << "//" << std::endl;
            of << "//" << std::endl;
            of << "const unsigned char gf[" << m->NbMessages() << "] = {" << std::endl;
            for (int y = 0; y < m->height(); y++) {
                of << "  /* CN " << y << " */ ";

                std::vector<CPoint *> *liste = m->line(y)->elements();
                for (int q = 0; q < liste->size(); q++) {
                    CPoint *p = liste->at(q);
                    of << p->v() << ", ";
                }
                of << std::endl;
            }
            of.seekp(-3, std::ios_base::cur);
            of << std::endl;
            of << "};" << std::endl << std::endl;
            of << std::endl;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::cout << "GF value = " << m->GF() << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << std::endl;
        of << "#endif //GEN_PAR_CPP_H" << std::endl;
        of.close();
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    static void WriteHorizontalSchedule(CMatrix* m, const char* filename)
    {
        std::ofstream of(filename);
        of << "#ifndef GEN_PAR_CPP_H" << std::endl;
        of << "#define GEN_PAR_CPP_H" << std::endl;
        of << std::endl;

        std::vector<int>   vDegCN;
        std::map<int, int> lDegCN;

        for(int y=0; y<m->height(); y++)
        {
            int deg = m->degCN( y );
            printf("Line %2d : degc = %d\n", y, m->degCN( y ));
            vDegCN.push_back( deg );
            lDegCN[deg] += 1;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> dCNs;
        for(auto imap: lDegCN)
            dCNs.push_back(imap.first);
        std::sort(dCNs.begin(), dCNs.end());

        std::string stateCN = (dCNs.size()==1) ? "true" : "false";
        of << "#define SINGLE_DEG_CHK_NODES " << stateCN << std::endl;
        for(int q=0; q<dCNs.size(); q++)
        {
            of << "#define NB_DEG_CHK_NODES " << (q+1)         <<                       std::endl;
            of << "#define DEG_"    << (q+1) << "_CHK_NODES  " << dCNs.at(q)         << std::endl;
            of << "#define NB_DEG_" << (q+1) << "_CNODES  "    << lDegCN[dCNs.at(q)] << std::endl;
        }
        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned short transpose[" << m->NbMessages()<<  "] = {" << std::endl;
        for(int y=0; y<m->height(); y++)
        {
            of <<  "  /* CN " << y << " */ ";
            std::vector<CPoint*>* liste = m->line(y)->elements();
            for(int q=0; q<liste->size(); q++)
            {
                CPoint* p = liste->at(q);
                of << p->msg() << ", ";
            }
            of <<  std::endl;
        }
        of.seekp(-3, std::ios_base::cur);
        of <<  std::endl;
        of <<  "};" << std::endl << std::endl;
        of <<  std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        cout << "value of GF = " << m->GF() << endl;
        if( m->GF() > 2 )
        {
            of << "//" << std::endl;
            of << "//" << std::endl;
            of << "//" << std::endl;
            of << "const unsigned char gf[" << m->NbMessages() <<  "] = {" << std::endl;
            for(int y=0; y<m->height(); y++)
            {
                of <<  "  /* CN " << y << " */ ";
                std::vector<CPoint*>* liste = m->line(y)->elements();
                for(int q=0; q<liste->size(); q++)
                {
                    CPoint* p = liste->at(q);
                    of << p->v() << ", ";
                }
                of <<  std::endl;
            }
            of.seekp(-3, std::ios_base::cur);
            of <<  std::endl;
            of <<  "};" << std::endl << std::endl;
            of <<  std::endl;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << std::endl;
        of << "#endif //GEN_PAR_CPP_H" << std::endl;
        of.close();
    }


    static void WriteQcHorizontalSchedule(CMatrix* m, const std::string filename, int Imax ,int INTER_FRAME, bool Archi_opt)
    {
        std::string header = filename + "ldpc_parameters.h";
        //std::of(header);
        ofstream of(header);
        of << "#ifndef LDPC_HEADER_H" << std::endl;
        of << "#define LDPC_HEADER_H" << std::endl;
        of << std::endl;
        of << "#define _N                   " << m->width()         << std::endl;
        of << "#define _K                   " << m->height()        << std::endl;
        of << "#define _M                   " << m->NbMessages()    << std::endl;
        of << std::endl;
        of << "#define QC                   " << m->qc()            << std::endl;
        of << std::endl;
        if(Archi_opt) {
            of << "#define FIFO_TO_LUT	// Convert part of Memory Buffer into Logic" << std::endl;
            of << std::endl;
        }
        of << "#define N_QC                 " << ceil(logf(m->qc())/logf(2.0)) << std::endl;
        of << "#define FORMAT               " << ceil(logf(INTER_FRAME * m->width())/logf(2.0)) << std::endl;
        of << std::endl;
        of << "#define MAX_ITERS            " << Imax << std::endl;
        of << "#define INTER_FRAME          " << INTER_FRAME << std::endl;
        of << "#define NOEUD   _N" << std::endl;
        of << "#define MESSAGE _M" << std::endl;
        of << std::endl;

        std::vector<int>   vDegCN;
        std::map<int, int> lDegCN;

        for(int y=0; y<m->height(); y++)
        {
            int deg = m->degCN( y );
            vDegCN.push_back( deg );
            lDegCN[deg] += 1;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> dCNs;
        for(auto imap: lDegCN)
            dCNs.push_back(imap.first);
        std::sort(dCNs.begin(), dCNs.end());

        std::cout << "Nombre de deg(CN) = " << dCNs.size() << std::endl;
        of << "#define NB_DEGRES            " << dCNs.size() << std::endl;

        int nDegs = dCNs.size() - 1;
        for(int q=0; q<dCNs.size(); q++)
        {
            std::cout << "  => " << dCNs.at(nDegs-q) << std::endl;
            of << "#define DEG_" << (q+1) << "                " << dCNs.at(nDegs-q) << std::endl;
        }
        for(int q=0; q<dCNs.size(); q++)
        {
            of << "#define DEG_" << (q+1) << "_COMPUTATIONS   " << lDegCN[dCNs.at(nDegs-q)] << std::endl;
        }
        of << std::endl;
        of << "#endif //LDPC_HEADER_H" << std::endl;
        of.close();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string code = filename + "ldpc_code.h";
        of.open(code);

        of << "#ifndef LDPC_STRUCTURE_H" << std::endl;
        of << "#define LDPC_STRUCTURE_H" << std::endl;
        of << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned char DegreeCNs[" << INTER_FRAME * (m->height())<<  "] = {" << std::endl << "  ";
        int latest = m->line( 0 )->deg();
        for(int y=0; y<m->height(); y++)
        {
            for(int k=0; k < INTER_FRAME; k++)
            {
                if( latest != m->line(y)->deg() ){
                    latest = m->line(y)->deg();
                    of << std::endl << "  ";
                }
                of << setw(2) << m->line(y)->deg() << ", ";
            }

        }
        of.seekp(-2, std::ios_base::cur);
        of << std::endl;
        of << "};" << std::endl << std::endl;
        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const sc_uint< FORMAT > PosBlocVNs[" << INTER_FRAME * m->NbMessages()<<  "] = {" << std::endl;
        for(int y=0; y<m->height(); y++)
        {
            for(int k=0; k < INTER_FRAME; k++) {
                of << "  /* CN " << setw(3) << y << " [" << m->line(y)->deg()<< "] */ ";
                std::vector<CPoint *> *liste = m->line(y)->elements();
                for (int q = 0; q < liste->size(); q++) {
                    CPoint *p = liste->at(q);
                    of << setw(3) << p->x() + (k * m->width()) << ", ";
                }
                of << std::endl;
            }
        }
        of.seekp(-3, std::ios_base::cur);
        of <<  std::endl;
        of <<  "};" << std::endl << std::endl;
        of <<  std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> vnPos;
        for(int x=0; x<m->width(); x++)
            vnPos.push_back( 0 );

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const sc_uint< N_QC > CoeffRotations[" << INTER_FRAME * (2*m->NbMessages()+m->width())<<  "] = {" << std::endl;
        of <<  "  /* OFFSETS FOR FIRST ITERATION */" << std::endl;
        for(int y=0; y<m->height(); y++)
        {
            for(int k=0; k < INTER_FRAME; k++) {
                of << "  /* CN " << setw(3) << y << " [" << m->line(y)->deg() << "] */ ";
                std::vector<CPoint *> *liste = m->line(y)->elements();
                for (int q = 0; q < liste->size(); q++) {
                    CPoint *p = liste->at(q);
                    int vn = p->x();
                    int off = (p->v() % m->qc());
                    int mv = ((m->qc() + off) - vnPos[vn]) % m->qc();
                    if(k == INTER_FRAME - 1)
                        vnPos[vn] = off;
                    of << setw(3) << mv << ", ";
                }
                of << std::endl;
            }
        }
        of <<  "  /* OFFSETS TO ALL THE OTHER DECODING ITERATIONS */" << std::endl;
        for(int y=0; y<m->height(); y++)
        {
            for(int k=0; k < INTER_FRAME; k++) {
                of << "  /* CN " << setw(3) << y << " [" << m->line(y)->deg() << "] */ ";
                std::vector<CPoint *> *liste = m->line(y)->elements();
                for (int q = 0; q < liste->size(); q++) {
                    CPoint *p = liste->at(q);
                    int vn = p->x();
                    int off = (p->v() % m->qc());
                    int mv = ((m->qc() + off) - vnPos[vn]) % m->qc();
                    if(k == INTER_FRAME - 1)
                        vnPos[vn] = off;
                    of << setw(3) << mv << ", ";
                }
                of << std::endl;
            }
        }
        of <<  "  /* OFFSETS TO COME BACK 0 */" << std::endl;
        of <<  "  ";
        for(int k=0; k < INTER_FRAME; k++) {
            for (int x = 0; x < m->width(); x++) {

                int off = 0; // le point d'arrive des VNs
                int mv = ((m->qc() + off) - vnPos[x]) % m->qc();
                of << setw(3) << mv << ", ";

            }
        }
        of <<  std::endl;
        of.seekp(-3, std::ios_base::cur);
        of <<  std::endl;
        of <<  "};" << std::endl;
        of <<  std::endl;

        of << "#endif //LDPC_STRUCTURE_H" << std::endl;
        of.close();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string my_module = filename + "barrel_shifter.h";
        of.open(my_module);

        of << "#ifndef _barrel_shifter_" << std::endl;
        of << "#define _barrel_shifter_" << std::endl<< std::endl;
        of << "#include \"systemc.h\"" << std::endl<< std::endl;
        of << "#include \"config.h\"" << std::endl<< std::endl;
        of << "#include \"ldpc_parameters.h\"" << std::endl<< std::endl;
        of << "        SC_MODULE(barrel_shifter)" << std::endl;
        of << "        {"<< std::endl;
        of << "            sc_in< TYPE_LLRS >	ibs_e;" << std::endl;
        of << "            sc_in< sc_uint< N_QC > >	ibs_rot;" << std::endl;
        of << "            sc_out< TYPE_LLRS >	ibs_s;" << std::endl<< std::endl;
        of << "            SC_CTOR(barrel_shifter)" << std::endl;
        of << "            {"<< std::endl;
        of << "                SC_METHOD(barrel_shifter_RIGHT);" << std::endl;
        of << "                sensitive << ibs_e;" << std::endl;
        of << "                sensitive << ibs_rot;" << std::endl;
        of << "            }" << std::endl<< std::endl;
        of << "        private:" << std::endl;
        of << "            void barrel_shifter_RIGHT(){" << std::endl<< std::endl;

        of << "             sc_uint< N_QC > c = ibs_rot.read();" << std::endl;
        of << "             TYPE_LLRS a = ibs_e.read();" << std::endl;
        of << "             TYPE_LLRS e;" << std::endl<< std::endl<< std::endl;;
        of <<  "            switch ( c ){" << std::endl;
        of <<  "                case   0:  e = a; break;" << std::endl;

        for(int q = 1; q < m->qc(); q += 1)
            of <<  "                case " << setw(3) << q << " :  e = ((sc_bigint<" << setw(3) << q << " * LLR_BITS>)a.range(" << setw(3) << q << " * LLR_BITS - 1, 0), (sc_bigint<" << setw(3) << (m->qc()-q) << " * LLR_BITS>)a.range(" << setw(3) << m->qc() << " * LLR_BITS - 1, " << setw(3) << q << " * LLR_BITS)); break;" << std::endl;
        of <<  "                default: e = a; break;" << std::endl;
        of <<  "            }" << std::endl;
        of <<  "        ibs_s.write(e);"<< std::endl;
        of <<  "    }" << std::endl;
        of <<  "};" << std::endl;

        of << "#endif " << std::endl;
        of.close();

    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void WriteSIMDHorizontalSchedule(CMatrix* m, const std::string filename)
    {
        std::string header = filename + "ldpc.h";
        //std::of(header);
        ofstream of(header);
        of << "#ifndef LDPC_HEADER_H" << std::endl;
        of << "#define LDPC_HEADER_H" << std::endl;
        of << std::endl;
        of << "#define _N                   " << (m->width() * m->qc() )         << std::endl;
        of << "#define _K                   " << (m->height() * m->qc() )        << std::endl;
        of << "#define _M                   " << (m->NbMessages() * m->qc() )    << std::endl;
        of << std::endl;
        of << "#define NOEUD   _N" << std::endl;
        of << "#define MESSAGE _M" << std::endl;
        of << std::endl;

        std::vector<int>   vDegCN;
        std::map<int, int> lDegCN;

        for(int y=0; y<m->height(); y++)
        {
            int deg = m->degCN( y );
            vDegCN.push_back( deg );
            lDegCN[deg] += 1;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<int> dCNs;
        for(auto imap: lDegCN)
            dCNs.push_back(imap.first);
        std::sort(dCNs.begin(), dCNs.end());

       // std::cout << "Nombre de deg(CN) = " << dCNs.size() << std::endl;
        of << "#define NB_DEGRES            " << dCNs.size() << std::endl;

        int nDegs = dCNs.size() - 1;
        for(int q=0; q<dCNs.size(); q++)
        {
            //std::cout << "  => " << dCNs.at(nDegs-q) << std::endl;
            of << "#define DEG_" << (q+1) << "                " << dCNs.at(nDegs-q) << std::endl;
        }
        for(int q=0; q<dCNs.size(); q++)
        {
            of << "#define DEG_" << (q+1) << "_COMPUTATIONS   " << ( lDegCN[dCNs.at(nDegs-q)] * m->qc() ) << std::endl;
        }
        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "//" << std::endl;
        of << "const unsigned short PosNoeudsVariable[" <<(m->NbMessages() * m->qc() )<<  "] = {" << std::endl;
        for(int y=0; y<(m->height() * m->qc()); y++)
        {
            int ligne = y / (m->qc());
            of <<  "  /* msg = " << setw(3) << y << " [" << m->line(ligne)->deg() << "] */ ";
            std::vector<CPoint*>* liste = m->line(ligne)->elements();
            for(int q=0; q<liste->size(); q++)
            {
                CPoint* p = liste->at(q);
                of << setw(3) << (p->x() * m->qc() + (  (p->v() % m->qc() + y ) % (m->qc()) ) ) << ", ";
            }
            of <<  std::endl;
        }
        of.seekp(-3, std::ios_base::cur);
        of <<  std::endl;
        of <<  "};" << std::endl << std::endl;
        of <<  std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        of << "#endif //LDPC_HEADER_H" << std::endl;
        of.close();
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void WriteInAdmmDecoderFormat(CMatrix* m, const char* filename)
    {
        std::ofstream of(filename);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        for(int y=0; y<m->height(); y++)
        {
            std::vector<CPoint*>* liste = m->line(y)->elements();
            for(int q=0; q<liste->size(); q++)
            {
                CPoint* p = liste->at(q);
                of << p->x() << " ";
            }
            of << std::endl;
        }

        of << std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        of.close();
    }

};

#endif //MAIN_READER_H
