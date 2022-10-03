#include "PCH.h"

class ManualCreditCard : public wxDialog
{
    public:
        ManualCreditCard(const wxString &title, double amountDue, double *paymentAmount);
        void cancel(wxCommandEvent &event);
        double getPayAmount();
        void keyPad(wxCommandEvent &event);
        void getFocus(wxFocusEvent &event);

    private:
        void keypadInsert(std::string num);
        int getMonth();
        int getYear();

        wxTextCtrl *cardAmountBox;
        wxTextCtrl *cardNumBox;
        wxTextCtrl *cardExpireYearBox;
        wxTextCtrl *cardExpireMonthBox;
        wxTextCtrl *cardValidationBox;

        double *payAmount = nullptr;
        double amount = 0.00;
        int focusId;
        const int MON_PER_YEAR = 12;

};