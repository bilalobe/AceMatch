#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <QWidget>
#include <QSqlDatabase>
#include "data/Joueur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerUI; }
QT_END_NAMESPACE

class PlayerUI : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~PlayerUI();

signals:
    void playerAdded(const Tournament::Joueur& joueur);
    void playerDeleted(const QString& playerName);
    void playerUpdated(const Tournament::Joueur& joueur);

private slots:
    void addPlayer();
    void deletePlayer();
    void updatePlayer();
    void loadPlayerDetails(const QModelIndex& index);
    void clearPlayerDetails();

private:
    Ui::PlayerUI *ui;
    QSqlDatabase db;
    QStandardItemModel* playersModel;

    void updatePlayerList();
};

#endif // PLAYERUI_H
