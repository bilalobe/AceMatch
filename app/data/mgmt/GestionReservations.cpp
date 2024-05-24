// Add a reservation
void GestionReservations::ajouterReservation(const Reservation& reservation) {
    reservations.push_back(reservation);
}

 void GestionReservations::supprimerReservation(Client* client, Partie* partie, int row, int col) {
   auto it = std::find_if(reservations.begin(), reservations.end(),
                          [&client, &partie, row, col](const Reservation& res) {
                            return res.getClient() == client && res.getPartie() == partie && res.getRow() == row && res.getCol() == col;
                          });
   if (it != reservations.end()) {
     // Release the seat in the Terrain
     it->getTerrain()->releaseSeat(row, col);
     reservations.erase(it);
   }
 }

 // Search for a reservation
 Reservation* GestionReservations::rechercherReservation(Client* client, Partie* partie, int row, int col) {
   auto it = std::find_if(reservations.begin(), reservations.end(),
                          [&client, &partie, row, col](const Reservation& res) {
                            return res.getClient() == client && res.getPartie() == partie && res.getRow() == row && res.getCol() == col;
                          });
   if (it != reservations.end()) {
     return &(*it); // Return a pointer to the found Reservation
   }
   return nullptr;
 }
// Display all reservations
void GestionReservations::afficherReservations() const {
    for (const auto& reservation : reservations) {
        reservation.afficher();
        cout << endl;
    }
}

// Get the list of reservations
const vector<Reservation>& GestionReservations::getReservations() const {
    return reservations;
}

// Sort reservations by client name
void GestionReservations::trierReservationsParClient() {
    sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
        return a.getClient()->getNom() < b.getClient()->getNom();
    });
}
