#include "main.h"
#include "program.h"
#include "SetUp.h"
#include "connection.h"

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
    ifile.open(MyApp::getPath() + "MysqlConnection.txt");
    if (ifile)
    {
        std::vector<std::string> fileAns;
        std::string fileTags;
        while (getline(ifile, fileTags))
        {
           fileAns.push_back(fileTags);
        }
        ifile.close();
        if (fileAns.at(1) != "" && fileAns.at(2) != "" && fileAns.at(4) != "" && fileAns.at(5) != "")
        {
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
    else
    {
        SetUp *setUpFrame = new SetUp(wxT("Set Up"));
        setUpFrame->Show(true);
    }
}

std::string MyApp::getPath()
{
    fs::path path = fs::canonical("/proc/self/exe");
    std::string pathStr = path.string();
    return pathStr.erase(pathStr.length() -6);
}