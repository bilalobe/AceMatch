#ifndef CLIENTSUUI_H
#define CLIENTSUUI_H

#include "qstandarditemmodel.h"
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


private slots:
    void addClient();
    void deleteClient();
    void updateClient();
    void searchClient(const QString& searchTerm);
    void loadClientDetails(const QModelIndex& index);
    void clearClientDetails();

private:
    Ui::ClientsUI *ui;
    QSqlDatabase db;
    QStandardItemModel* clientsModel;

    void updateClientsList();
    void clearSearch();
};

#endif // CLIENTSUUI_H
