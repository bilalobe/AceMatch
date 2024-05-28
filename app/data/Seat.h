#ifndef SEAT_H
#define SEAT_H

#include <QPointF>

class Seat
{
public:
    Seat(int id, const QPointF& center, qreal size, bool isAvailable);

    int getId() const { return id; }
    QPointF getCenter() const { return center; }
    qreal getSize() const { return size; }
    bool isAvailable() const { return available; }

private:
    int id;
    QPointF center;
    qreal size;
    bool available;
};

#endif // SEAT_H