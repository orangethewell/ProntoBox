#ifndef TRANSACTIONLISTVIEW_H
#define TRANSACTIONLISTVIEW_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <wx/dataview.h>
#include <wx/colour.h>
#include "../Items.h"

class TransactionModel : public wxDataViewIndexListModel {
public:
    TransactionModel(const std::vector<TransactionItem>& items)
        : wxDataViewIndexListModel(items.size()), m_items(items) {}

    virtual unsigned int GetColumnCount() const override { return 5; }
    virtual wxString GetColumnType(unsigned int col) const override { return "string"; }

    virtual bool SetValueByRow(const wxVariant &variant, unsigned int row, unsigned int col) override {
        return false;
    };

    virtual void GetValueByRow(wxVariant& value, unsigned int row, unsigned int col) const override {
        const auto& item = m_items[row];
        switch (col) {
            case 0: value = wxVariant(wxString::Format("%d", item.id)); break;
            case 1: value = wxVariant(wxString::Format("%.2f", item.value)); break;
            case 2: value = wxVariant(FormatDate(item.date)); break;
            case 3: value = wxVariant(FormatTime(item.date)); break;
            case 4: value = wxVariant(wxString::FromUTF8(item.description)); break;
        }
    }

    virtual bool GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr& attr) const override {
        if (col == 1) {
            if (m_items[row].value < 0)
                attr.SetColour(*wxRED);
            else if (m_items[row].value > 0)
                attr.SetColour(wxColour(0, 128, 0));
            return true;
        }
        return false;
    }

private:
    std::vector<TransactionItem> m_items;
    static std::string FormatDate(std::time_t t) {
        std::tm* tm_ptr = std::localtime(&t);
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << tm_ptr->tm_mday << "/"
             << std::setw(2) << std::setfill('0') << tm_ptr->tm_mon+1 << "/"
             << (tm_ptr->tm_year + 1900);
        return oss.str();
    }

    static std::string FormatTime(std::time_t t) {
        std::tm* tm_ptr = std::localtime(&t);
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << tm_ptr->tm_hour << ":"
             << std::setw(2) << std::setfill('0') << tm_ptr->tm_min;
        return oss.str();
    }
};

class TransactionDataListView : public wxDataViewListCtrl
{
    public:
        TransactionDataListView(
                wxWindow* parent,
                const wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0x0004,
                const wxValidator& validator = wxDefaultValidator,
                int todo = 0
            )
        : wxDataViewListCtrl(parent, id, pos, size, style, validator) {
            auto colId = this->AppendTextColumn("ID");
            colId->SetWidth(50);

            auto colValor = this->AppendTextColumn("Valor");
            colValor->SetWidth(100);

            auto colData = this->AppendTextColumn("Data");
            colData->SetWidth(100);

            auto colHora = this->AppendTextColumn("Hora");
            colHora->SetWidth(80);

            auto colDesc = this->AppendTextColumn("Descrição");

            colDesc->SetWidth(200);

        }

        float SetTransactions(const std::vector<TransactionItem>& items) {
            this->AssociateModel(new TransactionModel(items));
            float totalValue = 0.0;
            for (auto &i : items) {
                totalValue += i.value;
            }

            return totalValue;
        }

        int GetSelectedRow() {
            wxDataViewItem item = GetSelection();
            if (!item.IsOk()) return wxNOT_FOUND;
            return GetRowByItem(item); // ou equivalente
        }

        int GetItemID(int row) {
            wxVariant var;
            this->GetValue(var, row, 0); // supondo que a coluna 0 armazene o ID
            long tID = var.GetLong();
            return (int)tID;
        }

        virtual ~TransactionDataListView() {

        }

    protected:

    private:

};
#endif // TRANSACTIONLISTVIEW_H
