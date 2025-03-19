#ifndef CourtUI_H
#define CourtUI_H

#include "qstandarditemmodel.h"
#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class CourtUI; }
QT_END_NAMESPACE

class CourtUI : public QWidget
{
    Q_OBJECT

public:
    explicit CourtUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~CourtUI();

private slots:
    void addCourt();
    void deleteCourt();
    void updateCourt();
    void searchCourt(const QString &searchTerm);
    void loadCourtDetails(const QModelIndex& index);
    void clearCourtDetails();

private:
    Ui::CourtUI *ui;
    QSqlDatabase db;
    QStandardItemModel* courtsModel;

    void updateCourtsList();
};

#endif // CourtUI_H
