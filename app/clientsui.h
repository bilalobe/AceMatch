#ifndef CLIENTSUUI_H
#define CLIENTSUUI_H

#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientsUI; }
QT_END_NAMESPACE

class ClientsUI : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~ClientsUI();

signals:
    void clientAdded(const QString& nom, const QString& email, const QString& phoneNumber);
    void clientDeleted(int clientId);
    void clientUpdated(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);

private slots:
    void addClient();
    void deleteClient();
    void updateClient();
    void loadClientDetails(const QModelIndex& index);
    void clearClientDetails();

private:
    Ui::ClientsUI *ui;
    QSqlDatabase db;
    QStandardItemModel* clientsModel;

    void updateClientsList();
};

#endif // CLIENTSUUI_H