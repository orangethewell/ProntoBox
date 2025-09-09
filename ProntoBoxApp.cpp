/***************************************************************
 * Name:      ProntoBoxApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Wellington Júnior (orangethewell@gmail.com)
 * Created:   2025-09-05
 * Copyright: Wellington Júnior ()
 * License:
 **************************************************************/

#include "ProntoBoxApp.h"

#include <locale>

//(*AppHeaders
#include "ProntoBoxMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ProntoBoxApp);

bool ProntoBoxApp::OnInit()
{
    std::setlocale(LC_NUMERIC, "Portuguese_Brazil.1252");

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        ProntoBoxFrame* Frame = new ProntoBoxFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
