#pragma once

#include <PCH.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "SharedPoolAccess.h"
#include "Lab2ProvidedAPI.h"
#include "Timing.h"


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
         * @param theArray
         * @return
         */
        [[noreturn]] static std::deque<std::thread> socketIni(const std::string& IP,
                                                              int port_number,
                                                              int number_of_clients,
                                                              const std::function<void (int, char**, SharedPoolAccess&)>& thread_action_lambda,
                                                              char** shared_data_array,
                                                              SharedPoolAccess &pool_access_manager) {

            // Creating a thread (handler) array that will be return to the user for
            // reference
            std::deque<std::thread> thread_array;


            // File descriptors for sockaddr_in, server, client
            struct sockaddr_in sock_var;
            int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
            int clientFileDescriptor;


            // Forcefully attaching socket to the port
            int opt = 1;
            if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                           &opt, sizeof(opt)))
            {
                std::cout << "ERROR! Failed to reuse port. Please remake and restart! Aborting..." << std::endl;
                exit(-1);
            }

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
                int ID = 1;
                bool ready_to_get_avg = false;
                double sum_time_taken = 0;
                while(true) {

                    // Can handle upto @number_of_clients at a time
                    for (int i = 0; i < number_of_clients; i++) {

                        // For each accept request, we handle on different thread
                        clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);

                        #if 0
                            std::cout << "Connected to client " << clientFileDescriptor << std::endl;
                        #endif

                        thread_array.emplace_back([&, clientFileDescriptor, ID] {

                            #if DEBUG_MODE
                                std::cout << ID << "th request  "  << std::endl;
                            #endif

                            // TIMING SCOPE
                            double elapsed_time = 0;
                            {
                                Shell379::Utilities::totalTiming<std::milli> timer(&elapsed_time);
                                // The lambda (loosely speaking, the code block, like function pointer) is passed by
                                // reference for speed. The clientFileDescriptor however, is copied (passed by value)
                                thread_action_lambda(clientFileDescriptor, shared_data_array, pool_access_manager);
                            }
                            sum_time_taken += elapsed_time;

                        });

                        // Indicates we have finished a "batch". We will compute avg and write to fill.
                        // Ready for a new batch
                        if (ID == COM_NUM_REQUEST) {
                            ready_to_get_avg = true;
                            ID = 1;
                            break;
                        }

                        ID++;
                    }

                    for (auto &item : thread_array) {
                        item.detach();
                        thread_array.pop_front();
                    }

                    if (ready_to_get_avg) {

                        double result = (sum_time_taken / 1000) / COM_NUM_REQUEST;
                        double* avg_latency = &result;

                        Lab2ProvidedAPI::saveTimes(avg_latency, 1);

                        ready_to_get_avg = false;
                        sum_time_taken = 0;
                    }
                }

                close(serverFileDescriptor);
            }
            else {
                std::cout << "ERROR! Socket creation failed. Please remake and restart! Aborting..." << std::endl;
                exit(-1);
            }

            return thread_array;
        }

    };
}
