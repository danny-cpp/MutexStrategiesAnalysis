#include "ArgumentCheck.h"


void ProdCon::ArgumentCheck::checkArg(int &argc, char const *argv[],
                                      int &return_array_size,
                                      std::string &return_IP,
                                      int &return_port_number) {

    std::string ID = "0";

    if (argc == 1) {
        std::cout << "Error: No array size specified" << std::endl;
        exit(-1);
    }

    if (argc > 4) {
        std::cout << "Error: Unspecified inputs" << std::endl;
        exit(-1);
    }

    return_array_size = std::stoi(argv[1]);

    if (return_array_size < 1) {
        std::cout << "Error: Can't have array size less than 1" << std::endl;
        exit(-1);
    }

    return_IP = argv[2];

    return_port_number = std::stoi(argv[3]);

}