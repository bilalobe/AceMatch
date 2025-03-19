#ifndef PLACESUI_H
#define PLACESUI_H

#include <QWidget>
#include <QSqlDatabase> 

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
    void placeDeleted(int seatId);
    void placeUpdated(int seatId, const QString& newName, int newCapacity);
    void placeSearched(const QString& searchTerm); // Add this signal

private slots:
    void addPlace();
    void deletePlace();
    void updatePlace();
    void loadPlaceDetails(const QModelIndex& index);
    void clearPlaceDetails(); 
    void searchPlace(const QString& searchTerm); // Add this slot

private:
    Ui::PlacesUI *ui;
    QSqlDatabase db;
    QStandardItemModel* seatsModel;

    void updatePlacesList(); 
};

#endif // PLACESUI_H