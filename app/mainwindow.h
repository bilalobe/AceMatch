#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlayerBox.h"
#include "Scoreboard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    PlayerBox *playerBox;
    Scoreboard *scoreboard;

private slots:
    void updateResultsView();
};

#endif // MAINWINDOW_H
