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

    std::cout << "(II) USER GUIDE : command I F B Path " << std::endl;
    std::cout << "(II)      Parameters : " << std::endl;
    std::cout << "(II)                  - I     : (int) Number of Maximum Iteration " << std::endl;
    std::cout << "(II)                  - F     : (int) Number of Inter Frame parallelism  " << std::endl;
    std::cout << "(II)                  - B     : (bool) 0 : LUT optimized Archi, 1 : BRAM optimized Archi " << std::endl;
    std::cout << "(II)                  - Path  : (string) Path to the H Matrix file  " << std::endl;

    if (argc < 4)
        return -1;

    int Imax = atoi(argv[1]);
    int INTER_FRAME = atoi(argv[2]);
    bool Archi_opt = atoi(argv[3]);
    string file = argv[4];

    CMatrix *m;

    if (file.find(".QcId") != -1) {
        m = Reader::BinaryQcReader(file);
        m->ReOrderCNs();
    } else {
        std::cout << "ERROR file extension, required .QcId" << std::endl;
        return 0;
    }

    int widthBits = m->width() * m->qc();

    Writer::WriteQcHorizontalSchedule( m, "../../LDPC_QC_v4_no_flush/src/module/", Imax, INTER_FRAME, Archi_opt );

    std::cout << "PATH : LDPC_QC_v4_no_flush/src/module/"<< std::endl;
    std::cout << "Imax : "<< Imax <<std::endl;
    std::cout << "INTER_FRAME : "<< INTER_FRAME <<std::endl;
    std::cout << "BRAM optimization : ";
    if(Archi_opt)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

    exit( 0 );

}
