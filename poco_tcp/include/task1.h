#ifndef Task1_h
#define Task1_h

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Poco/Net/StreamSocket.h>

class Task
{
    public:

    Task() {}
    std::string solution_1();
    std::string solution_2(Poco::Net::StreamSocket&);
    std::string solution_3(Poco::Net::StreamSocket&);

    private:
    void make_converse(std::ifstream&, std::vector<int>&);
    void delete_converse(std::ifstream&, std::vector<int>&);
    int get_randomnumber(int, int);
    bool check_fill(std::vector<char>&);
    void transmit(Poco::Net::StreamSocket&);

    std::ostringstream o_str;
    char getf_user[4096];
    int answer;
};

#endif