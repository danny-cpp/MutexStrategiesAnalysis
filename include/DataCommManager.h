#pragma once


#include "SharedPoolAccess.h"

#include "Lab2ProvidedAPI.h"

namespace Ece420 {


    class DataCommManager {
    public:

        static void singleMutexComm(int clientFileDescriptor,
                                    char** theArray,
                                    Ece420::SharedPoolAccess &pool_access_manger);


        static void arrayMutexComm(int clientFileDescriptor,
                                   char** theArray,
                                   Ece420::SharedPoolAccess &pool_access_manger);


        static void singleRWLockComm(int clientFileDescriptor,
                                     char** theArray,
                                     Ece420::SharedPoolAccess &pool_access_manger);


        static void arrayRWLockComm(int clientFileDescriptor,
                                     char** theArray,
                                     Ece420::SharedPoolAccess &pool_access_manger);
    };
}