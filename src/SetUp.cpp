#include "SetUp.h"
#include <iostream>
#include <fstream>
#include <wx/display.h>

SetUp::SetUp(const wxString& title) :  wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(1, 1))
{
    wxDisplay display;
    wxRect screenSize = display.GetClientArea();
    this->SetSize(screenSize);

    wxPanel *setUpPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxBoxSizer *mainVSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *pathHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *userHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *passHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *userDBPathHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *userDBUserHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *userDBPassHSizer = new wxBoxSizer(wxHORIZONTAL);

    wxFont setUpFont = wxFont(wxFontInfo(16));
    wxStaticText *pathLabel = new wxStaticText(setUpPanel, wxID_ANY, wxT("Database Server Path: "));
    pathLabel->SetFont(setUpFont);

    pathBox = new wxTextCtrl(setUpPanel, wxID_ANY, wxT("IpAddress:port/table"));
    pathBox->SetFont(setUpFont);

    wxStaticText *userLabel = new wxStaticText(setUpPanel, wxID_ANY, wxT("Database Username: "));
    userLabel->SetFont(setUpFont);

    userBox = new wxTextCtrl(setUpPanel, wxID_ANY);
    userBox->SetFont(setUpFont);

    wxStaticText *passLabel = new wxStaticText(setUpPanel, wxID_ANY, wxT("Database Password: "));
    passLabel->SetFont(setUpFont);

    passBox = new wxTextCtrl(setUpPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passBox->SetFont(setUpFont);

    wxStaticText *userPathText = new wxStaticText(setUpPanel, wxID_ANY, wxT("User Database Server Path: "));
    userPathText->SetFont(setUpFont);

    userPathBox = new wxTextCtrl(setUpPanel, wxID_ANY, wxT("IpAddress:port/table"));
    userPathBox->SetFont(setUpFont);

    wxStaticText *userDBUserText = new wxStaticText(setUpPanel, wxID_ANY, wxT("User Database Username: "));
    userDBUserText->SetFont(setUpFont);

    userDBUserBox = new wxTextCtrl(setUpPanel, wxID_ANY);
    userDBUserBox->SetFont(setUpFont);

    wxStaticText *userPassText = new wxStaticText(setUpPanel, wxID_ANY, wxT("User Database Password: "));
    userPassText->SetFont(setUpFont);

    userPassBox = new wxTextCtrl(setUpPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    userPassBox->SetFont(setUpFont);

    wxButton *setUpBtn = new wxButton(setUpPanel, wxID_ANY, wxT("SetUp"));
    setUpBtn->SetFont(setUpFont);

    wxSizerFlags labelFlags = wxSizerFlags(0).Border(wxALL, 6);
    wxSizerFlags boxFlags = wxSizerFlags(1).Expand().Border(wxALL, 2);
    pathHSizer->Add(pathLabel, labelFlags);
    pathHSizer->Add(pathBox, boxFlags);

    userHSizer->Add(userLabel, labelFlags);
    userHSizer->Add(userBox, boxFlags);

    passHSizer->Add(passLabel, labelFlags);
    passHSizer->Add(passBox, boxFlags);

    userDBPathHSizer->Add(userPathText, labelFlags);
    userDBPathHSizer->Add(userPathBox, boxFlags);

    userDBUserHSizer->Add(userDBUserText, labelFlags);
    userDBUserHSizer->Add(userDBUserBox, boxFlags);

    userDBPassHSizer->Add(userPassText, labelFlags);
    userDBPassHSizer->Add(userPassBox, boxFlags);

    mainVSizer->Add(pathHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(userHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(passHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(userDBPathHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(userDBUserHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(userDBPassHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    mainVSizer->Add(setUpBtn, wxSizerFlags(0).Center().Border(wxALL, 4));

    setUpPanel->Bind(wxEVT_BUTTON, &SetUp::createFile, this);



    setUpPanel->SetSizer(mainVSizer);
}

void SetUp::createFile(wxCommandEvent &event)
{
    std::ofstream outfile ("MysqlConnection.txt");

    outfile << pathBox->GetLineText(0) << std::endl;
    outfile << userBox->GetLineText(0) << std::endl;
    outfile << passBox->GetLineText(0) << std::endl;
    outfile << userPathBox->GetLineText(0) << std::endl;
    outfile << userDBUserBox->GetLineText(0) << std::endl;
    outfile << userPassBox->GetLineText(0) << std::endl;

    outfile.close();
    this->Close(true);
}