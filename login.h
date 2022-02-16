#include <wx/wx.h>

class loginDialog : public wxDialog
{
    public:
        loginDialog(const wxString &title, bool isManagerLogin);
        void OnClose(wxCommandEvent &event);
        void OnLogIn(wxCommandEvent &event);
        void logIn();
        void enterKeyPad(wxCommandEvent &event);

    private:
        wxTextCtrl *loginUserBox;
        wxTextCtrl *loginPassBox;
        bool enteringUser;
        bool isTempManagerLogin = false;
};