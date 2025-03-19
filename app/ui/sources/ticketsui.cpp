#include "ticketsui.h"
#include "ui_ticketsui.h"
#include <QMessageBox>

TicketsUI::TicketsUI(QWidget *parent, const QSqlDatabase &database)
    : QWidget(parent), ui(new Ui::TicketsUI), db(database)
{
    ui->setupUi(this);

    // Initialize the ticketsModel
    ticketsModel = new QStandardItemModel(0, 6, this); // Adjust column count as needed
    ticketsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    ticketsModel->setHeaderData(1, Qt::Horizontal, tr("Client"));
    ticketsModel->setHeaderData(2, Qt::Horizontal, tr("Match"));
    ticketsModel->setHeaderData(3, Qt::Horizontal, tr("Seat"));
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

TicketsUI::~TicketsUI()
{
    delete ui;
    delete ticketsModel;
}

void TicketsUI::addTicket()
{
    int clientId = ui->clientComboBox->currentData().toInt();
    int matchId = ui->matchComboBox->currentData().toInt();
    int seatId = ui->seatComboBox->currentData().toInt();
    double price = ui->priceLineEdit->text().toDouble();
    QString status = ui->statusComboBox->currentText();

    emit ticketAdded(clientId, matchId, seatId, price, status);

    // Clear input fields
    // ...
    ui->clientComboBox->setCurrentIndex(0);
    ui->matchComboBox->setCurrentIndex(0);
    ui->placeComboBox->setCurrentIndex(0);
    ui->priceLineEdit->setText("");
    ui->statusComboBox->setCurrentIndex(0);

    // Update the tickets list
    updateTicketsList();
}

void TicketsUI::deleteTicket()
{
    QModelIndexList selectedIndexes = ui->ticketsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No ticket selected.");
        return;
    }

    int ticketId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get ticket ID

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Ticket",
                                                              "Are you sure you want to delete this ticket?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        emit ticketDeleted(ticketId);
        updateTicketsList();
        clearTicketDetails();

        // Status Bar Message (you need access to MainWindow's status bar)
        MainWindow *mainWindow = dynamic_cast<MainWindow *>(parent());
        if (mainWindow)
        {
            mainWindow->statusBar()->showMessage("Ticket deleted successfully.");
        }
    }
}

void TicketsUI::updateTicket()
{
    QModelIndexList selectedIndexes = ui->ticketsTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No ticket selected.");
        return;
    }

    int ticketId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get ticket ID
    int clientId = ui->clientComboBox->currentData().toInt();
    int matchId = ui->matchComboBox->currentData().toInt();
    int seatId = ui->seatComboBox->currentData().toInt();
    double price = ui->priceLineEdit->text().toDouble();
    QString status = ui->statusComboBox->currentText();

    emit ticketUpdated(ticketId, clientId, matchId, seatId, price, status);

    // Update the tickets list
    updateTicketsList();
}

void TicketsUI::loadTicketDetails(const QModelIndex &index)
{
    if (!index.isValid())
    {
        clearTicketDetails();
        return;
    }

    int row = index.row();
    // Get the ticket data
    Ticket selectedTicket = ticketManager->getTickets(db)[row]; // Adjust to get tickets data

    ui->idLineEdit->setText(QString::number(selectedTicket.getId()));
    // Set selected client in clientComboBox
    int clientIndex = ui->clientComboBox->findData(selectedTicket.getClientId());
    if (clientIndex != -1)
    {
        ui->clientComboBox->setCurrentIndex(clientIndex);
    }
    // Set selected match in matchComboBox
    int matchIndex = ui->matchComboBox->findData(selectedTicket.getMatchId());
    if (matchIndex != -1)
    {
        ui->matchComboBox->setCurrentIndex(matchIndex);
    }
    // Set selected seat in placeComboBox
    int placeIndex = ui->placeComboBox->findData(selectedTicket.getSeatId());
    if (placeIndex != -1)
    {
        ui->placeComboBox->setCurrentIndex(placeIndex);
    }
    ui->priceLineEdit->setText(QString::number(selectedTicket.getPrice()));
    // Set selected status in statusComboBox
    int statusIndex = ui->statusComboBox->findText(selectedTicket.getStatus());
    if (statusIndex != -1)
    {
        ui->statusComboBox->setCurrentIndex(statusIndex);
    }
}

void TicketsUI::clearTicketDetails()
{
    ui->idLineEdit->clear();
    ui->clientComboBox->setCurrentIndex(0);
    ui->matchComboBox->setCurrentIndex(0);
    ui->placeComboBox->setCurrentIndex(0);
    ui->priceLineEdit->clear();
    ui->statusComboBox->setCurrentIndex(0);
}

