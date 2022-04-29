#include "connection.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
std::string CreateConnection::address = "";
std::string CreateConnection::username = "";
std::string CreateConnection::password = "";
std::string CreateConnection::userAddress = "";
std::string CreateConnection::userUsername = "";
std::string CreateConnection::userPassword = "";
bool CreateConnection::connectionAvaible = false;


std::vector<std::string> CreateConnection::connection(std::string statement)
{
    if (CreateConnection::connectionAvaible)
    {
        std::vector<std::string> data;
        try
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::ResultSet *res;
            sql::PreparedStatement *pstmt;
            driver = get_driver_instance();
            con = driver->connect(CreateConnection::address, CreateConnection::username, CreateConnection::password);
            char quote = '"';
            pstmt = con->prepareStatement("SELECT * FROM products WHERE sku=" + statement + " or upc=" + statement + ";");
            res = pstmt->executeQuery();
            while (res->next())
            {
                std::string sku = res->getString("sku");
                std::string upc = res->getString("upc");
                std::string desc = res->getString("description");
                double regpriceD = res->getDouble("regularprice");
                double salepriceD = res->getDouble("saleprice");
                std::string regprice = std::to_string(regpriceD);
                std::string saleprice = std::to_string(salepriceD);
                data.push_back(sku);
                data.push_back(upc);
                data.push_back(desc);
                data.push_back(regprice);
                data.push_back(saleprice);
            
            }
            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException &e)
        {
            std::cout << "#ERR: " << e.what();
            std::cout << "Error Code: " << e.getErrorCode();
            std::cout << "SQL State: " << e.getSQLState() << std::endl;

        }
        return data;
    } 
}

std::vector<std::vector<std::string>> CreateConnection::lkUpConn(std::string statement)
{
    if (CreateConnection::connectionAvaible)
    {
        std::vector<std::vector<std::string>> data;
        std::vector<std::string> skuData;
        std::vector<std::string> upcData;
        std::vector<std::string> qtyData;
        std::vector<std::string> descData;
        std::vector<std::string> regPriceData;
        std::vector<std::string> salePriceData;
        try
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::ResultSet *res;
            sql::PreparedStatement *pstmt;
            driver = get_driver_instance();
            con = driver->connect(CreateConnection::address, CreateConnection::username, CreateConnection::password);
            char quote = '"';
            pstmt = con->prepareStatement("SELECT * FROM products WHERE sku Like '" + statement + "%' or upc LIKE '" + statement + "%';");
            res = pstmt->executeQuery();
            while (res->next())
            {
                std::string sku = res->getString("sku");
                skuData.push_back(sku);
                std::string upc = res->getString("upc");
                upcData.push_back(upc);
                std::string qty = res->getString("quantity");
                qtyData.push_back(qty);
                std::string desc = res->getString("description");
                descData.push_back(desc);
                double regpriceD = res->getDouble("regularprice");
                double salepriceD = res->getDouble("saleprice");
                std::string regprice = std::to_string(regpriceD);
                regPriceData.push_back(regprice);
                std::string saleprice = std::to_string(salepriceD);
                salePriceData.push_back(saleprice);
            
            }
            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException &e)
        {
            std::cout << "#ERR: " << e.what();
            std::cout << "Error Code: " << e.getErrorCode();
            std::cout << "SQL State: " << e.getSQLState() << std::endl;

        }
        data.push_back(skuData);
        data.push_back(upcData);
        data.push_back(qtyData);
        data.push_back(descData);
        data.push_back(regPriceData);
        data.push_back(salePriceData);
        return data;
    } 
}

bool CreateConnection::loginConn(std::string user, std::string userPass, std::string *name, bool *manager)
{
    if (connectionAvaible)
    {
        std::string password = "";
        bool Manager = false;
        std::string cashirName = "";
        try
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::ResultSet *res;
            sql::PreparedStatement *pstmt;
            driver = get_driver_instance();
            con = driver->connect(CreateConnection::userAddress, CreateConnection::userUsername, CreateConnection::userPassword);
            pstmt = con->prepareStatement("select user_pwd, manager, user_names from users where user_Number=" + user + ";");
            res = pstmt->executeQuery();
            while (res->next())
            {
                std::string pass = res->getString("user_pwd");
                password = pass;
                bool isManager = res->getBoolean("manager");
                Manager = isManager;
                std::string checkerName = res->getString("user_names");
                cashirName = checkerName;
            }
            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException &e)
        {
            std::cout << "#ERR: " << e.what();
            std::cout << "Error Code: " << e.getErrorCode();
            std::cout << "SQL State: " << e.getSQLState() << std::endl;

        }
        if (userPass == password)
        {
            *manager = Manager;
            *name = cashirName;
            return true;
        }
        return false;
    }
}


bool CreateConnection::establishConnection(std::string ip, std::string user, std::string pass, std::string userIp, std::string userUser, std::string userPass)
{
    bool result;
    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        driver = get_driver_instance();
        con = driver->connect(ip, user, pass);
        con = driver->connect(userIp, userUser, userPass);
        delete con;
        
        result = true;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "#ERR: " << e.what();
        std::cout << "Error Code: " << e.getErrorCode();
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        result = false;
    }
    return result;

}

void CreateConnection::setConnectionStatus(std::vector<std::string> fileAns)
{
    if (establishConnection(fileAns.at(0), fileAns.at(1), fileAns.at(2), fileAns.at(3), fileAns.at(4), fileAns.at(5)))
    {
	    CreateConnection::address = fileAns.at(0);
	    CreateConnection::username = fileAns.at(1);
	    CreateConnection::password = fileAns.at(2);
        CreateConnection::userAddress = fileAns.at(3);
        CreateConnection::userUsername = fileAns.at(4);
        CreateConnection::userPassword = fileAns.at(5);
	    CreateConnection::connectionAvaible = true;
    }
    else
    {
	    CreateConnection::connectionAvaible = false;
    }



}
