#include "seatsui.h"
#include "ui_seatsui.h"
#include <QDebug>
#include <QSqlQuery>
#include <QGraphicsSceneMouseEvent>

SeatsUI::SeatsUI(QWidget *parent, const QSqlDatabase& database) :
    QWidget(parent), ui(new Ui::SeatsUI), db(database)
{
    ui->setupUi(this);

    // Create the QGraphicsScene and QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    // Set the graphics view within the layout
    ui->seatsLayout->addWidget(view);

    // Create the seats
    updateSeatsTable();

    // Connect the mouse click event to the slot
    connect(scene, &QGraphicsScene::clicked, this, &SeatsUI::handleSeatClicked);
}

SeatsUI::~SeatsUI() {
    delete ui;
    delete scene;
    delete view;
}

void SeatsUI::updateSeatsTable() {
    scene->clear(); // Clear the existing scene

    // Fetch seat data from your database
    QList<Seat> seats = gestionSeats->getSeats(db); // Assuming you have a SeatManager class

    // Create the seats on the scene
    createSeats(seats);
}

void SeatsUI::createSeats(const QList<Seat>& seats) {
    for (const Seat& seat : seats) {
        QGraphicsPolygonItem* seatItem = new QGraphicsPolygonItem(createTriangle(seat.getCenter(), seat.getSize()));
        seatItem->setData(0, seat.getId());

        if (seat.isAvailable()) {
            seatItem->setBrush(Qt::green);
        } else {
            seatItem->setBrush(Qt::red);
        }

        scene->addItem(seatItem);
    }

    // Set the scene rect
    view->setSceneRect(scene->sceneRect());
}

QPolygonF SeatsUI::createTriangle(const QPointF& center, qreal size) const {
    QPolygonF triangle;
    // Adjust these values to fine-tune the triangle shape
    triangle << QPointF(center.x() - size / 2, center.y() + size * 0.8660254); 
    triangle << QPointF(center.x(), center.y() - size * 0.8660254);
    triangle << QPointF(center.x() + size / 2, center.y() + size * 0.8660254);
    return triangle;
}

void SeatsUI::handleSeatClicked(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* clickedItem = event->item();

    if (clickedItem) {
        int seatId = clickedItem->data(0).toInt();

        // Emit the seatSelected signal
        emit seatSelected(seatId);

        // Toggle the seat status
        bool isAvailable = clickedItem->brush().color() == Qt::green;
        if (isAvailable) {
            clickedItem->setBrush(Qt::red);
        } else {
            clickedItem->setBrush(Qt::green);
        }

        // Emit the seatStatusChanged signal
        emit seatStatusChanged(seatId, !isAvailable);
    }
}