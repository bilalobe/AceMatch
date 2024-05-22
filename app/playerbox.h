#ifndef PLAYERBOX_H
#define PLAYERBOX_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QSignalMapper>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerBox; }
QT_END_NAMESPACE

class PlayerBox : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerBox(QWidget *parent = nullptr);
    ~PlayerBox();

signals:
    void playerAdded(const QString& name, int ranking);
    void playerRemoved(const QString& name);
    void playerUpdated(const QString& name, int newRanking);
    void playerSearched(const QString& searchTerm);

private slots:
    void addPlayer();
    void removePlayer();
    void updatePlayer();
    void searchPlayer(const QString& text);
    void playerSelectionChanged();


private:
    Ui::PlayerBox *ui;
    QList<QString> players;
};

#endif // PLAYERBOX_H
