#include <iostream>
#include <vector>

struct CreateConnection
{
    public:
        static std::vector<std::string> connection(std::string statement);
        static void setConnectionStatus(std::vector<std::string> fileAns);
        static bool establishConnection(std::string ip, std::string user, std::string pass);
    private:
        static bool connectionAvaible;
        static std::string address;
        static std::string username;
        static std::string password;
};
