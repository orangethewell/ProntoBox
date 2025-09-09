/***************************************************************
 * Name:      ProntoBoxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Wellington Júnior (orangethewell@gmail.com)
 * Created:   2025-09-05
 * Copyright: Wellington Júnior ()
 * License:
 **************************************************************/

#include "ProntoBoxMain.h"
#include "TransactionEditDialog.h"
#include "db.h"
#include "Items.h"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include <wx/imaglist.h>
#include <wx/wx.h>

//(*InternalHeaders(ProntoBoxFrame)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ProntoBoxFrame)
const wxWindowID ProntoBoxFrame::ID_DASHBOARDPANEL = wxNewId();
const wxWindowID ProntoBoxFrame::ID_LISTVIEW1 = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BUTTONCLIENTINSERT = wxNewId();
const wxWindowID ProntoBoxFrame::ID_CLIENTPANEL = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TRANSACTIONDATAVIEW = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BALANCELABEL = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BALANCECTRL = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BUTTONTRANSACTIONEDIT = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BUTTONTRANSACTIONDELETE = wxNewId();
const wxWindowID ProntoBoxFrame::ID_BUTTONTRANSACTIONINSERT = wxNewId();
const wxWindowID ProntoBoxFrame::ID_PANELCASH = wxNewId();
const wxWindowID ProntoBoxFrame::ID_NOTEBOOK1 = wxNewId();
const wxWindowID ProntoBoxFrame::idMenuQuit = wxNewId();
const wxWindowID ProntoBoxFrame::idMenuAbout = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBARHOME = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBARSO = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBARCLIENTS = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBARSERVICES = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBARCASH = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBAREQUIP = wxNewId();
const wxWindowID ProntoBoxFrame::ID_TOOLBAR = wxNewId();
//*)

const int SIMPLEBOOK_DASHBOARD_PAGE = 0;
const int SIMPLEBOOK_CLIENT_PAGE    = 1;
const int SIMPLEBOOK_CASH_PAGE      = 2;

BEGIN_EVENT_TABLE(ProntoBoxFrame,wxFrame)
    //(*EventTable(ProntoBoxFrame)
    //*)
END_EVENT_TABLE()

