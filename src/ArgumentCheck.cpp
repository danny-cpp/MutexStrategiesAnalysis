#include "ArgumentCheck.h"


void ProdCon::ArgumentCheck::checkArg(int &argc, char const *argv[], int &return_thread_num) {

    std::string ID = "0";

    if (argc == 1) {
        std::cout << "Error: No number of threads specified" << std::endl;
        exit(-1);
    }

    if (argc > 2) {
        std::cout << "Error: Unspecified inputs" << std::endl;
        exit(-1);
    }

    return_thread_num = std::stoi(argv[1]);

    if (return_thread_num < 1) {
        std::cout << "Error: Can't have less than 1 thread" << std::endl;
        exit(-1);
    }

    if ((int) sqrt(return_thread_num) != sqrt(return_thread_num)) {
        std::cout << "Error: Thread num must be a square!" << std::endl;
        exit(-2);
    }

}