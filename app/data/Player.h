#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
public:
    Player(const QString& name = "", int rang = 0) : name(name), rang(rang) {} // Inline constructor
    QString getName() const { return name; }
    int getRang() const { return rang; }

private:
    QString name;
    int rang;
};

#endif // PLAYER_H