ProntoBoxFrame::ProntoBoxFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ProntoBoxFrame)
    wxBoxSizer* BalanceBoxSizer;
    wxBoxSizer* BottomBoxSizer;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* ClientSizer;
    wxBoxSizer* ControlBoxSizer;
    wxBoxSizer* TransactionsPanelBoxSizer;
    wxMenu* MenuFile;
    wxMenu* MenuHelp;
    wxMenuBar* MenuBar;
    wxMenuItem* MenuFileItemQuit;
    wxMenuItem* MenuHelpItemAbout;

    Create(parent, wxID_ANY, _T("ProntoBox"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1080,720));
    MainSimplebook = new wxSimplebook(this, ID_NOTEBOOK1, wxPoint(184,208), wxSize(104,96), 0, _T("ID_NOTEBOOK1"));
    DashboardPanel = new wxPanel(MainSimplebook, ID_DASHBOARDPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_DASHBOARDPANEL"));
    ClientPanel = new wxPanel(MainSimplebook, ID_CLIENTPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CLIENTPANEL"));
    ClientSizer = new wxBoxSizer(wxVERTICAL);
    ClientListView = new wxListView(ClientPanel, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_LIST, wxDefaultValidator, _T("ID_LISTVIEW1"));
    ClientSizer->Add(ClientListView, 1, wxALL|wxEXPAND, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ClientInsertButton = new wxButton(ClientPanel, ID_BUTTONCLIENTINSERT, _T("Inserir"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCLIENTINSERT"));
    BoxSizer1->Add(ClientInsertButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ClientSizer->Add(BoxSizer1, 0, wxALL|wxALIGN_RIGHT, 5);
    ClientPanel->SetSizer(ClientSizer);
    TransactionsPanel = new wxPanel(MainSimplebook, ID_PANELCASH, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANELCASH"));
    TransactionsPanelBoxSizer = new wxBoxSizer(wxVERTICAL);
    TransactionDataView = new TransactionListView(TransactionsPanel, ID_TRANSACTIONDATAVIEW, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES|wxDV_VERT_RULES, wxDefaultValidator);
    TransactionsPanelBoxSizer->Add(TransactionDataView, 1, wxALL|wxEXPAND, 5);
    BottomBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    BalanceBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    BalanceLabel = new wxStaticText(TransactionsPanel, ID_BALANCELABEL, _T("Saldo Atual"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BALANCELABEL"));
    BalanceBoxSizer->Add(BalanceLabel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BalanceCtrl = new wxTextCtrl(TransactionsPanel, ID_BALANCECTRL, _T("R$"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT, wxDefaultValidator, _T("ID_BALANCECTRL"));
    BalanceBoxSizer->Add(BalanceCtrl, 1, wxALL|wxEXPAND, 5);
    BottomBoxSizer->Add(BalanceBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BottomBoxSizer->Add(-1,-1,1, wxALL, 5);
    ControlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    TransactionsEditButton = new wxButton(TransactionsPanel, ID_BUTTONTRANSACTIONEDIT, _T("Editar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONTRANSACTIONEDIT"));
    TransactionsEditButton->Disable();
    ControlBoxSizer->Add(TransactionsEditButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TransactionsDeleteButton = new wxButton(TransactionsPanel, ID_BUTTONTRANSACTIONDELETE, _T("Apagar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONTRANSACTIONDELETE"));
    TransactionsDeleteButton->Disable();
    ControlBoxSizer->Add(TransactionsDeleteButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TransactionsInsertButton = new wxButton(TransactionsPanel, ID_BUTTONTRANSACTIONINSERT, _T("Novo..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONTRANSACTIONINSERT"));
    ControlBoxSizer->Add(TransactionsInsertButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BottomBoxSizer->Add(ControlBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TransactionsPanelBoxSizer->Add(BottomBoxSizer, 0, wxALL|wxEXPAND, 5);
    TransactionsPanel->SetSizer(TransactionsPanelBoxSizer);
    MainSimplebook->AddPage(DashboardPanel, _T("Dashboard"), true);
    MainSimplebook->AddPage(ClientPanel, _T("Clients"), false);
    MainSimplebook->AddPage(TransactionsPanel, _T("Transactions"), false);
    MenuBar = new wxMenuBar();
    MenuFile = new wxMenu();
    MenuFileItemQuit = new wxMenuItem(MenuFile, idMenuQuit, _T("Sair\tAlt-F4"), _T("Quit the application"), wxITEM_NORMAL);
    MenuFile->Append(MenuFileItemQuit);
    MenuBar->Append(MenuFile, _T("Arquivos"));
    MenuHelp = new wxMenu();
    MenuHelpItemAbout = new wxMenuItem(MenuHelp, idMenuAbout, _T("Sobre\tF1"), _T("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuHelpItemAbout);
    MenuBar->Append(MenuHelp, _T("Ajuda"));
    SetMenuBar(MenuBar);
    ToolBar = new wxToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_TEXT|wxBORDER_SIMPLE|wxBORDER_RAISED|wxBORDER_STATIC|wxTAB_TRAVERSAL, _T("ID_TOOLBAR"));
    ToolBar->SetToolBitmapSize(wxSize(32,32));
    ToolBarItem6 = ToolBar->AddTool(ID_TOOLBARHOME, _T("Início"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\home.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar->AddSeparator();
    ToolBarItem2 = ToolBar->AddTool(ID_TOOLBARSO, _T("Ordens"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\orders.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem1 = ToolBar->AddTool(ID_TOOLBARCLIENTS, _T("Clientes"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\client.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar->AddSeparator();
    ToolBarItem3 = ToolBar->AddTool(ID_TOOLBARSERVICES, _T("Serviços"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\services.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem4 = ToolBar->AddTool(ID_TOOLBARCASH, _T("Caixa"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\cash.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem5 = ToolBar->AddTool(ID_TOOLBAREQUIP, _T("Equipamento"), wxBitmap(wxImage(_T("C:\\Users\\Wellington Júnior\\Documents\\Projetos\\ProntoBox\\resources\\icons\\equipament.png"))), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar->Realize();
    SetToolBar(ToolBar);
    Center();

    DashboardPanel->Connect(wxEVT_PAINT, (wxObjectEventFunction)&ProntoBoxFrame::OnDashboardPanelPaint, NULL, this);
    Connect(ID_TRANSACTIONDATAVIEW, wxEVT_DATAVIEW_SELECTION_CHANGED, (wxObjectEventFunction)&ProntoBoxFrame::OnTransactionDataViewRowSelected);
    Connect(ID_BUTTONTRANSACTIONEDIT, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnTransactionsEditButtonClick);
    Connect(ID_BUTTONTRANSACTIONDELETE, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnTransactionsDeleteButtonClick);
    Connect(ID_BUTTONTRANSACTIONINSERT, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnTransactionInsertClick);
    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&ProntoBoxFrame::OnQuit);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&ProntoBoxFrame::OnAbout);
    Connect(ID_TOOLBARHOME, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    Connect(ID_TOOLBARSO, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    Connect(ID_TOOLBARCLIENTS, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    Connect(ID_TOOLBARSERVICES, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    Connect(ID_TOOLBARCASH, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    Connect(ID_TOOLBAREQUIP, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&ProntoBoxFrame::OnToolBarClicked);
    //*)

    ::wxInitAllImageHandlers();

    DashboardPanelImage = wxImage("resources\\background.jpg", wxBITMAP_TYPE_JPEG);
    if (!DashboardPanelImage.IsOk()) {
        wxMessageBox("Erro ao carregar a imagem de fundo para painel principal.", "Houve um erro no programa", wxOK | wxICON_ERROR);
    }

    db_open("user.db");
}

ProntoBoxFrame::~ProntoBoxFrame()
{
    //(*Destroy(ProntoBoxFrame)
    //*)
    db_close();
}

void ProntoBoxFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ProntoBoxFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ProntoBoxFrame::CreateDashboardScaledBg()
{
    wxSize sz = DashboardPanel->GetSize();
    DashboardPanelScaledBg = wxBitmap(DashboardPanelImage.Scale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_NORMAL));
}

void ProntoBoxFrame::OnDashboardPanelPaint(wxPaintEvent& event)
{
    if ( DashboardPanel->GetSize() != DashboardPanelScaledBg.GetSize() )
    {
        CreateDashboardScaledBg();
    }

    wxPaintDC dc(DashboardPanel);
    dc.DrawBitmap(DashboardPanelScaledBg,0,0);
}

void ProntoBoxFrame::OnToolBarClicked(wxCommandEvent& event)
{
    int id = event.GetId();

    if (id == ID_TOOLBARHOME)
        MainSimplebook->ChangeSelection(SIMPLEBOOK_DASHBOARD_PAGE);

    else if (id == ID_TOOLBARSO)
        wxMessageBox("Abrir Ordens de Serviço");

    else if (id == ID_TOOLBARCLIENTS)
        MainSimplebook->ChangeSelection(SIMPLEBOOK_CLIENT_PAGE);

    else if (id == ID_TOOLBARSERVICES)
        wxMessageBox("Abrir Serviços");

    else if (id == ID_TOOLBARCASH) {
        BalanceCtrl->SetValue(wxString::Format("R$ %.2f", TransactionDataView->SetTransactions(TransactionItem::db_getAll(g_db))));
        MainSimplebook->ChangeSelection(SIMPLEBOOK_CASH_PAGE);
    }

    else if (id == ID_TOOLBAREQUIP)
        wxMessageBox("Abrir Equipamentos");

    else
        event.Skip();
}

void ProntoBoxFrame::OnTransactionInsertClick(wxCommandEvent& event)
{
    TransactionEditDialog dlg(this);

    if (dlg.ShowModal() == wxID_OK) {
        BalanceCtrl->SetValue(wxString::Format("R$ %.2f", TransactionDataView->SetTransactions(TransactionItem::db_getAll(g_db))));
    }
}

void ProntoBoxFrame::OnTransactionDataViewRowSelected(wxDataViewEvent& event)
{
    bool hasSelection = TransactionDataView->GetSelectedRow() != wxNOT_FOUND;
    TransactionsEditButton->Enable(hasSelection);
    TransactionsDeleteButton->Enable(hasSelection);
}

void ProntoBoxFrame::OnTransactionsDeleteButtonClick(wxCommandEvent& event)
{
    int row = TransactionDataView->GetSelectedRow();
    if (row == wxNOT_FOUND) return;

    int tID = TransactionDataView->GetItemID(row);

    if (tID == -1) return;

    if (wxMessageBox(_T("Tem certeza que deseja excluir esta transação?"),
                     _T("Confirmação"), wxYES_NO | wxICON_QUESTION) == wxYES) {
        TransactionItem::db_delete(g_db, tID);
        BalanceCtrl->SetValue(wxString::Format("R$ %.2f", TransactionDataView->SetTransactions(TransactionItem::db_getAll(g_db))));
    }
}

void ProntoBoxFrame::OnTransactionsEditButtonClick(wxCommandEvent& event)
{
    int row = TransactionDataView->GetSelectedRow();
    if (row == wxNOT_FOUND) return;

    int tID = TransactionDataView->GetItemID(row); // precisa ter um getter no seu ListView

    TransactionEditDialog dlg(this, tID);
    if (dlg.ShowModal() == wxID_OK) {
        BalanceCtrl->SetValue(wxString::Format("R$ %.2f", TransactionDataView->SetTransactions(TransactionItem::db_getAll(g_db))));
    }
}
