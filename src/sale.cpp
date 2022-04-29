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

double sale::getCashAmount(string amount)
{
    string cashReady;
    std::cout << amount << std::endl;
    //amount.erase(std::remove(amount.begin(), amount.end(), '.'), amount.end());
    cashReady = amount;
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

void sale::getTotal(std::string totalAmount)
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
    if (pos >= 0)
    {
        std::advance(itsku, pos);
        std::advance(itqty, pos);
        std::advance(itprice, pos);
    }
    if (pos >= 0)
    {
        itemSkuList.erase(itsku);
        itemQtyList.erase(itqty);
        itemPriceList.erase(itprice);
    }
}

void sale::clearSkuList()
{
    itemSkuList.clear();
}

void sale::clearQtyList()
{
    itemQtyList.clear();
}

void sale::clearPriceList()
{
    itemPriceList.clear();
}

void sale::removeTranx()
{
    std::thread sku(clearSkuList);
    std::thread qty(clearQtyList);
    std::thread price(clearPriceList);
    sku.join();
    qty.join();
    price.join();
}

int sale::scanRemoveItem(std::string sku)
{
    int posToRemove = -1;
    int pos = 0;
    for (auto it = itemSkuList.begin(); it != itemSkuList.end(); it++)
    {
        if (sku == std::to_string(*it))
        {
            posToRemove = pos;
            break;
        }
        pos++;
    }
    return posToRemove;
}

void sale::getItem(int pos, int *sku, int *qty, double *price)
{
    auto skuIt = itemSkuList.begin(); 
    auto qtyIt = itemQtyList.begin();
    auto priceIt = itemPriceList.begin();

    std::advance(skuIt, pos);
    std::advance(qtyIt, pos);
    std::advance(priceIt, pos);

    if (sku != nullptr)
        *sku = *skuIt;
    if (qty != nullptr)
        *qty = *qtyIt;
    if (price != nullptr)
        *price = *priceIt;
}

void sale::changeQty(int pos, int qty)
{
    auto it = itemQtyList.begin();
    std::advance(it, pos);
    *it = qty;
}

void sale::changePrice(int pos, double price)
{
    auto it = itemPriceList.begin();
    std::advance(it, pos);
    *it = price;
}

int sale::getTranxLength(){return itemSkuList.size();}
