#include "TransactionEditDialog.h"

//(*InternalHeaders(TransactionEditDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/wx.h>
#include "Items.h"

//(*IdInit(TransactionEditDialog)
const wxWindowID TransactionEditDialog::ID_CURRENCYLABEL = wxNewId();
const wxWindowID TransactionEditDialog::ID_RADIOBUTTON1 = wxNewId();
const wxWindowID TransactionEditDialog::ID_RADIOBUTTON2 = wxNewId();
const wxWindowID TransactionEditDialog::ID_CURRENCYCTRL = wxNewId();
const wxWindowID TransactionEditDialog::ID_DATETIMELABEL = wxNewId();
const wxWindowID TransactionEditDialog::ID_DATEPICKERCTRL = wxNewId();
const wxWindowID TransactionEditDialog::ID_TIMEPICKERCTRL = wxNewId();
const wxWindowID TransactionEditDialog::ID_DESCRIPTIONLABEL = wxNewId();
const wxWindowID TransactionEditDialog::ID_DESCRIPTIONFIELD = wxNewId();
const wxWindowID TransactionEditDialog::ID_CANCELBUTTON = wxNewId();
const wxWindowID TransactionEditDialog::ID_SAVEBUTTON = wxNewId();
//*)

BEGIN_EVENT_TABLE(TransactionEditDialog,wxDialog)
    //(*EventTable(TransactionEditDialog)
    //*)
END_EVENT_TABLE()

