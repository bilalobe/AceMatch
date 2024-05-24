#ifndef SCOREBOARDMATCHDETAILSUI_H
#define SCOREBOARDMATCHDETAILSUI_H

#include <QWidget>

namespace Ui {
class scoreboardmatchdetailsui;
}

class scoreboardmatchdetailsui : public QWidget
{
    Q_OBJECT

public:
    explicit scoreboardmatchdetailsui(QWidget *parent = nullptr);
    ~scoreboardmatchdetailsui();

private:
    Ui::scoreboardmatchdetailsui *ui;
};

#endif // SCOREBOARDMATCHDETAILSUI_H
