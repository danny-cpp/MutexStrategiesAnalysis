#pragma once

#include <PCH.h>


namespace ProdCon {
    /**
     * Checking input argument at the call for the program. Specifically argc and argv
     */
    class ArgumentCheck {
    public:
        /**
         * Handle arguments. Return number of threads user issued.
         *
         * @param argc
         * @param argv
         * @param return_thread_num
         */
        static void checkArg(int &argc, char const *argv[], int &return_thread_num);
    };
}