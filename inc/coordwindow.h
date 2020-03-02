#ifndef COORDWINDOW_H
#define COORDWINDOW_H

#include "lib.h"

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

namespace Ui {
class CoordWindow;
}

class CoordWindow : public QDialog
{
    Q_OBJECT
    explicit CoordWindow(QWidget *parent = nullptr);
    CoordWindow();

public:
    CoordWindow(CoordWindow const & ref) = delete;
    static CoordWindow  &getInstance();
    ~CoordWindow();

private:
    Ui::CoordWindow     *ui;

    QGraphicsScene          *_scene;
    QGraphicsEllipseItem    *_circle;
    QGraphicsLineItem       *_line_x;
    QGraphicsLineItem       *_line_y;

    float               _value_x;
    float               _value_y;

    void                _draw();


//  MARK: - slots and signals
public slots:
    void    slot_new_param(float x, float y);
    void    slot_fresh();
};

#endif // COORDWINDOW_H
