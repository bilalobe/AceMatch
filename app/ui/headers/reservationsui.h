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

private slots:
    void addReservation();
    void deleteReservation();
    void updateReservation();
    void searchReservations(QString& searchTerm);
    void loadReservationDetails(const QModelIndex& index);
    void clearReservationDetails();

private:
    Ui::ReservationsUI *ui;
    QSqlDatabase db;
    QStandardItemModel* reservationsModel;

    void updateReservationsList();
    void updateClientComboBox();
    void updatePlaceComboBox();
    void on_clientIdComboBox_currentIndexChanged(int index);
    void on_placeIdComboBox_currentIndexChanged(int index);

};

#endif // RESERVATIONSUI_H
