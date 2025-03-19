#ifndef COURT_H
#define COURT_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

class Court
{
public:
    Court(int id = -1, const QString& name = "", const QString& type = "") : id(id), name(name), type(type) {} // Inline constructor
    int getId() const { return id; }
    QString getName() const { return name; }
    QString getType() const { return type; }

private:
    int id;
    QString name;
    QString type;
};

#endif // COURT_H