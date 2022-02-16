#pragma once

#include <PCH.h>


namespace ProdCon {
    /**
     * Checking input argument at the call for the program. Specifically argc and argv
     */
    class ArgumentCheck {
    public:
        /**
         * Handle arguments. Return shared array size
         *
         * @param argc
         * @param argv
         * @param return_array_size
         */
        static void checkArg(int &argc,
                             char const *argv[],
                             int &return_array_size,
                             std::string &return_IP,
                             int &return_port_number);
    };
}