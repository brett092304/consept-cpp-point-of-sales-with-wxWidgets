#include <wx/wx.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class StartUp
{
    public:
        void start();
        bool fileExists(const std::string& name);
};