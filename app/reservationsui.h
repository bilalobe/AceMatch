#ifndef RESERVATIONSUI_H
#define RESERVATIONSUI_H

#include <QWidget>

namespace Ui {
class ReservationsUI;
}

class ReservationsUI : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationsUI(QWidget *parent = nullptr);
    ~ReservationsUI();

private:
    Ui::ReservationsUI *ui;
};

#endif // RESERVATIONSUI_H
