#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playerbox.h" // Include the PlayerBox header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayerAdded(const QString& name, int ranking); // Slot to handle adding players
    void handlePlayerRemoved(const QString& name); // Slot to handle removing players
    void handlePlayerUpdated(const QString& name, int newRanking); // Slot to handle updating players
    void handlePlayerSearched(const QString& searchTerm); // Slot to handle search queries

private:
    Ui::MainWindow *ui;
    PlayerBox *playerBox;
};

#endif // MAINWINDOW_H
