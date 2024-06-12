#ifndef TICKETSUI_H
#define TICKETSUI_H

#include "qstandarditemmodel.h"
#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class TicketsUI; }
QT_END_NAMESPACE

class TicketsUI : public QWidget
{
    Q_OBJECT

public:
    explicit TicketsUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~TicketsUI();


private slots:
    void addTicket();
    void deleteTicket();
    void updateTicket();
    void searchTickets(const QString& searchTerm);
    void loadTicketDetails(const QModelIndex& index);
    void clearTicketDetails();

private:
    Ui::TicketsUI *ui;
    QSqlDatabase db;
    QStandardItemModel* ticketsModel;

    void updateTicketsList();
    void updateClientComboBox();
    void updateMatchComboBox();
    void updatePlaceComboBox();
};

#endif // TICKETSUI_H
