#include "PCH.h"

class sale
{
    public:
        sale(int sku, int qty, double price);

        static std::string formatTotalPrice(int n);
        static double getCashAmount(std::string amount);
        static double formateToDoubleCash(std::string amount);
        static void printTotal(std::string totalAmount);
        static void addItem(int item, int quantity, double itemPrice);
        static void removeItem(int position);
        static void removeTranx();
        static int scanRemoveItem(std::string sku);
        static sale getItem(int pos);
        static int getTranxLength();
        static std::string formatStringd(double num);

        void changeQty(int qty, int pos);
        void changePrice(double price, int pos);
        int getSku();
        int getQty();
        double getPrice();

    private:
        static std::list<sale> itemList;

        int itemSku, itemQty;
        double itemPrice;
        double cashAmount;

};