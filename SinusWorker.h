#ifndef SINUSWORKER_H
#define SINUSWORKER_H

#include "lib.h"

#include <QObject>

class SinusWorker : public QObject
{
    Q_OBJECT

public:
    SinusWorker(float value_x = 0, float delta_x = 0.2, int delta_t = 500);
//    SinusWorker();
    virtual ~SinusWorker();


private:
    float   _value_x;
    float   _value_y;

    float   _delta_x;
    int     _delta_t;
    bool    _is_pause;

    void    _calculate();

//  MARK: - slots and signals
public slots:
    void    slot_resume();
    void    slot_stop();
    void    slot_pause();
    void    slot_change_dx(float dx);
    void    slot_change_dt(int dt);

    void    slot_start_calculate(float value_x, float delta_x, int delta_t);

signals:
    void    signal_calc_values(float x, float y);
};

#endif // SINUSWORKER_H
