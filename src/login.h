#include "PCH.h"

class loginDialog : public wxDialog
{
    public:
        loginDialog(const wxString &title, bool isManagerLogin);
        void OnClose(wxCommandEvent &event);
        void OnLogIn(wxCommandEvent &event);
        void OnCancel(wxCommandEvent &event);
        void logIn();
        void enterKeyPad(wxCommandEvent &event);
        std::string hashFunc(std::string password);
    private:
        wxTextCtrl *loginUserBox;
        wxTextCtrl *loginPassBox;
        bool enteringUser;
        bool isTempManagerLogin = false;
};