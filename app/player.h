#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int ranking READ getRanking WRITE setRanking NOTIFY rankingChanged)

public:
    explicit Player(QObject *parent = nullptr);
    Player(int id, QString name, int ranking, QObject *parent = nullptr);

    int getId() const;
    QString getName() const;
    int getRanking() const;

public slots:
    void setId(int id);
    void setName(QString name);
    void setRanking(int ranking);

signals:
    void idChanged(int id);
    void nameChanged(QString name);
    void rankingChanged(int ranking);

private:
    int m_id;
    QString m_name;
    int m_ranking;
};

#endif // PLAYER_H
