#include "ticketsui.h"
#include "ui_ticketsui.h"
#include <QMessageBox>

TicketsUI::TicketsUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::TicketsUI), db(database)
{
    ui->setupUi(this);

    // Initialize the ticketsModel
    ticketsModel = new QStandardItemModel(0, 6, this); // Adjust column count as needed
    ticketsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    ticketsModel->setHeaderData(1, Qt::Horizontal, tr("Client"));
    ticketsModel->setHeaderData(2, Qt::Horizontal, tr("Match"));
    ticketsModel->setHeaderData(3, Qt::Horizontal, tr("Place"));
    ticketsModel->setHeaderData(4, Qt::Horizontal, tr("Price"));
    ticketsModel->setHeaderData(5, Qt::Horizontal, tr("Status"));
    // ... (Add more headers if needed) ...
    ui->ticketsTableView->setModel(ticketsModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update combo boxes and tickets list
    updateClientComboBox();
    updateMatchComboBox();
    updatePlaceComboBox();
    updateTicketsList();

    // Connect signals and slots:
    connect(ui->addTicketButton, &QPushButton::clicked, this, &TicketsUI::addTicket);
    connect(ui->deleteTicketButton, &QPushButton::clicked, this, &TicketsUI::deleteTicket);
    connect(ui->updateTicketButton, &QPushButton::clicked, this, &TicketsUI::updateTicket);
    connect(ui->ticketsTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TicketsUI::loadTicketDetails);
}

TicketsUI::~TicketsUI() {
    delete ui;
    delete ticketsModel;
}

void TicketsUI::addTicket() {
    int clientId = ui->clientComboBox->currentData().toInt();
    int matchId = ui->matchComboBox->currentData().toInt();
    int placeId = ui->placeComboBox->currentData().toInt();
    double price = ui->priceLineEdit->text().toDouble();
    QString status = ui->statusComboBox->currentText();

    emit ticketAdded(clientId, matchId, placeId, price, status);

    // Clear input fields
    // ...

    // Update the tickets list
    updateTicketsList();
}

void TicketsUI::deleteTicket() {
    // ... (Implementation similar to delete functions in other tabs) ...
}

void TicketsUI::updateTicket() {
    // ... (Implementation similar to update functions in other tabs) ...
}

void TicketsUI::loadTicketDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearTicketDetails();
        return;
    }

    int row = index.row();
    // Get the ticket data
    Ticket selectedTicket = gestionTickets->getTickets(db)[row]; // Adjust to get tickets data

    ui->idLineEdit->setText(QString::number(selectedTicket.getId()));
    // Set selected client in clientComboBox
    int clientIndex = ui->clientComboBox->findData(selectedTicket.getClientId());
    if (clientIndex != -1) {
        ui->clientComboBox->setCurrentIndex(clientIndex);
    }
    // Set selected match in matchComboBox
    int matchIndex = ui->matchComboBox->findData(selectedTicket.getMatchId());
    if (matchIndex != -1) {
        ui->matchComboBox->setCurrentIndex(matchIndex);
    }
    // Set selected place in placeComboBox
    int placeIndex = ui->placeComboBox->findData(selectedTicket.getPlaceId());
    if (placeIndex != -1) {
        ui->placeComboBox->setCurrentIndex(placeIndex);
    }
    ui->priceLineEdit->setText(QString::number(selectedTicket.getPrice()));
    // Set selected status in statusComboBox
    int statusIndex = ui->statusComboBox->findText(selectedTicket.getStatus());
    if (statusIndex != -1) {
        ui->statusComboBox->setCurrentIndex(statusIndex);
    }

    // ... (Set values for other ticket detail fields) ...
}

void TicketsUI::clearTicketDetails() {
    // ... (Clear all input fields and labels in the details section) ...
}

void TicketsUI::updateTicketsList() {
    ticketsModel->clear();
    ticketsModel->setHorizontalHeaderLabels({"ID", "Client", "Match", "Place", "Price", "Status"});

    QList<Ticket> tickets = gestionTickets->getTickets(db);

    for (const Ticket& ticket : tickets) {
        int row = ticketsModel->rowCount();
        ticketsModel->insertRow(row);

        // Use the correct data from your Ticket class
        reservationsModel->setData(ticketsModel->index(row, 0), ticket.getId());
        reservationsModel->setData(ticketsModel->index(row, 1), ticket.getClient().getNom()); // Assuming you can access the client name
        reservationsModel->setData(ticketsModel->index(row, 2), ticket.getMatch().getNom()); // Assuming you can access the match name
        reservationsModel->setData(ticketsModel->index(row, 3), ticket.getPlace().getNom()); // Assuming you can access the place name
        reservationsModel->setData(ticketsModel->index(row, 4), ticket.getPrice());
        reservationsModel->setData(ticketsModel->index(row, 5), ticket.getStatus());

        // Optional: Store the ticket ID in the Qt::UserRole of the first column
        reservationsModel->setData(ticketsModel->index(row, 0), ticket.getId(), Qt::UserRole);
    }
}

void TicketsUI::updateClientComboBox() {
    ui->clientComboBox->clear();
    // Get clients (you'll likely need a GestionClients or similar)
    QList<Client> clients = gestionClients->getClients(db);  // Assuming you have a getClients() function
    for (const Client& client : clients) {
        ui->clientComboBox->addItem(client.getNom(), client.getId()); // Add client name and ID to combo box
    }
}

void TicketsUI::updateMatchComboBox() {
    ui->matchComboBox->clear();
    // Get matches
    QList<Match> matches = gestionJoueurs->getMatches(db);
    for (const Match& match : matches) {
        QString matchDescription = QString("%1 vs %2").arg(match.getJoueur1().getNom(), match.getJoueur2().getNom());
        ui->matchComboBox->addItem(matchDescription, match.getId()); // Add match name and ID to combo box
    }
}

void TicketsUI::updatePlaceComboBox() {
    ui->placeComboBox->clear();
    // Get places
    QList<Place> places = gestionPlaces->getPlaces(db);
    for (const Place& place : places) {
        ui->placeComboBox->addItem(place.getNom(), place.getId()); // Add place name and ID to combo box
    }
}
