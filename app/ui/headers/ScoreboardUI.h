#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Scoreboard; }
QT_END_NAMESPACE

class Scoreboard : public QWidget
{
    Q_OBJECT

public:
    explicit Scoreboard(QWidget *parent = nullptr);
    ~Scoreboard();

    void setPlayer1Name(const QString& name);
    void setPlayer2Name(const QString& name);
    void setScore1(int score);
    void setScore2(int score);
    void clear();

private:
    Ui::Scoreboard *ui;
};

#endif // SCOREBOARD_H