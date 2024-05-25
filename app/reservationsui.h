#ifndef RESERVATIONSUI_H
#define RESERVATIONSUI_H

#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class ReservationsUI; }
QT_END_NAMESPACE

class ReservationsUI : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationsUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~ReservationsUI();

signals:
    void reservationAdded(int clientId, int placeId, const QDateTime& dateTime);
    void reservationDeleted(int reservationId);
    void reservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);

private slots:
    void addReservation();
    void deleteReservation();
    void updateReservation();
    void loadReservationDetails(const QModelIndex& index);
    void clearReservationDetails();

private:
    Ui::ReservationsUI *ui;
    QSqlDatabase db;
    QStandardItemModel* reservationsModel;

    void updateReservationsList();
    void updateClientComboBox();
    void updatePlaceComboBox();
};

#endif // RESERVATIONSUI_H
