// GestionReservations.cpp
// ... (Other includes) ...

bool GestionReservations::ajouterReservation(QSqlDatabase& db, int clientId, int placeId, const QDateTime& dateTime) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Reservations (clientId, placeId, dateTime) VALUES (:clientId, :placeId, :dateTime)");
    query.bindValue(":clientId", clientId);
    query.bindValue(":placeId", placeId);
    query.bindValue(":dateTime", dateTime);

    if (!query.exec()) {
        qDebug() << "Error adding reservation:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionReservations::supprimerReservation(QSqlDatabase& db, int reservationId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Reservations WHERE id = :reservationId");
    query.bindValue(":reservationId", reservationId);

    if (!query.exec()) {
        qDebug() << "Error deleting reservation:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionReservations::modifierReservation(QSqlDatabase& db, int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime) {
    QSqlQuery query(db);
    query.prepare("UPDATE Reservations SET clientId = :newClientId, placeId = :newPlaceId, dateTime = :newDateTime WHERE id = :reservationId");
    query.bindValue(":newClientId", newClientId);
    query.bindValue(":newPlaceId", newPlaceId);
    query.bindValue(":newDateTime", newDateTime);
    query.bindValue(":reservationId", reservationId);

    if (!query.exec()) {
        qDebug() << "Error updating reservation:" << query.lastError();
        return false;
    }
    return true;
}

QList<Reservation> GestionReservations::getReservations(const QSqlDatabase& db) const {
    QList<Reservation> reservations;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Reservations"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int placeId = query.value("placeId").toInt();
        QDateTime dateTime = query.value("dateTime").toDateTime();

        // Assuming you have a way to get Client and Place objects by ID
        Client client = gestionClients->getClientById(db, clientId); 
        Place place = gestionPlaces->getPlaceById(db, placeId); 

        reservations.append(Reservation(id, client, place, dateTime)); 
    }
    return reservations;
}