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
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <qsqlerror>

#include "ui/headers/scoreboardmatchdetailsui.h"
#include "ui/headers/playerprofileui.h"
#include "ui/headers/placesui.h"
#include "ui/headers/reservationsui.h"
#include "ui/headers/terrainsui.h"
#include "ui/headers/ticketsui.h"
#include "ui/headers/matchui.h"
#include "ui/headers/playerbox.h"




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

    // Database Connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tournament.db"); // Or your database name
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError();
        return 1;
    }

    // Main Tab Widget
    QTabWidget* tabWidget = new QTabWidget(&mainWindow);

    // Players Tab
    PlayerBox *playerBox = new PlayerBox(&mainWindow, db);
    QWidget* playersTab = new QWidget();
    QVBoxLayout* playersLayout = new QVBoxLayout(playersTab);
    playersLayout->addWidget(playerBox);
    tabWidget->addTab(playersTab, "Players");

    // Matches Tab
    MatchUI* matchUI = new MatchUI(&mainWindow, db);
    QWidget* matchesTab = new QWidget();
    QVBoxLayout* matchesLayout = new QVBoxLayout(matchesTab);
    matchesLayout->addWidget(matchUI);
    tabWidget->addTab(matchesTab, "Matches");

    // Standings Tab
    QWidget* standingsTab = new QWidget();
    QVBoxLayout* standingsLayout = new QVBoxLayout(standingsTab);
    QTableView* standingsTableView = new QTableView(standingsTab);
    standingsLayout->addWidget(standingsTableView);
    tabWidget->addTab(standingsTab, "Standings");

    // Create a model for standings data (you'll populate this later)
    QStandardItemModel* standingsModel = new QStandardItemModel(0, 2, standingsTab); // 0 rows, 2 columns
    standingsModel->setHeaderData(0, Qt::Horizontal, tr("Player"));
    standingsModel->setHeaderData(1, Qt::Horizontal, tr("Wins")); // Or other relevant data
    standingsTableView->setModel(standingsModel);

    // Scoreboard & Match Details Tab
    ScoreboardMatchDetailsUI* scoreboardMatchDetailsUI = new ScoreboardMatchDetailsUI(&mainWindow, db);
    QWidget* detailsTab = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsTab);
    detailsLayout->addWidget(scoreboardMatchDetailsUI);
    tabWidget->addTab(detailsTab, "Scoreboard & Match Details");

    // Player Profile Tab
    PlayerProfileUI* playerProfileUI = new PlayerProfileUI(&mainWindow, db);
    QWidget* profileTab = new QWidget();
    QVBoxLayout* profileLayout = new QVBoxLayout(profileTab);
    profileLayout->addWidget(playerProfileUI);
    tabWidget->addTab(profileTab, "Player Profile");

    // Tournament Management Tab with Mini-Tabs
    QTabWidget* tournamentTabWidget = new QTabWidget(&mainWindow);
    QWidget* tournamentTab = new QWidget();
    QVBoxLayout* tournamentLayout = new QVBoxLayout(tournamentTab);
    tournamentLayout->addWidget(tournamentTabWidget);
    tabWidget->addTab(tournamentTab, "Tournament Management");

    // Places Mini-Tab
    PlacesUI* placesUI = new PlacesUI(&mainWindow, db);
    tournamentTabWidget->addTab(placesUI, "Places");

    // Reservations Mini-Tab
    ReservationsUI* reservationsUI = new ReservationsUI(&mainWindow, db);
    tournamentTabWidget->addTab(reservationsUI, "Reservations");

    // Terrains Mini-Tab
    TerrainUI* terrainsUI = new TerrainUI(&mainWindow, db);
    tournamentTabWidget->addTab(terrainsUI, "Terrains");

    // Tickets Mini-Tab
    TicketsUI* ticketsUI = new TicketsUI(&mainWindow, db);
    tournamentTabWidget->addTab(ticketsUI, "Tickets");

    // Set tabWidget as the central widget
    mainWindow.setCentralWidget(tabWidget);

    // Status Bar
    mainWindow.statusBar()->showMessage("Ready");

    mainWindow.show();

    return app.exec();
}
