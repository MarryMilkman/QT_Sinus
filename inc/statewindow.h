#ifndef STATEWINDOW_H
#define STATEWINDOW_H

#include "lib.h"

#include <QDialog>
#include <QPainter>


namespace Ui {
class StateWindow;
}

class StateWindow : public QDialog
{
    Q_OBJECT
    explicit StateWindow(QWidget *parent = nullptr);
    StateWindow();

public:
    StateWindow(StateWindow const & ref) = delete;
    StateWindow &operator=(StateWindow const & ref) = delete;
    static StateWindow     &getInstance();
    ~StateWindow();

    float   get_delta_x() const;
    int     get_delta_t() const;

private:
    Ui::StateWindow *ui;
    float           _value_x;
    float           _value_y;
    float           _delta_x;
    int             _delta_t;
    QPainter        _qr_painter;


    void    _update_current_sin_lable();
//    void    _draw_qr();

    void     paintEvent(QPaintEvent *event) override;


//  MARK: - slots and signals
public slots:
    void    slot_new_param(float x, float y);
    void    slot_fresh();

signals:
    void    signal_change_dx(float);
    void    signal_change_dt(int);
private slots:

    void on_delta_x_line_edit_editingFinished();
    void on_delta_t_line_edit_editingFinished();
};

#endif // STATEWINDOW_H
