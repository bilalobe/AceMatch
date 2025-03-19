#include "courtsui.h"
#include "ui_courtsui.h"
#include <QMessageBox>

CourtUI::CourtUI(QWidget *parent, const QSqlDatabase &database)
    : QWidget(parent), ui(new Ui::CourtUI), db(database)
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
    updateCourtsList();

    // Connect signals and slots:
    connect(ui->addCourtButton, &QPushButton::clicked, this, &CourtUI::addCourt);
    connect(ui->deleteCourtButton, &QPushButton::clicked, this, &CourtUI::deleteCourt);
    connect(ui->updateCourtButton, &QPushButton::clicked, this, &CourtUI::updateCourt);
    connect(ui->courtsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &CourtUI::loadCourtDetails);
}

CourtUI::~CourtUI()
{
    delete ui;
    delete courtsModel;
}

void CourtUI::addCourt()
{
    QString name = ui->nameLineEdit->text();
    QString type = ui->typeLineEdit->text(); // Adjust based on your Court class

    emit CourtAdded(name, type); // Emit the signal with the correct parameters

    // Clear input fields
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear(); // Clear the type field

    // Update the Courts list
    updateCourtsList();
}

void CourtUI::deleteCourt()
{
    QModelIndexList selectedIndexes = ui->courtsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No court selected.");
        return;
    }

    int CourtId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get Court ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Court",
                                                              "Are you sure you want to delete this court?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        emit CourtDeleted(CourtId);
        updateCourtsList();
        clearCourtDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow *mainWindow = dynamic_cast<MainWindow *>(parent());
        if (mainWindow)
        {
            mainWindow->statusBar()->showMessage("Court deleted successfully.");
        }
    }
}

void CourtUI::searchCourt(const QString& searchTerm) {
       courtsModel->clear(); // Clear the existing model data
    courtsModel->setHorizontalHeaderLabels({"ID", "Name", "Type"}); // Adjust if needed

    // Get courts from CourtManager (or wherever you store Court data)
    QList<Court> Courts = courtManager->getCourts(db); // Adjust to your actual method

    for (const Court &Court : Courts)
    {
        if (Court.getName().contains(searchTerm, Qt::CaseInsensitive) ||
            QString::number(Court.getId()).contains(searchTerm)) { // Search ID as well
            int row = courtsModel->rowCount();
            courtsModel->insertRow(row);

            // Use the correct data from your Court class
            courtsModel->setData(courtsModel->index(row, 0), Court.getId());
            courtsModel->setData(courtsModel->index(row, 1), Court.getName());
            courtsModel->setData(courtsModel->index(row, 2), Court.getType());

            // Optional: Store the Court ID in the Qt::UserRole of the first column
            courtsModel->setData(courtsModel->index(row, 0), Court.getId(), Qt::UserRole);
        }
    }
}


void CourtUI::updateCourt()
{
    QModelIndexList selectedIndexes = ui->courtsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No court selected.");
        return;
    }

    int CourtId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get Court ID
    QString newName = ui->nameLineEdit->text();
    QString newType = ui->typeLineEdit->text(); // Adjust based on your Court class

    emit CourtUpdated(CourtId, newName, newType); // Emit the signal with the correct parameters

    // Update the Courts list
    updateCourtsList();
}

void CourtUI::loadCourtDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearCourtDetails();
        return;
    }

    int row = index.row();

    // Get the selected Court from your CourtManager (or wherever you store Court data)
    Court selectedCourt = courtManager->getCourts(db)[row]; // Adjust to your actual method

    ui->idLineEdit->setText(QString::number(selectedCourt.getId())); // Assuming your Court class has an getId() method
    ui->nameLineEdit->setText(selectedCourt.getName());               // Adjust based on your Court class
    ui->typeLineEdit->setText(selectedCourt.getType());              // Adjust based on your Court class

    // ... (Set values for other Court detail fields) ...
}

void CourtUI::loadCourtDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearCourtDetails();
        return;
    }

    int row = index.row();

    // Get the selected Court from your CourtManager (or wherever you store Court data)
    Court selectedCourt = courtManager->getCourts(db)[row]; // Adjust to your actual method

    ui->idLineEdit->setText(QString::number(selectedCourt.getId())); // Assuming your Court class has an getId() method
    ui->nameLineEdit->setText(selectedCourt.getName());               // Adjust based on your Court class
    ui->typeLineEdit->setText(selectedCourt.getType());              // Adjust based on your Court class

    // ... (Set values for other Court detail fields) ...
}

void CourtUI::clearCourtDetails()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->typeLineEdit->clear();
    // ... (Clear other Court detail fields) ...
}

void CourtUI::updateCourtsList()
{
    courtsModel->clear();
    courtsModel->setHorizontalHeaderLabels({"ID", "Name", "Type"}); // Adjust if needed

    // Get Courts from CourtManager (or wherever you store Court data)
    QList<Court> Courts = courtManager->getCourts(db); // Adjust to your actual method

    for (const Court &Court : Courts)
    {
        int row = courtsModel->rowCount();
        courtsModel->insertRow(row);

        // Use the correct data from your Court class
        courtsModel->setData(courtsModel->index(row, 0), Court.getId());
        courtsModel->setData(courtsModel->index(row, 1), Court.getName());
        courtsModel->setData(courtsModel->index(row, 2), Court.getType());

        // Optional: Store the Court ID in the Qt::UserRole of the first column
        courtsModel->setData(courtsModel->index(row, 0), Court.getId(), Qt::UserRole);
    }
}

