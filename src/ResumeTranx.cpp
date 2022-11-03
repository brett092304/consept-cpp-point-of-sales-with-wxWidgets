#include "ResumeTranx.h"
#include "connection.h"
#include "program.h"
#include "main.h"

ResumeTranx::ResumeTranx(const wxString &title, int* receiptCode) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    wxSize screenSize = wxGetDisplaySize() * 7/8;
    this->SetSize(screenSize);
    receiptNumber = receiptCode;

    resumePanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *resumeVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *resumeHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *tableSizer = new wxBoxSizer(wxVERTICAL);

    table = new wxGrid(resumePanel, wxID_ANY);
    table->CreateGrid(1, 1);
    table->SetDefaultRowSize(40);
    table->SetDefaultColSize(100);
    table->EnableEditing(false);
    table->DeleteRows(0, 1);
    //table->DeleteCols(0, 1);
    wxFont tableFont = wxFont(wxFontInfo(18));
    try
    {
    std::vector<std::vector<std::string>> rawData = CreateConnection::resumeTranxView();

    std::vector<std::vector<std::string>> data;
    std::vector<std::string> tempData;

    for (int i = 0; i < rawData.at(0).size(); i++)
    {
        for (int j = 0; j < rawData.size(); j++)
        {
            tempData.push_back(rawData.at(j).at(i));
        }
        std::reverse(tempData.begin(), tempData.end());
        data.push_back(tempData);
        tempData.clear();
    }

    std::vector<std::string> receiptNums;
    for (auto iter = data.begin(); iter != data.end(); iter++)
    {
        receiptNums.push_back(iter->at(0));
    }

    if (receiptNums.size() > 0)
    {
        std::sort(receiptNums.begin(), receiptNums.end());
        receiptNums.erase(std::unique(receiptNums.begin(), receiptNums.end()));
    }

    std::vector<std::vector<std::string>> dataToUse;
    tempData.clear();
    for (int i = 0; i < receiptNums.size(); i++)
    {
        tempData.push_back(receiptNums.at(i));
        for (int j = 0; j < data.size(); j++)
        {
            if (data.at(j).at(0) == receiptNums.at(i))
            {
                tempData.push_back(data.at(j).at(1));
            }
        }
        dataToUse.push_back(tempData);
        tempData.clear();
    }

    if (MainFrame::isDebug)
    {
        for (int i = 0; i < dataToUse.size(); i++)
        {
            for (int j = 0; j < dataToUse.at(i).size(); j++)
            {
                std::cout << dataToUse.at(i).at(j) << std::endl;
            }
            std::cout << "\n";
        }
    }

    table->AppendRows(dataToUse.size());
    int numCols = 1;
    for (int i = 0; i < dataToUse.size(); i++)
    {
        if (dataToUse.at(i).size() > numCols)
            numCols = dataToUse.at(i).size();
    }
    table->AppendCols(numCols);

    for (int i = 0; i < dataToUse.size(); i++)
    {
        for (int j = 0; j < dataToUse.at(i).size(); j++)
        {

            table->SetCellValue(i, j, dataToUse.at(i).at(j));
            table->SetCellFont(i, j, tableFont);
            table->SetCellAlignment(i, j, wxCenter, wxCenter);
        }
    }
    } 
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    wxBoxSizer *controlSizer = new wxBoxSizer(wxVERTICAL);

    wxButton *resumeTranxBtn = new wxButton(resumePanel, 801, wxT("Resume Transaction"));
    resumeTranxBtn->SetFont(wxFontInfo(18));
    wxBitmap resumeUp;
    wxBitmap resumeDown;
    resumeUp.LoadFile(MyApp::getPath() + "icons/uparrow.bmp", wxBITMAP_TYPE_BMP);
    resumeDown.LoadFile(MyApp::getPath() + "icons/downarrow.bmp", wxBITMAP_TYPE_BMP);

    wxBitmapButton *resumeUpBtn = new wxBitmapButton(resumePanel, 802, resumeUp);
    wxBitmapButton *resumeDownBtn = new wxBitmapButton(resumePanel, 803, resumeDown);

    controlSizer->Add(resumeUpBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));
    controlSizer->Add(resumeDownBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));
    controlSizer->Add(resumeTranxBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    wxButton *closeBtn = new wxButton(resumePanel, 800, wxT("Close"));
    closeBtn->Bind(wxEVT_BUTTON, &ResumeTranx::close, this);

    tableSizer->Add(table, wxSizerFlags(1).Expand().Border(wxALL, 0));
    resumeHSizer->Add(controlSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    resumeHSizer->Add(tableSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    resumeVSizer->Add(resumeHSizer, wxSizerFlags(10).Expand().Border(wxALL, 2));
    resumeVSizer->Add(closeBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    resumePanel->Bind(wxEVT_BUTTON, &ResumeTranx::buttonControls, this);
    Bind(wxEVT_SIZE, &ResumeTranx::resizeTable, this);
    resumePanel->SetSizer(resumeVSizer);


    Centre();
    ShowModal();
}

void ResumeTranx::resizeTable(wxSizeEvent &event)
{
    float gridWidth = (resumePanel->GetSize().x);
    int numCols = table->GetNumberCols();
    for (int i = 0; i < numCols; i++)
    {
        table->SetColSize(i, 400);
    }
    event.Skip();
}

void ResumeTranx::close(wxCommandEvent &event)
{
    this->Destroy();
    event.Skip();
}

void ResumeTranx::getReceipt()
{
    try
    {
        if (table->GetCellValue(tablePos, 0) != "")
        {
            int receipt = std::stoi(table->GetCellValue(tablePos, 0).ToStdString());
            *receiptNumber = receipt;
        }
    }
    catch(const std::exception& e)
    {
        if (MainFrame::isDebug)
        {
            std::cout << e.what() << '\n';
        }
    }
    
}

void ResumeTranx::buttonControls(wxCommandEvent &event)
{
    int key = event.GetId();
    switch(key)
    {
        case 800: //close btn
            close(event);
            break;

        case 801: //resume Tranx / enter key
            getReceipt();
            close(event);
            break;

        case 802: //uparrow
            tablePos --;
            if (tablePos >= 0)
            {
                table->SelectRow(tablePos);
            }
            else
            {
                table->SelectRow(0);
                tablePos = 0;
            }
            break;
        
        case 803: //downarrow
            tablePos++;
            if (tablePos <= table->GetNumberRows() - 1)
            {
                table->SelectRow(tablePos);
            }
            else
            {
                table->SelectRow(table->GetNumberRows() - 1);
                tablePos = table->GetNumberRows() - 1;
            }
            break;

        default:
            break;
    }
    event.Skip();
}