#include "placesui.h"
#include "ui_placesui.h"
#include <QMessageBox>

PlacesUI::PlacesUI(QWidget *parent, const QSqlDatabase& database) 
    : QWidget(parent), ui(new Ui::PlacesUI), db(database)
{
    ui->setupUi(this);

    // Get access to GestionPlaces
    gestionPlaces = dynamic_cast<MainWindow*>(parent)->getGestionPlaces(); 
    if (!gestionPlaces) {
        qDebug() << "Error: Could not access GestionPlaces.";
        return; 
    }

    // Initialize the placesModel
    placesModel = new QStandardItemModel(0, 3, this); // 3 columns (ID, Name, Capacity)
    placesModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    placesModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    placesModel->setHeaderData(2, Qt::Horizontal, tr("Capacity"));
    ui->placesTableView->setModel(placesModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update the places list
    updatePlacesList(); 

    // Connect signals and slots:
    connect(ui->addPlaceButton, &QPushButton::clicked, this, &PlacesUI::addPlace);
    connect(ui->deletePlaceButton, &QPushButton::clicked, this, &PlacesUI::deletePlace);
    connect(ui->updatePlaceButton, &QPushButton::clicked, this, &PlacesUI::updatePlace);
    connect(ui->placesTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &PlacesUI::loadPlaceDetails);
}

PlacesUI::~PlacesUI() {
    delete ui;
    delete placesModel;
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
    QModelIndexList selectedIndexes = ui->placesTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No place selected.");
        return;
    }

    int placeId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get place ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Place", 
                                                              "Are you sure you want to delete this place?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit placeDeleted(placeId);
        updatePlacesList();
        clearPlaceDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(parent());
        if (mainWindow) {
            mainWindow->statusBar()->showMessage("Place deleted successfully.");
        }
    }
}

void PlacesUI::updatePlace() {
    QModelIndexList selectedIndexes = ui->placesTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No place selected.");
        return;
    }

    int placeId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get place ID
    QString newName = ui->nameLineEdit->text();
    int newCapacity = ui->capacitySpinBox->value();

    emit placeUpdated(placeId, newName, newCapacity);

    // Update the places list
    updatePlacesList();
}

void PlacesUI::loadPlaceDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearPlaceDetails();
        return;
    }

    int row = index.row();
    Place selectedPlace = gestionPlaces->getPlaces(db)[row]; // Assuming you can access places by index

    ui->idLineEdit->setText(QString::number(selectedPlace.getId()));
    ui->nameLineEdit->setText(selectedPlace.getNom());
    ui->capacitySpinBox->setValue(selectedPlace.getCapacity()); // Assuming getCapacity() is a method in your Place class
    ui->placesTableView->setFocus();
}

void PlacesUI::clearPlaceDetails() {
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->capacitySpinBox->setValue(0);
    // ... (Clear other place detail fields) ...
}

void PlacesUI::updatePlacesList() {
    placesModel->clear();
    placesModel->setHorizontalHeaderLabels({"ID", "Name", "Capacity"}); 

    QList<Place> places = gestionPlaces->getPlaces(db); 

    for (const Place& place : places) {
        int row = placesModel->rowCount();
        placesModel->insertRow(row);
        placesModel->setData(placesModel->index(row, 0), place.getId());
        placesModel->setData(placesModel->index(row, 1), place.getNom());
        placesModel->setData(placesModel->index(row, 2), place.getCapacity());

        // Optional: Store the place ID in the Qt::UserRole of the first column
        placesModel->setData(placesModel->index(row, 0), place.getId(), Qt::UserRole);
    }
}

