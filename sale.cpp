#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "sale.h"
#include "program.h"
using std::string;

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
    for (int i = 0; i < quantity; i++)
    {
        itemSkuList.push_back(item);
        itemPriceList.push_back(itemPrice);
    }
}

void sale::removeItem(int pos)
{
    auto itsku = itemSkuList.begin();
    auto itprice = itemPriceList.begin();
    std::advance(itsku, pos -1);
    std::advance(itprice, pos -1);
    itemSkuList.erase(itsku);
    itemPriceList.erase(itprice);
}