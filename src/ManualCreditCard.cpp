#include "ManualCreditCard.h"
#include "program.h"
#include "sale.h"

ManualCreditCard::ManualCreditCard(const wxString &title, double amountDue, double *paymentAmount) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    wxSize screenSize = wxGetDisplaySize() * 2/4;
    this->SetSize(screenSize);

    amount = amountDue;
    payAmount = paymentAmount;

    wxPanel *MCCPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *mainVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mainHSizer = new wxBoxSizer(wxHORIZONTAL);

    //card info
    wxBoxSizer *MCCVSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *MCCAmountHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MCCNumberHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MCCExpireYearHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MCCExpireMonthHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MCCValidateHSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags cardInfoLabels = wxSizerFlags(0).Expand().Border(wxALL, 2);
    wxSizerFlags cardInfoBoxs = wxSizerFlags(1).Expand().Border(wxALL, 2);
    wxFont cardInfoFont = wxFontInfo(16);

    wxStaticText *totalDueLabel = new wxStaticText(MCCPanel, wxID_ANY, "Total Due: $" + sale::formatStringd(amountDue));
    totalDueLabel->SetFont(cardInfoFont);

    wxStaticText *cardAmountLabel = new wxStaticText(MCCPanel, wxID_ANY, wxT("Amount to Pay: "));
    cardAmountLabel->SetFont(cardInfoFont);
    cardAmountBox = new wxTextCtrl(MCCPanel, 921);
    cardAmountBox->SetFont(cardInfoFont);

    wxStaticText *cardNumLabel = new wxStaticText(MCCPanel, wxID_ANY, wxT("Card Number: "));
    cardNumLabel->SetFont(cardInfoFont);
    cardNumBox = new wxTextCtrl(MCCPanel, 922);
    cardNumBox->SetFont(cardInfoFont);

    wxStaticText *cardExpireYearLabel = new wxStaticText(MCCPanel, wxID_ANY, wxT("Expiring Year: "));
    cardExpireYearLabel->SetFont(cardInfoFont);
    cardExpireYearBox = new wxTextCtrl(MCCPanel, 923);
    cardExpireYearBox->SetFont(cardInfoFont);

    wxStaticText *cardExpireMonthLabel = new wxStaticText(MCCPanel, wxID_ANY, wxT("Expiring Month: "));
    cardExpireMonthLabel->SetFont(cardInfoFont);
    cardExpireMonthBox = new wxTextCtrl(MCCPanel, 924);
    cardExpireMonthBox->SetFont(cardInfoFont);

    wxStaticText *cardValidationLabel = new wxStaticText(MCCPanel, wxID_ANY, wxT("Validation Code: "));
    cardValidationLabel->SetFont(cardInfoFont);
    cardValidationBox = new wxTextCtrl(MCCPanel, 925);
    cardValidationBox->SetFont(cardInfoFont);

    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());
    MCCVSizer->Add(totalDueLabel, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());

    MCCAmountHSizer->Add(cardAmountLabel, cardInfoLabels);
    MCCAmountHSizer->Add(cardAmountBox, cardInfoBoxs);

    MCCNumberHSizer->Add(cardNumLabel, cardInfoLabels);
    MCCNumberHSizer->Add(cardNumBox, cardInfoBoxs);

    MCCExpireYearHSizer->Add(cardExpireYearLabel, cardInfoLabels);
    MCCExpireYearHSizer->Add(cardExpireYearBox, cardInfoBoxs);

    MCCExpireMonthHSizer->Add(cardExpireMonthLabel, cardInfoLabels);
    MCCExpireMonthHSizer->Add(cardExpireMonthBox, cardInfoBoxs);

    MCCValidateHSizer->Add(cardValidationLabel, cardInfoLabels);
    MCCValidateHSizer->Add(cardValidationBox, cardInfoBoxs);

    MCCVSizer->Add(MCCAmountHSizer, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());
    MCCVSizer->Add(MCCNumberHSizer, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());
    MCCVSizer->Add(MCCExpireYearHSizer, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());
    MCCVSizer->Add(MCCExpireMonthHSizer, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());
    MCCVSizer->Add(MCCValidateHSizer, cardInfoLabels);
    MCCVSizer->Add(1, 1, wxSizerFlags(1).Expand());


    //numpad
    wxBoxSizer *MCCPadSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *MCCPadHSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MCCPadV1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *MCCPadV2Sizer = new wxBoxSizer(wxVERTICAL);
    wxSizerFlags numPadNumBtnFlags = wxSizerFlags(1).Expand().Border(wxALL, 2);
    wxSizerFlags numPadRowFlags = wxSizerFlags(1).Expand().Top().Border(wxALL, 2);

    wxBoxSizer *NumPadNumRow1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *NumPadNumRow4 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *numPad1Btn = new wxButton(MCCPanel, 901, wxT("1"));
    wxButton *numPad2Btn = new wxButton(MCCPanel, 902, wxT("2"));
    wxButton *numPad3Btn = new wxButton(MCCPanel, 903, wxT("3"));
    wxButton *numPad4Btn = new wxButton(MCCPanel, 904, wxT("4"));
    wxButton *numPad5Btn = new wxButton(MCCPanel, 905, wxT("5"));
    wxButton *numPad6Btn = new wxButton(MCCPanel, 906, wxT("6"));
    wxButton *numPad7Btn = new wxButton(MCCPanel, 907, wxT("7"));
    wxButton *numPad8Btn = new wxButton(MCCPanel, 908, wxT("8"));
    wxButton *numPad9Btn = new wxButton(MCCPanel, 909, wxT("9"));
    wxButton *numPad0Btn = new wxButton(MCCPanel, 910, wxT("0"));
    wxButton *numPadDotBtn = new wxButton(MCCPanel, 911, wxT("."));
    wxButton *numPadEnterBtn = new wxButton(MCCPanel, 912, wxT("Enter"));
    wxButton *numPadBkSpBtn = new wxButton(MCCPanel, 913, wxT("BackSpace"));
    wxButton *numPadClearBtn = new wxButton(MCCPanel, 914, wxT("Clear"));
    wxButton *numPadCancelBtn = new wxButton (MCCPanel, 915, wxT("Cancel"));

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

    MCCPadV1Sizer->Add(NumPadNumRow1, numPadRowFlags);
    MCCPadV1Sizer->Add(NumPadNumRow2, numPadRowFlags);
    MCCPadV1Sizer->Add(NumPadNumRow3, numPadRowFlags);
    MCCPadV1Sizer->Add(NumPadNumRow4, numPadRowFlags);

    MCCPadV2Sizer->Add(numPadCancelBtn, numPadNumBtnFlags);
    MCCPadV2Sizer->Add(numPadClearBtn, numPadNumBtnFlags);
    MCCPadV2Sizer->Add(numPadBkSpBtn, numPadNumBtnFlags);
    MCCPadV2Sizer->Add(numPadEnterBtn, numPadNumBtnFlags);

    MCCPadHSizer->Add(MCCPadV1Sizer, wxSizerFlags(2).Expand().Border(wxALL, 2));
    MCCPadHSizer->Add(MCCPadV2Sizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    MCCPadSizer->Add(MCCPadHSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));

    mainHSizer->Add(MCCVSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));
    mainHSizer->Add(MCCPadSizer, wxSizerFlags(1).Expand().Border(wxALL, 8));
    mainVSizer->Add(mainHSizer, wxSizerFlags(1).Expand().Border(wxALL, 2));

    numPadCancelBtn->Bind(wxEVT_BUTTON, &ManualCreditCard::cancel, this);
    cardAmountBox->Bind(wxEVT_SET_FOCUS, &ManualCreditCard::getFocus, this);
    cardNumBox->Bind(wxEVT_SET_FOCUS, &ManualCreditCard::getFocus, this);
    cardExpireYearBox->Bind(wxEVT_SET_FOCUS, &ManualCreditCard::getFocus, this);
    cardExpireMonthBox->Bind(wxEVT_SET_FOCUS, &ManualCreditCard::getFocus, this);
    cardValidationBox->Bind(wxEVT_SET_FOCUS, &ManualCreditCard::getFocus, this);
    MCCPanel->Bind(wxEVT_BUTTON, &ManualCreditCard::keyPad, this);

    MCCPanel->SetSizer(mainVSizer);

    cardAmountBox->SetFocus();
    Center();
    ShowModal();
}

