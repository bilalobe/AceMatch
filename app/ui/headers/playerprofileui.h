#ifndef PLAYERPROFILEUI_H
#define PLAYERPROFILEUI_H

#include <QWidget>

namespace Ui {
class PlayerProfileUI;
}

class PlayerProfileUI : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerProfileUI(QWidget *parent = nullptr);
    ~PlayerProfileUI();

private:
    Ui::PlayerProfileUI *ui;
};

#endif // PLAYERPROFILEUI_H
