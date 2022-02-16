#pragma once

#include <PCH.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


namespace Ece420 {

    class Networking {
    public:

        /**
         * Create a sockaddr_in address that binds to the IP and port provided
         *
         * @param IP
         * @param port_number
         * @param number_of_clients
         * @param thread_action_lambda
         * @return
         */
        [[noreturn]] static std::vector<std::thread> socketIni(const std::string& IP,
                                           int port_number,
                                           int number_of_clients,
                                           const std::function<void(int)>& thread_action_lambda) {

            // Creating a thread (handler) array that will be return to the user for
            // reference
            std::vector<std::thread> thread_array;
            thread_array.reserve(number_of_clients);

            // File descriptors for sockaddr_in, server, client
            struct sockaddr_in sock_var;
            int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
            int clientFileDescriptor;

            // Initiate with IP and port
            sock_var.sin_addr.s_addr=inet_addr(IP.c_str());
            sock_var.sin_port=port_number;
            sock_var.sin_family=AF_INET;

            /**
             * !!! IMPORTANT !!! Multi-thread server implementation
             */
            // Start binding with client. For each client, we use a different thread
            if(bind(serverFileDescriptor,(struct sockaddr*)&sock_var,sizeof(sock_var))>=0) {

                #if DEBUG_MODE
                    std::cout << "\"socket has been created\"" << std::endl;
                #endif

                listen(serverFileDescriptor,2000);

                // Ready to accept new client (if it is within the limit)
                while(true) {

                    // Can handle upto @number_of_clients at a time
                    for (int i = 0; i < number_of_clients; i++) {

                        // For each accept request, we handle on different thread
                        clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);

                        #if DEBUG_MODE
                        std::cout << "Connected to client " << clientFileDescriptor << std::endl;
                        #endif

                        thread_array.emplace_back([&, clientFileDescriptor] {

                            // The lambda (loosely speaking, the code block, like function pointer) is passed by
                            // reference for speed. The clientFileDescriptor however, is copied (passed by value)
                            thread_action_lambda(clientFileDescriptor);
                        });
                    }

                }
                close(serverFileDescriptor);
            }
            else {
                std::cout << "Socket creation failed" << std::endl;
            }

            return thread_array;
        }

    };
}
