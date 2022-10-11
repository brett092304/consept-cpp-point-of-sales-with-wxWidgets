#include "ResumeTranx.h"
#include "connection.h"
#include "program.h"

ResumeTranx::ResumeTranx(const wxString &title) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    wxSize screenSize = wxGetDisplaySize() * 7/8;
    this->SetSize(screenSize);

    wxPanel *resumePanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *resumeVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *resumeHSizer = new wxBoxSizer(wxHORIZONTAL);

    table = new wxGrid(resumePanel, wxID_ANY);





    wxButton *closeBtn = new wxButton(resumePanel, wxID_ANY, wxT("Close"));
    closeBtn->Bind(wxEVT_BUTTON, &ResumeTranx::close, this);

    resumeVSizer->Add(resumeHSizer, wxSizerFlags(10).Expand().Border(wxALL, 2));
    resumeVSizer->Add(closeBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    resumePanel->SetSizer(resumeVSizer);

    Centre();
    ShowModal();
}

void ResumeTranx::close(wxCommandEvent &event)
{
    this->Destroy();
    event.Skip();
}