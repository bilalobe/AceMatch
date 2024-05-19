#include "playerbox.h"
#include "ui_playerbox.h"

PlayerBox::PlayerBox(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::PlayerBox)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->addPlayerButton, &QPushButton::clicked, this, &PlayerBox::addPlayer);
    connect(ui->removePlayerButton, &QPushButton::clicked, this, &PlayerBox::removePlayer);
    connect(ui->updatePlayerButton, &QPushButton::clicked, this, &PlayerBox::updatePlayer);
    connect(ui->searchPlayerLineEdit, &QLineEdit::textChanged, this, &PlayerBox::searchPlayer);

    // Connect the list widget's item selection signal
    connect(ui->playerListWidget, &QListWidget::itemSelectionChanged, this, &PlayerBox::playerSelectionChanged);
}

PlayerBox::~PlayerBox()
{
    delete ui;
}

void PlayerBox::addPlayer() {
    QString name = ui->playerNameLineEdit->text();
    int ranking = ui->playerRankingSpinBox->value();

    // Emit signal to notify the main application
    emit playerAdded(name, ranking);

    // Clear input fields
    ui->playerNameLineEdit->clear();
    ui->playerRankingSpinBox->setValue(0);
}

void PlayerBox::removePlayer() {
    // Get the currently selected item
    QListWidgetItem* selectedItem = ui->playerListWidget->currentItem();

    if (selectedItem) {
        QString name = selectedItem->text().split(" ").last();

        // Emit signal to notify the main application
        emit playerRemoved(name);

        // Remove from internal list and the list widget
        delete selectedItem;
        players.removeOne(selectedItem->text());
    }
}

void PlayerBox::updatePlayer() {
    // Get the currently selected item
    QListWidgetItem* selectedItem = ui->playerListWidget->currentItem();

    if (selectedItem) {
        QString name = selectedItem->text().split(" ").last();
        int newRanking = ui->playerRankingSpinBox->value();

        // Emit signal to notify the main application
        emit playerUpdated(name, newRanking);

        // Update the internal list and the list widget
        int index = ui->playerListWidget->row(selectedItem);
        players[index] = QString::number(newRanking) + " " + name;
        selectedItem->setText(players[index]);

        // Clear input fields
        ui->updatePlayerLineEdit->clear();
        ui->playerRankingSpinBox->setValue(0);
    }
}

void PlayerBox::searchPlayer(const QString& text) {
    QString searchTerm = text;

    // Emit signal to notify the main application
    emit playerSearched(searchTerm);

    // (Optional)  You could display search results directly in the PlayerBox
    // if you want to make it a self-contained widget.
}

// New slot for handling list item selection
void PlayerBox::playerSelectionChanged() {
    QListWidgetItem* selectedItem = ui->playerListWidget->currentItem();
    if (selectedItem) {
        QString name = selectedItem->text().split(" ").last();

        // Update the "Update Player" section
        ui->updatePlayerLineEdit->setText(name);
    }
}
