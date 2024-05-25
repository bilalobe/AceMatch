#ifndef PLACESUI_H
#define PLACESUI_H

#include <QWidget>
#include <QSqlDatabase>
#include "GestionPlaces.h" 

QT_BEGIN_NAMESPACE
namespace Ui { class PlacesUI; }
QT_END_NAMESPACE

class PlacesUI : public QWidget
{
    Q_OBJECT

public:
    explicit PlacesUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~PlacesUI();

signals:
    void placeAdded(const QString& name, int capacity);
    void placeDeleted(int placeId);
    void placeUpdated(int placeId, const QString& newName, int newCapacity);

private slots:
    void addPlace();
    void deletePlace();
    void updatePlace();
    void searchPlace();
    void loadPlaceDetails(const QModelIndex& index);
    void clearPlaceDetails(); 

private:
    Ui::PlacesUI *ui;
    QSqlDatabase db;
    GestionPlaces* gestionPlaces; 
    QStandardItemModel* placesModel;

    void updatePlacesList(); 
};

#endif // PLACESUI_H