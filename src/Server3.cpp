/**
 * Danh Nguyen, 2022
 *
 * https://github.com/danny-cpp
 *
 */
#include <PCH.h>

#include "Lab2ProvidedAPI.h"
#include "Networking.h"
#include "ArgumentCheck.h"
#include "SharedPoolAccess.h"
#include "DataCommManager.h"


int main(int argc, char const *argv[]) {

    std::cout << "Server using 1 single read-write mutex method!" << std::endl;

    int number_of_client = 1000;
    int string_array_size = 0;
    std::string IP;
    int port_number = 0;

    ProdCon::ArgumentCheck::checkArg(argc, argv, string_array_size, IP, port_number);


    char** theArray = (char **) malloc(string_array_size * sizeof (char *));
    for (int i = 0; i < string_array_size; i++) {
        theArray[i] = (char *) malloc(COM_BUFF_SIZE * sizeof (char ));
        sprintf(theArray[i], "String %d: the initial value", i);
    }


    Ece420::SharedPoolAccess sharedPoolAccess(true, 1);


    Ece420::Networking::socketIni(IP,
                                  port_number,
                                  number_of_client,
                                  Ece420::DataCommManager::singleRWLockComm,
                                  theArray,
                                  sharedPoolAccess);


    for (int i = 0; i < string_array_size; i++) {
        delete theArray[i];
    }
    delete theArray;

    return 0;
}