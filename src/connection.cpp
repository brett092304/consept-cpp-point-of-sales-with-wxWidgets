#include "connection.h"
#include "program.h"
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
    std::vector<std::string> data;
    if (CreateConnection::connectionAvaible)
    {
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
    }
    else
    {
        MainFrame::Error("Database Not Available");
    }
    return data;
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
            pstmt = con->prepareStatement("select pass, manager, name from users where user_num=" + user + ";");
            res = pstmt->executeQuery();
            while (res->next())
            {
                std::string pass = res->getString("pass");
                password = pass;
                bool isManager = res->getBoolean("manager");
                Manager = isManager;
                std::string checkerName = res->getString("name");
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

void CreateConnection::suspendTrx(sale item, std::string itemDesc, int randNum)
{
    if (connectionAvaible)
    {
        try
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::PreparedStatement *pstmt;
            driver = get_driver_instance();
            con = driver->connect(address, username, password);
            char quote = '"';
            pstmt = con->prepareStatement("insert into suspended_trx(sku, quantity, description, price, unique_receipt) values (" + std::to_string(item.getSku()) + 
            "," + std::to_string(item.getQty()) + "," + quote + itemDesc + quote + ","+ std::to_string(item.getPrice()) + "," + std::to_string(randNum) + ");");
            pstmt->executeQuery();

            delete pstmt;
            delete con;
        }
        catch(sql::SQLException &e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}

std::vector<std::vector<std::string>> CreateConnection::resumeTranxView(std::string statement)
{
    if (connectionAvaible)
    {
        std::vector<std::vector<std::string>> data;
        std::vector<std::string> skuvec;
        std::vector<std::string> descvec;
        std::Vector<std::string> qtyvec;
        std::vector<std::string> pricevec;
        std::vector<std::string> receiptvec;

        try
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::ResultSet *res;
            sql::PreparedStatement *pstmt;

            driver = get_driver_instance();
            con = driver->connect(address, username, password);
            pstmt = con->prepareSatement("select * from suspended_trx");
            res = pstmt->ExecuteQuery();
            while(res->next())
            {
                std::string sku = res->getString("sku");
                skuvec.push_back(sku);
                std::string desc = res->getString("description");
                descvec.push_back(desc);
                std::string qty = res->getString("quantity");
                qtyvec.push_back(qty);
                std::string price = res->getString("price");
                pricevec.push_back(price);
                std::string receipt = res->getString("unique_receipt");
                receiptvec.push_back(receipt);
            }
            delete pstmt;
            delete res;
            delete con;
        }
        catch (sql::SQLException &e)
        {
            std::cout << "#ERR: " << e.what();
            std::cout << "Error Code: " << e.getErrorCode();
            std::cout << "SQL State: " << e.getSQLState() << std::endl;

        }
        data.push_back(skuvec);
        data.push_back(descvec);
        data.push_back(qtyvec);
        data.push_back(pricevec);
        data.push_back(receiptvec);
        return data;
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
