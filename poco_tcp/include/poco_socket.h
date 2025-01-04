#pragma once

class newConnect : public Poco::Net::TCPServerConnection
{
    public:
    newConnect(const Poco::Net::StreamSocket& str_sock);

    void run();

    private:

    Task m_task;
    Poco::Net::StreamSocket& str_sock;
    std::ostringstream o_str_sock;
    char data[4096];
    int answer;

    void menu();

    void transmit();
};