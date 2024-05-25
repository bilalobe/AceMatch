#ifndef SCOREUI_H
#define SCOREUI_H

#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class ScoreUI; }
QT_END_NAMESPACE

class ScoreUI : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~ScoreUI();

signals:
    void scoreAdded(int matchId, int score1, int score2);
    void scoreDeleted(int scoreId);
    void scoreUpdated(int scoreId, int newScore1, int newScore2);

private slots:
    void addScore();
    void deleteScore();
    void updateScore();
    void loadScoreDetails(const QModelIndex& index);
    void clearScoreDetails();

private:
    Ui::ScoreUI *ui;
    QSqlDatabase db;
    QStandardItemModel* scoresModel;

    void updateScoresList();
    void updateMatchComboBox(); // To populate the combo box with matches 
};

#endif // SCOREUI_H