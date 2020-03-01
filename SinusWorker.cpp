#include "SinusWorker.h"
#include <cmath>

SinusWorker::SinusWorker(float value_x, float delta_x, int delta_t)
    : _value_x(value_x)
    , _value_y(0)
    , _delta_x(delta_x)
    , _delta_t(delta_t)
    , _is_pause(true)
{
}

//SinusWorker::SinusWorker()
//    : _value_x(0)
//    , _value_y(0)
//    , _delta_x(1)
//    , _delta_t(1000)
//    , _is_pause(true)
//{
//
//}

SinusWorker::~SinusWorker() {

}


// Public slots:
void    SinusWorker::_calculate() {
    if (_is_pause == false) {
        _value_y = std::sin(_value_x);
        emit signal_calc_values(_value_x, _value_y);
        _value_x += _delta_x;
    }
    QTimer::singleShot(_delta_t, this, &SinusWorker::_calculate);
}

void    SinusWorker::slot_start_calculate(float value_x, float delta_x, int delta_t) {
    this->_value_x = value_x;
    this->_delta_x = delta_x;
    this->_delta_t = delta_t;
    this->_calculate();
}

void    SinusWorker::slot_resume() {
    _is_pause = false;
}

void    SinusWorker::slot_stop() {
    _is_pause = true;
    _value_x = 0;
    _value_y = 0;
}

void    SinusWorker::slot_pause() {
    _is_pause = true;
}

void    SinusWorker::slot_change_dt(int dt) {
    _delta_t = dt;
}

void    SinusWorker::slot_change_dx(float dx) {
    _delta_x = dx;
}
