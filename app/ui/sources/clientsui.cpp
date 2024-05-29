#include "clientsui.h"
#include "qsqldatabase.h"
#include "ui_clientsui.h"
#include <QMessageBox>

ClientsUI::ClientsUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::ClientsUI), db(database)
{
    ui->setupUi(this);

    // Initialize the clientsModel
    clientsModel = new QStandardItemModel(0, 4, this); // 4 columns (ID, Name, Email, Phone Number)
    clientsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    clientsModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    clientsModel->setHeaderData(2, Qt::Horizontal, tr("Email"));
    clientsModel->setHeaderData(3, Qt::Horizontal, tr("Phone Number"));
    ui->clientsTableView->setModel(clientsModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update the clients list
    updateClientsList();

    // Connect signals and slots:
    connect(ui->addClientButton, &QPushButton::clicked, this, &ClientsUI::addClient);
    connect(ui->deleteClientButton, &QPushButton::clicked, this, &ClientsUI::deleteClient);
    connect(ui->updateClientButton, &QPushButton::clicked, this, &ClientsUI::updateClient);
    connect(ui->clientsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ClientsUI::loadClientDetails);
}

ClientsUI::~ClientsUI() {
    delete ui;
    delete clientsModel;
}


void ClientsUI::addClient() {
    QString name = ui->nameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString phoneNumber = ui->phoneNumberLineEdit->text();

    emit clientAdded(name, email, phoneNumber);

    // Clear input fields
    ui->nameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->phoneNumberLineEdit->clear();

    // Update the clients list
    updateClientsList();
}

void ClientsUI::deleteClient() {
       QModelIndexList selectedIndexes = ui->clientsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No client selected.");
        return;
    }

    int clientId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get client ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Client",
                                                              "Are you sure you want to delete this client?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit clientDeleted(clientId);
        updateClientsList();
        clearClientDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(parent());
        if (mainWindow) {
            mainWindow->statusBar()->showMessage("Client deleted successfully.");
        }
    }
}

void ClientsUI::updateClient() {
    QModelIndexList selectedIndexes = ui->clientsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No client selected.");
        return;
    }

    int clientId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get client ID
    QString newName = ui->nameLineEdit->text();
    QString newEmail = ui->emailLineEdit->text();
    QString newPhoneNumber = ui->phoneNumberLineEdit->text();

    emit clientUpdated(clientId, newName, newEmail, newPhoneNumber);

    // Update the clients list
    updateClientsList();
}


void ClientsUI::loadClientDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearClientDetails();
        return;
    }

    int row = index.row();

    // Get the selected client from your GestionClients (or wherever you store client data)
    Client selectedClient = gestionClients->getClients(db)[row];

    ui->idLineEdit->setText(QString::number(selectedClient.getId()));
    ui->nameLineEdit->setText(selectedClient.getNom());
    ui->emailLineEdit->setText(selectedClient.getEmail());
    ui->phoneNumberLineEdit->setText(selectedClient.getPhoneNumber());

    // ... (Set values for other client detail fields) ...
}

void ClientsUI::clearClientDetails() {
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
}

void ClientsUI::updateClientsList() {
    clientsModel->clear();
    clientsModel->setHorizontalHeaderLabels({"ID", "Name", "Email", "Phone Number"});

    QList<Client> clients = gestionClients->getClients(db);

    for (const Client& client : clients) {
        int row = clientsModel->rowCount();
        clientsModel->insertRow(row);

        // Use the correct data from your Client class
        clientsModel->setData(clientsModel->index(row, 0), client.getId());
        clientsModel->setData(clientsModel->index(row, 1), client.getNom());
        clientsModel->setData(clientsModel->index(row, 2), client.getEmail());
        clientsModel->setData(clientsModel->index(row, 3), client.getPhoneNumber());

        // Optional: Store the client ID in the Qt::UserRole of the first column
        clientsModel->setData(clientsModel->index(row, 0), client.getId(), Qt::UserRole);
    }
}

void ClientsUI::searchClient(const QString& searchTerm) {
    clientsModel->clear(); // Clear the existing model data
    clientsModel->setHorizontalHeaderLabels({"ID", "Name", "Email", "Phone Number"});

    // Get clients from GestionClients (or wherever you store client data)
    QList<Client> clients = gestionClients->getClients(db); // Adjust to your actual method

    for (const Client &client : clients)
    {
        if (client.getNom().contains(searchTerm, Qt::CaseInsensitive) ||
            client.getEmail().contains(searchTerm, Qt::CaseInsensitive) ||
            client.getPhoneNumber().contains(searchTerm, Qt::CaseInsensitive) ||
            QString::number(client.getId()).contains(searchTerm)) { // Search ID as well
            int row = clientsModel->rowCount();
            clientsModel->insertRow(row);

            // Use the correct data from your Client class
            clientsModel->setData(clientsModel->index(row, 0), client.getId());
            clientsModel->setData(clientsModel->index(row, 1), client.getNom());
            clientsModel->setData(clientsModel->index(row, 2), client.getEmail());
            clientsModel->setData(clientsModel->index(row, 3), client.getPhoneNumber());

            // Optional: Store the client ID in the Qt::UserRole of the first column
            clientsModel->setData(clientsModel->index(row, 0), client.getId(), Qt::UserRole);
        }
    }
}

void ClientsUI::clearSearch() {
    ui->searchLineEdit->clear();
    updateClientsList();
}

