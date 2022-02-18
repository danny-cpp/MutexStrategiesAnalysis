#pragma once


#include "SharedPoolAccess.h"

#include "Lab2ProvidedAPI.h"
#include "Timing.h"

namespace Ece420 {


    class DataCommManager {
    public:

        static double singleMutexComm(int clientFileDescriptor,
                                      char** theArray,
                                      Ece420::SharedPoolAccess &pool_access_manger);


        static double arrayMutexComm(int clientFileDescriptor,
                                     char** theArray,
                                     Ece420::SharedPoolAccess &pool_access_manger);


        static double singleRWLockComm(int clientFileDescriptor,
                                       char** theArray,
                                       Ece420::SharedPoolAccess &pool_access_manger);


        static double arrayRWLockComm(int clientFileDescriptor,
                                      char** theArray,
                                      Ece420::SharedPoolAccess &pool_access_manger);
    };
}