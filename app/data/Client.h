#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client(int id = -1, const QString& nom = "", const QString& email = "", const QString& phoneNumber = "")
        : id(id), nom(nom), email(email), phoneNumber(phoneNumber) {} // Inline constructor
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getEmail() const { return email; }
    QString getPhoneNumber() const { return phoneNumber; }

private:
    int id;
    QString nom;
    QString email;
    QString phoneNumber;
};

#endif // CLIENT_H