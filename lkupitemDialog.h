#include <wx/wx.h>
#include <wx/grid.h>

class LkUpItemDialog : public wxDialog
{
    public:
        LkUpItemDialog(const wxString &title, wxString sku);
        void OnClose(wxKeyEvent &event);
        void dataTableSize(wxSizeEvent &event);
        void BtnClose(wxCommandEvent &event);
    private:
        wxPanel *LkUpItemPanel;
        wxGrid *dataTable;
};