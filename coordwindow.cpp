#include "coordwindow.h"
#include "ui_coordwindow.h"


CoordWindow::CoordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoordWindow)
{
    ui->setupUi(this);
    this->setGeometry(10, 40, 400, 400);

    this->_scene = new QGraphicsScene(0, 0, 200, 200, this->ui->graphicsView);

    qDebug() << this->_scene->width();
    qDebug() << this->_scene->height();
    float   h = this->_scene->height();
    float   w = this->_scene->width();

    this->_circle = new QGraphicsEllipseItem(w / 2 - 15, h / 2 - 15, 30, 30);
    this->_line_x = new QGraphicsLineItem(0 - w, h / 2, w + w, h / 2);
    this->_line_y = new QGraphicsLineItem(w / 2, 0 - h, w / 2, h + h);


    ui->graphicsView->setScene(this->_scene);
    this->_scene->addItem(this->_circle);
    this->_scene->addItem(this->_line_x);
    this->_scene->addItem(this->_line_y);
//    this->_scene->addLine(0, 0, 100, 100, this->ui->graphicsView);
}

CoordWindow     &CoordWindow::getInstance() {
    static CoordWindow coord_win(nullptr);

    return coord_win;
}

CoordWindow::~CoordWindow()
{
    delete ui;
}

void    CoordWindow::_draw() {
    ui->_lable_value_x->setText(QString::number(this->_value_x));
    ui->_lable_value_y->setText(QString::number(this->_value_y));

    _circle->setX(this->_value_x * 15);
    _circle->setY(-(this->_value_y * 15));
}

//  Public slots:

void    CoordWindow::slot_new_param(float x, float y) {
    _value_x = x;
    _value_y = y;
    this->_draw();
}

void    CoordWindow::slot_fresh() {

}
