#include <iostream>
#include <list>
#include <vector>

struct sale
{
    public:
        std::string formatTotalPrice(int n);
        void getCashAmount(std::string amount);
        double formateToDoubleCash(std::string amount);
        void getTotal(std::string totalAmount);
        void addItem(int item, int quantity, double itemPrice);
        void removeItem(int position);
    private:
        double cashAmount;
        static std::list<int> itemSkuList;
        static std::list<double> itemPriceList;
};