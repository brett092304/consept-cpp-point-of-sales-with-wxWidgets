#include "PCH.h"

class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
        void OnLogout(bool loginManager);
        void keyPress(wxKeyEvent &event);
        void GridSize(wxSizeEvent &event);
        void EnterNumPadNumber(wxCommandEvent &event);
        void MenuLgout(wxCommandEvent &event);
        void LkUpItem();
        void getCash();
        void reciveCash();
        void getManualCard();
        void scanDelete();
        void deleteItem(int pos);
        void deleteTranx(bool recievedPayment);
        void duplicateTableLine();
        void addItem();
        void addQty();
        void changeQty();
        void changePrice();
        void getFromDatabase();
        void cancelOperation();
        void addDataToTable(std::vector<std::string> data);
        std::string cashAmountEntered;
        static void Error(std::string errorMessage);
        bool loggedIn = false;
        static bool isDebug;
        static bool isManager;
        static bool isTempManager;
        static std::string cashirName;
        static std::string cashirNumbers;
        void updateTable(std::string desc, std::string qty, double price, std::string sku);
        void totalTranx();
        double subTotalTranx();
        double taxTotalTranx(double subtotal);
        void determineTotalAfterPayment(double payment);
        void taxExempt();
        
    private:
        wxPanel *mainPanel;
        wxBoxSizer *mainVSizer;
        wxMenuBar *menuBar;
        wxMenu *file;
        wxTextCtrl *UPCorPLUBox;
        wxBoxSizer *dataTableVSizer;
        wxGrid *dataTable;
        wxBoxSizer *virtNumPadSizer;
        wxBoxSizer *elementsVSizer;
        wxStaticText *UPCorPLUText;
        wxStaticText *todaysDate;
        wxStaticText *personLoggedIn;
        wxStaticText *numbersLoggedIn;
        wxStaticText *isManagerText;
        wxStaticText *isDebugText;
        wxStaticText *transactionPersonText;
        wxBoxSizer *functionVSizer;
        wxBoxSizer *paymentVSizer;
        wxBoxSizer *mainMenuVSizer;
        wxBoxSizer *managerMenuVSizer;
        wxBoxSizer *loggedInHSizer;

        wxBoxSizer *finalTotalHSizer;
        wxStaticText *finalTotalLabel;
        wxStaticText *finalTotalDue;
        wxStaticText *totalSaleAmount;
        wxStaticText *subTotalAmount;
        wxStaticText *taxTotalAmount;

        int tablePos = -1;

        bool gettingCash = false;
        bool gettingItem = false;
        bool scanDeleteItem = false;
        bool changingQty = false;
        bool changingPrice = false;
        bool isTaxExempt = false;
        bool settingTaxExempt = false;
        bool recievedPartialPayment = false;
        bool hasChange = false;

        int itemToAdd;
        int qtyToAdd;
        double totalDue;

};
