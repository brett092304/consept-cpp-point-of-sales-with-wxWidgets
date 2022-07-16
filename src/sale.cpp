#include "sale.h"
#include "program.h"
using std::string;
std::list<sale> sale::itemList = {};

sale::sale(int sku, int qty, double price)
{
    this->itemSku = sku;
    this->itemQty = qty;
    this->itemPrice = price;
}

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

double sale::getCashAmount(string amount)
{
    string cashReady;
    if (MainFrame::isDebug)
        std::cout << amount << std::endl;
    //amount.erase(std::remove(amount.begin(), amount.end(), '.'), amount.end());
    cashReady = amount;
    if (MainFrame::isDebug)
        std::cout << cashReady << std::endl;
    double cashRecived = 0.0;
    try
    {
        //int cashAmountInt = std::stoi(cashReady);
        //cashRecived = std::stod(formatTotalPrice(cashAmountInt));
        cashRecived = std::stod(cashReady);
    }
    catch(const std::exception& e)
    {
        MainFrame::Error("Bad Cash Amount Error");
    }
    return cashRecived;
}

void sale::printTotal(std::string totalAmount)
{
    std::cout << totalAmount << std::endl;
}

std::string sale::formatStringd(double num)
{
    std::stringstream ss;
    ss << std::fixed <<std::setprecision(2) << num;
    std::string numStr = ss.str();
    return numStr;
}

void sale::addItem(int item, int quantity, double price)
{
    itemList.push_back(sale(item, quantity, price));
}

void sale::removeItem(int pos)
{
    auto itsku = itemList.begin();
    if (pos >= 0)
    {
        std::advance(itsku, pos);
    }
    if (pos >= 0)
    {
        itemList.erase(itsku);
    }
}

void sale::removeTranx()
{
    itemList.clear();
}

int sale::scanRemoveItem(std::string sku)
{
    int posToRemove = -1;
    int pos = 0;
    for (auto it = itemList.begin(); it != itemList.end(); it++)
    {
        if (sku == std::to_string(it->itemSku))
        {
            posToRemove = pos;
            break;
        }
        pos++;
    }
    return posToRemove;
}

sale sale::getItem(int pos)
{
    auto skuIt = itemList.begin();
    std::advance(skuIt, pos);
    return *skuIt;
}

void sale::changeQty(int qty, int pos)
{
    auto it = itemList.begin();
    std::advance(it, pos);
    it->itemQty = qty;

}

void sale::changePrice(double price, int pos)
{
    auto it = itemList.begin();
    std::advance(it, pos);
    it->itemPrice = price;
}

int sale::getTranxLength(){return itemList.size();}
int sale::getSku(){return this->itemSku;}
int sale::getQty(){return this->itemQty;}
double sale::getPrice(){return this->itemPrice;}
