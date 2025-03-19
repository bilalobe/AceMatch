#include "seatsui.h"
#include "qsqldatabase.h"
#include "ui_seatsui.h"
#include <QMessageBox>

PlacesUI::PlacesUI(QWidget *parent, const QSqlDatabase& database) 
    : QWidget(parent), ui(new Ui::PlacesUI), db(database)
{
    ui->setupUi(this);

    // Initialize the seatsModel
    seatsModel = new QStandardItemModel(0, 3, this); // 3 columns (ID, Name, Capacity)
    seatsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    seatsModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    seatsModel->setHeaderData(2, Qt::Horizontal, tr("Capacity"));
    ui->seatsTableView->setModel(seatsModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update the seats list
    updatePlacesList(); 

    // Connect signals and slots:
    connect(ui->addPlaceButton, &QPushButton::clicked, this, &PlacesUI::addPlace);
    connect(ui->deletePlaceButton, &QPushButton::clicked, this, &PlacesUI::deletePlace);
    connect(ui->updatePlaceButton, &QPushButton::clicked, this, &PlacesUI::updatePlace);
    connect(ui->seatsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &PlacesUI::loadPlaceDetails);
}

PlacesUI::~PlacesUI() {
    delete ui;
    delete seatsModel;
}

void PlacesUI::addPlace() {
    QString name = ui->nameLineEdit->text();
    int capacity = ui->capacitySpinBox->value();

    emit placeAdded(name, capacity);

    // Clear input fields
    ui->nameLineEdit->clear();
    ui->capacitySpinBox->setValue(0);

    // Update the places list
    updatePlacesList();
}

void PlacesUI::deletePlace() {
    QModelIndexList selectedIndexes = ui->seatsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No seat selected.");
        return;
    }

    int seatId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get place ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Seat", 
                                                                 "Are you sure you want to delete this seat?",
                                                                 QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit placeDeleted(seatId);
        updatePlacesList();
        clearPlaceDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(parent());
        if (mainWindow) {
            mainWindow->statusBar()->showMessage("Seat deleted successfully.");
        }
    }
}

void PlacesUI::updatePlace() {
    QModelIndexList selectedIndexes = ui->seatsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No seat selected.");
        return;
    }

    int seatId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get place ID
    QString newName = ui->nameLineEdit->text();
    int newCapacity = ui->capacitySpinBox->value();

    emit placeUpdated(seatId, newName, newCapacity);

    // Update the places list
    updatePlacesList();
}

void PlacesUI::loadPlaceDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearPlaceDetails();
        return;
    }

    int row = index.row();
    Seat selectedPlace = seatManager->getSeats(db)[row]; // Assuming you can access places by index

    ui->idLineEdit->setText(QString::number(selectedPlace.getId()));
    ui->nameLineEdit->setText(selectedPlace.getName());
    ui->capacitySpinBox->setValue(selectedPlace.getCapacity()); // Assuming getCapacity() is a method in your Seat class

    // ... (Set values for other place detail fields) ...
}

void PlacesUI::clearPlaceDetails() {
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->capacitySpinBox->setValue(0);
    // ... (Clear other place detail fields) ...
}

void PlacesUI::updatePlacesList() {
    seatsModel->clear();
    seatsModel->setHorizontalHeaderLabels({"ID", "Name", "Capacity"}); 

    QList<Seat> seats = seatManager->getSeats(db); 

    for (const Seat& place : places) {
        int row = seatsModel->rowCount();
        seatsModel->insertRow(row);
        seatsModel->setData(seatsModel->index(row, 0), place.getId());
        seatsModel->setData(seatsModel->index(row, 1), place.getName());
        seatsModel->setData(seatsModel->index(row, 2), place.getCapacity());

        // Optional: Store the place ID in the Qt::UserRole of the first column
        seatsModel->setData(seatsModel->index(row, 0), place.getId(), Qt::UserRole); 
    }
}

void PlacesUI::searchPlace(const QString& searchTerm) {
    seatsModel->clear(); // Clear the existing model data
    seatsModel->setHorizontalHeaderLabels({"ID", "Name", "Capacity"});

    QList<Seat> places = seatManager->getSeats(db); 

    for (const Seat& place : places) {
        if (place.getName().contains(searchTerm, Qt::CaseInsensitive) ||
            QString::number(place.getId()).contains(searchTerm)) { // Search ID as well
            int row = seatsModel->rowCount();
            seatsModel->insertRow(row);
            seatsModel->setData(seatsModel->index(row, 0), place.getId());
            seatsModel->setData(seatsModel->index(row, 1), place.getName());
            seatsModel->setData(seatsModel->index(row, 2), place.getCapacity());
            // Optional: Store the place ID in the Qt::UserRole of the first column
            seatsModel->setData(seatsModel->index(row, 0), place.getId(), Qt::UserRole); 
        }
    }
}
