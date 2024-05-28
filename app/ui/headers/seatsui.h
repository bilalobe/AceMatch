#ifndef SEATSUI_H
#define SEATSUI_H

#include <QWidget>
#include <QSqlDatabase>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class SeatsUI; }
QT_END_NAMESPACE

class SeatsUI : public QWidget
{
    Q_OBJECT

public:
    explicit SeatsUI(QWidget *parent = nullptr, const QSqlDatabase& database = QSqlDatabase());
    ~SeatsUI();

signals:
    void seatSelected(int seatId);
    void seatStatusChanged(int seatId, bool isAvailable);

private slots:
    void updateSeatsTable();
    void handleSeatClicked(QGraphicsSceneMouseEvent* event);

private:
    Ui::SeatsUI *ui;
    QSqlDatabase db;
    QGraphicsScene* scene;
    QGraphicsView* view;

    void createSeats(const QList<Seat>& seats);
    QPolygonF createTriangle(const QPointF& center, qreal size) const;
};

#endif // SEATSUI_H