#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client(int id = -1, const QString& name = "", const QString& email = "", const QString& phoneNumber = "")
        : id(id), name(name), email(email), phoneNumber(phoneNumber) {} // Inline constructor
    int getId() const { return id; }
    QString getName() const { return name; }
    QString getEmail() const { return email; }
    QString getPhoneNumber() const { return phoneNumber; }

private:
    int id;
    QString name;
    QString email;
    QString phoneNumber;
};

#endif // CLIENT_H