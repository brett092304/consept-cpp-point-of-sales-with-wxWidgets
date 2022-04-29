#include <wx/wx.h>

class SetUp : public wxFrame
{
    public:
        SetUp(const wxString& title);
        void createFile(wxCommandEvent &event);

    private:
        wxTextCtrl *pathBox;
        wxTextCtrl *userBox;
        wxTextCtrl *passBox;

        wxTextCtrl *userPathBox;
        wxTextCtrl *userDBUserBox;
        wxTextCtrl *userPassBox;

};