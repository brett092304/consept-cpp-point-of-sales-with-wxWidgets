#include "login.h"
#include "program.h"

loginDialog::loginDialog(const wxString &title, bool isManagerLogin) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    enteringUser = true;
    wxSize screenSize = wxGetDisplaySize() * 2/4;
    this->SetSize(screenSize);

    wxPanel *loginPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *mainVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mainHSizer = new wxBoxSizer(wxHORIZONTAL);

    wxFont font = wxFont(wxFontInfo(14));
    wxStaticText *loginUserText = new wxStaticText(loginPanel, wxID_ANY, wxT("Username: "));
    loginUserText->SetFont(font);
    loginUserBox = new wxTextCtrl(loginPanel, wxID_ANY);
    loginUserBox->SetFont(font);
    wxStaticText *loginPassText = new wxStaticText(loginPanel, wxID_ANY, wxT("Password: "));
    loginPassText->SetFont(font);
    loginPassBox = new wxTextCtrl(loginPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    loginPassBox->SetFont(font);
    wxButton *loginBtn = new wxButton(loginPanel, wxID_ANY, wxT("Login"));
    loginBtn->SetFont(font);
    wxButton *quitBtn = new wxButton(loginPanel, wxID_ANY, wxT("Quit"));
    quitBtn->SetFont(font);
    if (isManagerLogin)
    {
        quitBtn->Disable();
    }

    loginBtn->Bind(wxEVT_BUTTON, &loginDialog::OnLogIn, this);

    wxBoxSizer *loginFieldVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *loginFieldH1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loginFieldH2Sizer = new wxBoxSizer(wxHORIZONTAL);

    loginFieldH1Sizer->Add(loginUserText, wxSizerFlags(0).Expand().Border(wxALL, 4));
    loginFieldH1Sizer->Add(loginUserBox, wxSizerFlags(1).Expand().Border(wxALL, 4));

    loginFieldH2Sizer->Add(loginPassText, wxSizerFlags(0).Expand().Border(wxALL, 4));
    loginFieldH2Sizer->Add(loginPassBox, wxSizerFlags(1).Expand().Border(wxALL, 4));

    loginFieldVSizer->Add(loginFieldH1Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loginFieldVSizer->Add(loginFieldH2Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loginFieldVSizer->Add(loginBtn, wxSizerFlags(0).Center().Border(wxALL, 4));
    loginFieldVSizer->Add(quitBtn, wxSizerFlags(0).Center().Border(wxALL, 4));

    //login numpad
    wxBoxSizer *loginNumPadSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *loginNumPadHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loginNumPadV1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *loginNumPadV2Sizer = new wxBoxSizer(wxVERTICAL);
    wxSizerFlags numPadNumBtnFlags = wxSizerFlags(1).Expand().Border(wxALL, 2);
    wxSizerFlags numPadRowFlags = wxSizerFlags(1).Expand().Top().Border(wxALL, 2);

    wxBoxSizer *NumPadNumRow1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow4 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *numPad1Btn = new wxButton(loginPanel, 401, wxT("1"));
    wxButton *numPad2Btn = new wxButton(loginPanel, 402, wxT("2"));
    wxButton *numPad3Btn = new wxButton(loginPanel, 403, wxT("3"));
    wxButton *numPad4Btn = new wxButton(loginPanel, 404, wxT("4"));
    wxButton *numPad5Btn = new wxButton(loginPanel, 405, wxT("5"));
    wxButton *numPad6Btn = new wxButton(loginPanel, 406, wxT("6"));
    wxButton *numPad7Btn = new wxButton(loginPanel, 407, wxT("7"));
    wxButton *numPad8Btn = new wxButton(loginPanel, 408, wxT("8"));
    wxButton *numPad9Btn = new wxButton(loginPanel, 409, wxT("9"));
    wxButton *numPad0Btn = new wxButton(loginPanel, 410, wxT("0"));
    wxButton *numPadDotBtn = new wxButton(loginPanel, 411, wxT("."));
    wxButton *numPadEnterBtn = new wxButton(loginPanel, 412, wxT("Enter"));
    wxButton *numPadBkSpBtn = new wxButton(loginPanel, 413, wxT("BackSpace"));
    wxButton *numPadClearBtn = new wxButton(loginPanel, 414, wxT("Clear"));

    NumPadNumRow1->Add(numPad7Btn, numPadNumBtnFlags);
    NumPadNumRow1->Add(numPad8Btn, numPadNumBtnFlags);
    NumPadNumRow1->Add(numPad9Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad4Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad5Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad6Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad1Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad2Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad3Btn, numPadNumBtnFlags);
    NumPadNumRow4->Add(numPad0Btn, wxSizerFlags(3).Expand().Border(wxALL, 2));
    NumPadNumRow4->Add(numPadDotBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    loginNumPadV1Sizer->Add(NumPadNumRow1, numPadRowFlags);
    loginNumPadV1Sizer->Add(NumPadNumRow2, numPadRowFlags);
    loginNumPadV1Sizer->Add(NumPadNumRow3, numPadRowFlags);
    loginNumPadV1Sizer->Add(NumPadNumRow4, numPadRowFlags);

    loginNumPadV2Sizer->Add(numPadBkSpBtn, numPadNumBtnFlags);
    loginNumPadV2Sizer->Add(numPadClearBtn, numPadNumBtnFlags);
    loginNumPadV2Sizer->Add(numPadEnterBtn, numPadNumBtnFlags);

    loginNumPadHSizer->Add(loginNumPadV1Sizer, wxSizerFlags(2).Expand().Border(wxALL, 2));
    loginNumPadHSizer->Add(loginNumPadV2Sizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    loginNumPadSizer->Add(loginNumPadHSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));

    quitBtn->Bind(wxEVT_BUTTON, &loginDialog::OnClose, this);

    mainHSizer->Add(loginFieldVSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    mainHSizer->Add(loginNumPadSizer, wxSizerFlags(1).Expand().Border(wxALL, 8));
    mainVSizer->Add(mainHSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));

    loginPanel->SetSizer(mainVSizer);

    loginPanel->Bind(wxEVT_BUTTON, &loginDialog::enterKeyPad, this);

    Centre();
    ShowModal();
}

void loginDialog::OnClose(wxCommandEvent &event)
{
    EndModal(wxCANCEL);
    event.Skip();
}

void loginDialog::OnLogIn(wxCommandEvent &event)
{
    if (!loginUserBox->IsEmpty() && !loginPassBox->IsEmpty())
        EndModal(wxOK);
    event.Skip();
}

void loginDialog::enterKeyPad(wxCommandEvent &event)
{
    int key = event.GetId();
    switch(key)
    {
        case 401:
            if (enteringUser)
                loginUserBox->AppendText("1");
            else
                loginPassBox->AppendText("1");
            break;
        case 402:
            if (enteringUser)
                loginUserBox->AppendText("2");
            else
                loginPassBox->AppendText("2");
            break;
        case 403:
            if (enteringUser)
                loginUserBox->AppendText("3");
            else
                loginPassBox->AppendText("3");
            break;
        case 404:
            if (enteringUser)
                loginUserBox->AppendText("4");
            else
                loginPassBox->AppendText("4");
            break;
        case 405:
            if (enteringUser)
                loginUserBox->AppendText("5");
            else
                loginPassBox->AppendText("5");
            break;
        case 406:
            if (enteringUser)
                loginUserBox->AppendText("6");
            else
                loginPassBox->AppendText("6");
            break;
        case 407:
            if (enteringUser)
                loginUserBox->AppendText("7");
            else
                loginPassBox->AppendText("7");
            break;
        case 408:
            if (enteringUser)
                loginUserBox->AppendText("8");
            else
                loginPassBox->AppendText("8");
            break;
        case 409:
            if (enteringUser)
                loginUserBox->AppendText("9");
            else
                loginPassBox->AppendText("9");
            break;
        case 410:
            if (enteringUser)
                loginUserBox->AppendText("0");
            else
                loginPassBox->AppendText("0");
            break;
        case 411:
            if (enteringUser)
                loginUserBox->AppendText(".");
            else
                loginPassBox->AppendText(".");
            break;
        case 413:
            if (enteringUser)
                loginUserBox->Remove(loginUserBox->GetLineLength(0) -1, loginUserBox->GetLineLength(0));
            else
                loginPassBox->Remove(loginPassBox->GetLineLength(0) -1, loginPassBox->GetLineLength(0));
            break;
        case 414:
            if (enteringUser)
                loginUserBox->Clear();
            else
                loginPassBox->Clear();
            break;
        case 412:
            if (enteringUser)
                enteringUser = false;
            else
                OnLogIn(event);
            break;
        default: 
            break;
    }

    event.Skip();
}