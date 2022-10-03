#include "PCH.h"
namespace fs = std::experimental::filesystem;

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
        static std::string getPath();
        static std::string trimPath(std::string fullpath);
};

class StartUp
{
    public:
        void start();
        bool fileExists(const std::string& name);
};