#include "reservationsui.h"
#include "qsqldatabase.h"
#include "ui_reservationsui.h"

ReservationsUI::ReservationsUI(QWidget *parent)
    : QWidget(parent), ui(new Ui::ReservationsUI)
{
    ui->setupUi(this);
}

ReservationsUI::ReservationsUI(QWidget *parent, const QSqlDatabase &database)
{
    ui = new Ui::ReservationsUI;
    ui->setupUi(this);
    db = database;
    reservationManager = new ReservationManager(db);
}

// Initialize the reservationsModel
reservationsModel = new QStandardItemModel(0, 4, this);
reservationsModel->setHeaderData(0, Qt::Horizontal, tr("Client ID"));
reservationsModel->setHeaderData(1, Qt::Horizontal, tr("Seat ID"));
reservationsModel->setHeaderData(2, Qt::Horizontal, tr("Date Time"));
reservationsModel->setHeaderData(3, Qt::Horizontal, tr("Status"));
ui->reservationsTableView->setModel(reservationsModel);

// Connect signals and slots
connect(ui->addReservationButton, &QPushButton::clicked, this, &ReservationsUI::addReservation);
connect(ui->deleteReservationButton, &QPushButton::clicked, this, &ReservationsUI::deleteReservation);
connect(ui->updateReservationButton, &QPushButton::clicked, this, &ReservationsUI::updateReservation);
connect(ui->reservationsTableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &ReservationsUI::loadReservationDetails);
connect(ui->clearButton, &QPushButton::clicked, this, &ReservationsUI::clearReservationDetails);


ReservationsUI::~ReservationsUI()
{
    delete ui;
}

void ReservationsUI::addReservation()
{
    // Get the client ID
    int clientId = ui->clientIdLineEdit->text().toInt();

    // Get the seat ID
    int seatId = ui->placeIdLineEdit->text().toInt();

    // Get the date and time
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    // Emit the signal to add the reservation
    emit reservationAdded(clientId, seatId, dateTime);

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

    // Get the updated seat ID
    int seatId = ui->placeIdLineEdit->text().toInt();

    // Get the updated date and time
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    // Emit the signal to update the reservation
    emit reservationUpdated(reservationId, clientId, seatId, dateTime);

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
    Reservation reservation = reservationManager->getReservation(db, reservationId);

    // Display the reservation details
    ui->clientIdLineEdit->setText(QString::number(reservation.clientId));
    ui->placeIdLineEdit->setText(QString::number(reservation.seatId));
    ui->dateTimeEdit->setDateTime(reservation.dateTime);
}

void ReservationsUI::searchReservations(const QString& searchTerm) {
        // Clear the existing model data
    reservationsModel->clear();

    // Set the horizontal header labels
    reservationsModel->setHorizontalHeaderLabels({"Client ID", "Seat ID", "Date Time", "Status"});

    // Get the reservations from the database
    QList<Reservation> reservations = reservationManager->getReservations(db, searchTerm);

    // Add the reservations to the model
    for (const Reservation& reservation : reservations) {
        int row = reservationsModel->rowCount();
        reservationsModel->insertRow(row);

        // Set the data for each column
        reservationsModel->setData(reservationsModel->index(row, 0), reservation.clientId);
        reservationsModel->setData(reservationsModel->index(row, 1), reservation.seatId);
        reservationsModel->setData(reservationsModel->index(row, 2), reservation.dateTime);
        reservationsModel->setData(reservationsModel->index(row, 3), reservation.status);

        // Set the reservation ID in the Qt::UserRole of the first column
        reservationsModel->setData(reservationsModel->index(row, 0), reservation.id, Qt::UserRole);
    }
}

void ReservationsUI::clearReservationDetails()
{
    ui->clientIdLineEdit->clear();
    ui->seatIdLineEdit->clear();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

void ReservationsUI::updateReservationsList()
{
    // Clear the existing model data
    reservationsModel->clear();

    // Set the horizontal header labels
    reservationsModel->setHorizontalHeaderLabels({"Client ID", "Seat ID", "Date Time", "Status"});

    // Get the reservations from the database
    QList<Reservation> reservations = reservationManager->getReservations(db);

    // Add the reservations to the model
    for (const Reservation& reservation : reservations) {
        int row = reservationsModel->rowCount();
        reservationsModel->insertRow(row);

        // Set the data for each column
        reservationsModel->setData(reservationsModel->index(row, 0), reservation.clientId);
        reservationsModel->setData(reservationsModel->index(row, 1), reservation.seatId);
        reservationsModel->setData(reservationsModel->index(row, 2), reservation.dateTime);
        reservationsModel->setData(reservationsModel->index(row, 3), reservation.status);

        // Set the reservation ID in the Qt::UserRole of the first column
        reservationsModel->setData(reservationsModel->index(row, 0), reservation.id, Qt::UserRole);
    }
}

void ReservationsUI::updateClientComboBox()
{
    // Clear the existing items
    ui->clientIdComboBox->clear();
   // Add the client IDs to the combo box
    QList<int> clientIds = clientManager->getClientIds(db);
    for (int clientId : clientIds) {
        ui->clientIdComboBox->addItem(QString::number(clientId));
    }
}

void ReservationsUI::updatePlaceComboBox()
{
    // Clear the existing items
    ui->placeIdComboBox->clear();

    // Add the place IDs to the combo box
    QList<int> placeIds = seatManager->getSeatIds(db);
    for (int seatId : placeIds) {
        ui->placeIdComboBox->addItem(QString::number(seatId));
    }
}

void ReservationsUI::on_clientIdComboBox_currentIndexChanged(int index)
{
    // Get the selected client ID
    int clientId = ui->clientIdComboBox->itemText(index).toInt();

    // Update the client ID line edit
    ui->clientIdLineEdit->setText(QString::number(clientId));
}

void ReservationsUI::on_placeIdComboBox_currentIndexChanged(int index)
{
    // Get the selected place ID
    int seatId = ui->placeIdComboBox->itemText(index).toInt();

    // Update the place ID line edit
    ui->placeIdLineEdit->setText(QString::number(seatId));
}

void ReservationsUI::on_searchButton_clicked()
{
    // Get the search term
    QString searchTerm = ui->searchLineEdit->text();

    // Search for reservations
    searchReservations(searchTerm);
}

