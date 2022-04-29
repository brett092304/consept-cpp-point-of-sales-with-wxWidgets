#include "lkupitemDialog.h"
#include "connection.h"

LkUpItemDialog::LkUpItemDialog(const wxString &title, wxString skuwx) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    wxSize screenSize = wxGetDisplaySize() * 3/4;
    this->SetSize(screenSize);

    LkUpItemPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *LkUpItemVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *LkUpItemHSizer = new wxBoxSizer(wxHORIZONTAL);

    //get connection for item

    //data table for items
    dataTable = new wxGrid(LkUpItemPanel, wxID_ANY);
    wxBoxSizer *tableSizer = new wxBoxSizer(wxVERTICAL);

    dataTable->CreateGrid(1, 6);
    dataTable->SetDefaultRowSize(40);
    dataTable->EnableEditing(false);
    dataTable->SetColLabelValue(0, "Sku");
    dataTable->SetColLabelValue(1, "Upc");
    dataTable->SetColLabelValue(2, "Qty");
    dataTable->SetColLabelValue(3, "Description");
    dataTable->SetColLabelValue(4, "Regular Price");
    dataTable->SetColLabelValue(5, "Sale Price");
    dataTable->DeleteRows(0, 1);
    wxFont tableFont = wxFont(wxFontInfo(18));

    std::string sku = skuwx.ToStdString();
    std::vector<std::vector<std::string>> data = CreateConnection::lkUpConn(sku);

    for (int k = 0; k < data.at(0).size(); k++)
    {
        dataTable->AppendRows(1);
    
        for (int j = 0; j < data.size(); j++)
        {
            //std::cout << data.at(j).at(k) << std::endl;
            dataTable->SetCellValue(k, j, data.at(j).at(k));
            dataTable->SetCellFont(k, j, tableFont);
            dataTable->SetCellAlignment(k, j, wxCenter, wxCenter);
        }
    }

    wxButton *closeBtn = new wxButton(LkUpItemPanel, wxID_ANY, wxT("Close/Exit"));
    closeBtn->Bind(wxEVT_BUTTON, &LkUpItemDialog::BtnClose, this);

    tableSizer->Add(dataTable, wxSizerFlags(1).Expand().Border(wxALL, 0));
    LkUpItemHSizer->Add(tableSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    LkUpItemVSizer->Add(LkUpItemHSizer, wxSizerFlags(10).Expand().Border(wxALL, 2));
    LkUpItemVSizer->Add(closeBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    this->Bind(wxEVT_CHAR_HOOK, &LkUpItemDialog::OnClose, this);
    LkUpItemPanel->Bind(wxEVT_SIZE, &LkUpItemDialog::dataTableSize, this);

    LkUpItemPanel->SetSizer(LkUpItemVSizer);

    Centre();
    ShowModal();
}

void LkUpItemDialog::dataTableSize(wxSizeEvent &event)
{
    float gridWidth = (LkUpItemPanel->GetSize().x);
    dataTable->SetColSize(0, gridWidth * 1/7);
    dataTable->SetColSize(1, gridWidth * 1/7);
    dataTable->SetColSize(2, gridWidth * 1/12);
    dataTable->SetColSize(3, gridWidth * 2/7);
    dataTable->SetColSize(4, gridWidth * 1/7);
    dataTable->SetColSize(5, gridWidth * 1/7);
    event.Skip();
}

void LkUpItemDialog::OnClose(wxKeyEvent &event)
{
    if (event.GetUnicodeKey() == WXK_ESCAPE)
    {
        this->Destroy();
    }
    event.Skip();
}

void LkUpItemDialog::BtnClose(wxCommandEvent &event)
{
    this->Destroy();
    event.Skip();
}