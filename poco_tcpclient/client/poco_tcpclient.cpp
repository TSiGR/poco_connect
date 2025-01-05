#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/FileStream.h>
#include <Poco/Exception.h>
#include <Poco/Net/SocketStream.h>

#include <iostream>
#include <fstream>
#include "poco_tcpclient.h"


Client::Client(const std::string& addr, const std::string& port) : m_sock_addr(addr, port), m_sock(m_sock_addr)
{
}

    // initialize connection for the first time

void Client::initConnection()
{
    while (strcmp(input, "start"))
    {
        std::cout << "To begin working with server type the word ""start""\n";
        memset(input, '\0', sizeof(input));
        std::cin >> input;
    }
    sendReceive();
    std::cout << buff;
}

    // input data and send to server after that we get answer and output to terminal

void Client::transfer()
{
    memset(input, '\0', sizeof(input));
    std::cin >> input;
    memset(buff, '\0', sizeof(buff));
    sendReceive();
    std::cout << buff;
    if (strcmp(buff, "%Ready to get files.\n") == 0)
        getfiles();
}

    // after input the necessary parameter to server we can get files with information

void Client::getfiles()
{
    memset(buff, '\0', sizeof(buff));
    while (strcmp(input, "y"))
    {
        std::cout << "To start getting files. You need to type the letter ""y: ";
        memset(input, '\0', sizeof(input));
        std::cin >> input;
    }
    sendReceive();

    while (strncmp(buff, "%End", 4))
    {
        std::string filename;
        std::cout << "Input filename: ";
        std::cin >> filename;
        std::ofstream filestream("../../" + filename);
        filestream.write(buff, sizeof(buff));
        filestream.close();
        memset(buff, '\0', sizeof(buff));
        memset(input, '\0', sizeof(input));
        while (strcmp(input, "y"))
        {
            std::cout << "To get the file. You need to type the letter ""y: ";
            memset(input, '\0', sizeof(input));
            std::cin >> input;
        }
        sendReceive();
    }
    std::cout << buff;
}

    // repeated operations of getting and receiving data in one method

void Client::sendReceive()
{
    strncpy(buff, input, strlen(input));
    m_sock.sendBytes(buff, sizeof(buff));
    memset(buff, '\0', sizeof(buff));
    m_sock.receiveBytes(buff, sizeof(buff));
}

int main(int argc, char** argv)
{

    std::cout << "This task is created to perform 3 tasks\n\n";

    try
    {
        Client client("127.0.0.1", "12345");

        client.initConnection();

        while (1)
            client.transfer();
        
    }
    catch(const Poco::Exception& e)
    {
        std::cerr << e.displayText() << '\n';
    }
     
    return 0;
}