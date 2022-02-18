#include "DataCommManager.h"


double Ece420::DataCommManager::singleMutexComm(int clientFileDescriptor, char **theArray,
                                                Ece420::SharedPoolAccess &pool_access_manger) {


    char str[COM_BUFF_SIZE];
    read(clientFileDescriptor,str,COM_BUFF_SIZE);


    Lab2ProvidedAPI::ClientRequest request;
    Lab2ProvidedAPI::ParseMsg(str, &request);


    char to_be_sent[COM_BUFF_SIZE];
    double elapsed_time = 0;
    if (request.is_read == 1) {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.normalLock();
            Lab2ProvidedAPI::getContent(to_be_sent, request.pos, theArray);
            pool_access_manger.normalUnlock();
            // End critical section
        }

        write(clientFileDescriptor, to_be_sent, COM_BUFF_SIZE);
    }
    else {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.normalLock();
            Lab2ProvidedAPI::setContent(request.msg, request.pos, theArray);
            pool_access_manger.normalUnlock();
            // End critical section
        }
    }

    close(clientFileDescriptor);

    return elapsed_time;
}

double Ece420::DataCommManager::arrayMutexComm(int clientFileDescriptor, char **theArray,
                                               Ece420::SharedPoolAccess &pool_access_manger) {


    char str[COM_BUFF_SIZE];
    read(clientFileDescriptor,str,COM_BUFF_SIZE);


    Lab2ProvidedAPI::ClientRequest request;
    Lab2ProvidedAPI::ParseMsg(str, &request);


    char to_be_sent[COM_BUFF_SIZE];
    double elapsed_time = 0;
    if (request.is_read == 1) {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.normalLock(request.pos);
            Lab2ProvidedAPI::getContent(to_be_sent, request.pos, theArray);
            pool_access_manger.normalUnlock(request.pos);
            // End critical section
        }

        write(clientFileDescriptor, to_be_sent, COM_BUFF_SIZE);
    }
    else {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.normalLock(request.pos);
            Lab2ProvidedAPI::setContent(request.msg, request.pos, theArray);
            pool_access_manger.normalUnlock(request.pos);
            // End critical section
        }
    }

    close(clientFileDescriptor);

    return elapsed_time;
}

double Ece420::DataCommManager::singleRWLockComm(int clientFileDescriptor, char **theArray,
                                                 Ece420::SharedPoolAccess &pool_access_manger) {


    char str[COM_BUFF_SIZE];
    read(clientFileDescriptor,str,COM_BUFF_SIZE);


    Lab2ProvidedAPI::ClientRequest request;
    Lab2ProvidedAPI::ParseMsg(str, &request);


    char to_be_sent[COM_BUFF_SIZE];
    double elapsed_time = 0;
    if (request.is_read == 1) {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);


            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.readLock();
            Lab2ProvidedAPI::getContent(to_be_sent, request.pos, theArray);
            pool_access_manger.readUnlock();
            // End critical section
        }

        write(clientFileDescriptor, to_be_sent, COM_BUFF_SIZE);
    }
    else {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.writeLock();
            Lab2ProvidedAPI::setContent(request.msg, request.pos, theArray);
            pool_access_manger.writeUnlock();
            // End critical section
        }
    }

    close(clientFileDescriptor);

    return elapsed_time;
}

double Ece420::DataCommManager::arrayRWLockComm(int clientFileDescriptor, char **theArray,
                                                Ece420::SharedPoolAccess &pool_access_manger) {


    char str[COM_BUFF_SIZE];
    read(clientFileDescriptor,str,COM_BUFF_SIZE);


    Lab2ProvidedAPI::ClientRequest request;
    Lab2ProvidedAPI::ParseMsg(str, &request);


    char to_be_sent[COM_BUFF_SIZE];
    double elapsed_time = 0;
    if (request.is_read == 1) {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.readLock(request.pos);
            Lab2ProvidedAPI::getContent(to_be_sent, request.pos, theArray);
            pool_access_manger.readUnlock(request.pos);
            // End critical section
        }

        write(clientFileDescriptor, to_be_sent, COM_BUFF_SIZE);
    }
    else {

        // Enter timing scope
        {
            Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);

            // Attempt to modify share memory. It should lock this critical section
            pool_access_manger.writeLock(request.pos);
            Lab2ProvidedAPI::setContent(request.msg, request.pos, theArray);
            pool_access_manger.writeUnlock(request.pos);
            // End critical section
        }
    }

    close(clientFileDescriptor);

    return elapsed_time;
}
