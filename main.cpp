#include "main.h"
#include "program.h"
#include "SetUp.h"
#include "connection.h"
#include <iostream>
#include <fstream>
#include <thread>

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    StartUp StartUp;
    StartUp.start();
    return true;
}

void StartUp::start()
{
    std::ifstream ifile;
    ifile.open("MysqlConnection.txt");
    if (ifile)
    {
        std::vector<std::string> fileAns;
        std::string fileTags;
        while (getline(ifile, fileTags))
        {
           fileAns.push_back(fileTags);
        }
        ifile.close();
        CreateConnection::setConnectionStatus(fileAns);
        MainFrame *frame = new MainFrame(wxT("Sales"));
        frame->Show(true);
    }
    else
    {
        SetUp *setUpFrame = new SetUp(wxT("Set Up"));
        setUpFrame->Show(true);
    }
}