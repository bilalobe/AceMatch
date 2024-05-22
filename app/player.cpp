#include "Player.h"

Player::Player(QObject *parent)
    : QObject(parent), m_id(0), m_name(""), m_ranking(0) {}

Player::Player(int id, QString name, int ranking, QObject *parent)
    : QObject(parent), m_id(id), m_name(name), m_ranking(ranking) {}

int Player::getId() const {
    return m_id;
}

QString Player::getName() const {
    return m_name;
}

int Player::getRanking() const {
    return m_ranking;
}

void Player::setId(int id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged(m_id);
    }
}

void Player::setName(QString name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Player::setRanking(int ranking) {
    if (m_ranking != ranking) {
        m_ranking = ranking;
        emit rankingChanged(m_ranking);
    }
}
