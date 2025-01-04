#pragma once

class Transmit
{
    public:

    static int transmit(char data[], int amount, std::ostringstream& o_str_sock, Poco::Net::StreamSocket& str_sock)
    {
        memset(data, '\0', amount);
        strncpy(data, o_str_sock.str().c_str(), o_str_sock.str().size());
        str_sock.sendBytes(data, amount);
        o_str_sock.str("");
        o_str_sock.clear();
        memset(data, '\0', amount);
        return str_sock.receiveBytes(data, amount);
    }
};