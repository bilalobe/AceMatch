#include "terrainsui.h"
#include "ui_terrainsui.h"
#include <QMessageBox>

TerrainUI::TerrainUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::TerrainUI), db(database)
{
    ui->setupUi(this);

    // Initialize the terrainsModel
    terrainsModel = new QStandardItemModel(0, 3, this); // 3 columns (ID, Name, Type) - adjust if needed
    terrainsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    terrainsModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    terrainsModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    ui->terrainsTableView->setModel(terrainsModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update the terrains list
    updateTerrainsList();

    // Connect signals and slots:
    connect(ui->addTerrainButton, &QPushButton::clicked, this, &TerrainUI::addTerrain);
    connect(ui->deleteTerrainButton, &QPushButton::clicked, this, &TerrainUI::deleteTerrain);
    connect(ui->updateTerrainButton, &QPushButton::clicked, this, &TerrainUI::updateTerrain);
    connect(ui->terrainsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TerrainUI::loadTerrainDetails);
}

TerrainUI::~TerrainUI() {
    delete ui;
    delete terrainsModel;
}

void TerrainUI::addTerrain() {
    QString name = ui->nameLineEdit->text();
    QString type = ui->typeLineEdit->text(); // Adjust based on your Terrain class

    emit terrainAdded(name, type); // Emit the signal with the correct parameters

    // Clear input fields
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear(); // Clear the type field

    // Update the terrains list
    updateTerrainsList();
}

void TerrainUI::deleteTerrain() {
    // ... (Implementation similar to deletePlace() in PlacesUI) ...
}

void TerrainUI::updateTerrain() {
    // ... (Implementation similar to updatePlace() in PlacesUI) ...
}

void TerrainUI::loadTerrainDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearTerrainDetails();
        return;
    }

    int row = index.row();

    // Get the selected terrain from your GestionTerrains (or wherever you store terrain data)
    Terrain selectedTerrain = gestionTerrains->getTerrains(db)[row]; // Adjust to your actual method

    ui->idLineEdit->setText(QString::number(selectedTerrain.getId())); // Assuming your Terrain class has an getId() method
    ui->nameLineEdit->setText(selectedTerrain.getNom()); // Adjust based on your Terrain class
    ui->typeLineEdit->setText(selectedTerrain.getType()); // Adjust based on your Terrain class

    // ... (Set values for other terrain detail fields) ...
}

void TerrainUI::clearTerrainDetails() {
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear();
    // ... (Clear other terrain detail fields) ...
}

void TerrainUI::updateTerrainsList() {
    terrainsModel->clear();
    terrainsModel->setHorizontalHeaderLabels({"ID", "Name", "Type"}); // Adjust if needed

    // Get terrains from GestionTerrains (or wherever you store terrain data)
    QList<Terrain> terrains = gestionTerrains->getTerrains(db); // Adjust to your actual method

    for (const Terrain& terrain : terrains) {
        int row = terrainsModel->rowCount();
        terrainsModel->insertRow(row);

        // Use the correct data from your Terrain class
        terrainsModel->setData(terrainsModel->index(row, 0), terrain.getId());
        terrainsModel->setData(terrainsModel->index(row, 1), terrain.getNom());
        terrainsModel->setData(terrainsModel->index(row, 2), terrain.getType());

        // Optional: Store the terrain ID in the Qt::UserRole of the first column
        terrainsModel->setData(terrainsModel->index(row, 0), terrain.getId(), Qt::UserRole);
    }
}
