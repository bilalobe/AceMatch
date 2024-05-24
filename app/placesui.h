#ifndef PLACESUI_H
#define PLACESUI_H

#include <QTabWidget>

namespace Ui {
class PlacesUI;
}

class PlacesUI : public QTabWidget
{
    Q_OBJECT

public:
    explicit PlacesUI(QWidget *parent = nullptr);
    ~PlacesUI();

private:
    Ui::PlacesUI *ui;
};

#endif // PLACESUI_H
