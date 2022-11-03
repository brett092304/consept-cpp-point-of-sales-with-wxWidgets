#include "PCH.h"

class ResumeTranx : public wxDialog
{
    public:
        ResumeTranx(const wxString &title, int* receiptCode);
        void close(wxCommandEvent &event);

    private:
        wxGrid *table;
        wxPanel *resumePanel;
        int tablePos = -1;
        int* receiptNumber;

        void resizeTable(wxSizeEvent &event);
        void buttonControls(wxCommandEvent &event);
        void getReceipt();

};