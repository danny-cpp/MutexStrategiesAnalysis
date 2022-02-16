/**
 * Danh Nguyen, 2022
 *
 * https://github.com/danny-cpp
 *
 */
#include <PCH.h>

#include "Lab2ProvidedAPI.h"
#include "Networking.h"


void doSomething(int in) {
    int clientFileDescriptor=in;
    char str[200];

    read(clientFileDescriptor,str,200);
    printf("reading from client:%s\n",str);
    write(clientFileDescriptor,str,200);
    close(clientFileDescriptor);
}

int main(int argc, char const *argv[]) {

    std::cout << "Server initiated!" << std::endl;

    int number_of_client = 10;
    int string_array_size = 10;

    // Lab2ProvidedAPI::ClientRequest rq;
    // char* msg = strdup("000-0-hello");
    // Lab2ProvidedAPI::ParseMsg(msg, &rq);

    char** theArray = (char **) malloc(string_array_size * sizeof (char *));
    for (int i = 0; i < 10; i++) {
        theArray[i] = (char *) malloc(COM_BUFF_SIZE * sizeof (char ));
        sprintf(theArray[i], "String %d: the initial value", i);
    }

    Ece420::Networking::socketIni("127.0.0.1", 3000, number_of_client, doSomething);


    // char* src = "hello";
    // Lab2ProvidedAPI::setContent(src, 3, theArray);
    // char result[15];
    // Lab2ProvidedAPI::getContent(result, 3, theArray);
    //
    // std::cout << result << std::endl;



    return 0;
}