#include "statewindow.h"
#include "ui_statewindow.h"
#include <QLineEdit>

StateWindow::StateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateWindow)
{
    ui->setupUi(this);
    this->setGeometry(10, 480, 400, 400);
    _value_x = 0;
    _value_y = 0;
    _delta_x = 0.1;
    _delta_t = 300;
    ui->delta_x_line_edit->setText(QString::number(_delta_x));
    ui->delta_t_line_edit->setText(QString::number(_delta_t));
    this->_update_current_sin_lable();

}

StateWindow     &StateWindow::getInstance() {
    static StateWindow state_win(nullptr);

    return state_win;
}

StateWindow::~StateWindow()
{
    delete ui;
}

float   StateWindow::get_delta_x() const {
    return this->_delta_x;
}

int     StateWindow::get_delta_t() const {
    return this->_delta_t;
}


void    StateWindow::_update_current_sin_lable() {
    QString string;

    string += "sin(" + QString::number(_value_x) + ") = " + QString::number(_value_y);
    ui->current_sin_lable->setText(string);
}

//  Public slots:

void    StateWindow::slot_new_param(float x, float y) {
    _value_x = x;
    _value_y = y;
    this->_update_current_sin_lable();
}

void    StateWindow::slot_fresh() {
    _value_x = 0;
    _value_y = 0;
    this->_update_current_sin_lable();
}


void StateWindow::on_delta_x_line_edit_editingFinished()
{
    this->_delta_x = ui->delta_x_line_edit->text().toFloat();
    emit signal_change_dx(_delta_x);
}

void StateWindow::on_delta_t_line_edit_editingFinished()
{
    this->_delta_t = ui->delta_t_line_edit->text().toInt();
    emit signal_change_dt(_delta_t);
}
