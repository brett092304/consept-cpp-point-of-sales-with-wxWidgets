#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/display.h>

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
        void deleteItem(int pos);
        void addItem();
        void addQty();
        void cancelOperation();
        void addDataToTable(std::vector<std::string> data);
        std::string cashAmountEntered;
        static void Error(std::string errorMessage);
        bool loggedIn = false;
        bool isManager = false;
        bool isTempManager = false;
        void updateTable(std::string desc, std::string qty, double price, std::string sku);
        
    private:
        wxPanel *mainPanel;
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
        wxStaticText *transactionPersonText;
        wxBoxSizer *functionVSizer;
        wxBoxSizer *paymentVSizer;
        wxBoxSizer *mainMenuVSizer;
        wxBoxSizer *managerMenuVSizer;
        wxBoxSizer *loggedInHSizer;

        wxStaticText *finalTotalDue;
        wxStaticText *totalSaleAmount;
        wxStaticText *subTotalAmount;
        wxStaticText *taxTotalAmount;

        int tablePos = 0;

        bool gettingCash = false;
        bool gettingItem = false;

        int itemToAdd;

        const int ID_Logout = wxNewId();
};
