#include "PCH.h"
#include "sale.h"

class CreateConnection
{
    public:
        static std::vector<std::string> connection(std::string statement);
        static std::vector<std::vector<std::string>> lkUpConn(std::string statement);
        static bool loginConn(std::string user, std::string userPass, std::string *name, bool *manager);
        static void setConnectionStatus(std::vector<std::string> fileAns);
        static bool establishConnection(std::string ip, std::string user, std::string pass, std::string userIp, std::string userUser, std::string userPass);
        static void suspendTrx(sale item, std::string itemDesc, int randNum);

    private:
        static bool connectionAvaible;
        static std::string address;
        static std::string username;
        static std::string password;
        static std::string userAddress;
        static std::string userUsername;
        static std::string userPassword;
};
