#ifndef PLAYERBOX_H
#define PLAYERBOX_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QSignalMapper>
#include <QListWidget>
#include "Joueur.h" // Include your Joueur.h header
#include <QSqlDatabase> 

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerBox; }
QT_END_NAMESPACE

class PlayerBox : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerBox(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~PlayerBox();

private slots:
    void addPlayer();
    void deletePlayer();
    void updatePlayer();
    void searchPlayer(const QString& text);
    void playerSelectionChanged(); 

private:
    Ui::PlayerBox *ui;
    QSqlDatabase db;

    void updatePlayerList();
    void on_addplayerButton_clicked();
    void on_deleteplayerButton_clicked();
    void on_updateplayerButton_clicked();
    void on_searchplayerLineEdit_textChanged(const QString& searchTerm);
    void on_playerTableView_clicked(const QModelIndex& index);
    void on_playerTableView_doubleClicked(const QModelIndex& index);

};

#endif // PLAYERBOX_H