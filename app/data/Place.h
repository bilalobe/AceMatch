#ifndef PLACE_H
#define PLACE_H

#include <QString>

class Place
{
public:
    Place(int id = -1, const QString& nom = "", int capacity = 0) : id(id), nom(nom), capacity(capacity) {} // Inline constructor
    int getId() const { return id; }
    QString getNom() const { return nom; }
    int getCapacity() const { return capacity; }

private:
    int id;
    QString nom;
    int capacity;
};

#endif // PLACE_H