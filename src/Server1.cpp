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


void doSomething(int clientFileDescriptor, char** theArray, Ece420::SharedPoolAccess &pool_access_manger) {

    char str[COM_BUFF_SIZE];
    read(clientFileDescriptor,str,COM_BUFF_SIZE);


    Lab2ProvidedAPI::ClientRequest request;
    Lab2ProvidedAPI::ParseMsg(str, &request);


    char to_be_sent[COM_BUFF_SIZE];
    if (request.is_read == 1) {
        // Attempt to modify share memory. It should lock this critical section
        pool_access_manger.normalLock();
        Lab2ProvidedAPI::getContent(to_be_sent, request.pos, theArray);
        pool_access_manger.normalUnlock();
        // End critical section

        write(clientFileDescriptor, to_be_sent, COM_BUFF_SIZE);
    }
    else {
        // Attempt to modify share memory. It should lock this critical section
        pool_access_manger.normalLock();
        Lab2ProvidedAPI::setContent(request.msg, request.pos, theArray);
        pool_access_manger.normalUnlock();
        // End critical section
    }

    // write(clientFileDescriptor, "to_be_sent", COM_BUFF_SIZE);
    // printf("reading from client:%s\n",str);


    close(clientFileDescriptor);
}

int main(int argc, char const *argv[]) {

    std::cout << "Server using 1 single mutex method!" << std::endl;

    int number_of_client = 1000;
    int string_array_size = 0;
    std::string IP;
    int port_number = 0;

    ProdCon::ArgumentCheck::checkArg(argc, argv, string_array_size, IP, port_number);

    // Lab2ProvidedAPI::ClientRequest rq;
    // char* msg = strdup("000-0-hello");
    // Lab2ProvidedAPI::ParseMsg(msg, &rq);

    char** theArray = (char **) malloc(string_array_size * sizeof (char *));
    for (int i = 0; i < string_array_size; i++) {
        theArray[i] = (char *) malloc(COM_BUFF_SIZE * sizeof (char ));
        sprintf(theArray[i], "String %d: the initial value", i);
    }


    Ece420::SharedPoolAccess sharedPoolAccess(false, 1);


    Ece420::Networking::socketIni(IP, port_number, number_of_client, doSomething, theArray, sharedPoolAccess);


    // char* src = "hello";
    // Lab2ProvidedAPI::setContent(src, 3, theArray);
    // char result[15];
    // Lab2ProvidedAPI::getContent(result, 3, theArray);
    //
    // std::cout << result << std::endl;


    // for (auto &item : handlers) {
    //     item.detach();
    // }


    for (int i = 0; i < string_array_size; i++) {
        delete theArray[i];
    }
    delete theArray;

    return 0;
}