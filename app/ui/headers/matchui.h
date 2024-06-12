#ifndef MATCHUI_H
#define MATCHUI_H

#include <QWidget>
#include <QSqlDatabase>
#include "qstandarditemmodel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MatchUI; }
QT_END_NAMESPACE

class MatchUI : public QWidget
{
    Q_OBJECT

public:
    explicit MatchUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~MatchUI();

signals:
    void matchCreated(const QString& player1Name, const QString& player2Name, int score1, int score2);
    void matchDeleted(int matchId);
    void matchUpdated(int matchId, int newScore1, int newScore2);

private slots:
    void createMatch();
    void deleteMatch();
    void updateMatch();
    void searchMatch(const QString& searchText);
    void updateMatchList();
    void updateMatchDetails(const QModelIndex& index);
    void updatePlayerComboBoxes();



private:
    Ui::MatchUI *ui;
    QSqlDatabase db;
    QStandardItemModel* matchModel;

    void clearMatchDetails();
};

#endif // MATCHUI_H