void ManualCreditCard::cancel(wxCommandEvent &event)
{
    this->Destroy();
    event.Skip();
}

void ManualCreditCard::getFocus(wxFocusEvent &event)
{
    focusId = event.GetId();
    event.Skip();
}

int ManualCreditCard::getMonth()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1 + ltm->tm_mon;
}

int ManualCreditCard::getYear()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

void ManualCreditCard::keypadInsert(std::string num)
{
    if (focusId == 921)
        cardAmountBox->AppendText(num);
    else if (focusId == 922)
        cardNumBox->AppendText(num);
    else if (focusId == 923)
        cardExpireYearBox->AppendText(num);
    else if(focusId == 924)
        cardExpireMonthBox->AppendText(num);
    else if (focusId == 925)
        cardValidationBox->AppendText(num);
}

void ManualCreditCard::keyPad(wxCommandEvent &event)
{
    int key = event.GetId();
    switch(key)
    {
        case 915: //cancel
            cancel(event);
            break;
        
        case 901: //1key
            keypadInsert("1");
            break;

        case 902: //2key
            keypadInsert("2");
            break;

        case 903: //3key
            keypadInsert("3");
            break;

        case 904: //4key
            keypadInsert("4");
            break;

        case 905: //5key
            keypadInsert("5");
            break;

        case 906: //6key
            keypadInsert("6");
            break;

        case 907: //7key
            keypadInsert("7");
            break;

        case 908: //8key
            keypadInsert("8");
            break;

        case 909: //9key
            keypadInsert("9");
            break;

        case 910: //0key
            keypadInsert("0");
            break;

        case 911: //.key
            keypadInsert(".");
            break;

        case 913: //bkspace
            if (focusId == 921)
                cardAmountBox->Remove(cardAmountBox->GetLineLength(0) -1, cardAmountBox->GetLineLength(0));
            else if (focusId == 922)
                cardNumBox->Remove(cardNumBox->GetLineLength(0) -1, cardNumBox->GetLineLength(0));
            else if (focusId == 923)
                cardExpireYearBox->Remove(cardExpireYearBox->GetLineLength(0) -1, cardExpireYearBox->GetLineLength(0));
            else if(focusId == 924)
                cardExpireMonthBox->Remove(cardExpireMonthBox->GetLineLength(0) -1, cardExpireMonthBox->GetLineLength(0));
            else if (focusId == 925)
                cardValidationBox->Remove(cardValidationBox->GetLineLength(0) -1, cardValidationBox->GetLineLength(0));
            break;

        case 914: //clear
            if (focusId == 921)
                cardAmountBox->Clear();
            else if (focusId == 922)
                cardNumBox->Clear();
            else if (focusId == 923)
                cardExpireYearBox->Clear();
            else if(focusId == 924)
                cardExpireMonthBox->Clear();
            else if (focusId == 925)
                cardValidationBox->Clear();
            break;

        case 912: //enterkey
            if (focusId == 921)
                cardNumBox->SetFocus();
            else if (focusId == 922)
                cardExpireYearBox->SetFocus();
            else if (focusId == 923)
                cardExpireMonthBox->SetFocus();
            else if(focusId == 924)
                cardValidationBox->SetFocus();
            else if (focusId == 925)
            {
                if ((cardAmountBox->GetLineText(0) != "") && 
                    (cardNumBox->GetLineText(0) != "") && 
                    (cardExpireYearBox->GetLineText(0) != "") && 
                    (cardExpireMonthBox->GetLineText(0) != "") && 
                    (cardValidationBox->GetLineText(0) != ""))
                {
                    if (wxAtof(cardAmountBox->GetLineText(0)) <= std::stod(sale::formatStringd(amount)))
                    {
                        if (cardNumBox->GetLineText(0).length() == 10)
                        {
                            if (wxAtoi(cardExpireYearBox->GetLineText(0)) >= getYear())
                            {
                                if (wxAtoi(cardExpireMonthBox->GetLineText(0)) >= getMonth() && wxAtoi(cardExpireMonthBox->GetLineText(0)) <= MON_PER_YEAR)
                                {
                                    *payAmount = std::stod(sale::formatStringd(wxAtof(cardAmountBox->GetLineText(0))));
                                    cancel(event);
                                }
                                else
                                    cardExpireMonthBox->SetFocus();
                            }
                            else
                                cardExpireYearBox->SetFocus();
                        }
                        else
                            cardNumBox->SetFocus();
                    }
                    else
                    {
                        if (std::stod(sale::formatStringd(amount)) < 0)
                        {
                            if (cardNumBox->GetLineText(0).length() == 10)
                            {
                                if (wxAtoi(cardExpireYearBox->GetLineText(0)) >= getYear())
                                {
                                    if (wxAtoi(cardExpireMonthBox->GetLineText(0)) >= getMonth() && wxAtoi(cardExpireMonthBox->GetLineText(0)) <= MON_PER_YEAR)
                                    {
                                        *payAmount = std::stod(sale::formatStringd(wxAtof(cardAmountBox->GetLineText(0))));
                                        cancel(event);
                                    }
                                    else
                                        cardExpireMonthBox->SetFocus();
                                }
                                else
                                    cardExpireYearBox->SetFocus();
                            }
                            else
                                cardNumBox->SetFocus();
                        }
                        else
                            cardAmountBox->SetFocus();
                    }
                }
                else
                    cardAmountBox->SetFocus();
            }
            break;

    }
    event.Skip();
}