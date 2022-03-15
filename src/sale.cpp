#include "sale.h"
#include "program.h"
using std::string;
std::list<int> sale::itemSkuList = {};
std::list<double> sale::itemPriceList = {};
std::list<int> sale::itemQtyList = {};

string sale::formatTotalPrice(int n)
{
    string formatedCashStr;
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::showbase << std::put_money(n);
    formatedCashStr = ss.str();
    formatedCashStr.erase(std::remove(formatedCashStr.begin(), formatedCashStr.end(), '$'), formatedCashStr.end());
    return formatedCashStr;
}

void sale::getCashAmount(string amount)
{
    string cashReady;
    amount.erase(std::remove(amount.begin(), amount.end(), '.'), amount.end());
    cashReady = amount;
    try
    {
         int cashAmountInt = std::stoi(cashReady);
         std::cout << formatTotalPrice(cashAmountInt) << std::endl;
         formateToDoubleCash(formatTotalPrice(cashAmountInt));
    }
    catch(const std::exception& e)
    {
        MainFrame::Error("Bad Cash Amount Error");
    }
}

void sale::getTotal(std::string totalAmount)
{
    std::cout << totalAmount << std::endl;
}

double sale::formateToDoubleCash(string amount)
{
    return cashAmount = std::stod(amount);
    
}

void sale::addItem(int item, int quantity, double itemPrice)
{
    itemSkuList.push_back(item);
    itemQtyList.push_back(quantity);
    itemPriceList.push_back(itemPrice);
}

void sale::removeItem(int pos)
{
    auto itsku = itemSkuList.begin();
    auto itprice = itemPriceList.begin();
    auto itqty = itemQtyList.begin();
    if ((pos -1) > 0)
    {
        std::advance(itsku, pos -1);
        std::advance(itqty, pos -1);
        std::advance(itprice, pos -1);
    }
    if (pos -1 > 0)
    {
        itemSkuList.erase(itsku);
        itemQtyList.erase(itqty);
        itemPriceList.erase(itprice);
    }
    else
    {
        itemSkuList.clear();
        itemQtyList.clear();
        itemPriceList.clear();
    }
}

int sale::scanRemoveItem(std::string sku)
{
    int posToRemove = 0;
    int pos;
    bool foundItem = false;
    auto it = itemSkuList.begin();
    while (!foundItem)
    {
        posToRemove++;
        if (*it == sku)
        {
            pos = posToRemove;
            foundItem = true;
        }
        
        if (it != itemSkuList.end())
        {
            it++;
        }
        else
        {
            foundItem = true;
            pos = -1;
        }
    }
    std::cout << pos << std::endl;
    return pos;
}