
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerParams.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/NamedEvent.h>
#include <Poco/Process.h>

#include "task1.h"
#include "transmit.h"
#include "poco_socket.h"

#include <iostream>
#include <sstream>

#if defined(POCO_OS_FAMILY_WINDOWS)
	Poco::NamedEvent terminator(Poco::ProcessImpl::terminationEventName(Poco::Process::id()));
#else
	Poco::Event terminator;
#endif

    newConnect::newConnect(const Poco::Net::StreamSocket& str_sock) : Poco::Net::TCPServerConnection(str_sock), str_sock(socket())
    {
    }

    void newConnect::run()
    {
        
        try
        {
            std::cout << "Created connection " << str_sock.peerAddress().host().toString() << "\n";
            str_sock.receiveBytes(data, sizeof(data));
            std::string out_of_func;

            while (1)
            {
                menu();
                Transmit::transmit(data, sizeof(data), o_str_sock, str_sock);

                switch (data[0])
                {
                    case 'a':
                        out_of_func = m_task.solution_1();
                        o_str_sock << out_of_func;
                        out_of_func.clear();
                        break;
                    case 'b':
                        out_of_func = m_task.solution_2(str_sock);
                        o_str_sock << out_of_func;
                        out_of_func.clear();
                        break;
                    case 'c':
                        out_of_func = m_task.solution_3(str_sock);
                        o_str_sock << out_of_func;
                        out_of_func.clear();
                        break;
                    default:
                        o_str_sock << "This task doesn't exist.\nPlease, input only the next letters from menu.\n";
                        break;
                }

                while (strcmp(data, "yes") && strcmp(data, "no"))
                {
                    o_str_sock << "Start again? (yes/no): ";
                    Transmit::transmit(data, sizeof(data), o_str_sock, str_sock);
                }
                if (strcmp(data, "no"))
                    continue;
                else
                    break;
            }

            o_str_sock.str("");
            o_str_sock.clear();
            o_str_sock << "Connection closed.\nType Ctrl-C to disconnect from the server.\nSee you later. Bye!";
            memset(data, '\0', sizeof(data));
            strncpy(data, o_str_sock.str().c_str(), o_str_sock.str().size());
            str_sock.sendBytes(data, sizeof(data));
            o_str_sock.str("");
            o_str_sock.clear();
            str_sock.shutdownReceive();
        }
        catch(const Poco::Exception& e)
        {
            std::cerr << "Exception during connect " << e.displayText() << '\n';
        }
    }

    void newConnect::menu()
    {
        o_str_sock <<   "============ MENU ============\n" <<
                        "a - Get odd values from array\n" <<
                        "b - Remove the repeated values from 2 files\n" <<
                        "c - Play the Hang-Man game\n" << 
                        "Input letter in lower case to start performing the task: ";
    }

int main()
{
    try
    {
        // create socket for the server

        Poco::Net::ServerSocket srv(12345);

        // define some parameters for the server

        Poco::Net::TCPServerParams *param = new Poco::Net::TCPServerParams();
        param->setMaxThreads(4);
        param->setMaxQueued(4);
        param->setThreadIdleTime(50);

        // start the server according to parameters

        Poco::Net::TCPServer server(new Poco::Net::TCPServerConnectionFactoryImpl<newConnect>(), srv, param);
        server.start();
    
        std::cout << "TCP server is running on port " << server.port() << "\n";

        terminator.wait();

        server.stop();

    }
    catch(const Poco::Exception& e)
    {
        std::cerr << "Exception in main tcp server " << e.displayText() << '\n';
    }
    return 0;
}