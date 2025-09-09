#ifndef TRANSACTIONEDITDIALOG_H
#define TRANSACTIONEDITDIALOG_H

//(*Headers(TransactionEditDialog)
#include <wx/button.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dialog.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timectrl.h>
//*)

class TransactionEditDialog: public wxDialog
{
    public:

        TransactionEditDialog(wxWindow* parent, int tID=-1, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~TransactionEditDialog();

        //(*Declarations(TransactionEditDialog)
        wxButton* CancelButton;
        wxButton* SaveButton;
        wxDatePickerCtrl* DatePickerCtrl;
        wxRadioButton* RadioCosts;
        wxRadioButton* RadioDeposits;
        wxStaticText* CurrencyLabel;
        wxStaticText* DateTimeLabel;
        wxStaticText* DescriptionLabel;
        wxTextCtrl* CurrencyCtrl;
        wxTextCtrl* DescriptionField;
        wxTimePickerCtrl* TimePickerCtrl;
        //*)

    protected:

        //(*Identifiers(TransactionEditDialog)
        static const wxWindowID ID_CURRENCYLABEL;
        static const wxWindowID ID_RADIOBUTTON1;
        static const wxWindowID ID_RADIOBUTTON2;
        static const wxWindowID ID_CURRENCYCTRL;
        static const wxWindowID ID_DATETIMELABEL;
        static const wxWindowID ID_DATEPICKERCTRL;
        static const wxWindowID ID_TIMEPICKERCTRL;
        static const wxWindowID ID_DESCRIPTIONLABEL;
        static const wxWindowID ID_DESCRIPTIONFIELD;
        static const wxWindowID ID_CANCELBUTTON;
        static const wxWindowID ID_SAVEBUTTON;
        //*)

    private:

        //(*Handlers(TransactionEditDialog)
        void OnCurrencyCtrlChange(wxCommandEvent& event);
        void OnSaveButtonClick(wxCommandEvent& event);
        void OnCancelButtonClick(wxCommandEvent& event);
        void OnRadioButton1Select(wxCommandEvent& event);
        void OnRadioButton2Select(wxCommandEvent& event);
        //*)

        int tID;
        DECLARE_EVENT_TABLE()
};

#endif
