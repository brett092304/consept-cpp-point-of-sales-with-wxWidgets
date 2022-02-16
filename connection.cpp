#include "connection.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

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
            pstmt = con->prepareStatement("SELECT * FROM products WHERE sku=" + statement + ";");
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

bool CreateConnection::establishConnection(std::string ip, std::string user, std::string pass)
{
    bool result;
    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        driver = get_driver_instance();
        con = driver->connect(ip, user, pass);
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
    if (establishConnection(fileAns.at(0), fileAns.at(1), fileAns.at(2)))
    {
	    CreateConnection::address = fileAns.at(0);
	    CreateConnection::username = fileAns.at(1);
	    CreateConnection::password = fileAns.at(2);
	    CreateConnection::connectionAvaible = true;
    }
    else
    {
	    CreateConnection::connectionAvaible = false;
    }



}
