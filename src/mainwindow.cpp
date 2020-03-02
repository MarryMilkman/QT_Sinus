#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _setting("last_session.conf", QSettings::IniFormat)
    , _state_win(StateWindow::getInstance())
    , _coord_win(CoordWindow::getInstance())
{
    this->_value_x = _setting.value("value_x", -1).toFloat();
    this->_delta_t = _state_win.get_delta_t();
    this->_delta_x = _state_win.get_delta_x();

    ui->setupUi(this);
      // CoordWindow connection
    QObject::connect(this, &MainWindow::signal_pass_param,
                     &_coord_win, &CoordWindow::slot_new_param);
    QObject::connect(this, &MainWindow::signal_fresh_wins,
                     &_coord_win, &CoordWindow::slot_fresh);
      // StateWindow connection
    QObject::connect(this, &MainWindow::signal_pass_param,
                     &_state_win, &StateWindow::slot_new_param);
    QObject::connect(this, &MainWindow::signal_fresh_wins,
                     &_state_win, &StateWindow::slot_fresh);
    QObject::connect(&_state_win, &StateWindow::signal_change_dt,
                     this, &MainWindow::slot_changed_delta_t);
    QObject::connect(&_state_win, &StateWindow::signal_change_dx,
                     this, &MainWindow::slot_changed_delta_x);

      // thread connection:
    this->_sinus_worker.moveToThread(&this->_sinus_worker_thread);
          // connect signal of MainWindow to slots of SinusWorker
    QObject::connect(this, &MainWindow::signal_resume,
                     &this->_sinus_worker, &SinusWorker::slot_resume);
    QObject::connect(this, SIGNAL(signal_stop()),
                     &this->_sinus_worker, SLOT(slot_stop()));
    QObject::connect(this, &MainWindow::signal_pause,
                     &this->_sinus_worker, &SinusWorker::slot_pause);
    QObject::connect(this, &MainWindow::signal_param_dx,
                     &this->_sinus_worker, &SinusWorker::slot_change_dx);
    QObject::connect(this, &MainWindow::signal_param_dt,
                     &this->_sinus_worker, &SinusWorker::slot_change_dt);
    QObject::connect(this, &MainWindow::signal_start_calculate,
                     &this->_sinus_worker, &SinusWorker::slot_start_calculate);
    QObject::connect(this, &MainWindow::signal_once_calculate,
                     &this->_sinus_worker, &SinusWorker::slot_once_calculate);
          // connect signal (only one) of SinusWorker to slot MW
    QObject::connect(&this->_sinus_worker, &SinusWorker::signal_calc_values,
                     this, &MainWindow::slot_param_from_thread);
    this->_sinus_worker_thread.start();
    emit signal_once_calculate(this->_value_x);
    emit signal_start_calculate(this->_value_x, this->_delta_x, this->_delta_t);

}

MainWindow::~MainWindow()
{
    this->_state_win.close();
    this->_coord_win.close();
    this->_sinus_worker_thread.quit();
    this->_sinus_worker_thread.wait();
    delete ui;
    _setting.setValue("value_x", this->_value_x);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->_state_win.close();
    this->_coord_win.close();
    event->accept();
}

// Public slots:

void MainWindow::slot_param_from_thread(float x, float y) {
    this->_value_x = x;
    this->_value_y = y;
    this->_time += this->_delta_t;
    emit this->signal_pass_param(x, y);
}


void MainWindow::slot_changed_delta_x(float new_dx) {
    this->_delta_x = new_dx;
    emit this->signal_param_dx(new_dx);
}

void MainWindow::slot_changed_delta_t(int new_dt) {
    this->_delta_t = new_dt;
    emit this->signal_param_dt(new_dt);
}


// Private slots:

void MainWindow::on_coordButton_clicked()
{
    if (_coord_win.isHidden())
        _coord_win.show();
    else
        _coord_win.hide();
}

void MainWindow::on_stateButton_clicked()
{
    if (_state_win.isHidden())
        _state_win.show();
    else
        _state_win.hide();
}

void MainWindow::on_resume_button_clicked()
{
    emit this->signal_resume();
}




void MainWindow::on_pause_button_clicked()
{
    emit this->signal_pause();
}



void MainWindow::on_stop_button_clicked()
{
    emit this->signal_stop();
    emit this->signal_fresh_wins();
}
