#ifndef MATCHUI_H
#define MATCHUI_H

#include <QWidget>

namespace Ui {
class MatchUI;
}

class MatchUI : public QWidget
{
    Q_OBJECT

public:
    explicit MatchUI(QWidget *parent = nullptr);
    ~MatchUI();

private:
    Ui::MatchUI *ui;
};

#endif // MATCHUI_H
