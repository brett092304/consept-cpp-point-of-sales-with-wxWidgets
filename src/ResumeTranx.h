#include "PCH.h"

class ResumeTranx : public wxDialog
{
    public:
        ResumeTranx(const wxString &title);
        void close(wxCommandEvent &event);

    private:
        wxGrid *table;

};