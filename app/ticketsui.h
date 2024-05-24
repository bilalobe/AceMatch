#ifndef TICKETSUI_H
#define TICKETSUI_H

#include <QWidget>

namespace Ui {
class TicketUI;
}

class TicketUI : public QWidget
{
    Q_OBJECT

public:
    explicit TicketUI(QWidget *parent = nullptr);
    ~TicketUI();

private:
    Ui::TicketUI *ui;
};

#endif // TICKETSUI_H
