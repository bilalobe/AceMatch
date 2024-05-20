#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QLineEdit>
#include <QVBoxLayout>

#include "playerbox.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon("ball.svg")); // Set your app's logo
    mainWindow.resize(720, 720); // Widen the overall interface

    // Menu Bar
    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("New Tournament");
    fileMenu->addAction("Save");
    fileMenu->addAction("Load");
    fileMenu->addAction("Export Data");
    fileMenu->addAction("Import Data");
    menuBar->addMenu("Edit");
    menuBar->addMenu("View");
    menuBar->addMenu("Settings");
    menuBar->addMenu("Help");

    // Toolbar
    QToolBar *toolbar = mainWindow.addToolBar("Toolbar");
    toolbar->addAction(QIcon("path_to_new_player_icon.png"), "New Player");
    toolbar->addAction(QIcon("path_to_new_match_icon.png"), "New Match");
    toolbar->addAction(QIcon("path_to_statistics_icon.png"), "Statistics");

    // Search Bar
    QLineEdit *searchBar = new QLineEdit(&mainWindow);
    toolbar->addWidget(searchBar);

    // Main Display Area
    QTabWidget *tabWidget = new QTabWidget(&mainWindow);

    // Create PlayerBox instance and add it to the "Players" tab
    PlayerBox *playerBox = new PlayerBox(&mainWindow);
    QWidget *playersTab = new QWidget(); // Create a widget for the "Players" tab
    QVBoxLayout *playersLayout = new QVBoxLayout(playersTab); // Layout for the "Players" tab
    playersLayout->addWidget(playerBox); // Add playerBox to the layout
    tabWidget->addTab(playersTab, "Players");

    tabWidget->addTab(new QWidget(), "Matches");
    tabWidget->addTab(new QWidget(), "Standings");
    tabWidget->addTab(new QWidget(), "Player Profile");
    tabWidget->addTab(new QWidget(), "Match Details");

    // Set tabWidget as the central widget
    mainWindow.setCentralWidget(tabWidget);

    // Status Bar
    mainWindow.statusBar()->showMessage("Ready");

    mainWindow.show();

    return app.exec();
}
