#include "reservationsui.h"
#include "ui_reservationsui.h"

ReservationsUI::ReservationsUI(QWidget *parent)
    : QWidget(parent), ui(new Ui::ReservationsUI)
{
    ui->setupUi(this);
}

// Initialize the reservationsModel
reservationsModel = new QStandardItemModel(0, 4, this);
reservationsModel->setHeaderData(0, Qt::Horizontal, tr("Client ID"));
reservationsModel->setHeaderData(1, Qt::Horizontal, tr("Place ID"));
reservationsModel->setHeaderData(2, Qt::Horizontal, tr("Date Time"));
reservationsModel->setHeaderData(3, Qt::Horizontal, tr("Status"));
ui->reservationsTableView->setModel(reservationsModel);

// Connect signals and slots
connect(ui->addReservationButton, &QPushButton::clicked, this, &ReservationsUI::addReservation);
connect(ui->deleteReservationButton, &QPushButton::clicked, this, &ReservationsUI::deleteReservation);
connect(ui->updateReservationButton, &QPushButton::clicked, this, &ReservationsUI::updateReservation);
connect(ui->reservationsTableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &ReservationsUI::loadReservationDetails);
connect(ui->clearButton, &QPushButton::clicked, this, &ReservationsUI::clearReservationDetails);

// Update the reservations list
updateReservationsList();
}

ReservationsUI::~ReservationsUI()
{
    delete ui;
}

void ReservationsUI::addReservation()
{
    // Get the client ID
    int clientId = ui->clientIdLineEdit->text().toInt();

    // Get the place ID
    int placeId = ui->placeIdLineEdit->text().toInt();

    // Get the date and time
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    // Emit the signal to add the reservation
    emit reservationAdded(clientId, placeId, dateTime);

    // Update the reservations list
    updateReservationsList();

    // Clear the input fields
    ui->clientIdLineEdit->clear();
    ui->placeIdLineEdit->clear();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

void ReservationsUI::deleteReservation()
{ // Get the selected reservation
    QModelIndexList selectedIndexes = ui->reservationsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No reservation selected.");
        return;
    }

    // Get the reservation ID
    int reservationId = selectedIndexes.at(0).data(Qt::UserRole).toInt();

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Reservation",
                                                              "Are you sure you want to delete this reservation?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        // Emit the signal to delete the reservation
        emit reservationDeleted(reservationId);

        // Update the reservations list
        updateReservationsList();

        // Clear the reservation details
        clearReservationDetails();
    }
}

void ReservationsUI::updateReservation()
{
    // Get the selected reservation
    QModelIndexList selectedIndexes = ui->reservationsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No reservation selected.");
        return;
    }

    // Get the reservation ID
    int reservationId = selectedIndexes.at(0).data(Qt::UserRole).toInt();

    // Get the updated client ID
    int clientId = ui->clientIdLineEdit->text().toInt();

    // Get the updated place ID
    int placeId = ui->placeIdLineEdit->text().toInt();

    // Get the updated date and time
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    // Emit the signal to update the reservation
    emit reservationUpdated(reservationId, clientId, placeId, dateTime);

    // Update the reservations list
    updateReservationsList();
}

void ReservationsUI::loadReservationDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearReservationDetails();
        return;
    }

    // Get the reservation ID
    int reservationId = index.data(Qt::UserRole).toInt();

    // Get the reservation details
    Reservation reservation = gestionReservations->getReservation(db, reservationId);

    // Display the reservation details
    ui->clientIdLineEdit->setText(QString::number(reservation.clientId));
    ui->placeIdLineEdit->setText(QString::number(reservation.placeId));
    ui->dateTimeEdit->setDateTime(reservation.dateTime);
}
