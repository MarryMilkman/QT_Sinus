#include "statewindow.h"
#include "ui_statewindow.h"
#include <QLineEdit>

#include "QrCode.hpp"
#include <QJsonObject>
#include <QJsonDocument>


StateWindow::StateWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StateWindow)
    , _qr_painter(this)
{
    ui->setupUi(this);
    this->setGeometry(10, 480, 400, 500);

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

void StateWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QJsonObject         js_data = {
        {"x", this->_value_x},
        {"y", this->_value_y}
    };
    QJsonDocument       js_doc(js_data);
    QPainter            painter(this);
    qrcodegen::QrCode   qr = qrcodegen::QrCode::encodeText(js_doc.toJson(QJsonDocument::Compact)
                                                           , qrcodegen::QrCode::Ecc::MEDIUM);
    int                 size_qr = qr.getSize();
    int                 indent_x = this->width() / 2 - size_qr * 3;

    painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::FlatCap));
    for (int x = 0; x < size_qr; x++) {
        int indent_y = 120;
        for (int y = 0; y < size_qr; y++) {
            if (qr.getModule(x, y))
                painter.drawPoint(x + indent_x, y + indent_y);
            indent_y += 5;
        }
        indent_x += 5;
    }
}

//  Public slots:

void    StateWindow::slot_new_param(float x, float y) {
    _value_x = x;
    _value_y = y;
    repaint();
    this->_update_current_sin_lable();
}

void    StateWindow::slot_fresh() {
    _value_x = 0;
    _value_y = 0;
    repaint();
    this->_update_current_sin_lable();
}


void StateWindow::on_delta_x_line_edit_editingFinished()
{
    this->_delta_x = ui->delta_x_line_edit->text().toFloat();
    if (this->_delta_x == 0) {
        this->_delta_t = 0;
        ui->delta_x_line_edit->setText(QString::number(_delta_x));
    }
    emit signal_change_dx(_delta_x);
}

void StateWindow::on_delta_t_line_edit_editingFinished()
{
    this->_delta_t = ui->delta_t_line_edit->text().toInt();
    if (this->_delta_t < 10) {
        this->_delta_t = 10;
        ui->delta_t_line_edit->setText(QString::number(_delta_t));
    }
    emit signal_change_dt(_delta_t);
}
