#ifndef SCOREBOARDMATCHDETAILUI_H
#define SCOREBOARDMATCHDETAILUI_H

#include <QWidget>
#include <QSqlDatabase>
#include "A:\workspace\special-broccoli\app\data\mgmt\PlayerManager.h"
#include "A:\workspace\special-broccoli\app\data\mgmt\MatchManager.h"
#include "A:\workspace\special-broccoli\app\ui\headers\ScoreboardUI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ScoreboardMatchDetailsUI; }
QT_END_NAMESPACE

class ScoreboardMatchDetailsUI : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreboardMatchDetailsUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~ScoreboardMatchDetailsUI();

signals:
    void matchSelected(int matchId);

private slots:
    void loadMatchDetails();

private:
    Ui::ScoreboardMatchDetailsUI *ui;
    QSqlDatabase db;
    PlayerManager* playerManager;
    MatchManager* matchManager;
    Scoreboard* scoreboard; // Pointer to the scoreboard widget

    void updateMatchComboBox();
    void displayMatchDetails(const Match& match);
    void clearMatchDetails();
};

#endif // SCOREBOARDMATCHDETAILUI_H