void TicketsUI::searchTickets(const QString& searchTerm) {
       ticketsModel->clear(); // Clear the existing model data
    ticketsModel->setHorizontalHeaderLabels({"ID", "Client", "Match", "Seat", "Price", "Status"}); // Adjust if needed

    // Get tickets from TicketManager (or wherever you store ticket data)
    QList<Ticket> tickets = ticketManager->getTickets(db); // Adjust to your actual method

    for (const Ticket &ticket : tickets)
    {
        if (ticket.getClient().getName().contains(searchTerm, Qt::CaseInsensitive) ||
            ticket.getMatch().getName().contains(searchTerm, Qt::CaseInsensitive) ||
            ticket.getPlace().getName().contains(searchTerm, Qt::CaseInsensitive) ||
            QString::number(ticket.getId()).contains(searchTerm) ||
            QString::number(ticket.getPrice()).contains(searchTerm) ||
            ticket.getStatus().contains(searchTerm, Qt::CaseInsensitive)) { // Search ID as well
            int row = ticketsModel->rowCount();
            ticketsModel->insertRow(row);

            // Use the correct data from your Ticket class
            ticketsModel->setData(ticketsModel->index(row, 0), ticket.getId());
            ticketsModel->setData(ticketsModel->index(row, 1), ticket.getClient().getName()); // Assuming you can access the client name
            ticketsModel->setData(ticketsModel->index(row, 2), ticket.getMatch().getName());  // Assuming you can access the match name
            ticketsModel->setData(ticketsModel->index(row, 3), ticket.getPlace().getName());  // Assuming you can access the seat name
            ticketsModel->setData(ticketsModel->index(row, 4), ticket.getPrice());
            ticketsModel->setData(ticketsModel->index(row, 5), ticket.getStatus());

            // Optional: Store the ticket ID in the Qt::UserRole of the first column
            ticketsModel->setData(ticketsModel->index(row, 0), ticket.getId(), Qt::UserRole);
        }
    }
}

void TicketsUI::updateTicketsList()
{
    ticketsModel->clear();
    ticketsModel->setHorizontalHeaderLabels({"ID", "Client", "Match", "Seat", "Price", "Status"});

    QList<Ticket> tickets = ticketManager->getTickets(db);

    for (const Ticket &ticket : tickets)
    {
        int row = ticketsModel->rowCount();
        ticketsModel->insertRow(row);

        // Use the correct data from your Ticket class
        reservationsModel->setData(ticketsModel->index(row, 0), ticket.getId());
        reservationsModel->setData(ticketsModel->index(row, 1), ticket.getClient().getName()); // Assuming you can access the client name
        reservationsModel->setData(ticketsModel->index(row, 2), ticket.getMatch().getName());  // Assuming you can access the match name
        reservationsModel->setData(ticketsModel->index(row, 3), ticket.getPlace().getName());  // Assuming you can access the seat name
        reservationsModel->setData(ticketsModel->index(row, 4), ticket.getPrice());
        reservationsModel->setData(ticketsModel->index(row, 5), ticket.getStatus());

        // Optional: Store the ticket ID in the Qt::UserRole of the first column
        reservationsModel->setData(ticketsModel->index(row, 0), ticket.getId(), Qt::UserRole);
    }
}

void TicketsUI::updateClientComboBox()
{
    ui->clientComboBox->clear();
    // Get clients (you'll likely need a ClientManager or similar)
    QList<Client> clients = clientManager->getClients(db); // Assuming you have a getClients() function
    for (const Client &client : clients)
    {
        ui->clientComboBox->addItem(client.getName(), client.getId()); // Add client name and ID to combo box
    }
}

void TicketsUI::updateMatchComboBox()
{
    ui->matchComboBox->clear();
    // Get matches
    QList<Match> matches = playerManager->getMatches(db);
    for (const Match &match : matches)
    {
        QString matchDescription = QString("%1 vs %2").arg(match.getPlayer1().getName(), match.getPlayer2().getName());
        ui->matchComboBox->addItem(matchDescription, match.getId()); // Add match name and ID to combo box
    }
}

void TicketsUI::updatePlaceComboBox()
{
    ui->placeComboBox->clear();
    // Get places
    QList<Seat> places = seatManager->getSeats(db);
    for (const Seat &place : places)
    {
        ui->placeComboBox->addItem(place.getName(), place.getId()); // Add place name and ID to combo box
    }
}
