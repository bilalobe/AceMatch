#include "courtsui.h"
#include "ui_courtsui.h"
#include <QMessageBox>

TerrainUI::TerrainUI(QWidget *parent, const QSqlDatabase &database)
    : QWidget(parent), ui(new Ui::TerrainUI), db(database)
{
    ui->setupUi(this);

    // Initialize the courtsModel
    courtsModel = new QStandardItemModel(0, 3, this); // 3 columns (ID, Name, Type) - adjust if needed
    courtsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    courtsModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    courtsModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    ui->courtsTableView->setModel(courtsModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update the courts list
    updateTerrainsList();

    // Connect signals and slots:
    connect(ui->addTerrainButton, &QPushButton::clicked, this, &TerrainUI::addTerrain);
    connect(ui->deleteTerrainButton, &QPushButton::clicked, this, &TerrainUI::deleteTerrain);
    connect(ui->updateTerrainButton, &QPushButton::clicked, this, &TerrainUI::updateTerrain);
    connect(ui->courtsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TerrainUI::loadTerrainDetails);
}

TerrainUI::~TerrainUI()
{
    delete ui;
    delete courtsModel;
}

void TerrainUI::addTerrain()
{
    QString name = ui->nameLineEdit->text();
    QString type = ui->typeLineEdit->text(); // Adjust based on your Court class

    emit terrainAdded(name, type); // Emit the signal with the correct parameters

    // Clear input fields
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear(); // Clear the type field

    // Update the terrains list
    updateTerrainsList();
}

void TerrainUI::deleteTerrain()
{
    QModelIndexList selectedIndexes = ui->courtsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No court selected.");
        return;
    }

    int terrainId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get terrain ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Court",
                                                              "Are you sure you want to delete this court?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        emit terrainDeleted(terrainId);
        updateTerrainsList();
        clearTerrainDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow *mainWindow = dynamic_cast<MainWindow *>(parent());
        if (mainWindow)
        {
            mainWindow->statusBar()->showMessage("Court deleted successfully.");
        }
    }
}

void TerrainUI::searchTerrain(const QString& searchTerm) {
       courtsModel->clear(); // Clear the existing model data
    courtsModel->setHorizontalHeaderLabels({"ID", "Name", "Type"}); // Adjust if needed

    // Get courts from CourtManager (or wherever you store terrain data)
    QList<Court> terrains = courtManager->getCourts(db); // Adjust to your actual method

    for (const Court &terrain : terrains)
    {
        if (terrain.getName().contains(searchTerm, Qt::CaseInsensitive) ||
            QString::number(terrain.getId()).contains(searchTerm)) { // Search ID as well
            int row = courtsModel->rowCount();
            courtsModel->insertRow(row);

            // Use the correct data from your Court class
            courtsModel->setData(courtsModel->index(row, 0), terrain.getId());
            courtsModel->setData(courtsModel->index(row, 1), terrain.getName());
            courtsModel->setData(courtsModel->index(row, 2), terrain.getType());

            // Optional: Store the terrain ID in the Qt::UserRole of the first column
            courtsModel->setData(courtsModel->index(row, 0), terrain.getId(), Qt::UserRole);
        }
    }
}


void TerrainUI::updateTerrain()
{
    QModelIndexList selectedIndexes = ui->courtsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No court selected.");
        return;
    }

    int terrainId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get terrain ID
    QString newName = ui->nameLineEdit->text();
    QString newType = ui->typeLineEdit->text(); // Adjust based on your Court class

    emit terrainUpdated(terrainId, newName, newType); // Emit the signal with the correct parameters

    // Update the terrains list
    updateTerrainsList();
}

void TerrainUI::loadTerrainDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearTerrainDetails();
        return;
    }

    int row = index.row();

    // Get the selected terrain from your CourtManager (or wherever you store terrain data)
    Court selectedTerrain = courtManager->getCourts(db)[row]; // Adjust to your actual method

    ui->idLineEdit->setText(QString::number(selectedTerrain.getId())); // Assuming your Court class has an getId() method
    ui->nameLineEdit->setText(selectedTerrain.getName());               // Adjust based on your Court class
    ui->typeLineEdit->setText(selectedTerrain.getType());              // Adjust based on your Court class

    // ... (Set values for other terrain detail fields) ...
}

void TerrainUI::loadTerrainDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearTerrainDetails();
        return;
    }

    int row = index.row();

    // Get the selected terrain from your CourtManager (or wherever you store terrain data)
    Court selectedTerrain = courtManager->getCourts(db)[row]; // Adjust to your actual method

    ui->idLineEdit->setText(QString::number(selectedTerrain.getId())); // Assuming your Court class has an getId() method
    ui->nameLineEdit->setText(selectedTerrain.getName());               // Adjust based on your Court class
    ui->typeLineEdit->setText(selectedTerrain.getType());              // Adjust based on your Court class

    // ... (Set values for other terrain detail fields) ...
}

void TerrainUI::clearTerrainDetails()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear();
    // ... (Clear other terrain detail fields) ...
}

void TerrainUI::updateTerrainsList()
{
    courtsModel->clear();
    courtsModel->setHorizontalHeaderLabels({"ID", "Name", "Type"}); // Adjust if needed

    // Get terrains from CourtManager (or wherever you store terrain data)
    QList<Court> terrains = courtManager->getCourts(db); // Adjust to your actual method

    for (const Court &terrain : terrains)
    {
        int row = courtsModel->rowCount();
        courtsModel->insertRow(row);

        // Use the correct data from your Court class
        courtsModel->setData(courtsModel->index(row, 0), terrain.getId());
        courtsModel->setData(courtsModel->index(row, 1), terrain.getName());
        courtsModel->setData(courtsModel->index(row, 2), terrain.getType());

        // Optional: Store the terrain ID in the Qt::UserRole of the first column
        courtsModel->setData(courtsModel->index(row, 0), terrain.getId(), Qt::UserRole);
    }
}

