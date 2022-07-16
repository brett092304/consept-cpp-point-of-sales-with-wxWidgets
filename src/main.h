#include "PCH.h"
namespace fs = std::experimental::filesystem;

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
        static std::string getPath();
};

class StartUp
{
    public:
        void start();
        bool fileExists(const std::string& name);
};