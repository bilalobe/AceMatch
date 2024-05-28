// scoreboard.cpp
#include "scoreboard.h"
#include "ui_scoreboard.h"

Scoreboard::Scoreboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Scoreboard)
{
    ui->setupUi(this);
}

Scoreboard::~Scoreboard()
{
    delete ui;
}

void Scoreboard::setPlayer1Name(const QString& name) {
    ui->player1NameLabel->setText(name);
}

void Scoreboard::setPlayer2Name(const QString& name) {
    ui->player2NameLabel->setText(name);
}

void Scoreboard::setScore1(int score) {
    ui->player1ScoreLabel->setText(QString::number(score));
}

void Scoreboard::setScore2(int score) {
    ui->player2ScoreLabel->setText(QString::number(score));
}

void Scoreboard::clear() {
    ui->player1NameLabel->clear();
    ui->player2NameLabel->clear();
    ui->player1ScoreLabel->clear();
    ui->player2ScoreLabel->clear();
}