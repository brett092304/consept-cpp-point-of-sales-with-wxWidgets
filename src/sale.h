#include "PCH.h"

struct sale
{
    public:
        std::string formatTotalPrice(int n);
        double getCashAmount(std::string amount);
        double formateToDoubleCash(std::string amount);
        void getTotal(std::string totalAmount);
        void addItem(int item, int quantity, double itemPrice);
        void removeItem(int position);
        void removeTranx();
        int scanRemoveItem(std::string sku);
        void getItem(int pos, int *sku, int *qty, double *price);
        void changeQty(int pos, int qty);
        void changePrice(int pos, double price);
        int getTranxLength();
        static std::string formatStringd(double num);
    private:
        double cashAmount;
        static std::list<int> itemSkuList;
        static std::list<double> itemPriceList;
        static std::list<int> itemQtyList;

        static void clearSkuList();
        static void clearPriceList();
        static void clearQtyList();
};