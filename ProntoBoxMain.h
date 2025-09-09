/***************************************************************
 * Name:      ProntoBoxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Wellington Júnior (orangethewell@gmail.com)
 * Created:   2025-09-05
 * Copyright: Wellington Júnior ()
 * License:
 **************************************************************/

#ifndef PRONTOBOXMAIN_H
#define PRONTOBOXMAIN_H

//(*Headers(ProntoBoxFrame)
#include <wx/button.h>
#include <wx/dataview.h>
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>
//*)
#include <wx/simplebook.h>
#include "widgets/TransactionDataListView.h"


class ProntoBoxFrame: public wxFrame
{
    public:

        ProntoBoxFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ProntoBoxFrame();

    private:

        //(*Handlers(ProntoBoxFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnDashboardPanelPaint(wxPaintEvent& event);
        void OnToolBarClicked(wxCommandEvent& event);
        void OnMainSimplebookPageChanged(wxNotebookEvent& event);
        void OnTransactionInsertClick(wxCommandEvent& event);
        void OnTransactionDataViewRowSelected(wxDataViewEvent& event);
        void OnTransactionsDeleteButtonClick(wxCommandEvent& event);
        void OnTransactionsEditButtonClick(wxCommandEvent& event);
        //*)

        void CreateDashboardScaledBg();

        //(*Identifiers(ProntoBoxFrame)
        static const wxWindowID ID_DASHBOARDPANEL;
        static const wxWindowID ID_LISTVIEW1;
        static const wxWindowID ID_BUTTONCLIENTINSERT;
        static const wxWindowID ID_CLIENTPANEL;
        static const wxWindowID ID_TRANSACTIONDATAVIEW;
        static const wxWindowID ID_BALANCELABEL;
        static const wxWindowID ID_BALANCECTRL;
        static const wxWindowID ID_BUTTONTRANSACTIONEDIT;
        static const wxWindowID ID_BUTTONTRANSACTIONDELETE;
        static const wxWindowID ID_BUTTONTRANSACTIONINSERT;
        static const wxWindowID ID_PANELCASH;
        static const wxWindowID ID_NOTEBOOK1;
        static const wxWindowID idMenuQuit;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_TOOLBARHOME;
        static const wxWindowID ID_TOOLBARSO;
        static const wxWindowID ID_TOOLBARCLIENTS;
        static const wxWindowID ID_TOOLBARSERVICES;
        static const wxWindowID ID_TOOLBARCASH;
        static const wxWindowID ID_TOOLBAREQUIP;
        static const wxWindowID ID_TOOLBAR;
        //*)

        //(*Declarations(ProntoBoxFrame)
        TransactionListView* TransactionDataView;
        wxButton* ClientInsertButton;
        wxButton* TransactionsDeleteButton;
        wxButton* TransactionsEditButton;
        wxButton* TransactionsInsertButton;
        wxListView* ClientListView;
        wxPanel* ClientPanel;
        wxPanel* DashboardPanel;
        wxPanel* TransactionsPanel;
        wxSimplebook* MainSimplebook;
        wxStaticText* BalanceLabel;
        wxTextCtrl* BalanceCtrl;
        wxToolBar* ToolBar;
        wxToolBarToolBase* ToolBarItem1;
        wxToolBarToolBase* ToolBarItem2;
        wxToolBarToolBase* ToolBarItem3;
        wxToolBarToolBase* ToolBarItem4;
        wxToolBarToolBase* ToolBarItem5;
        wxToolBarToolBase* ToolBarItem6;
        //*)

        wxImage DashboardPanelImage;
        wxBitmap DashboardPanelScaledBg;

        DECLARE_EVENT_TABLE()
};

#endif // PRONTOBOXMAIN_H
