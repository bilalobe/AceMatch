#ifndef TERRAINUI_H
#define TERRAINUI_H

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

signals:
    void terrainAdded(const QString& name, const QString& type); // Adjust signal parameters based on your Terrain class
    void terrainDeleted(int terrainId);
    void terrainUpdated(int terrainId, const QString& newName, const QString& newType);  // Adjust signal parameters

private slots:
    void addTerrain();
    void deleteTerrain();
    void updateTerrain();
    void loadTerrainDetails(const QModelIndex& index);
    void clearTerrainDetails();

private:
    Ui::TerrainUI *ui;
    QSqlDatabase db;
    QStandardItemModel* terrainsModel;

    void updateTerrainsList();
};

#endif // TERRAINUI_H
