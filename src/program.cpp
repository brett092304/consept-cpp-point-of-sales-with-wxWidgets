#include "program.h"
#include "lkupitemDialog.h"
#include "sale.h"
#include "login.h"
#include "connection.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, 9099, title, wxPoint(-1, -1), wxSize(1, 1))
{
    wxDisplay display;
    wxRect size = display.GetClientArea();
    this->SetSize(size);

    menuBar = new wxMenuBar;
    file = new wxMenu;
    file->Append(ID_Logout, wxT("&Quit\tCtrl+Q"));

    menuBar->Append(file, wxT("&File"));
    SetMenuBar(menuBar);

    this->Bind(wxEVT_MENU, &MainFrame::MenuLgout, this);

    mainPanel = new wxPanel(this, 50, wxDefaultPosition, wxDefaultSize);
    wxBoxSizer *mainVSizer = new wxBoxSizer(wxVERTICAL);

    //sku sizers and elements
    wxBoxSizer *elementsHSizer = new wxBoxSizer(wxHORIZONTAL);
    elementsVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *skuHSizer = new wxBoxSizer(wxHORIZONTAL);

    wxFont skuFont = wxFont(wxFontInfo(12));
    UPCorPLUText = new wxStaticText(mainPanel, wxID_ANY, wxT("Sku or Upc: "));
    UPCorPLUText->SetFont(skuFont);
    skuHSizer->Add(UPCorPLUText, wxSizerFlags(0).Top().Border(wxALL, 4));
    UPCorPLUBox = new wxTextCtrl(mainPanel, wxID_ANY);
    UPCorPLUBox->SetFont(skuFont);
    UPCorPLUBox->SetFont(skuFont);
    skuHSizer->Add(UPCorPLUBox, wxSizerFlags(1).Top().Border(wxALL, 4));

    //logged in person **above sku boxes**
    loggedInHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loggedInV1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *loggedInV2Sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *loggedInH1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loggedInH101Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loggedInH2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loggedInH201Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *loggedInH103Sizer = new wxBoxSizer(wxHORIZONTAL);

    personLoggedIn = new wxStaticText(mainPanel, wxID_ANY, wxT(""));
    numbersLoggedIn = new wxStaticText(mainPanel, wxID_ANY, wxT(""));
    isManagerText = new wxStaticText(mainPanel, wxID_ANY, wxT("Manager"));
    transactionPersonText = new wxStaticText(mainPanel, wxID_ANY, wxT("Portage - Customer"));
    wxStaticText *transactionPersonLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Customer: "));
    wxStaticText *loggedInLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Cashier: "));
    wxStaticText *numbersLoggedInLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Name: "));

    loggedInH1Sizer->Add(loggedInLabel, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInH1Sizer->Add(numbersLoggedIn, wxSizerFlags(0).Expand().Border(wxALL, 2));

    loggedInH101Sizer->Add(numbersLoggedInLabel, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInH101Sizer->Add(personLoggedIn, wxSizerFlags(0).Expand().Border(wxALL, 2));

    loggedInH103Sizer->Add(transactionPersonLabel, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInH103Sizer->Add(transactionPersonText, wxSizerFlags(0).Expand().Border(wxALL, 2));

    loggedInH2Sizer->Add(isManagerText, wxSizerFlags(0).Expand().Border(wxALL, 2));
    isManagerText->Show(false);

    loggedInV1Sizer->Add(loggedInH1Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInV1Sizer->Add(loggedInH101Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInV1Sizer->Add(loggedInH103Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));

    loggedInV2Sizer->Add(loggedInH2Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInV2Sizer->Add(loggedInH201Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));

    loggedInHSizer->Add(loggedInV1Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));
    loggedInHSizer->Add(loggedInV2Sizer, wxSizerFlags(0).Expand().Border(wxALL, 2));

    //NumPad virtual Btns
    wxSizerFlags numPadNumBtnFlags = wxSizerFlags(1).Expand().Border(wxALL, 2);
    wxSizerFlags numPadMnuBtnFlags = wxSizerFlags(1).Expand().Border(wxALL, 2);
    wxSizerFlags numPadRowFlags = wxSizerFlags(1).Expand().Top().Border(wxALL, 2);
    wxSizerFlags menuPanelSizerFlags = wxSizerFlags(1).Expand().Border(wxALL, 4);

    virtNumPadSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *virtNumPadV1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *virtNumPadV2Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *virtNumPadV3Sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *NumPadNumRow1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadMnuRow1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadMnuRow2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadMnuRow3 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *numPad1Btn = new wxButton(mainPanel, 5001, wxT("1"));
    wxButton *numPad2Btn = new wxButton(mainPanel, 5002, wxT("2"));
    wxButton *numPad3Btn = new wxButton(mainPanel, 5003, wxT("3"));
    wxButton *numPad4Btn = new wxButton(mainPanel, 5004, wxT("4"));
    wxButton *numPad5Btn = new wxButton(mainPanel, 5005, wxT("5"));
    wxButton *numPad6Btn = new wxButton(mainPanel, 5006, wxT("6"));
    wxButton *numPad7Btn = new wxButton(mainPanel, 5007, wxT("7"));
    wxButton *numPad8Btn = new wxButton(mainPanel, 5008, wxT("8"));
    wxButton *numPad9Btn = new wxButton(mainPanel, 5009, wxT("9"));
    wxButton *numPad0Btn = new wxButton(mainPanel, 5000, wxT("0"));
    wxButton *numPadDotBtn = new wxButton(mainPanel, 5020, wxT("."));
    
    wxButton *numPadBkSp = new wxButton(mainPanel, 5011, wxT("BackSpace"));
    wxButton *numPadSku = new wxButton(mainPanel, 5024, wxT("Sku/Plu"));
    wxButton *numPadEnter = new wxButton(mainPanel, 5010, wxT("Enter"));
    wxButton *numPadSbTtl = new wxButton(mainPanel, 5014, wxT("SubTotal"));
    wxButton *numPadClear = new wxButton(mainPanel, 5012, wxT("Clear"));
    wxButton *numPadLkUpItem = new wxButton(mainPanel, 5015, wxT("Look-Up Item"));
    wxButton *numPadFxnMnu = new wxButton(mainPanel, 5016, wxT("Fxn Menu"));
    wxButton *numPadMngrMnu = new wxButton(mainPanel, 5017, wxT("Manager Menu"));
    wxButton *numPadMainMnu = new wxButton(mainPanel, 5023, wxT("Main Menu"));
    wxButton *numPadVoid = new wxButton(mainPanel, 5021, wxT("Void"));
    wxButton *numPadChngePrice = new wxButton(mainPanel, 5019, wxT("Change Price"));

    NumPadNumRow1->Add(numPad7Btn, numPadNumBtnFlags);
    NumPadNumRow1->Add(numPad8Btn, numPadNumBtnFlags);
    NumPadNumRow1->Add(numPad9Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad4Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad5Btn, numPadNumBtnFlags);
    NumPadNumRow2->Add(numPad6Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad1Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad2Btn, numPadNumBtnFlags);
    NumPadNumRow3->Add(numPad3Btn, numPadNumBtnFlags);
    NumPadNumRow4->Add(numPad0Btn, wxSizerFlags(2).Expand().Border(wxALL, 2));
    NumPadNumRow4->Add(numPadDotBtn, wxSizerFlags(1).Expand().Border(wxALL, 2));

    NumPadMnuRow1->Add(numPadMainMnu, numPadMnuBtnFlags);
    NumPadMnuRow1->Add(numPadChngePrice, numPadMnuBtnFlags);
    NumPadMnuRow1->Add(numPadClear, numPadMnuBtnFlags);
    NumPadMnuRow2->Add(numPadFxnMnu, numPadMnuBtnFlags);
    NumPadMnuRow2->Add(numPadVoid, numPadMnuBtnFlags);
    NumPadMnuRow2->Add(numPadBkSp, numPadMnuBtnFlags);
    NumPadMnuRow3->Add(numPadMngrMnu, numPadMnuBtnFlags);
    NumPadMnuRow3->Add(numPadLkUpItem, numPadMnuBtnFlags);

    virtNumPadV1Sizer->Add(NumPadMnuRow1, numPadRowFlags);
    virtNumPadV1Sizer->Add(NumPadMnuRow2, numPadRowFlags);
    virtNumPadV1Sizer->Add(NumPadMnuRow3, numPadRowFlags);

    virtNumPadV2Sizer->Add(NumPadNumRow1, numPadRowFlags);
    virtNumPadV2Sizer->Add(NumPadNumRow2, numPadRowFlags);
    virtNumPadV2Sizer->Add(NumPadNumRow3, numPadRowFlags);
    virtNumPadV2Sizer->Add(NumPadNumRow4, numPadRowFlags);

    virtNumPadV3Sizer->Add(numPadSku, wxSizerFlags(1).Expand().Border(wxALL, 1));
    virtNumPadV3Sizer->Add(numPadSbTtl, wxSizerFlags(1).Expand().Top().Border(wxALL, 1));
    virtNumPadV3Sizer->Add(numPadEnter, wxSizerFlags(1).Expand().Top().Border(wxALL, 1));

    virtNumPadSizer->Add(virtNumPadV1Sizer, wxSizerFlags(2).Expand().Top().Border(wxALL, 1));
    virtNumPadSizer->Add(virtNumPadV2Sizer, wxSizerFlags(2).Expand().Top().Border(wxALL, 1));
    virtNumPadSizer->Add(virtNumPadV3Sizer, wxSizerFlags(1).Expand().Top().Border(wxALL, 1));

    //function panel **flips with payment panel**
    functionVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *functionH1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *functionH2Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *functionChngeQtyBtn = new wxButton(mainPanel, 7003, wxT("Change Qty"));
    wxButton *functionSuspendBtn = new wxButton(mainPanel, 7001, wxT("Suspend"));
    wxButton *functionResumeBtn = new wxButton(mainPanel, 7002, wxT("Resume"));
    wxButton *functionNoSaleBtn = new wxButton(mainPanel, 7004, wxT("No Sale"));
    functionNoSaleBtn->Disable();
    wxButton *functionLogOutBtn = new wxButton(mainPanel, 7099, wxT("Logout"));

    functionH1Sizer->Add(functionSuspendBtn, menuPanelSizerFlags);
    functionH1Sizer->Add(functionNoSaleBtn, menuPanelSizerFlags);
    
    functionH2Sizer->Add(functionResumeBtn, menuPanelSizerFlags);
    functionH2Sizer->Add(functionChngeQtyBtn, menuPanelSizerFlags);
    functionH2Sizer->Add(functionLogOutBtn, menuPanelSizerFlags);

    functionVSizer->Add(functionH1Sizer, menuPanelSizerFlags);
    functionVSizer->Add(functionH2Sizer, menuPanelSizerFlags);

    //main menu panel **flips with function panel**
    mainMenuVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mainMenuHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *mainMenuV1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mainMenuV2Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mainMenuH1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *mainMenuH2Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *scanVoidBtn = new wxButton(mainPanel, 6001, wxT("Scan Void"));
    wxButton *receiptCopyBtn = new wxButton(mainPanel, 6006, wxT("Receipt Copy"));
    receiptCopyBtn->Disable();
    wxButton *venderCouponMenuBtn = new wxButton(mainPanel, 6002, wxT("Manufacture Coupon"));
    wxButton *storeCouponMenuBtn = new wxButton(mainPanel, 6003, wxT("Store Coupon"));
    wxBitmap uparrow;
    wxBitmap downarrow;
    uparrow.LoadFile("/home/brett/C++/src/uparrow.bmp", wxBITMAP_TYPE_BMP);
    downarrow.LoadFile("/home/brett/C++/src/downarrow.bmp", wxBITMAP_TYPE_BMP);

    wxBitmapButton *upListBtn = new wxBitmapButton(mainPanel, 6004, uparrow);
    wxBitmapButton *downListBtn = new wxBitmapButton(mainPanel, 6005, downarrow);

    mainMenuV2Sizer->Add(upListBtn, menuPanelSizerFlags);
    mainMenuV2Sizer->Add(downListBtn, menuPanelSizerFlags);

    mainMenuH1Sizer->Add(scanVoidBtn, menuPanelSizerFlags);
    mainMenuH1Sizer->Add(receiptCopyBtn, menuPanelSizerFlags);

    mainMenuH2Sizer->Add(storeCouponMenuBtn, menuPanelSizerFlags);
    mainMenuH2Sizer->Add(venderCouponMenuBtn, menuPanelSizerFlags);

    mainMenuV1Sizer->Add(mainMenuH1Sizer, menuPanelSizerFlags);
    mainMenuV1Sizer->Add(mainMenuH2Sizer, menuPanelSizerFlags);

    mainMenuHSizer->Add(mainMenuV1Sizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    mainMenuHSizer->Add(mainMenuV2Sizer, menuPanelSizerFlags);

    mainMenuVSizer->Add(mainMenuHSizer, menuPanelSizerFlags);

    //manager Menu **flips with mainMenu or function menu**
    managerMenuVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *managerMenuH1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *managerMenuH2Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *managerLogInBtn = new wxButton(mainPanel, 8001, wxT("Manager Login"));
    wxButton *managerRefundBtn = new wxButton(mainPanel, 8002, wxT("Refund"));
    wxButton *managerReturnBtn = new wxButton(mainPanel, 8003, wxT("Return"));

    managerMenuH1Sizer->Add(managerLogInBtn, menuPanelSizerFlags);
    managerMenuH1Sizer->Add(managerRefundBtn, menuPanelSizerFlags);

    managerMenuH2Sizer->Add(managerReturnBtn, menuPanelSizerFlags);

    managerMenuVSizer->Add(managerMenuH1Sizer, menuPanelSizerFlags);
    managerMenuVSizer->Add(managerMenuH2Sizer, menuPanelSizerFlags);


    //payment panel **this can flip between different panels**
    paymentVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *paymentHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *paymentV1Sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *paymentV2Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *paymentH1sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *paymentH2Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *CashPaymentBtn = new wxButton(mainPanel, 9001, wxT("Cash"));
    wxButton *CardPaymentBtn = new wxButton(mainPanel, 9002, wxT("Card  --  PinPad"));
    CardPaymentBtn->Disable();
    wxButton *ManualCardPaymentBtn = new wxButton(mainPanel, 9004, wxT("Manual Card"));
    wxButton *CheckPaymentBtn = new wxButton(mainPanel, 9003, wxT("Check"));
    CheckPaymentBtn->Disable();
    wxButton *ManualCheckPaymentBtn = new wxButton(mainPanel, 9004, wxT("Manual Check"));

    paymentHSizer->Add(paymentV1Sizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    paymentHSizer->Add(paymentV2Sizer, wxSizerFlags(1).Expand().Border(wxALL, 4));

    paymentV1Sizer->Add(paymentH1sizer, wxSizerFlags(1).Expand().Border(wxALL, 4));
    paymentV1Sizer->Add(paymentH2Sizer, wxSizerFlags(1).Expand().Border(wxALL, 4));

    paymentH1sizer->Add(CheckPaymentBtn, wxSizerFlags(1).Expand().Border(wxALL, 4));
    paymentH1sizer->Add(ManualCheckPaymentBtn, wxSizerFlags(1).Expand().Border(wxALL, 4));

    paymentH2Sizer->Add(ManualCardPaymentBtn, wxSizerFlags(1).Expand().Border(wxALL, 4));

    paymentV2Sizer->Add(CashPaymentBtn, wxSizerFlags(1).Expand().Border(wxALL, 4));
    paymentV2Sizer->Add(CardPaymentBtn, wxSizerFlags(1).Expand().Border(wxALL, 4));

    paymentVSizer->Add(paymentHSizer, wxSizerFlags(1).Expand().Border(wxALL, 4));


    //database table elements
    dataTableVSizer = new wxBoxSizer(wxVERTICAL);

    dataTable = new wxGrid(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);

    dataTable->CreateGrid(1, 6);
    dataTable->SetDefaultRowSize(50);
    dataTable->EnableEditing(false);
    dataTable->SetRowLabelSize(0);
    dataTable->SetColLabelValue(0, "Description");
    dataTable->SetColLabelValue(1, "Qty");
    dataTable->SetColLabelValue(2, "Price");
    dataTable->SetColLabelValue(3, "sku");
    dataTable->HideCol(3);
    dataTable->SetColLabelValue(4, "modified");
    dataTable->HideCol(4);
    dataTable->SetColLabelValue(5, "Code");
    dataTable->HideCol(5);
    dataTable->DeleteRows(0, 1, true);
    
    dataTableVSizer->Add(dataTable, wxSizerFlags(1).Expand().Top().Border(wxALL, 0));

    //money owed **total and subtotal**
    wxFont totalFont  = wxFont(wxFontInfo(14));
    wxBoxSizer *totalHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *finalTotalLabel = new wxStaticText(mainPanel, 2001, wxT("Total: $"));
    finalTotalDue = new wxStaticText(mainPanel, 5002, wxT("0.00"));
    finalTotalLabel->SetFont(totalFont);
    finalTotalDue->SetFont(totalFont);

    wxStaticText *totalSaleLabel = new wxStaticText(mainPanel, 5003, wxT("Total Sale: $"));
    totalSaleAmount = new wxStaticText(mainPanel, 5004, wxT("0.00"));
    totalSaleLabel->SetFont(totalFont);
    totalSaleAmount->SetFont(totalFont);

    wxStaticText *subTotalLabel = new wxStaticText(mainPanel, 5005, wxT("SubTotal: $"));
    subTotalAmount = new wxStaticText(mainPanel, 5006, wxT("0.00"));
    subTotalLabel->SetFont(totalFont);
    subTotalAmount->SetFont(totalFont);

    wxStaticText *taxTotalLabel = new wxStaticText(mainPanel, 5007, wxT("Tax: $"));
    taxTotalAmount = new wxStaticText(mainPanel, 5008, wxT("0.00"));
    taxTotalLabel->SetFont(totalFont);
    taxTotalAmount->SetFont(totalFont);

    wxBoxSizer *finalTotalHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *totalSaleHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *subTotalHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *taxTotalHSizer = new wxBoxSizer(wxHORIZONTAL);

    finalTotalHSizer->Add(finalTotalLabel, wxSizerFlags(0).Expand().Border(wxALL, 1));
    finalTotalHSizer->Add(finalTotalDue, wxSizerFlags(0).Expand().Border(wxALL, 1));

    totalSaleHSizer->Add(totalSaleLabel, wxSizerFlags(0).Expand().Border(wxALL, 1));
    totalSaleHSizer->Add(totalSaleAmount, wxSizerFlags(0).Expand().Border(wxALL, 1));

    subTotalHSizer->Add(subTotalLabel, wxSizerFlags(0).Expand().Border(wxALL, 1));
    subTotalHSizer->Add(subTotalAmount, wxSizerFlags(0).Expand().Border(wxALL, 1));

    taxTotalHSizer->Add(taxTotalLabel, wxSizerFlags(0).Expand().Border(wxALL, 1));
    taxTotalHSizer->Add(taxTotalAmount, wxSizerFlags(0).Expand().Border(wxALL, 1));

    totalHSizer->Add(subTotalHSizer, wxSizerFlags(1).Expand().Border(wxALL, 4));
    totalHSizer->Add(taxTotalHSizer, wxSizerFlags(1).Expand().Border(wxALL, 4));
    totalHSizer->Add(totalSaleHSizer, wxSizerFlags(1).Expand().Border(wxALL, 4));
    totalHSizer->Add(finalTotalHSizer, wxSizerFlags(1).Expand().Border(wxALL, 4));

    dataTableVSizer->Add(totalHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    
    //Add elements to mainsizer
    elementsHSizer->Add(dataTableVSizer, wxSizerFlags(1).Expand().Top().Border(wxALL, 4));
    elementsHSizer->Add(elementsVSizer, wxSizerFlags(1).Expand().Top().Border(wxALL, 4));
    elementsVSizer->Add(loggedInHSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
    elementsVSizer->Add(skuHSizer, wxSizerFlags(0).Expand().Top().Border(wxALL, 4));
    elementsVSizer->Add(virtNumPadSizer, wxSizerFlags(1).Expand().Top().Border(wxALL, 4));
    elementsVSizer->Add(mainMenuVSizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    elementsVSizer->Add(paymentVSizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    paymentVSizer->Show(false);
    elementsVSizer->Add(functionVSizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    functionVSizer->Show(false);
    elementsVSizer->Add(managerMenuVSizer, wxSizerFlags(2).Expand().Border(wxALL, 4));
    managerMenuVSizer->Show(false);
    
    mainVSizer->Add(elementsHSizer, wxSizerFlags(1).Expand().Top().Border(wxALL, 5));
    mainPanel->SetSizer(mainVSizer);

    mainPanel->Bind(wxEVT_BUTTON, &MainFrame::EnterNumPadNumber, this);
    Bind(wxEVT_SIZE, &MainFrame::GridSize, this);
    mainPanel->Bind(wxEVT_CHAR_HOOK, &MainFrame::keyPress, this);
    wxWindow::Layout();
    
    
    OnLogout(false);

    UPCorPLUBox->SetFocus();
}

void MainFrame::GridSize(wxSizeEvent &event)
{
    float gridWidth = (dataTable->GetSize().x - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
    dataTable->SetColSize(0, gridWidth * 5/8);
    dataTable->SetColSize(1, gridWidth * 1/8);
    dataTable->SetColSize(2, gridWidth * 2/8);
    event.Skip();
}

void MainFrame::cancelOperation()
{
    UPCorPLUText->SetLabel(wxT("Sku or Upc: "));
    UPCorPLUBox->Clear();
}

void MainFrame::OnLogout(bool loginManager)
{
    cancelOperation();
    loginDialog *loginFrame = new loginDialog(wxT("Login"), loginManager);
    loggedIn = false;
    isTempManager = false;
    isManagerText->Show(false);

    if (loginFrame->ShowModal() == wxOK)
    {
        loginFrame->Destroy();
        loggedIn = true;
        if (loginManager)
        {
            isTempManager = true;
            isManagerText->Show(true);
            std::cout << isTempManager << std::endl;
        }
        loggedInHSizer->Layout();
    }
    else
    {
        loginFrame->Destroy();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->Close(true);
    }
}

void MainFrame::LkUpItem()
{
    LkUpItemDialog *LkUpFrame = new LkUpItemDialog(wxT("Look-Up Item"), UPCorPLUBox->GetLineText(0));
    LkUpFrame->Show(true);
}

void MainFrame::getCash()
{
    gettingCash = true;
    if (UPCorPLUBox->GetLineText(0) != "")
    {
        reciveCash();
    }
    else
    {
        UPCorPLUText->SetLabel(wxT("Cash: $"));
    }
}

void MainFrame::reciveCash()
{
    if (UPCorPLUBox->GetLineText(0) != "")
    {
        sale sale;
        //sale.getTotal(std::string(finalTotalDue->GetLabelText().mb_str()));
        sale.getCashAmount(std::string(UPCorPLUBox->GetLineText(0).mb_str()));
        UPCorPLUText->SetLabel(wxT("Sku or Upc: "));
        UPCorPLUBox->Clear();
        gettingCash = false;
    }
    else
    {
        UPCorPLUBox->SetFocus();
    }
}

void MainFrame::scanDelete()
{
    sale sale;
    wxString skuToRemove = UPCorPLUBox->GetLineText(0);
    std::string sku = std::string(skuToRemove.mb_str());
    std::cout << sku << std::endl;
    deleteItem(sale.scanRemoveItem(sku));
    scanDeleteItem = false;
}

void MainFrame::addItem()
{
    wxString itemStr = UPCorPLUBox->GetLineText(0);
    UPCorPLUBox->Clear();
    //std::cout << itemStr << std::endl;
    UPCorPLUText->SetLabelText(wxT("Quantity: "));
    itemToAdd = wxAtoi(itemStr);
    //std::cout << itemToAddStr << std::endl;
    gettingItem = true;
}

void MainFrame::addQty()
{
    sale sale;
    wxString qtyStr = UPCorPLUBox->GetLineText(0);
    cancelOperation();
    int qty = wxAtoi(qtyStr);
    std::vector<std::string> connectionData = CreateConnection::connection(std::to_string(itemToAdd));
    if (connectionData.size() >= 1)
    {
        std::vector<std::string> data;
        for (auto it = connectionData.begin(); it != connectionData.end(); it++)
        {
            data.push_back(*it);
        }

        std::string sku = data.at(0);
        std::string desc = data.at(2);
        std::string regPriceStr = data.at(3);
        std::string salePriceStr = data.at(4);

        double regularprice = std::stod(regPriceStr);
        double saleprice = std::stod(salePriceStr);

        
        double priceToAdd;
        if (saleprice < regularprice)
        {
            priceToAdd = saleprice;
        }
        else
        {
            priceToAdd = regularprice;
        }

        sale.addItem(itemToAdd, qty, priceToAdd);
        updateTable(desc, std::to_string(qty), priceToAdd, sku);
    }
    else
    {
        Error("Item NOT Found Error");
    }
    gettingItem = false;

}

void MainFrame::updateTable(std::string desc, std::string qty, double price, std::string sku)
{
    double visualPriceD = std::stod(qty) * price;
    std::string visualPriceValue = std::to_string((visualPriceD * 100) / 100);

    std::string tableRow[6] = {desc, qty, visualPriceValue, sku, "0", "0"};
    dataTable->AppendRows(1);
    int rowCount = dataTable->GetNumberRows() - 1;
    tablePos = rowCount;
    int colCount = dataTable->GetNumberCols();
    wxFont tableFont = wxFont(wxFontInfo(18));
    for (int i = 0; i < colCount; i++)
    {
        dataTable->SetCellValue(rowCount, i, tableRow[i]);
        dataTable->SetCellFont(rowCount, i, tableFont);
        dataTable->SetCellAlignment(rowCount, i, wxCenter, wxCenter);
    }
    dataTable->SelectRow(tablePos);
}

void MainFrame::deleteItem(int pos)
{
    sale sale;
    if (pos > -1)
    {
        sale.removeItem(pos);
        tablePos--;
        dataTable->DeleteRows(pos, 1);
    }
    else
    {
        Error("Item Not Found In List");
    }
}

void MainFrame::MenuLgout(wxCommandEvent &event)
{
    this->Close(true);
    event.Skip();
}

void MainFrame::keyPress(wxKeyEvent &event)
{
    wxChar key = event.GetUnicodeKey();
    if (key != WXK_NONE)
    {
        switch (key)
        {
            case WXK_ESCAPE:
                break;
            default:
                break;
        }
    }
    event.Skip();
}

void MainFrame::Error(std::string errorMessage)
{
    wxMessageDialog dlg(NULL, errorMessage, wxT("Error"), wxOK | wxCENTER, wxDefaultPosition);
    dlg.ShowModal();
}