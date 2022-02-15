/**
 * Danh Nguyen, 2022
 *
 * https://github.com/danny-cpp
 *
 */
#include <PCH.h>

#include "Lab2ProvidedAPI.h"


int main(int argc, char const *argv[]) {

    std::cout << "Server initiated!" << std::endl;

    Lab2ProvidedAPI::ClientRequest rq;
    char* msg = strdup("000-0-hello");
    Lab2ProvidedAPI::ParseMsg(msg, &rq);

    char** theArray = (char **) malloc(10*sizeof (char *));
    for (int i = 0; i < 10; i++) {
        theArray[i] = (char *) malloc(10 * sizeof (char ));
    }
    char* src = "hello";
    Lab2ProvidedAPI::setContent(src, 3, theArray);
    char result[15];
    Lab2ProvidedAPI::getContent(result, 3, theArray);

    std::cout << result << std::endl;



    return 0;
}