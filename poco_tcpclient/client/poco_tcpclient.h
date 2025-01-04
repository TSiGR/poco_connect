#pragma once

#include <string>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/Socket.h>

class Client
{
    public:
    Client(const std::string&, const std::string&);
    // initialize connection for the first time

    void initConnection();

    // input data from client and send to server after that we get answer and output to terminal

    void transfer();
private:
    Poco::Net::SocketAddress m_sock_addr;
    Poco::Net::StreamSocket m_sock;

    char buff[4096]; // buffer to send and receive answers from server
    char input[4096];// buffer for client input

    // after input the necessary parameter to server we can get files with information

    void getfiles();

    // repeated operations of getting and receiving data in one method

    void sendReceive();
};