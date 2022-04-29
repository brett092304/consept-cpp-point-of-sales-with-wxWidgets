#include "PCH.h"
#include "program.h"
#include "login.h"
#include "connection.h"
#include "sale.h"

void MainFrame::EnterNumPadNumber(wxCommandEvent &event)
{
    bool OpenMenu = false;
    int key = event.GetId();
    switch(key)
    {
        //static menu with 5000 ids
        case 5001: //5000-5009 & 5020 - NumPad
            UPCorPLUBox->AppendText("1");
            break;
        case 5002:
            UPCorPLUBox->AppendText("2");
            break;
        case 5003:
            UPCorPLUBox->AppendText("3");
            break;
        case 5004:
            UPCorPLUBox->AppendText("4");
            break;
        case 5005:
            UPCorPLUBox->AppendText("5");
            break;
        case 5006:
            UPCorPLUBox->AppendText("6");
            break;
        case 5007:
            UPCorPLUBox->AppendText("7");
            break;
        case 5008:
            UPCorPLUBox->AppendText("8");
            break;
        case 5009:
            UPCorPLUBox->AppendText("9");
            break;
        case 5000:
            UPCorPLUBox->AppendText("0");
            break;
        case 5020:
            UPCorPLUBox->AppendText(".");
            break;
        case 5011: //BackSpace
            UPCorPLUBox->Remove(UPCorPLUBox->GetLineLength(0) -1, UPCorPLUBox->GetLineLength(0));
            break;
        case 5012: //Clear Button
            cancelOperation();
            if (gettingCash)
                gettingCash = false;
            else if (gettingItem)
                gettingItem = false;
            else if (scanDeleteItem)
                scanDeleteItem = false;
            else if (changingQty)
                changingQty = false;
            else if (changingPrice)
                changingPrice = false;
            else if (hasChange)
            {
                deleteTranx(true);
                hasChange = false;
                totalTranx();
                finalTotalLabel->SetLabelText("Total: $");
                finalTotalHSizer->Layout();
            }
            else
            {
                UPCorPLUBox->Clear();
		        UPCorPLUText->SetLabelText("Sku or Upc: ");
            }
            elementsVSizer->Layout();
            break;
        case 5015: //Look Up Item
            LkUpItem();
            OpenMenu = true;
            break;
        case 5010: //Enter Button
            if (gettingCash)
            {
                reciveCash();
            }
            else if (gettingItem)
            {
                addQty();
                totalTranx();
            }
            else if (scanDeleteItem)
            {
                scanDelete();
                totalTranx();
            }
            else if (changingQty)
                changeQty();
            else if (changingPrice)
                changePrice();
            else if (settingTaxExempt)
                taxExempt();
            break;

        case 5021: //Void Item
            deleteItem(tablePos);
            totalTranx();
            break;

        case 5024: //Sku/Plu Button
            if (!hasChange)
                addItem();
            break;

        case 5019: //Change price Button
            changingPrice = true;
            UPCorPLUText->SetLabelText(wxT("Price: $"));
            break;

        case 5023: //Main Menu Button - go to Main Menu
            functionVSizer->Show(false);
            paymentVSizer->Show(false);
            managerMenuVSizer->Show(false);
            mainMenuVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 5014: //SubTotal Button - go to Payment Menu
            mainMenuVSizer->Show(false);
            functionVSizer->Show(false);
            managerMenuVSizer->Show(false);
            paymentVSizer->Show(true);
            elementsVSizer->Layout();
            totalTranx();
            break;
        case 5016: //Function Menu Button - go to Function Menu
            paymentVSizer->Show(false);
            mainMenuVSizer->Show(false);
            managerMenuVSizer->Show(false);
            functionVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 5017: //Manager Menu Button - go to Manager menu
            paymentVSizer->Show(false);
            mainMenuVSizer->Show(false);
            functionVSizer->Show(false);
            managerMenuVSizer->Show(true);
            elementsVSizer->Layout();
            break;

        //Manager Menu with 8000 ids
        case 8001: //Manger Login Button
            OnLogout(true);
            break;
        
        case 8004: //Void Transaction
            deleteTranx(false);
            totalTranx();
            break;

        case 8005: //Copy Row/Line Button
            duplicateTableLine();
            break;

        case 8003: //return button - temp
            break;

        //Function Menu with 7000 ids
        case 7099: //Logout Button
            OnLogout(false);
            break;

        case 7003: //Change Qty Button
            changingQty = true;
            UPCorPLUText->SetLabelText(wxT("Quantity: "));
            break;

        case 7001: //tax exempt
            settingTaxExempt = true;
            UPCorPLUText->SetLabelText(wxT("Tax Exempt: "));
            break;

        //Main Menu with 6000 ids
        case 6001: //Scanvoid Button
            UPCorPLUText->SetLabelText("Sku or Upc to Void: ");
            elementsVSizer->Layout();
            scanDeleteItem = true;
            totalTranx();
            break;
        case 6004: //Up List Button
            tablePos --;
            if (tablePos >= 0)
            {
                dataTable->SelectRow(tablePos);
            }
            else
            {
                dataTable->SelectRow(0);
                tablePos = 0;
            }
            break;
        case 6005: //Down list Button
            tablePos++;
            if (tablePos <= dataTable->GetNumberRows() - 1)
            {
                dataTable->SelectRow(tablePos);
            }
            else
            {
                dataTable->SelectRow(dataTable->GetNumberRows() - 1);
                tablePos = dataTable->GetNumberRows() - 1;
            }
            break;

        //Payment Menu with 9000 ids
        case 9001: //Get Cash
            getCash();
            break;

        default:
            break;
    }
    if (OpenMenu == false)
    {
        UPCorPLUBox->SetFocus();
        UPCorPLUBox->SetInsertionPoint(UPCorPLUBox->GetLineLength(0));
    }
}
