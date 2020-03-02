#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib.h"

#include <QMainWindow>
#include <QSettings>

#include "coordwindow.h"
#include "statewindow.h"
#include "SinusWorker.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow      *ui;

    QSettings           _setting;

    float               _value_x;
    float               _value_y;
    unsigned int        _time;

    float               _delta_x;
    int                 _delta_t;

    StateWindow         &_state_win;
    CoordWindow         &_coord_win;

    QThread             _sinus_worker_thread;
    SinusWorker         _sinus_worker;

    void                closeEvent(QCloseEvent *event) override;

//  MARK: - slots and signals
public slots:

    // for thread
    void    slot_param_from_thread(float x, float y);

    // for windows
    void    slot_changed_delta_x(float new_dx);
    void    slot_changed_delta_t(int new_dt);


private slots:

    // for button (hide/show)
    void    on_coordButton_clicked();
    void    on_stateButton_clicked();

    void    on_resume_button_clicked();

    void    on_pause_button_clicked();

    void    on_stop_button_clicked();

signals:

    // for thread
    void    signal_resume();
    void    signal_stop();
    void    signal_pause();
    void    signal_param_dx(float dx);
    void    signal_param_dt(int dt);
    void    signal_once_calculate(float value_x);
    void    signal_start_calculate(float value_x, float delta_x, int delta_t);


    // for windows
    void    signal_pass_param(float x, float y);
    void    signal_fresh_wins();

};
#endif // MAINWINDOW_H
