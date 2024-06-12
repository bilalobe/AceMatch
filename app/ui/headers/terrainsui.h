#ifndef TERRAINUI_H
#define TERRAINUI_H

#include "qstandarditemmodel.h"
#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class TerrainUI; }
QT_END_NAMESPACE

class TerrainUI : public QWidget
{
    Q_OBJECT

public:
    explicit TerrainUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~TerrainUI();

private slots:
    void addTerrain();
    void deleteTerrain();
    void updateTerrain();
    void searchTerrain(const QString &searchTerm);
    void loadTerrainDetails(const QModelIndex& index);
    void clearTerrainDetails();

private:
    Ui::TerrainUI *ui;
    QSqlDatabase db;
    QStandardItemModel* terrainsModel;

    void updateTerrainsList();
};

#endif // TERRAINUI_H
