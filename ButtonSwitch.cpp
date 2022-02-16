#include <iostream>
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
        case 5001:
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
        case 5011:
            UPCorPLUBox->Remove(UPCorPLUBox->GetLineLength(0) -1, UPCorPLUBox->GetLineLength(0));
            break;
        case 5012:
            if (gettingCash)
            {
                cancelOperation();
                gettingCash = false;
            }
            else if (gettingItem)
            {
                cancelOperation();
                gettingItem = false;
            }
            else
            {
                UPCorPLUBox->Clear();
            }
            elementsVSizer->Layout();
            break;
        case 5015:
            LkUpItem();
            OpenMenu = true;
            break;
        case 9001:
            getCash();
            break;
        case 5010:
            if (gettingCash)
            {
                reciveCash();
            }
            else if (gettingItem)
            {
                addQty();
            }
            break;
        case 5021:

            deleteItem(tablePos);
            break;
        case 5024:
            addItem();
            break;

        //function Menu Here with 7000s ID
        case 5023:
            functionVSizer->Show(false);
            paymentVSizer->Show(false);
            managerMenuVSizer->Show(false);
            mainMenuVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 5014:
            mainMenuVSizer->Show(false);
            functionVSizer->Show(false);
            managerMenuVSizer->Show(false);
            paymentVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 5016:
            paymentVSizer->Show(false);
            mainMenuVSizer->Show(false);
            managerMenuVSizer->Show(false);
            functionVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 5017:
            paymentVSizer->Show(false);
            mainMenuVSizer->Show(false);
            functionVSizer->Show(false);
            managerMenuVSizer->Show(true);
            elementsVSizer->Layout();
            break;
        case 7099:
            OnLogout(false);
            break;

        //Manager Menu owith 8000 ids
        case 8001:
            OnLogout(true);
            break;
        
        //Main Menu
        case 6004:
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
        case 6005:
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
        default:
            break;
    }
    if (OpenMenu == false)
    {
        UPCorPLUBox->SetFocus();
        UPCorPLUBox->SetInsertionPoint(UPCorPLUBox->GetLineLength(0));
    }
}