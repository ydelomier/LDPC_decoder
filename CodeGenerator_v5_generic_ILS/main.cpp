#include <iostream>
#include "src/Reader.h"
#include "src/Writer.h"
#include <dirent.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

using namespace std;

int main(int argc, char* argv[]) {

    std::cout << "(II) USER GUIDE : command N Zmax Path1 Path2 .. PathN Z1 Z1 .. ZM" << std::endl;
    std::cout << "(II)      Parameters : " << std::endl;
    std::cout << "(II)                  - N     : Number of matrix " << std::endl;
    std::cout << "(II)                  - Zmax  : Maximum QC factor " << std::endl;
    std::cout << "(II)                  - PathN : Path to matrix N " << std::endl;
    std::cout << "(II)                  - ZM    : value of the QC factor M, with Zmax multiple of ZM " << std::endl;
    std::cout << "      !!! NB: Work with 5G matrix !!!" << std::endl;

    if (argc < 4)
        return -1;

    int Nb_Matrix = atoi(argv[1]);
    int Zmax = atoi(argv[2]);
    int Nb_Z = argc - (Nb_Matrix + 3);
    //std::cout << "(DD) Nb_Matrix : " << Nb_Matrix << std::endl;
    //std::cout << "(DD) Zmax : " << Zmax << std::endl;
    //std::cout << "(DD) Nb_Z : " << Nb_Z << std::endl;

    CMatrix m[20];
    int Z_factor[20];

    for (int i = 0; i < Nb_Matrix; i++) {
        std::cout << "  MATRIX :" << i+1 << std::endl;
        string file = argv[i + 3];
        //std::cout << "(DD) Path "<<i<<" : " << file << std::endl;
        if (file.find(".QcId") != -1) {
            CMatrix *matrix;
            matrix = Reader::BinaryQcReader(file);
            matrix->ReOrderCNs();
            m[i] = *matrix;
        } else {
            std::cout << "ERROR file extension, required .QcId" << std::endl;
            return 0;
        }
    }
    for (int i = 0; i < Nb_Z; i++) {
        Z_factor[i] = atoi(argv[i + 3 + Nb_Matrix]);
        //std::cout << "(DD) Z_factor "<<i<<" : " << Z_factor[i] << std::endl;
    }

    Writer::WriteQcHorizontalSchedule( m, Nb_Matrix, Z_factor, Zmax, Nb_Z , "../../LDPC_QC_v4_generic_1_ILS/src/module/" );
    std::cout << "File written PATH : LDPC_QC_v4_generic_1_ILS/src/module/"<< std::endl;

    exit( 0 );

}