TransactionEditDialog::TransactionEditDialog(wxWindow* parent,int tID, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(TransactionEditDialog)
    wxBoxSizer* CurrencyBoxSizer;
    wxBoxSizer* DateTimeBoxSizer;
    wxBoxSizer* DateTimeFieldBoxSizer;
    wxBoxSizer* DescriptionVBoxSizer;
    wxBoxSizer* DialogControlBoxSizer;
    wxBoxSizer* MainBoxSizer;

    Create(parent, id, _T("Edit Transaction"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    MainBoxSizer = new wxBoxSizer(wxVERTICAL);
    CurrencyBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    CurrencyLabel = new wxStaticText(this, ID_CURRENCYLABEL, _T("Valor"), wxDefaultPosition, wxSize(46,16), 0, _T("ID_CURRENCYLABEL"));
    CurrencyBoxSizer->Add(CurrencyLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioDeposits = new wxRadioButton(this, ID_RADIOBUTTON1, _T("Deposit"), wxDefaultPosition, wxSize(72,20), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioDeposits->SetValue(true);
    CurrencyBoxSizer->Add(RadioDeposits, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    RadioCosts = new wxRadioButton(this, ID_RADIOBUTTON2, _T("Despesa"), wxDefaultPosition, wxSize(65,20), 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    CurrencyBoxSizer->Add(RadioCosts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    CurrencyCtrl = new wxTextCtrl(this, ID_CURRENCYCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CURRENCYCTRL"));
    CurrencyBoxSizer->Add(CurrencyCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainBoxSizer->Add(CurrencyBoxSizer, 0, wxALL|wxEXPAND, 5);
    DateTimeBoxSizer = new wxBoxSizer(wxVERTICAL);
    DateTimeLabel = new wxStaticText(this, ID_DATETIMELABEL, _T("Date and Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DATETIMELABEL"));
    DateTimeBoxSizer->Add(DateTimeLabel, 1, wxALL|wxALIGN_LEFT, 5);
    DateTimeFieldBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    DatePickerCtrl = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL"));
    DateTimeFieldBoxSizer->Add(DatePickerCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TimePickerCtrl = new wxTimePickerCtrl(this, ID_TIMEPICKERCTRL, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TIMEPICKERCTRL"));
    DateTimeFieldBoxSizer->Add(TimePickerCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DateTimeBoxSizer->Add(DateTimeFieldBoxSizer, 0, wxALL|wxEXPAND, 5);
    MainBoxSizer->Add(DateTimeBoxSizer, 0, wxALL|wxEXPAND, 5);
    DescriptionVBoxSizer = new wxBoxSizer(wxVERTICAL);
    DescriptionLabel = new wxStaticText(this, ID_DESCRIPTIONLABEL, _T("Description"), wxDefaultPosition, wxSize(52,17), 0, _T("ID_DESCRIPTIONLABEL"));
    DescriptionVBoxSizer->Add(DescriptionLabel, 1, wxALL|wxALIGN_LEFT|wxSHAPED, 5);
    DescriptionField = new wxTextCtrl(this, ID_DESCRIPTIONFIELD, wxEmptyString, wxDefaultPosition, wxSize(359,30), 0, wxDefaultValidator, _T("ID_DESCRIPTIONFIELD"));
    DescriptionField->SetMaxLength(255);
    DescriptionVBoxSizer->Add(DescriptionField, 0, wxALL|wxEXPAND, 5);
    MainBoxSizer->Add(DescriptionVBoxSizer, 0, wxALL|wxEXPAND, 5);
    DialogControlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    CancelButton = new wxButton(this, ID_CANCELBUTTON, _T("Cancelar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCELBUTTON"));
    DialogControlBoxSizer->Add(CancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SaveButton = new wxButton(this, ID_SAVEBUTTON, _T("Salvar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SAVEBUTTON"));
    DialogControlBoxSizer->Add(SaveButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainBoxSizer->Add(DialogControlBoxSizer, 0, wxALL|wxEXPAND, 5);
    SetSizer(MainBoxSizer);
    MainBoxSizer->SetSizeHints(this);

    Connect(ID_CURRENCYCTRL, wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&TransactionEditDialog::OnCurrencyCtrlChange);
    Connect(ID_CANCELBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&TransactionEditDialog::OnCancelButtonClick);
    Connect(ID_SAVEBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&TransactionEditDialog::OnSaveButtonClick);
    //*)

    SetTitle("Editar Transação");
    DateTimeLabel->SetLabel("Horário");
    DescriptionLabel->SetLabel("Descrição");
    RadioDeposits->SetLabel("Depósito");
    this->tID = tID;
    if (tID >= 0) {
        TransactionItem editable;
        if (!TransactionItem::db_get(g_db, tID, editable))
            wxMessageBox(_("Erro: Não foi possível encontrar esse item."), _("Houve um erro"), wxICON_ERROR | wxOK);

        CurrencyCtrl->SetValue(wxString::Format("%.2f", fabs(editable.value)));
        if(editable.value < 0.0)
            RadioCosts->SetValue(true);

        DescriptionField->SetValue(wxString(editable.description));

        // Data e hora
        wxDateTime dt = wxDateTime::UNow(); // fallback caso a conversão falhe
        if (editable.date > 0)
            dt = wxDateTime::UNow() + wxTimeSpan(0, 0, 0, editable.date); // converte timestamp
        DatePickerCtrl->SetValue(dt);
        TimePickerCtrl->SetValue(dt);

    }
    Connect(ID_CURRENCYCTRL, wxEVT_TEXT, (wxObjectEventFunction)&TransactionEditDialog::OnCurrencyCtrlChange);
}

TransactionEditDialog::~TransactionEditDialog()
{
    //(*Destroy(TransactionEditDialog)
    //*)
}

void TransactionEditDialog::OnCurrencyCtrlChange(wxCommandEvent& event)
{
    wxString value = CurrencyCtrl->GetValue();

    // Só permitir dígitos e, no máximo, uma vírgula
    wxString filtered;
    bool hasComma = false;

    for (auto ch : value)
    {
        if (wxIsdigit(ch))
        {
            if (filtered.empty() && ch == _("0")) continue;
            filtered += ch;
        }
        else if (ch == ',' && !hasComma)
        {
            filtered += ch;
            hasComma = true;
        }
        // ignora qualquer outro caractere
    }

    if (filtered != value)
    {
        // se houve caracteres inválidos, ajusta o campo
        long pos = CurrencyCtrl->GetInsertionPoint();
        CurrencyCtrl->ChangeValue(filtered); // não dispara wxEVT_TEXT
        CurrencyCtrl->SetInsertionPoint(pos > (int)filtered.length() ? filtered.length() : pos);
    }
}

void TransactionEditDialog::OnSaveButtonClick(wxCommandEvent& event)
{
    TransactionItem eItem;
    eItem.id = this->tID;

    wxString strValue = CurrencyCtrl->GetValue();
    double val = 0.0;
    strValue.ToDouble(&val);

    if (RadioCosts->GetValue()) {
        val = -val;
    }

    eItem.value = static_cast<float>(val);

    eItem.description = std::string(DescriptionField->GetValue().mb_str());

    wxDateTime date = DatePickerCtrl->GetValue();
    wxDateTime time = TimePickerCtrl->GetValue();

    wxDateTime combined(
        date.GetDay(),
        date.GetMonth(),
        date.GetYear(),
        time.GetHour(),
        time.GetMinute(),
        time.GetSecond()
    );

    eItem.date = combined.GetTicks();

    if (eItem.id >= 0) {
        TransactionItem::db_update(g_db, eItem);
    } else {
        TransactionItem::db_insert(g_db, eItem);
    }

    EndModal(wxID_OK);
}



void TransactionEditDialog::OnCancelButtonClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
